void CMSTable() {

    //Place the following plots in a folder labelled ~/Plots/CMS/Original - make sure emme plot is made using the DF MC-only script

    std::vector<TString> inputFileNames = {
        "ee-Cut_CMS-Mll_CMS_Shift0-lin.root",
        "mm-Cut_CMS-Mll_CMS_Shift0-lin.root",
        "eemm-Cut_CMS-Mll_CMS_Shift0-lin.root",
        "emme-Cut_CMS-Mll_CMS_Shift0-lin.root"
    };

    //Update these numbers if the addSystBand script is updated

    double dibosonSyst = 0.49;
    double fsSyst = 0.11;
    double otherSyst = 0.23;
    double fakeSyst = 0.76;
    double zjetsSyst = 0.42;

    for (auto inputFileName:inputFileNames) {

        //Open file - use top hist instead of FS hist for OF plot
        TString inputPath = "/afs/cern.ch/user/m/mazhang/Plots/CMS/Original/";
        std::cout<<inputFileName<<std::endl;
        TFile *f =  new TFile(inputPath+inputFileName);
        TH1F *hist_data = (TH1F*)f->Get("hist_data");
        TH1F *hist_Diboson = (TH1F*)f->Get("hist_Diboson");
        TH1F *hist_Flav__Sym_ = (TH1F*)f->Get("hist_Flav__Sym_");
        if (inputFileName.EqualTo(TString("emme-Cut_CMS-Mll_CMS_Shift0-lin.root")))
            hist_Flav__Sym_ = (TH1F*)f->Get("hist_Top");
        TH1F *hist_Zjets = (TH1F*)f->Get("hist_Zjets");
        TH1F *hist_Wjets = (TH1F*)f->Get("hist_Wjets");
        TH1F *hist_Other = (TH1F*)f->Get("hist_Other");

        float data = 0;
        float diboson = 0, dibosonErr = 0;
        float fs = 0, fsErr = 0;
        float zjets = 0, zjetsErr = 0;
        float wjets = 0, wjetsErr = 0;
        float other = 0, otherErr = 0;

        //Sum up bins for mll from 20-70
        for(int i=3; i<=7; i++) {
            data += hist_data->GetBinContent(i);
            diboson += hist_Diboson->GetBinContent(i);
            dibosonErr += pow(hist_Diboson->GetBinError(i),2);
            fs += hist_Flav__Sym_->GetBinContent(i);
            fsErr += pow(hist_Flav__Sym_->GetBinError(i),2);
            zjets += hist_Zjets->GetBinContent(i);
            zjetsErr += pow(hist_Zjets->GetBinError(i),2);
            wjets += hist_Wjets->GetBinContent(i);
            wjetsErr += pow(hist_Wjets->GetBinError(i),2);
            other += hist_Other->GetBinContent(i);
            otherErr += pow(hist_Other->GetBinError(i),2);
        }

        dibosonErr = pow(dibosonErr + pow(diboson*dibosonSyst,2), 0.5);
        fsErr = pow(fsErr + pow(fs*fsSyst,2), 0.5);
        zjetsErr = pow(zjetsErr + pow(zjets*zjetsSyst,2), 0.5);
        wjetsErr = pow(wjetsErr + pow(wjets*fakeSyst,2), 0.5);
        otherErr = pow(otherErr + pow(other*otherSyst,2), 0.5);

        std::cout<<diboson<<" ± "<<dibosonErr<<std::endl;
        std::cout<<fs<<" ± "<<fsErr<<std::endl;
        std::cout<<zjets<<" ± "<<zjetsErr<<std::endl;
        std::cout<<wjets<<" ± "<<wjetsErr<<std::endl;
        std::cout<<other<<" ± "<<otherErr<<std::endl;
        std::cout<<"Total: "<<diboson+fs+zjets+wjets+other<<" ± "<<pow(dibosonErr*dibosonErr + fsErr*fsErr + zjetsErr*zjetsErr + wjetsErr*wjetsErr + otherErr*otherErr, 0.5)<<std::endl;
        std::cout<<"Data: "<<data<<std::endl;
    }
}
