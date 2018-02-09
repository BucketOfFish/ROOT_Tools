#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Formatting

template <typename type> string SigFig(type input, int precision) {
    ostringstream out;
    out << setprecision(precision) << input;
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
