#include "../Libraries/Definitions.h"
#include "../Libraries/Functions.h"
#include <iostream>

// Plotting options

TString saveDirectory;
bool saveImage;
TString saveExtension = "pdf";

// Classes

class Plot {

    TString plotValue, plotTitle;
    TCut plotWeight;
    float plotXLow, plotXHigh;
    int plotXBins;
    //vector<int> plotColors = vector<int> {kRed, kBlue, kMagenta, kGray, kOrange, kCyan, kGreen+3, kRed-7, kMagenta+3, kCyan-2};
    vector<int> plotColors = vector<int> {kRed, kBlue, kOrange, kCyan, kGreen+3, kRed-7, kMagenta+3, kCyan-2};
    bool drawLegend = true, drawLog = false, normalize = false;

public:

    Plot(TString value, TCut weight, TString name, int bins, float low, float high) {
        plotValue = value;
        plotWeight = weight;
        plotTitle = name;
        plotXBins = bins;
        plotXLow = low;
        plotXHigh = high;
    }

    void SetLegend(bool setting) {
        drawLegend = setting;
    }

    void SetLog(bool setting) {
        drawLog = setting;
    }

    void SetNormalize(bool setting) {
        normalize = setting;
    }

    bool DrawLegend() {
        return drawLegend;
    }

    TString PlotValue() {
        return plotValue;
    }

    TCut PlotWeight() {
        return plotWeight;
    }

    TString PlotTitle() {
        return plotTitle;
    }

    vector<int> PlotColors() {
        return plotColors;
    }

    int PlotColors(int index) {
        return plotColors[index];
    }

    int XBins() {
        return plotXBins;
    }

    int XLow() {
        return plotXLow;
    }

    int XHigh() {
        return plotXHigh;
    }

    bool IsLog() {
        return drawLog;
    }

    bool Normalize() {
        return normalize;
    }
};

vector<Plot> plots;
TString treeName = "outputTree";
typedef vector<vector<double>> dataTable;
typedef pair<dataTable, dataTable> dataTables;

// Helper Functions

string SigFig(float input, int precision) {
    ostringstream out;
    out << setprecision(precision) << input;
    return out.str();
}

void PerformOverflowBinning(TH1F* hist) {
    int nBins = hist->GetSize()-2;
    hist->SetBinContent(nBins,hist->GetBinContent(nBins)+hist->GetBinContent(nBins+1));
    hist->SetBinContent(nBins+1,0);
    hist->SetBinContent(1,hist->GetBinContent(0)+hist->GetBinContent(1));
    hist->SetBinContent(0,0);
}

//void Mkdir(TString saveDirectory) {
    //Placeholder
//}

// Plots

void SetTree(TString name) {
    treeName = name;
}

void SetSaveExtension(TString extension) {
    saveExtension = extension;
}

void AddPlot(TString value, TCut weight, TString name, int bins, float low, float high, bool isLog=false, bool normalize=false) {
    Plot newPlot(value, weight, name, bins, low, high);
    newPlot.SetLog(isLog);
    newPlot.SetNormalize(normalize);
    plots.push_back(newPlot);
}

int NPlots() {
    return plots.size();
}

void ResetPlots() {
    plots.clear();
}

TString PlotTitle(int nPlot) {
    return plots[nPlot].PlotTitle();
}

