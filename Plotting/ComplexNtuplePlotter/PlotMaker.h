#include <TFile.h>
#include <TH1.h>
#include <TTree.h>
#include <THStack.h>
#include <algorithm>

void Plot(string plotSaveName, vector<int> options);
void FillHistograms();
void GetBranches(TTree* tree);
void SetupSplitting();

//Variables for behind the scenes
vector<string> histIDs = {};
vector<float> xSections = {}, kFactors = {}, genEfficiencies = {};
vector<int> categories = {}, colors = {kRed, kOrange, kMagenta, kGreen, kGray, kBlue, kCyan, kGreen+3, kRed-7, kMagenta+3, kCyan-2};
vector<string> defaultCategoryNames = {};
vector<float> integrals(50,0), uncertainties(50,0); //Poor code

vector<TFile*> files;
vector<TTree*> trees;
vector<TH1F*> splitHists;
vector<TH1F*> channelhUn;
vector<TH2F*> splitScatterPlots;
TH1F* dataHist;
THStack* hs;

vector<int> cuts;
vector<float> fillValue, fillSecondValue;
vector<string> cutNames;
vector<TCut> simpleCuts;

TString histTitle, YTitle;

//Plotting options
int xBins, yBins;
float xRangeLow, xRangeHigh, yRangeLow, yRangeHigh;
bool setYHigh;
float luminosity;
int plotValueChoice, plotSecondValueChoice, eventTypeChoice, splitTypeChoice, plotTypeChoice;
vector<TString> plotValues, eventTypes, splitTypes, plotTypes;
bool blinded;
vector<int> splitChannel, splitCategories;
vector<string> splitCategoryNames;
vector<vector<float>> cutflowCategories;
bool performWeighting, pileupReweighting, muRescaling, useWeight1fb;
bool printCutflow, printFinalNumbers, plotLogY, plotData, plotRatioBox, drawLegend, drawStats, saveImage;
float ratioMin, ratioMax;
string saveDirectory;
string saveTag;
TString MCPath, dataPath, filetype, treeName;
bool setMaxEventsPerFile;
int maxEventsPerFile;
int trig_mm2;
string dataName;

//Reset variables
void reset() {
    for (int i=0; i<splitHists.size(); i++)
        delete splitHists[i];
    for (int i=0; i<channelhUn.size(); i++)
        delete channelhUn[i];
    for (int i=0; i<splitScatterPlots.size(); i++)
        delete splitScatterPlots[i];
    splitHists = {};
    channelhUn = {};
    splitScatterPlots = {};
    delete dataHist;
    delete hs;
    histIDs = {};
    files = {};
    trees = {};
    xSections = {};
    kFactors = {};
    genEfficiencies = {};
    categories = {};
    defaultCategoryNames = {};
    cutflowCategories = {};
    simpleCuts = {};
    splitCategories = {};
    splitCategoryNames = {};
    integrals = vector<float>(50,0);
    uncertainties = vector<float>(50,0);
}

//Helper functions
string sigFig(float input) {
    ostringstream out;
    out << setprecision(3) << input;
    return out.str();
}

void addSample(string sampleName, string category) {
    histIDs.push_back(sampleName);
    for (int i=0; i<defaultCategoryNames.size();i++) {
        if (defaultCategoryNames[i]==category) {
            categories.push_back(i);
            return;
        }
    }
    categories.push_back(defaultCategoryNames.size());
    defaultCategoryNames.push_back(category);
}

void addSample(int ID, string category) {
    addSample(to_string(ID), category);
}

void addCut (string name, string cut) {
    if (cuts.size() != 0) {
        cout << "ERROR: Mixing simple and looped cuts!" << endl;
        exit(0);
    }
    cutNames.push_back(name);
    simpleCuts.push_back(TCut(TString(cut)));
}

void addCut (string name, int cut) {
    if (simpleCuts.size() != 0) {
        cout << "ERROR: Mixing simple and looped cuts!" << endl;
        exit(0);
    }
    cutNames.push_back(name);
    cuts.push_back(cut);
}

void addCut (int cut) {
    addCut("", cut);
}

void addCut (string cut) {
    addCut("", cut);
}

