#ifndef GROUP_H
#define GROUP_H

#include "Sample.h"

class Group {

private:

    TString path = "";
    TString name = "";
    vector<Sample> samples;
    bool isData=false;
    int fillColor, lineColor=kBlack; 
    bool stack=true;

public:

    Group(TString _name) {
        name = _name;
    }

    void SetPath(TString _path) {
        path = _path;
    }

    void AddSample(TString sampleName) {
        Sample newSample(sampleName);
        newSample.SetPath(path);
        samples.push_back(newSample);
    }

    void AddSample(int sampleID) {
        AddSample((TString)to_string(sampleID));
    }

    TString GetName() {
        return name;
    }

    void SetData(bool set=true) {
        isData = set;
    }

    void SetNoStack(bool set=true) {
        stack = !set;
    }

    bool IsData() {
        return isData; 
    }

    void SetLineColor(int _lineColor) {
        lineColor = _lineColor;
    }

    void SetFillColor(int _fillColor) {
        fillColor = _fillColor;
    }

    TH1* Plot(TString value, TCut selection, int xBins, float xLow, float xHigh) {
        THStack* plot = new THStack("plot", "");
        std::cout<<"Checkpoint "<<__LINE__<<std::endl;
        for (int i=0; i<samples.size(); i++) {
            samples[i].SetLineColor(lineColor);
            samples[i].SetFillColor(fillColor);
            plot->Add(samples[i].Plot(value, selection, xBins, xLow, xHigh));
        }
        std::cout<<"Checkpoint "<<__LINE__<<std::endl;
        return plot->GetHistogram();
    }
};

#endif