// For each plot, stack all groups - FTTX
dataTables Plot(bool stacked = true) {

    dataTable yields = {};
    dataTable errors = {};

    //cout << "Creating histogram stacks." << endl;
    
    vector<THStack*> stacks;
    for (int nPlot=0; nPlot<NPlots(); nPlot++) {
        THStack* stack = new THStack(TString("stack"+to_string(nPlot)), PlotTitle(nPlot));
        stacks.push_back(stack);
    }

    //cout << "Filling histogram stacks." << endl;

    int dataGroup = -1;

    for (int nGroup=0; nGroup<NGroups(); nGroup++) {

        if (IsData(nGroup)) {
            dataGroup = nGroup;
            //std::cout<<"Data group"<<std::endl;
            continue;
        }

        TChain* groupChain = groups[nGroup].GetChain(treeName);

        vector<double> groupYields = {};
        vector<double> groupErrors = {};

        for (int nPlot=0; nPlot<NPlots(); nPlot++) {

            TString histName = TString("hist_" + to_string(nPlot) + "_" + to_string(nGroup));
            TString histTitle = groups[nGroup].Name();
            TH1F* newHist = new TH1F(histName, histTitle, plots[nPlot].XBins(), plots[nPlot].XLow(), plots[nPlot].XHigh());

            newHist->SetStats(0);
            if (stacked) {
                newHist->SetLineColor(kBlack);
                newHist->SetFillColor(plots[nPlot].PlotColors(nGroup));
                newHist->SetMarkerColor(plots[nPlot].PlotColors(nGroup));
            }
            else {
                newHist->SetLineColor(plots[nPlot].PlotColors(nGroup));
                newHist->SetMarkerColor(plots[nPlot].PlotColors(nGroup));
            }

            TCanvas *canvas = new TCanvas("canvas","",696,472);

            if (groups[nGroup].GetCustomWeight() == "")
                groupChain->Draw(plots[nPlot].PlotValue() + ">>" + histName, plots[nPlot].PlotWeight());
            else
                groupChain->Draw(plots[nPlot].PlotValue() + ">>" + histName, groups[nGroup].GetCustomWeight());
            delete canvas;

            PerformOverflowBinning(newHist);
            if (!newHist->GetSumw2N())
                newHist->Sumw2();
            if (plots[nPlot].Normalize()) {
                newHist->Scale(1.0 / newHist->Integral());
            }
            //Checkpoint
            newHist->SetMarkerStyle(7);
            stacks[nPlot]->Add(newHist);
            //Checkpoint
			double error = 0;
			double integral = newHist->IntegralAndError(1,newHist->GetSize(),error);
            groupYields.push_back(integral);
            groupErrors.push_back(error);
            //cout<<"\t"<<integral<<"+-"<<error;
            //cout<<"\t"<<newHist->Integral();

            if (saveExtension == "root") { 
                Mkdir(saveDirectory);
                TString imageName = plots[nPlot].PlotTitle()+"."+saveExtension;
                TFile f(saveDirectory+imageName, "new");
                newHist->Write("hist");
            }
        }

        yields.push_back(groupYields);
        errors.push_back(groupErrors);
    }

    //cout << "Drawing plots." << endl;

    for (int nPlot=0; nPlot<NPlots(); nPlot++) {

        TChain* dataChain;
        TH1F* dataHist;
        if (dataGroup > -1) {
            dataChain = groups[dataGroup].GetChain(treeName);
            dataHist = new TH1F("Data", "Data", plots[nPlot].XBins(), plots[nPlot].XLow(), plots[nPlot].XHigh());
            if (groups[dataGroup].GetCustomWeight() == "")
                dataChain->Draw(plots[nPlot].PlotValue()+">>Data", plots[nPlot].PlotWeight());
            else
                dataChain->Draw(plots[nPlot].PlotValue()+">>Data", groups[dataGroup].GetCustomWeight());
        }

        TCanvas *canvas = new TCanvas("canvas","",696,472);
        TPad* mainpad = new TPad("mainpad","mainpad",0.0,0.2,1.0,0.95);
        TPad* ratiopad = new TPad("ratiopad","ratiopad",0.0,0.05,1.0,0.2);
        canvas->cd();
        mainpad->Draw();
        ratiopad->Draw();
        mainpad->cd();

        if (stacked)
            stacks[nPlot]->Draw("hist e1");
        else
            stacks[nPlot]->Draw("hist nostack e1");
        if (dataGroup > -1) {
            dataHist->Draw("same e1");
			if (dataHist->GetMaximum() > stacks[nPlot]->GetMaximum())
				stacks[nPlot]->SetMaximum(dataHist->GetMaximum());
            //stacks[nPlot]->SetMaximum(1.3*(stacks[nPlot]->GetMaximum(), dataHist->GetMaximum()));
        }
        mainpad->BuildLegend();
        //else
            //stacks[nPlot]->SetMaximum(1.3*stacks[nPlot]->GetMaximum());

        if (plots[nPlot].IsLog())
            gPad->SetLogy();
		stacks[nPlot]->GetHistogram()->GetXaxis()->SetTitle(plots[nPlot].PlotValue());


        ratiopad->cd();
        TList *histos = stacks[nPlot]->GetHists();
        TIter next(histos);
        TH1F* hist = (TH1F*)next();
        TH1F* baseline = (TH1F*) hist->Clone("baseline");
        int nGroup = 0;
        while ((hist = (TH1F*)next())) {
            TH1F* hratio = (TH1F*) hist->Clone("hratio"); 
            hratio->SetStats(0);
            hratio->SetTitle("");
            hratio->GetYaxis()->SetLabelSize(0.2);
            hratio->Divide(baseline);
            hratio->SetMarkerStyle(7);
            hratio->SetLineColor(plots[nPlot].PlotColors(++nGroup));
            hratio->SetMarkerColor(plots[nPlot].PlotColors(nGroup));
            hratio->Draw("same e1");
            hratio->SetMinimum(0);
            hratio->SetMaximum(2);
            hratio->GetYaxis()->SetNdivisions(5);
        }

        TLine *line = new TLine(0.1, 0.5, 0.9, 0.5);
        line->SetNDC(kTRUE);
        line->SetLineWidth(1);
        line->SetLineStyle(2);
        line->SetLineColor(kGray);
        line->Draw();

        if (saveImage) {
            Mkdir(saveDirectory);
            TString imageName = plots[nPlot].PlotTitle()+"."+saveExtension;
            if (saveExtension != "root") { 
                //if (plots[nPlot].DrawLegend()) canvas->BuildLegend();
                canvas->Resize();
                canvas->Print(saveDirectory+imageName);
                canvas->Clear();
            }
            //else {
                //TFile f(saveDirectory+imageName, "new");
                ////DOESN'T GET THE CORRECT HISTOGRAM -> JUST AN EMPTY ONE FOR AXIS
                //TH1 *h1 = stacks[nPlot]->GetHistogram();
                //h1->Write("hist");
            //}
        }

        delete canvas;
        TList* hists = stacks[nPlot]->GetHists();
        hists->Delete();
        delete stacks[nPlot];
    }

    ResetPlots();
    ResetGroups();

    return std::make_pair(yields, errors);
}
