//Histogram filling functions
void createHistograms() {

    //Title and Labels
    YTitle = "Weighted Events";
    if (!performWeighting)
        YTitle = "Events";
    TString MCDataType;
    if (plotData)
        MCDataType = "(MC and Data)";
    else
        MCDataType = "(MC)";
    if (plotTypeChoice==2)
        histTitle = plotValues[plotValueChoice] + " vs " + plotValues[plotSecondValueChoice] + " for " + eventTypes[eventTypeChoice] + " " +  MCDataType;
    else
        histTitle = plotValues[plotValueChoice] + " for " + eventTypes[eventTypeChoice] + " " +  MCDataType;
    if (splitTypeChoice!=0) //Excepting default split
        histTitle = histTitle + " - Split by " + splitTypes[splitTypeChoice];

    //Create stack
    hs = new THStack("hs",TString(histTitle));

    //Setup split categories
    SetupSplitting();

    for (int i=0; i<splitCategories.size(); i++) {
        TString histName = "split"+to_string(i);
        splitHists.push_back(new TH1F(histName, histTitle, xBins, xRangeLow, xRangeHigh));
        splitHists[i]->SetFillColor(colors[i]);
        splitHists[i]->SetLineColor(colors[i]);
        splitHists[i]->Sumw2(); //might fix issue with stat uncs - Emma
        histName = histName+"_scatter";
        splitScatterPlots.push_back(new TH2F(histName, histTitle, xBins, xRangeLow, xRangeHigh, yBins, yRangeLow, yRangeHigh));
        splitScatterPlots[i]->SetMarkerColor(colors[i]);
        cutflowCategories.push_back({});
    }

    //Create data and uncertainty calculation histograms
    dataHist = new TH1F("data", "data", xBins, xRangeLow, xRangeHigh);
    categories.push_back(defaultCategoryNames.size());
    
    for (int i=0; i<splitHists.size(); i++) {
        TString histName = "channelhUn"+to_string(i);
        channelhUn.push_back(new TH1F(histName,"",1,0,1));
        channelhUn[i]->Sumw2();
    }
}

void getXSectionInfo() {

    map<string, vector<float>> xSecInfo;

    if (performWeighting) {
        ifstream infile("~/Projects/SUSYFramework/TheEventLoop/data/susy_crosssections_13TeV.txt");
        string line;
        while (getline(infile,line)) {
            istringstream iss(line);
            string ID;
            float xSec, kFac, eff;
            string name;
            if (!(iss >> ID >> name >> xSec >> kFac >> eff)) { continue; }
            xSecInfo[ID] = vector<float>({xSec, kFac, eff});
        }
    }

    for (string i:histIDs) {
        if (xSecInfo.find(i) != xSecInfo.end() && performWeighting) {
            xSections.push_back(xSecInfo[i][0]);
            kFactors.push_back(xSecInfo[i][1]);
            genEfficiencies.push_back(xSecInfo[i][2]);
        }
        else {
            if (performWeighting)
                cout<<"Could not find event weight info for "+i+"!"<<endl;
            xSections.push_back(1);
            kFactors.push_back(1);
            genEfficiencies.push_back(1);
        }
    }
}

int calculateCuts(int histNumber, float weight) {
    
    int passedCompleteCut;
    if (printCutflow) {
        //Calculate whether the event passed the complete cut
        for (int k=0; k<cuts.size(); k++) {
            int cut=cuts[k];
            passedCompleteCut *= cut;
            int category = categories[histNumber];
            if (cut==1) {
                if (k >= cutflowCategories[category].size()) {
                    if (performWeighting)
                        cutflowCategories[category].push_back(weight);
                    else
                        cutflowCategories[category].push_back(1);
                }
                else {
                    if (performWeighting)
                        cutflowCategories[category][k]+=weight;
                    else
                        cutflowCategories[category][k]++;
                }
            }
            else break;
        }
    }
    else {
        passedCompleteCut = (std::find(cuts.begin(), cuts.end(), 0) == cuts.end());
    }
    return passedCompleteCut;
}

