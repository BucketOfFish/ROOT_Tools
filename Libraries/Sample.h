#ifndef SAMPLE_H
#define SAMPLE_H

#import "Functions.h"

class Sample {

private:

    TString path = "";
    TString name = "";
    TFile* file;
    TTree* tree;
    bool openFile=false, openTree=false;
    float sumWeightedEvents;
    int lineColor=kBlack, fillColor;

public:

    Sample(TString _name) {
        name = _name;
    }

    Sample(int ID) {
        name = TString(to_string(ID));
    }

    TString GetName() {
        return name;
    }

    void SetPath(TString _path) {
        path = _path;
    }

    void Open() {
        file = new TFile(path+"/"+name+".root");
        openFile = true;
    }

    void Close() {
        delete file;
        openFile = false;
    }

    float GetSumWeightedEvents() {
        if (!openFile) Open();
        sumWeightedEvents = ((TH1F*)file->Get("EventCountHist"))->GetBinContent(2);
        return sumWeightedEvents;
    }

    TTree* GetTree(TString treeName = "outputTree") {
        if (!openFile) Open();
        if (!openTree) tree = (TTree*)file->Get(treeName);
        openTree = true;
        return tree;
    }

    void SetLineColor(int color) {
        lineColor = color;
    }

    void SetFillColor(int color) {
        fillColor = color;
    }

    TH1F* Plot(TString value, TCut selection, int xBins, float xLow, float xHigh) {
        if (!openTree) GetTree();
        TH1F* hist = new TH1F("hist", "", xBins, xLow, xHigh);
        hist->SetStats(0);
        hist->SetLineColor(lineColor);
        hist->SetFillColor(fillColor);
        tree->Draw(value + ">>hist", selection);
        PerformOverflowBinning(hist);
        return hist;
    }

    ~Sample() {
        if (openFile) Close();
        if (openTree) delete tree;
        openTree = false;
    }
};

#endif