// Other plotting functions

/* Sum of other plotting functions - separateGroups and separatePlots are options to draw a separate image for each sample group or plot.
// stackGroups and stackPlots are options to stack stuff on top of each other (rather than doing a line compare) when the previous options are false.
// TTXX - make separate image for each group/plot pair
// FTFX - for each plot criteria, make a line comparison of the groups 
// FTTX - for each plot criteria, make a stacked plot of all the groups together
// TFXF - for each group, make a line comparison of all plot criteria 
// TFXT - for each group, make a stacked plot of all plot criteria (e.g. SRZ+ee stacked on SRZ+mm)
// FFFF - line compare of each group/plot pair (e.g. ee/mm of two samples)
// other FFXX - never do this
// Consider calling CombineGroups() before using XFXX functions.*/

/*void CompletePlotter(bool separateGroups=false, bool separatePlots=true, bool stackGroups=true, bool stackPlots=false) {

    cout << "Creating histogram stacks." << endl;
    
    vector<THStack*> stacks;
    for (int nPlot=0; nPlot<NPlots(); nPlot++) {
        THStack* stack = new THStack(TString("stack"+to_string(nPlot)), PlotTitle(nPlot));
        stacks.push_back(stack);
    }

    cout << "Filling histogram stacks." << endl;

    int dataGroup = -1;

    for (int nGroup=0; nGroup<NGroups(); nGroup++) {

        if (IsData(nGroup)) {
            dataGroup = nGroup;
            continue;
        }

        TChain* groupChain = groups[nGroup].GetChain(treeName);

        for (int nPlot=0; nPlot<NPlots(); nPlot++) {

            TString histName = TString("hist_" + to_string(nPlot) + "_" + to_string(nGroup));
            TString histTitle = groups[nGroup].Name();
            TH1F* newHist = new TH1F(histName, histTitle, plots[nPlot].XBins(), plots[nPlot].XLow(), plots[nPlot].XHigh());

            newHist->SetStats(0);
            newHist->SetLineColor(kBlack);
            newHist->SetFillColor(plots[nPlot].PlotColors(nGroup));

            TCanvas *canvas = new TCanvas("canvas","",696,472);
            groupChain->Draw(plots[nPlot].PlotValue() + ">>" + histName, plots[nPlot].PlotWeight());
            delete canvas;

            PerformOverflowBinning(newHist);
            stacks[nPlot]->Add(newHist);
        }
    }

    cout << "Drawing plots." << endl;

    for (int nPlot=0; nPlot<NPlots(); nPlot++) {

        TChain* dataChain;
        TH1F* dataHist;
        if (dataGroup > -1) {
            dataChain = groups[dataGroup].GetChain(treeName);
            dataHist = new TH1F("Data", "Data", plots[nPlot].XBins(), plots[nPlot].XLow(), plots[nPlot].XHigh());
            if (groups[dataGroup].GetCustomWeight() == "")
                dataChain->Draw(plots[nPlot].PlotValue()+">>Data", plots[nPlot].PlotWeight());
            else
                dataChain->Draw(plots[nPlot].PlotValue()+">>Data", groups[dataGroup].GetCustomWeight());
        }

        TCanvas *canvas = new TCanvas("canvas","",696,472);

        stacks[nPlot]->Draw("hist");
        if (dataGroup > -1) dataHist->Draw("same e1");

        stacks[nPlot]->GetHistogram()->GetXaxis()->SetTitle(plots[nPlot].PlotValue());

        if (saveImage) {
            TString imageName = plots[nPlot].PlotTitle() + "." + saveExtension;
            if (plots[nPlot].DrawLegend()) canvas->BuildLegend();
            canvas->Resize();
            Mkdir(saveDirectory);
            canvas->Print(saveDirectory+imageName);
            canvas->Clear();
        }

        delete canvas;
        delete stacks[nPlot];
    }

    ResetPlots();
    ResetGroups();
}*/