void prepareHistograms() {

    for (int i=0; i<histIDs.size()+(plotData ? 1 : 0); i++) {

        if (i == histIDs.size() && plotData)
            cout<<"File "<<i+1<<" out of "<<histIDs.size()+(plotData ? 1 : 0)<<": Data"<<flush;
        else
            cout<<"File "<<i+1<<" out of "<<histIDs.size()+(plotData ? 1 : 0)<<": "<<histIDs[i]<<flush;

        //Open each file and extract variables
        bool isData = false;
        if (i==histIDs.size()) {
            if (dataName != NULL)
                files.push_back(new TFile(TString(dataPath+dataName+".root")));
            else if (!blinded)
                files.push_back(new TFile(TString(dataPath+"data.root")));
            else
                files.push_back(new TFile(TString(dataPath+"data_blinded.root")));
            isData = true;
            categories.push_back(defaultCategoryNames.size());
            splitCategoryNames.push_back("Data");
            cutflowCategories.push_back({});
        }
        else
            files.push_back(new TFile(TString(MCPath+histIDs[i]+".root")));
        trees.push_back((TTree*)files[i]->Get(treeName));
        GetBranches(trees[i]);

        //Calculate weights
        double weight = 1;
        float weight1fb = 1;
        double nonEventWeight = 1;
        double sampleWeight = 1;
        double eventWeight = 1;
        double pileupWeight = 1;
        vector<double> *leptonWeight = 0;
        vector<double> *jetWeight = 0;
        float sumWeightedEvents;
        double sf_mu50;

        if (!isData && performWeighting) {
            trees[i]->SetBranchStatus("eventWeight",1);
            trees[i]->SetBranchAddress("eventWeight",&eventWeight);
            trees[i]->SetBranchStatus("sampleWeight",1);
            trees[i]->SetBranchAddress("sampleWeight",&sampleWeight);
            if (muRescaling) {
                trees[i]->SetBranchStatus("pileupWeight_rew",1);
                trees[i]->SetBranchAddress("pileupWeight_rew",&pileupWeight); // With mu rescaling added in
            }
            else {
                trees[i]->SetBranchStatus("pileupWeight",1);
                trees[i]->SetBranchAddress("pileupWeight",&pileupWeight);
            }
            trees[i]->SetBranchStatus("lep_weight",1);
            trees[i]->SetBranchAddress("lep_weight",&leptonWeight);
            trees[i]->SetBranchStatus("jet_weight",1);
            trees[i]->SetBranchAddress("jet_weight",&jetWeight);
            if (useWeight1fb)
                trees[i]->SetBranchAddress("weight1fb",&weight1fb);
			//Checkpoint - remove later
            //trees[i]->SetBranchStatus("mmtrigweight",1);
            //trees[i]->SetBranchAddress("mmtrigweight",&sf_mu50);
			sf_mu50=1;
        }

        if (performWeighting) {
            if (i!=histIDs.size()) {
                sumWeightedEvents = ((TH1F*)files[i]->Get("EventCountHist"))->GetBinContent(2);
                //nonEventWeight = xSections[i]*genEfficiencies[i]*kFactors[i];
            }
        }

        int maxEvents = trees[i]->GetEntries();
        if (setMaxEventsPerFile)
            maxEvents = min((int)trees[i]->GetEntries(), maxEventsPerFile);

        cout<<" ("<<maxEvents<<" events)"<<flush;

        //Loop through events
        for (int j=0;j<maxEvents;j++) {

            if ((j*10)%maxEvents<10)
                cout<<"."<<flush;
            if (j==maxEvents-1)
                cout<<""<<endl;
            trees[i]->GetEntry(j);
            cuts = {};
            cutNames = {};
            fillValue = {};
            fillSecondValue = {};
            splitChannel = {};
            int passedCompleteCut=1;

            FillHistograms();

            if (splitTypeChoice==0) //Default split
                splitChannel.push_back(categories[i]); 

            //Event weighting
            if (performWeighting && !isData) {
                //weight = nonEventWeight*eventWeight*luminosity/sumWeightedEvents;
				weight = sampleWeight*eventWeight*luminosity/sumWeightedEvents;
                if (pileupReweighting)
                    weight = weight*pileupWeight;
                for (int i=0; i<max((int)leptonWeight->size(),2); i++) {
                    weight *= (*leptonWeight)[i];
                }
                for (int i=0; i<jetWeight->size(); i++) {
                    weight *= (*jetWeight)[i];
                }
                //weight *= 1+(sf_mu50-1)*trig_mm2;
            }

            if (useWeight1fb)
                weight = weight1fb*luminosity/1000.;

            calculateCuts(i, weight);

            //Fill histograms with event info
            if (!isData) {
                for (int k=0;k<splitCategories.size();k++) {
                    bool containsChannel = false;
                    if (std::find(splitChannel.begin(), splitChannel.end(), splitCategories[k]) != splitChannel.end())
                        containsChannel = true;
                    for (int l=0; l<fillValue.size(); l++) {
                        //if (fillValue[l]<=xRangeLow)
                            //splitHists[k]->Fill(xRangeLow+0.0001,weight*passedCompleteCut*containsChannel);
                        //else if (fillValue[l]>=xRangeHigh)
                            //splitHists[k]->Fill(xRangeHigh-0.0001,weight*passedCompleteCut*containsChannel);
                        //else
                        splitHists[k]->Fill(fillValue[l],weight*passedCompleteCut*containsChannel);
                        channelhUn[k]->Fill(0.5,weight*passedCompleteCut*containsChannel);
                        if (plotTypeChoice==2)
                            splitScatterPlots[k]->Fill(fillValue[l],fillSecondValue[l],weight*passedCompleteCut*containsChannel);
                    }
                }
            }
            else {
                for (int l=0; l<fillValue.size(); l++) {
                    dataHist->Fill(fillValue[l],weight*passedCompleteCut);
                }
            }
        }

        files[i]->Close();
    }
}

