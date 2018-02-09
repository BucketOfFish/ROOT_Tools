#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TTree.h"
#include "TString.h"
#include "TLorentzVector.h"

// Formatting

template <typename type> string SigFig(type input, int precision) {
    ostringstream out;
    //out << setprecision(precision) << input;
    out << fixed << setprecision(precision) << input;
    return out.str();
}

template <typename type> string FormatExcelTable(vector<vector<type> > data) {

    string table = "";
    for (int row=0; row<data.size(); row++) {
        for (int col=0; col<data[row].size(); col++) {
            table += to_string(data[row][col])+"\t";
        }
        table += "\n";
    }
    return table;
}

template <typename type> string FormatLatexTable(vector<vector<type> > data) {

    string table = "\\begin{table}\n\\begin{center}\n\\begin{tabular}{"+string(data[0].size(),'c')+"}\n";
    for (int row=0; row<data.size(); row++) {
        for (int col=0; col<data[row].size(); col++) {
            table += to_string(data[row][col]);
            if (col+1 != data[row].size()) table += " & ";
        }
        table += "\\\\\n";
    }
    table += "\\end{tabular}\n\\end{center}\n\\caption{CAPTION}\n\\label{tab:LABEL}\n\\end{table}";
    return table;
}

TCut to_TCut(TString val) {
    return TCut(val);
}

TCut to_TCut(string val) {
    return TCut(TString(val));
}

TCut to_TCut(const char* val) {
    return TCut(TString(val));
}

template <typename type> TCut to_TCut(type val) {
    return TCut(TString(to_string(val)));
}

template <typename type> TString to_TString(type val) {
    return TString(to_string(val));
}

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

void findReplace(std::string& str, const std::string& oldStr, const std::string& newStr)
{
  std::string::size_type pos = 0u;
  while((pos = str.find(oldStr, pos)) != std::string::npos){
     str.replace(pos, oldStr.length(), newStr);
     pos += newStr.length();
  }
}

// Misc

float getSampleWeight(int DSID) {

    ifstream infile("~/Projects/SUSYFramework/TheEventLoop/data/susy_crosssections_13TeV.txt");
    string line;
    while (getline(infile,line)) {
        istringstream iss(line);
        string ID;
        float xSec, kFac, eff;
        string name;
        if (!(iss >> ID >> name >> xSec >> kFac >> eff)) { continue; }
        if (std::stoi(ID) == DSID)
            return xSec*kFac*eff;
    }

    std::cout<<"Did not find sample weight info for sample "<<DSID<<std::endl;
    return 0;
}

// Histogram Functions

template <typename type> void PerformOverflowBinning(type hist) {
    int nBins = hist->GetSize()-2;
    hist->SetBinContent(nBins,hist->GetBinContent(nBins)+hist->GetBinContent(nBins+1));
    hist->SetBinContent(nBins+1,0);
    hist->SetBinContent(1,hist->GetBinContent(0)+hist->GetBinContent(1));
    hist->SetBinContent(0,0);
}

//void ToggleLegend(type hist) {}
//void ChangeXAxis(type hist, float xMin, float xMax) {}
//void ChangeColors(type hist, vector<kColor> colors) {}

// File IO

void Mkdir(TString directory) {

    gROOT->ProcessLine(TString(".! mkdir -p ")+directory);
}

void ls(TString directory) {

    gROOT->ProcessLine(TString(".! ls ")+directory);
}

void SaveCanvas (TCanvas* canvas, TString directory, TString name, TString filetype="pdf", bool addTimeStamp=false) {

    TString imageName = directory+"/"+name;
    if(addTimeStamp) {
        TString dateAndTime(TDatime().AsSQLString());
        imageName += "_"+dateAndTime;
    }
    imageName += "."+filetype;

    Mkdir(directory);
    imageName.ReplaceAll(" ","_").ReplaceAll("-","").ReplaceAll(":","");
    canvas->Print(imageName);
}

float GetEventCount (TString filename) {

    TFile* f = new TFile(filename, "read");
    if( !f->IsOpen() ) return 0;
    TH1F* EventCountHist = (TH1F*) f->Get("EventCountHist");
    return EventCountHist->GetBinContent(2);
}

// Branches

// Return a branch as a vector (e.g. vector<int> lep_n = {}; FillFromBranch(outputTree, lep_n, "lep_n");)
template <typename type> void FillFromBranch(TTree* tree, vector<type>& vec, TString branch) {

    type val;
    tree->SetBranchAddress(branch, &val);
    int n = (int) tree->GetEntries();
    for (int i = 0; i < n; ++i) {
        tree->GetEntry(i);
        vec.push_back(val);
    }
}

// May be fucked up
template <typename type> void AddBranch(TTree *tree, vector<type> branch, TString branchName) {

    type val;
    TBranch *newBranch = tree->Branch(branchName, &val);
    int n = (int) tree->GetEntries();
    for (int i = 0; i < n; ++i) {
        val = branch[i];
        newBranch->Fill();
    }
}

#endif //FUNCTIONS_H