// Draw all plots on one canvas (line compare), with groups combined - TFXF using CombineGroups()
/*void ComparePlots(TString plotName, bool plotStacked=false) {

    cout << "Creating histogram stack." << endl;
    
    THStack* stack = new THStack("stack", plotName);

    cout << "Filling histogram stack." << endl;

    TChain* totalChain = GetTotalChain();

    for (int nPlot=0; nPlot<NPlots(); nPlot++) {

        TString histName = TString("hist_" + to_string(nPlot));
        TString histTitle = plots[nPlot].PlotTitle();
        TH1F* newHist = new TH1F(histName, histTitle, plots[nPlot].XBins(), plots[nPlot].XLow(), plots[nPlot].XHigh());

        newHist->SetStats(0);

        if (plotStacked) {
            newHist->SetLineColor(kBlack);
            newHist->SetFillColor(plots[nPlot].PlotColors(nPlot));
        }
        else
            newHist->SetLineColor(plots[nPlot].PlotColors(nPlot));

        TCanvas *canvas = new TCanvas("canvas","",696,472);
        totalChain->Draw(plots[nPlot].PlotValue() + ">>" + histName, plots[nPlot].PlotWeight());
        delete canvas;

        PerformOverflowBinning(newHist);
        stack->Add(newHist);
    }

    cout << "Drawing plots." << endl;

    TCanvas *canvas = new TCanvas("canvas","",696,472);

    if (plotStacked)
        stack->Draw("hist");
    else
        stack->Draw("hist nostack");

    stack->GetHistogram()->GetXaxis()->SetTitle(plots[0].PlotValue());

    if (saveImage) {
        TString imageName = plotName + "." + saveExtension;
        if (plots[0].DrawLegend()) canvas->BuildLegend();
        canvas->Resize();
        Mkdir(saveDirectory);
        canvas->Print(saveDirectory+imageName);
        canvas->Clear();
    }

    delete canvas;
    delete stack;

    ResetPlots();
    ResetGroups();
}*/

// Draw all plots on one canvas (stacked), with groups combined - TFXT using CombineGroups()
/*void StackPlots(TString plotName) {
    ComparePlots(plotName, true);
}*/

// For each plot, line compare groups - FTFX
/*void CompareGroups(TString plotName, bool plotStacked=false) {

    cout << "Creating histogram stack." << endl;
    
    THStack* stack = new THStack("stack", plotName);

    cout << "Filling histogram stack." << endl;

    int dataGroup = -1;

    for (int nGroup=0; nGroup<NGroups(); nGroup++) {

        if (IsData(nGroup)) {
            dataGroup = nGroup;
            continue;
        }

        TChain* groupChain = groups[nGroup].GetChain(treeName);

        for (int nPlot=0; nPlot<NPlots(); nPlot++) {

            TString histName = TString("hist_" + to_string(nPlot));
            TString histTitle = PlotTitle(nPlot);
            TH1F* newHist = new TH1F(histName, histTitle, plots[nPlot].XBins(), plots[nPlot].XLow(), plots[nPlot].XHigh());

            newHist->SetStats(0);

            if (plotStacked) {
                newHist->SetLineColor(kBlack);
                newHist->SetFillColor(plots[nPlot].PlotColors(nPlot));
            }
            else
                newHist->SetLineColor(plots[nPlot].PlotColors(nPlot));

            TCanvas *canvas = new TCanvas("canvas","",696,472);
            groupChain->Draw(plots[nPlot].PlotValue() + ">>" + histName, plots[nPlot].PlotWeight());
            delete canvas;

            PerformOverflowBinning(newHist);
            stack->Add(newHist);
        }
    }

    for (int nPlot=0; nPlot<NPlots(); nPlot++) {

        cout << "Drawing plots." << endl;

        TCanvas *canvas = new TCanvas("canvas","",696,472);

        if (plotStacked)
            stack->Draw("hist");
        else
            stack->Draw("hist nostack");

        stack->GetHistogram()->GetXaxis()->SetTitle(plots[0].PlotValue());

        if (saveImage) {
            TString imageName = plotName + "." + saveExtension;
            if (plots[nPlot].DrawLegend()) canvas->BuildLegend();
            canvas->Resize();
            Mkdir(saveDirectory);
            canvas->Print(saveDirectory+imageName);
            canvas->Clear();
        }

        delete canvas;
        delete stack;
    }

    ResetPlots();
    ResetGroups();
}*/