void calculateIntegralsAndUncertainties() {
    for (int i=0;i<splitHists.size();i++) {
        hs->Add(splitHists[i]);
        integrals[i] += channelhUn[i]->GetBinContent(1);
        uncertainties[i] = channelhUn[i]->GetBinError(1);
    }
}

void performOverflowBinning() {
    for (int i=0;i<splitHists.size();i++) {
        splitHists[i]->SetBinContent(xBins,splitHists[i]->GetBinContent(xBins)+splitHists[i]->GetBinContent(xBins+1));
        splitHists[i]->SetBinContent(xBins+1,0);
        splitHists[i]->SetBinContent(1,splitHists[i]->GetBinContent(0)+splitHists[i]->GetBinContent(1));
        splitHists[i]->SetBinContent(0,0);
    }
    dataHist->SetBinContent(xBins,dataHist->GetBinContent(xBins)+dataHist->GetBinContent(xBins+1));
    dataHist->SetBinContent(xBins+1,0);
    dataHist->SetBinContent(1,dataHist->GetBinContent(0)+dataHist->GetBinContent(1));
    dataHist->SetBinContent(0,0);
}

//Display functions
void displayCutflow() {

    //Print by category
    //for (int i=0; i<splitCategoryNames.size(); i++) {
        //cout << "===============================================================" << endl;
        //cout << "Category: "<< splitCategoryNames[i] << endl;
        //for (int k=0; k<cutflowCategories[i].size(); k++)
            //cout << "Number of events passing cut "<<k+1<<": "<< cutflowCategories[i][k]<< endl;
        //cout << cutflowCategories[i][k]<< endl;
    //}
    //cout << "===============================================================" << endl;

    //Print by cut number
    cout << "===============================================================" << endl;
    int maxCuts = 0;
    for (int i=0; i<splitCategoryNames.size(); i++) {
        cout << "\t" << splitCategoryNames[i];
        if (maxCuts<cutflowCategories[i].size()) {
            maxCuts = cutflowCategories[i].size();
        }
    }
    cout << endl;
    for (int k=0; k<maxCuts; k++) {
        if (cutNames[k]=="")
            cout << "Cut "<<k+1<<":\t";
        else
            cout << cutNames[k] <<":\t";
        for (int i=0; i<splitCategoryNames.size(); i++) {
            if (k<cutflowCategories[i].size()) {
                cout << cutflowCategories[i][k] << "\t";
            }
            else
                cout << "\t";
        }
        cout << endl;
    }
    cout << "===============================================================" << endl;
}

