#include "../../Libraries/Definitions.h"
#include "../../Libraries/Functions.h"
#include <iostream>

TString saveDirectory;
bool saveImage;
TString saveExtension = "pdf";

vector<Plot*> plots;
TString treeName = "outputTree";
typedef vector<vector<double>> dataTable;
typedef pair<dataTable, dataTable> dataTables;

// Helper Functions

void PerformOverflowBinning(TH1F* hist) {
    int nBins = hist->GetSize()-2;
    hist->SetBinContent(nBins,hist->GetBinContent(nBins)+hist->GetBinContent(nBins+1));
    hist->SetBinContent(nBins+1,0);
    hist->SetBinContent(1,hist->GetBinContent(0)+hist->GetBinContent(1));
    hist->SetBinContent(0,0);
}

// Plotting Options

void SetTree(TString name) {
    treeName = name;
}

void SetSaveExtension(TString extension) {
    saveExtension = extension;
}

Plot* AddPlot(TString value, TCut weight, TString name="", int bins=20, float low=0, float high=1000, bool isLog=false, bool normalize=false) {
    if (!name) name=value;
    Plot* newPlot = new Plot(value, weight, name, bins, low, high);
    newPlot->SetLog(isLog);
    newPlot->SetNormalize(normalize);
    plots.push_back(newPlot);
    return newPlot;
}

int NPlots() {
    return plots.size();
}

void ResetPlots() {
    plots.clear();
}

TString PlotTitle(int nPlot) {
    return plots[nPlot]->PlotTitle();
}

// Plotting Function

