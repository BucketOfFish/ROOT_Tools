#include<TH1F.h>
#include<vector>

void printBins() {

    vector<TString> fileNames;
    fileNames.push_back("ee-Cut_EdgeSR_Low-Mll_low_new-lin.root");
    fileNames.push_back("ee-Cut_EdgeSR_Med-Mll_med_new-lin.root");
    fileNames.push_back("ee-Cut_EdgeSR_High-Mll_high-lin.root");
    fileNames.push_back("mm-Cut_EdgeSR_Low-Mll_low_new-lin.root");
    fileNames.push_back("mm-Cut_EdgeSR_Med-Mll_med_new-lin.root");
    fileNames.push_back("mm-Cut_EdgeSR_High-Mll_high-lin.root");

    for (int f=0; f<fileNames.size(); f++) {

        TFile *_file0 = TFile::Open(fileNames[f]);

        vector<TH1F*> hists;
        hists.push_back((TH1F*)_file0->Get("hist_data"));
        hists.push_back((TH1F*)_file0->Get("hist_Diboson"));
        hists.push_back((TH1F*)_file0->Get("hist_Flav__Sym_"));
        hists.push_back((TH1F*)_file0->Get("hist_Zjets"));
        hists.push_back((TH1F*)_file0->Get("hist_Wjets"));
        hists.push_back((TH1F*)_file0->Get("hist_Other"));

        vector<string> histNames;
        histNames.push_back("Data");
        histNames.push_back("Diboson");
        histNames.push_back("FS");
        histNames.push_back("ZJets");
        histNames.push_back("WJets");
        histNames.push_back("Other");

        for (int n=0; n<hists.size(); n++) {
            TH1F* hist = hists[n];
            string histName = histNames[n];
            for (int i=1; i<=hist->GetSize()-2; i++) {
                if (i==1)
                    cout<<histName<<"\t";
                cout<<hist->GetBinContent(i);
                if (i==hist->GetSize()-2)
                    cout<<endl;
                else
                    cout<<"\t";
            }
        }
    }
}
