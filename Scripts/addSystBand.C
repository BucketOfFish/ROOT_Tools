/*
Script to adjust err band in plots to include systs.
Runs on .root files output from the analysis code

Jan 19, 2016
Jonathan Long

*/


void addSystBand()
{
    gStyle->SetOptStat(0);

    bool includeSyst = true;

    // put ratio stuff under a flag so that we can switch easily
    bool hasRatio = true;

    //Get Bkgs to put syst in, could be changed per region later
    double dibosonSyst = 0.49;
    double fsSyst = 0.11;
    double otherSyst = 0.23;
    double fakeSyst = 0.76;
    double zjetsSyst = 0.42;

    TString inputPath = "/afs/cern.ch/user/m/mazhang/Plots/CMS/Original/";
    TString savePath = "/afs/cern.ch/user/m/mazhang/Plots/CMS/Altered/";

    std::vector<TString> inputFileNames = {
        //"ee-Cut_CMS-Mll_CMS_Shift0-lin.root",
        //"ee-Cut_CMS-Mll_CMS_Shift1-lin.root",
        //"eemm-Cut_CMS-Mll_CMS_Shift0-lin.root",
        //"eemm-Cut_CMS-Mll_CMS_Shift1-lin.root",
        "em-Cut_CMS-Mll_CMS_Shift0-lin.root",
        "em-Cut_CMS-Mll_CMS_Shift1-lin.root",
        "emme-Cut_CMS-Mll_CMS_Shift0-lin.root",
        "emme-Cut_CMS-Mll_CMS_Shift1-lin.root",
        "me-Cut_CMS-Mll_CMS_Shift0-lin.root",
        "me-Cut_CMS-Mll_CMS_Shift1-lin.root",
        //"mm-Cut_CMS-Mll_CMS_Shift0-lin.root",
        //"mm-Cut_CMS-Mll_CMS_Shift1-lin.root"
     };

    //// could automatically loop over all files in a directory
    //gROOT->ProcessLine(TString(".! ls ")+inputPath+" >> fileList.txt");
    //vector<TString> inputFileNames;
    //ifstream myfile("fileList.txt");
    //std::copy(std::istream_iterator<string>(myfile),
      //std::istream_iterator<string>(),
      //std::back_inserter(inputFileNames));

    for (auto inputFileName:inputFileNames) {

        // open file
        std::cout<<"Opening file "<<inputPath+inputFileName<<std::endl;
        TFile *f =  new TFile(inputPath+inputFileName);

        // canvas name, will change with file
        TString inputFileNameTemp = inputFileName;
        TString canvasName = ((string)(inputFileNameTemp.ReplaceAll("-","_"))).substr(0, ((string)inputFileName).length()-4);
		size_t pos = ((string)canvasName).find("_lin");
		canvasName = ((string)canvasName).substr(0,pos);
        TString saveName = inputFileName;

        TCanvas *cwhole = (TCanvas*)f->Get(canvasName);
        TH1F *master = (TH1F*)f->Get("master");
        master->SetTitle("");

        // Draw the thing
        cwhole->Draw();

        // Get pad with stuff in it
        TPad *tpad = (TPad*)cwhole->GetListOfPrimitives()->At(0);
        tpad->cd();

        // Change legend label
        TLegend * leg = (TLegend*)tpad->GetPrimitive("legend");
        TLegendEntry * tempData = leg->GetEntry();
        leg->DeleteEntry();
        leg->GetEntry()->SetLabel(" SM (stat+syst)");
        leg->InsertEntry("hist_data", " Data");

        // zero out old error graph
        TGraphAsymmErrors * oldErr = (TGraphAsymmErrors*)tpad->GetPrimitive("totalBkgErr");
        for (size_t point = 0; point < oldErr->GetN(); point++) {
            oldErr->SetPointError(point, 0,0,0,0);
        }

        // Get Total Bkg
        TString bkgName = "totalBkg";
        TH1D* hBkg = (TH1D*)tpad->GetPrimitive(bkgName)->Clone();
        // Get Data to redraw
        TString dataName = "hist_data";
        TH1D* hData = (TH1D*)f->Get(dataName);



        TString dibosonName = "hist_Diboson";
        TH1D* hDiboson = (TH1D*)f->Get(dibosonName);

        TString otherName = "hist_Other";
        TH1D* hOther = (TH1D*)f->Get(otherName);

        //TString fsName = "hist_Flav__Sym_";
        TString fsName = "hist_Top";
        TH1D* hFs = (TH1D*)f->Get(fsName);

        TString fakesName = "hist_Wjets";
        TH1D* hFakes = (TH1D*)f->Get(fakesName);

        TString zjetsName = "hist_Zjets";
        TH1D* hZjets = (TH1D*)f->Get(zjetsName);

        // Make TGraph centered on total Bkg
        TGraphAsymmErrors *tgerr = new TGraphAsymmErrors(hBkg);

        // Ratio error plot
        TPad *rpad = (TPad*)cwhole->GetListOfPrimitives()->At(1);
        TGraphAsymmErrors *ratioerr = (TGraphAsymmErrors*)rpad->GetPrimitive("ratioErrorGraph");

        for (size_t point = 1; point < tgerr->GetN()-1; point++)
        {
            // Be Careful with graph vs hist binning
            double x,y;
            tgerr->GetPoint(point, x, y);
            // Set New Errors here

            double upError   = tgerr->GetErrorYhigh(point);
            double downError = tgerr->GetErrorYlow(point);

            double leftError = tgerr->GetErrorXlow(point);
            double rightError = tgerr->GetErrorXhigh(point);


            // add sqrt(2) * fs error in here
            double newUpError = sqrt(pow(upError,2) + pow(hDiboson->GetBinContent(point+1) * dibosonSyst,2) +  pow(hFs->GetBinContent(point+1) * fsSyst,2) + pow(hFs->GetBinError(point+1),2) + pow(hOther->GetBinContent(point+1) * otherSyst,2)+ pow(hFakes->GetBinContent(point+1) * fakeSyst,2) + pow(hZjets->GetBinContent(point+1)*zjetsSyst, 2 ) );

            double newDownError = sqrt(pow(downError,2) + pow(hDiboson->GetBinContent(point+1) * dibosonSyst,2) + pow(hFs->GetBinContent(point+1) * fsSyst,2) + pow(hFs->GetBinError(point+1),2) + pow(hOther->GetBinContent(point+1) * otherSyst,2)+ pow(hFakes->GetBinContent(point+1) * fakeSyst,2) + pow(hZjets->GetBinContent(point+1)*zjetsSyst, 2 ));

            if (includeSyst) tgerr->SetPointError(point, leftError, rightError, newDownError, newUpError);

            // This seems to be enough to adjust the ratio error band
            if (includeSyst) ratioerr->SetPointError(point, ratioerr->GetErrorXlow(point), ratioerr->GetErrorXhigh(point), newDownError/downError*ratioerr->GetErrorYlow(point), newUpError/upError*ratioerr->GetErrorYhigh(point));
        }

        tgerr->SetFillStyle(3254); //3013
        tgerr->SetFillColor(14);
        tgerr->Draw("2");

        ratioerr->SetMaximum(2);
        ratioerr->SetMinimum(0);
        ratioerr->GetYaxis()->SetNdivisions(4);
		//ratioerr->Draw(); // this draws a weird thing on top

        // need to redraw data to get it ontop
        hData->Draw("same");

        gROOT->ProcessLine(TString(".! mkdir -p ")+savePath);
        cwhole->SaveAs(savePath+saveName + ".eps");
        cwhole->SaveAs(savePath+saveName + ".root");
        //cwhole->SaveAs(savePath+saveName + ".C");

    } // loop




}