void drawPlot() {
    //Create canvas
    TCanvas *canvas;
    if (plotData && plotRatioBox)
        canvas = new TCanvas("canvas","",696,590);
    else
        canvas = new TCanvas("canvas","",696,472);

    //Create MC/data ratio box
    TPad* mainpad = new TPad("mainpad","mainpad",0.0,0.2,1.0,0.95);
    TPad* ratiopad = new TPad("ratiopad","ratiopad",0.0,0.05,1.0,0.2);

    if (plotData && plotRatioBox) {
        canvas->cd();
        //Create TPad object (x1,y1,x2,y2) and draw plots on it
        mainpad->Draw();
        //Create 2nd TPad object
        ratiopad->Draw();
        //Get ready to draw plot
        mainpad->cd();
    }

    //Draw plot
    if (plotTypeChoice==0) {
        hs->Draw("hist");
        hs->SetMinimum(yRangeLow);
        if (setYHigh)
            hs->SetMaximum(yRangeHigh);
        hs->GetXaxis()->SetLimits(xRangeLow, xRangeHigh);
        hs->GetHistogram()->GetXaxis()->SetTitle(plotValues[plotValueChoice]);
        hs->GetHistogram()->GetYaxis()->SetTitle(YTitle);
        hs->GetHistogram()->GetYaxis()->SetTitleOffset(1.3);
    }
    else if (plotTypeChoice==1) {
        THStack *spliths = new THStack("spliths",TString(histTitle));
        for (int i=0; i<splitHists.size(); i++) {
            splitHists[i]->SetFillStyle(0);
            if (drawLegend || !drawStats)
                splitHists[i]->SetStats(0);
            //splitHists[i]->Draw("same hist");
            //splitHists[i]->SetMinimum(yRangeLow);
            //if (setYHigh)
                //splitHists[i]->SetMaximum(yRangeHigh);
            //splitHists[i]->GetXaxis()->SetRangeUser(xRangeLow, xRangeHigh);
            //splitHists[i]->GetXaxis()->SetTitle(plotValues[plotValueChoice]);
            splitHists[i]->GetYaxis()->SetTitle(YTitle);
            splitHists[i]->GetYaxis()->SetTitleOffset(1.3);
            spliths->Add(splitHists[i]);
        }
        //splitHists[0]->DrawNormalized("same hist");
        //splitHists[1]->DrawNormalized("same hist");
        spliths->Draw("nostack hist");
    }
    else if (plotTypeChoice==2) {
        for (int i=0; i<splitScatterPlots.size(); i++) {
            splitScatterPlots[i]->SetStats(0);
            splitScatterPlots[i]->Draw("same");
            splitScatterPlots[i]->GetXaxis()->SetTitle(plotValues[plotValueChoice]);
            splitScatterPlots[i]->GetYaxis()->SetTitle(plotValues[plotSecondValueChoice]);
            splitScatterPlots[i]->GetYaxis()->SetTitleOffset(1.3);
        }
    }

    //Print out final numbers
    if (printFinalNumbers) {
        cout << "===============================================================" << endl;
        for (int i=0; i<splitCategoryNames.size(); i++) {
            cout << splitCategoryNames[i] << "\t";
        }
        cout << endl;
        for (int i=0; i<splitCategoryNames.size(); i++) {
            cout << sigFig(integrals[i]) << "+-" << sigFig(uncertainties[i]) << "\t";
        }
        cout << endl;
        cout << "===============================================================" << endl;
    }

    //Draw legend and tweak plot visuals
    TLegend* leg = new TLegend(0.6, 0.85-.05*splitCategoryNames.size(), 0.9, 0.9);
    for (int i=0;i<splitCategoryNames.size();i++) {
        if (splitCategoryNames[i]=="Data") continue;
        leg->AddEntry(splitHists[i], TString(splitCategoryNames[i]+" - "+sigFig(integrals[i])+"+-"+sigFig(uncertainties[i])), "f");
    }
    if (drawLegend)
        leg->Draw();
    if (plotLogY)
        gPad->SetLogy();
    if (plotData) {
        dataHist->Draw("same e1");
        std::cout<<dataHist->Integral()<<std::endl;
        hs->SetMaximum(1.3*max(hs->GetMaximum(), dataHist->GetMaximum()));
    }

    //Create MC/data ratio box
    if (plotData && plotRatioBox) {
        ratiopad->cd();
        //Now create and draw the ratio histogram
        TH1F* hratio = (TH1F*) dataHist->Clone("hratio");
        hratio->SetStats(0);
        hratio->SetTitle("");
        hratio->GetYaxis()->SetLabelSize(0.2);
        //Sum stack
        TList *histos = hs->GetHists();
        TH1F *sum = new TH1F("sum","sum of histograms",xBins,xRangeLow,xRangeHigh);
        TIter next(histos);
        TH1F *hist;
        while ((hist =(TH1F*)next())) {
            sum->Add(hist);
        }
        //Draw ratio
        hratio->Divide(sum);
        hratio->Draw();
        hratio->SetMinimum(ratioMin);
        hratio->SetMaximum(ratioMax);
        hratio->GetYaxis()->SetNdivisions(5);
        delete sum;
    }

    //Save image
    if (saveImage) {
        TString dateAndTime(TDatime().AsSQLString());
        //TString imageName = saveDirectory+saveTag+"_"+dateAndTime+"."+filetype;
        TString imageName = saveDirectory+saveTag+"."+filetype;
        gROOT->ProcessLine(TString(".! mkdir -p ")+saveDirectory);
        imageName.ReplaceAll(" ","_").ReplaceAll("-","").ReplaceAll(":","");
        canvas->Print(imageName);
    }

    //Reset everything for next plot
    delete canvas;
}

//Main plotting code
void MakePlot() {

    createHistograms();
    //getXSectionInfo();
    prepareHistograms();
    calculateIntegralsAndUncertainties();
    performOverflowBinning();

    if (printCutflow) displayCutflow();
    drawPlot();

    reset();
}