dataTables MakePlot(bool stacked = true) {

    // Yield tables to be filled and returned
    dataTable yields = {};
    dataTable errors = {};
    
    vector<THStack*> stacks, dataStacks;
    for (int nPlot=0; nPlot<NPlots(); nPlot++) {
        THStack* stack = new THStack(TString("stack"+to_string(nPlot)), PlotTitle(nPlot));
        stacks.push_back(stack);
        THStack* dataStack = new THStack(TString("dataStack"+to_string(nPlot)), PlotTitle(nPlot));
        dataStacks.push_back(dataStack);
    }

    // Create histogram for each group in each plot region
    for (int nGroup=0; nGroup<NGroups(); nGroup++) {

        TChain* groupChain = groups[nGroup].GetChain(treeName);

        vector<double> groupYields = {};
        vector<double> groupErrors = {};

        for (int nPlot=0; nPlot<NPlots(); nPlot++) {

            TString histName = TString("hist_" + to_string(nPlot) + "_" + to_string(nGroup));
            TString histTitle = groups[nGroup].Name();
            TH1F* newHist = new TH1F(histName, histTitle, plots[nPlot]->XBins(), plots[nPlot]->XLow(), plots[nPlot]->XHigh());

            newHist->SetStats(0);

            if (!IsData(nGroup)) {
                if (stacked) {
                    newHist->SetLineColor(kBlack);
                    newHist->SetFillColor(plots[nPlot]->PlotColors(nGroup));
                    newHist->SetMarkerColor(plots[nPlot]->PlotColors(nGroup));
                }
                else {
                    newHist->SetLineColor(plots[nPlot]->PlotColors(nGroup));
                    newHist->SetMarkerColor(plots[nPlot]->PlotColors(nGroup));
                }
            }

            TCanvas *canvas = new TCanvas("canvas","",696,472);
            if (groups[nGroup].GetCustomWeight() == "")
                groupChain->Draw(plots[nPlot]->PlotValue() + ">>" + histName, plots[nPlot]->PlotWeight());
            else
                groupChain->Draw(plots[nPlot]->PlotValue() + ">>" + histName, groups[nGroup].GetCustomWeight());
            delete canvas;

            //Checkpoint - print out gaussian fit parameters
            //newHist->Fit("gaus");

            PerformOverflowBinning(newHist);
            if (!newHist->GetSumw2N())
                newHist->Sumw2();
            if (plots[nPlot]->Normalize()) {
                newHist->Scale(1.0 / newHist->Integral());
            }

            // Add histogram to either MC stack or data stack
            if (!IsData(nGroup)) {
                newHist->SetMarkerStyle(7);
                stacks[nPlot]->Add(newHist);
            }
            else
                dataStacks[nPlot]->Add(newHist);

			double error = 0;
			double integral = newHist->IntegralAndError(1,newHist->GetSize(),error);
            groupYields.push_back(integral);
            groupErrors.push_back(error);

            // Save each individual histogram
            if (saveExtension == "root") { 
                Mkdir(saveDirectory);
                TString imageName = plots[nPlot]->PlotTitle()+"_"+histTitle+"."+saveExtension;
                TFile f(saveDirectory+imageName, "new");
                newHist->Write("hist");
            }
        }

        yields.push_back(groupYields);
        errors.push_back(groupErrors);
    }

    for (int nPlot=0; nPlot<NPlots(); nPlot++) {

        TCanvas *canvas = new TCanvas("canvas","",696,472);
        TPad* mainpad = new TPad("mainpad","mainpad",0.0,0.2,1.0,0.95);
        TPad* ratiopad = new TPad("ratiopad","ratiopad",0.0,0.05,1.0,0.2);
        canvas->cd();
        //Checkpoint - turn on ratio box
        //mainpad->Draw();
        //ratiopad->Draw();
        //mainpad->cd();

        if (stacked)
            stacks[nPlot]->Draw("hist");
        else
            stacks[nPlot]->Draw("hist nostack e1");

        dataStacks[nPlot]->Draw("hist nostack same e1 ][");

        if (dataStacks[nPlot]->GetMaximum() > stacks[nPlot]->GetMaximum())
            stacks[nPlot]->SetMaximum(dataStacks[nPlot]->GetMaximum());
        if (dataStacks[nPlot]->GetMaximum() < stacks[nPlot]->GetMaximum())
            dataStacks[nPlot]->SetMaximum(stacks[nPlot]->GetMaximum());

        //Auto legend
        //Checkpoint - turn on ratio box
        //mainpad->BuildLegend(0.6, 0.85-0.05*NGroups(), 0.9, 0.9);
        canvas->BuildLegend(0.6, 0.85-0.05*NGroups(), 0.9, 0.9);

        //Manual legend
        //TLegend* leg = new TLegend(0.6, 0.85-.05*NGroups(), 0.9, 0.9);
        //for (int i=0;i<NGroups();i++) {
            ////leg->AddEntry(groups[i].Name(), TString(groups[i].Name()+" - "+SigFig(yields[i][0],2))+"+-"+SigFig(errors[i][0],2), "f");
            //std::cout<<groups[i].Name()<<std::endl;
            //std::cout<<groups[i].Name()<<std::endl;
            //leg->AddEntry(groups[i].Name(), TString(groups[i].Name()), "f");
            ////leg->AddEntry("test", "test", "f");
        //}
        //leg->Draw();

        if (plots[nPlot]->IsLog())
            gPad->SetLogy();

		stacks[nPlot]->GetHistogram()->GetXaxis()->SetTitle(plots[nPlot]->PlotValue());

        //Checkpoint - turn on ratio box
        //ratiopad->cd();
        //TList *histos = stacks[nPlot]->GetHists();
        //TIter next(histos);
        //TH1F* hist = (TH1F*)next();
        //TH1F* baseline = (TH1F*) hist->Clone("baseline");
        //int nGroup = 0;
        //while ((hist = (TH1F*)next())) {
            //TH1F* hratio = (TH1F*) hist->Clone("hratio"); 
            //hratio->SetStats(0);
            //hratio->SetTitle("");
            //hratio->GetYaxis()->SetLabelSize(0.2);
            //hratio->Divide(baseline);
            //hratio->SetMarkerStyle(7);
            //hratio->SetLineColor(plots[nPlot]->PlotColors(++nGroup));
            //hratio->SetMarkerColor(plots[nPlot]->PlotColors(nGroup));
            //hratio->Draw("same e1");
            //hratio->SetMinimum(0);
            //hratio->SetMaximum(2);
            //hratio->GetYaxis()->SetNdivisions(5);
        //}

        //TLine *line = new TLine(0.1, 0.5, 0.9, 0.5);
        //line->SetNDC(kTRUE);
        //line->SetLineWidth(1);
        //line->SetLineStyle(2);
        //line->SetLineColor(kGray);
        //line->Draw();

        if (saveImage) {
            Mkdir(saveDirectory);
            TString imageName = plots[nPlot]->PlotTitle()+"."+saveExtension;
            if (saveExtension != "root") { 
                //if (plots[nPlot]->DrawLegend()) canvas->BuildLegend();
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
        if (hists) hists->Delete();
        delete stacks[nPlot];
        TList* dataHists = dataStacks[nPlot]->GetHists();
        if (dataHists) dataHists->Delete();
        delete dataStacks[nPlot];
    }

    ResetPlots();
    ResetGroups();

    return std::make_pair(yields, errors);
}

void MakePlotAndPrintYields(bool stacked = true) {

    dataTables yieldsAndErrors = MakePlot(stacked);
    auto yields = yieldsAndErrors.first;
    auto errors = yieldsAndErrors.second;

    float sum = 0;
    float sumErr = 0;

    for (int i=0; i<yields.size()-1; i++) {
        //cout << groupNames[i] << ": " << yields[i][0] << endl;
        cout << groups[i].Name() << ": " << SigFig(yields[i][0],2) << " \\pm " << SigFig(errors[i][0],2) << endl;
        sum += yields[i][0];
        sumErr += pow(errors[i][0],2);
    }
    //cout<<"Total MC: "<<sum<<endl;
    cout<<"Total MC: "<<SigFig(sum,2)<<" \\pm "<<SigFig(sqrt(sumErr),2)<<endl;

    cout << "Data: " << SigFig(yields[yields.size()-1][0],2) << endl;
}
