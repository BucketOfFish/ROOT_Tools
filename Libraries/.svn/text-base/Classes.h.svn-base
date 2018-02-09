#ifndef CLASSES_H
#define CLASSES_H
 
TString MCPath = "";
TString dataPath = "";
bool blinded = false;
int luminosity = 3209;
 
// Classes
 
class Group {
 
    TString name, samplePath;
    vector<TString> samples;
    TCut customWeight = "";
 
public:
 
    bool isData = false;

    Group(TString initName, TString path = MCPath) {
        name = initName;
        samplePath = path;
    }
 
    void AddSample(TString sampleName, TString path = MCPath) {
        samples.push_back(sampleName);
        samplePath = path;
    }
 
    void AddSample(int sampleNumber, TString path = MCPath) {
        AddSample((TString)to_string(sampleNumber), path);
    }
 
    vector<TString> GetSamples() {
        return samples;
    }
 
    void SetName(TString newName) {
        name = newName;
    }

    TString Name() {
        return name;
    }
 
    bool IsData() {
        return isData;
    }
 
    TChain* GetChain(TString treeName = "outputTree") {
        TChain* returnChain = new TChain(treeName);
        for (int i=0; i<samples.size(); i++) {
            returnChain->Add(samplePath+samples[i]+".root");
        }
        return returnChain;
    }
 
    TTree* GetTree(TString treeName = "outputTree") {
        return GetChain(treeName)->CloneTree();
    }
 
    TString GetPath() {
        return samplePath;
    }
 
    void SetPath(TString newPath) {
        samplePath = newPath;
    }

    void SetCustomWeight(TCut cut) {
        customWeight = cut;
    }

    TCut GetCustomWeight() {
        return customWeight;
    }
};

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

    void SetBins(int bins, float low, float high) {
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
 
vector<Group> groups;
 
void AddGroup(Group group) {
    groups.push_back(group);
}
 
int NGroups() {
    return groups.size();
}
 
bool IsData(int nGroup) {
    return groups[nGroup].IsData();
}
 
TChain* GetTotalChain(TString treeName = "outputTree") {
    TChain* returnChain = new TChain(treeName);
    for (int groupNumber=0; groupNumber<groups.size(); groupNumber++) {
        if (groups[groupNumber].IsData()) continue;
        returnChain->Add(groups[groupNumber].GetChain());
    }
    return returnChain;
}
 
void ResetGroups() {
    groups.clear();
}
 
// Merge all current groups into a single group
void CombineGroups(TString name = "MC") {
    Group combinedGroup(name);
    for (int i=0; i<NGroups(); i++) {
        vector<TString> samples = groups[i].GetSamples();
        for (int j=0; j<samples.size(); j++) combinedGroup.AddSample(samples[j]);
    }
    ResetGroups();
    combinedGroup.SetPath(MCPath);
    AddGroup(combinedGroup);
}
 
void SetLuminosity(int lum) {

	luminosity = lum;
    MCWeight = "weight1fb/1000*"+TString(to_string(lum));
}
 
#endif //CLASSES_H
