//copy-paste relevant section into ROOT

ZTruthMETSR_Plots {

    vector<TString> titles1 = {"SRLow", "SRMed", "SRHigh", "SRZ"};
    vector<TString> titles2 = {"Zee", "Zmm", "Ztt", "Zee_bVeto", "Zee_bFilter"};
    for (int i=0; i<titles1.size(); i++) {
        for (int j=0; j<titles2.size(); j++) {
            TString title1 = titles1[i];
            TString title2 = titles2[j];
            TString title = title1 + " " + title2;
            cout<<title<<endl;
            TFile *_file0 = new TFile(title1 + "truthMET_NonInt_" + title2 + ".root");
            TFile *_file1 = new TFile(title1 + "truthMET_IntOut_" + title2 + ".root");
            TFile *_file2 = new TFile(title1 + "fakeMET_" + title2 + ".root");
            vector<TH1F*> hist = {};
            vector<TString> histName = {};
            hist.push_back((TH1F*)((TCanvas*)_file0->Get("hist")));
            histName.push_back("NonInt MET");
            hist.push_back((TH1F*)((TCanvas*)_file1->Get("hist")));
            histName.push_back("IntOut MET");
            hist.push_back((TH1F*)((TCanvas*)_file2->Get("hist")));
            histName.push_back("Fake MET");
            vector<int> colors = {kRed, kOrange, kMagenta, kGreen, kGray, kBlue, kCyan, kYellow, kBlack};
            THStack *hs = new THStack("hs","");
            for (int i=0; i<hist.size(); i++) {
                hist[i]->SetLineColor(colors[i]);
                hs->Add(hist[i]);
            }
            hs->SetTitle(title);
            TCanvas* canvas = new TCanvas("canvas","",696,472);
            hs->Draw("nostack hist");
            hs->SetMinimum(0);
            TLegend* leg = new TLegend(0.6, 0.85-.05*4, 0.9, 0.9);
            for (int i=0;i<histName.size();i++) {
                leg->AddEntry(hist[i], histName[i], "f");
            }
            leg->Draw();
            canvas->Print("~/Plots/ZTruthMETSR/" + title + ".pdf");
            delete canvas;
        }
    }

}

CombineHistograms {

    vector<TString> plots = {"h_nVtx", "h_x", "h_y", "h_z", "h_HSRecox", "h_HSRecoy", "h_HSRecoz", "h_HSTruex", "h_HSTruey", "h_HSTruez", "h_HSRecEff", "h_xHSRes", "h_yHSRes", "h_zHSRes", "h_DzSplits", "h_HSCategory", "h_nClass", "h_HSSumPtTracks", "h_HSSumPt2Tracks", "h_nTracks", "h_HSnTracks", "h_Dz"};

    TFile *_file0 = new TFile("8209.root");
    TFile *_file1 = new TFile("8210.root");
    TFile *_file2 = new TFile("8211.root");

    for (int i=0; i<plots.size(); i++) {
        vector<TH1F*> hist = {};
        vector<TString> histName = {};
        hist.push_back((TH1F*)((TCanvas*)_file0->Get(plots[i])));
        //TH1F* hist = new TH1F;
        //hist.push_back(_file0->Draw(plots[i]));
        histName.push_back("8209");
        hist.push_back((TH1F*)((TCanvas*)_file1->Get(plots[i])));
        histName.push_back("8210");
        hist.push_back((TH1F*)((TCanvas*)_file2->Get(plots[i])));
        histName.push_back("8211");
        vector<int> colors = {kRed, kOrange, kGreen, kGray, kBlue, kCyan, kRed+3, kBlack};
        THStack *hs = new THStack("hs","");
        std::cout<<plots[i]<<std::endl;
        for (int i=0; i<hist.size(); i++) {
            hist[i]->SetLineColor(colors[i]);
            hs->Add(hist[i]);
            hist[i]->Fit("gaus");
        }
        hs->SetTitle(plots[i]);
        TCanvas* canvas = new TCanvas("canvas","",696,472);
        hs->Draw("nostack hist");
        TLegend* leg = new TLegend(0.6, 0.85-.05*4, 0.9, 0.9);
        for (int i=0;i<histName.size();i++) {
            leg->AddEntry(hist[i], histName[i], "f");
        }
        leg->Draw();
        //canvas->Print(plots[i] + ".pdf");
        delete canvas;
    }

}

ITkGeometryComparison {

    gROOT->LoadMacro("AtlasStyle.C");
    gROOT->LoadMacro("AtlasUtils.C");
    gROOT->LoadMacro("AtlasLabels.C");
    SetAtlasStyle();

    vector<TString> plots = {"p_resX_slice1", "p_resX_slice2", "p_resX_slice3", "p_resX_slice4", "p_resY_slice1", "p_resY_slice2", "p_resY_slice3", "p_resY_slice4", "p_resZ_slice1", "p_resZ_slice2", "p_resZ_slice3", "p_resZ_slice4", "h_nClass_slice1", "h_nClass_slice2", "h_nClass_slice3", "h_nClass_slice4", "p_nTracks_z_slice1", "p_nTracks_z_slice2", "p_nTracks_z_slice3", "p_nTracks_z_slice4", "p_recEff_z_slice1", "p_recEff_z_slice2", "p_recEff_z_slice3", "p_recEff_z_slice4", "h_HSCategory", "h_HSRecEff", "p_nTracks_z", "p_recEff_z", "h_HSRecEff", "p_resX", "p_resY", "p_resZ"}
    vector<TString> xLabels = {"resX (mm)", "resX (mm)", "resX (mm)", "resX (mm)", "resY (mm)", "resY (mm)", "resY (mm)", "resY (mm)", "resZ (mm)", "resZ (mm)", "resZ (mm)", "resZ (mm)", "", "", "", "", "z (mm)", "z (mm)", "z (mm)", "z (mm)", "z (mm)", "z (mm)", "z (mm)", "z (mm)", "", "", "z (mm)", "z (mm)", "", "resX (mm)", "resY (mm)", "resZ (mm)"}
    vector<TString> yLabels = {"# vertices", "# vertices", "# vertices", "# vertices", "# vertices", "# vertices", "# vertices", "# vertices", "# vertices", "# vertices", "# vertices", "# vertices", "# vertices", "# vertices", "# vertices", "# vertices", "average # tracks", "average # tracks", "average # tracks", "average # tracks", "vertex reco efficiency", "vertex reco efficiency", "vertex reco efficiency", "vertex reco efficiency", "# vertices", "vertex reconstruction efficiency", "average # tracks", "vertex reco efficiency", "vertex reconstruction efficiency", "# vertices", "# vertices", "# vertices"}
    vector<TString> text = {"Vertex sum_pT^2 from 0-50", "Vertex sum_pT^2 from 50-100", "Vertex sum_pT^2 from 100-200", "Vertex sum_pT^2 above 200", "Vertex sum_pT^2 from 0-50", "Vertex sum_pT^2 from 50-100", "Vertex sum_pT^2 from 100-200", "Vertex sum_pT^2 above 200", "Vertex sum_pT^2 from 0-50", "Vertex sum_pT^2 from 50-100", "Vertex sum_pT^2 from 100-200", "Vertex sum_pT^2 above 200", "Vertex sum_pT^2 from 0-50", "Vertex sum_pT^2 from 50-100", "Vertex sum_pT^2 from 100-200", "Vertex sum_pT^2 above 200", "Vertex sum_pT^2 from 0-50", "Vertex sum_pT^2 from 50-100", "Vertex sum_pT^2 from 100-200", "Vertex sum_pT^2 above 200", "Vertex sum_pT^2 from 0-50", "Vertex sum_pT^2 from 50-100", "Vertex sum_pT^2 from 100-200", "Vertex sum_pT^2 above 200", "Hard scatter vertices", "Hard scatter vertices", "All vertices", "All vertices", "Hard scatter vertices", "All vertices", "All vertices", "All vertices"}

    TFile *_file0 = new TFile("hist_8414.root");
    TFile *_file1 = new TFile("hist_8415.root");

    for (int i=0; i<plots.size(); i++) {
        vector<TH1F*> hist = {};
        vector<TString> histName = {};
        hist.push_back((TH1F*)((TCanvas*)_file0->Get(plots[i])));
        histName.push_back("ExtBrl_4");
        hist.push_back((TH1F*)((TCanvas*)_file1->Get(plots[i])));
        histName.push_back("InclBrl_4");
        vector<int> colors = {kRed, kOrange, kGreen, kGray, kBlue, kCyan, kYellow, kBlack};
        THStack *hs = new THStack("hs","");
        std::cout<<plots[i]<<std::endl;
        for (int i=0; i<hist.size(); i++) {
            hist[i]->SetLineColor(colors[i]);
            hs->Add(hist[i]);
        }
        //hs->SetTitle(((TH1F*)((TCanvas*)_file0->Get(plots[i])))->GetTitle());
        hs->SetTitle(hist[0]->GetTitle());
        TCanvas* canvas = new TCanvas("canvas","",696,472);
        hs->Draw("nostack hist e1");
        hs->GetHistogram()->GetXaxis()->SetTitle(xLabels[i]);
        hs->GetHistogram()->GetYaxis()->SetTitle(yLabels[i]);
        myText(0.025,0.025,1,text[i]);
        TLegend* leg = new TLegend(0.75, 0.8, 0.9, 0.9);
        for (int i=0;i<histName.size();i++) {
            leg->AddEntry(hist[i], histName[i], "f");
        }
        leg->Draw();
        ATLASLabel(0.2,0.85,"Simulation Internal");
        //myText(0.2,0.75,1,"Simulation #sqrt{s} = 14 TeV");
        //myText(0.2,0.65,1,"ttbar, <#mu> = 200");
        canvas->Print(plots[i] + ".pdf");
        delete canvas;
    }

}

EricForwardTrackComparison {

    gROOT->LoadMacro("AtlasStyle.C");
    gROOT->LoadMacro("AtlasUtils.C");
    gROOT->LoadMacro("AtlasLabels.C");
    SetAtlasStyle();

    vector<TString> plots = {"p_recEff_dzHS", "p_trackstdz0_eta", "p_tracketa_dz"};
    vector<TString> xLabels = {"dz(mm)", "eta", "dz(mm)"};
    vector<TString> yLabels = {"Efficiency", "std(z0)", "|eta|"};
    vector<TString> text = {"Vertex reco efficiency vs. z distance from truth HS vertex", "Average track std(z0) vs. eta", "Average track |eta| vs. vertex dz(reco-truth)"};

    TFile *_file0 = new TFile("hist_8414.root");
    TFile *_file1 = new TFile("hist_8415.root");

    for (int i=0; i<plots.size(); i++) {
        vector<TH1F*> hist = {};
        vector<TString> histName = {};
        hist.push_back((TH1F*)((TCanvas*)_file0->Get(plots[i])));
        histName.push_back("ExtBrl_4");
        hist.push_back((TH1F*)((TCanvas*)_file1->Get(plots[i])));
        histName.push_back("InclBrl_4");
        vector<int> colors = {kRed, kOrange, kGreen, kGray, kBlue, kCyan, kYellow, kBlack};
        THStack *hs = new THStack("hs","");
        std::cout<<plots[i]<<std::endl;
        for (int i=0; i<hist.size(); i++) {
            hist[i]->SetLineColor(colors[i]);
            hs->Add(hist[i]);
        }
        //hs->SetTitle(((TH1F*)((TCanvas*)_file0->Get(plots[i])))->GetTitle());
        hs->SetTitle(hist[0]->GetTitle());
        TCanvas* canvas = new TCanvas("canvas","",696,472);
        hs->Draw("nostack hist e1");
        hs->GetHistogram()->GetXaxis()->SetTitle(xLabels[i]);
        hs->GetHistogram()->GetYaxis()->SetTitle(yLabels[i]);
        myText(0.025,0.025,1,text[i]);
        TLegend* leg = new TLegend(0.75, 0.8, 0.9, 0.9);
        for (int i=0;i<histName.size();i++) {
            leg->AddEntry(hist[i], histName[i], "f");
        }
        leg->Draw();
        ATLASLabel(0.2,0.85,"Simulation Internal");
        canvas->Print(plots[i] + ".pdf");
        delete canvas;
    }

}

ITkGeometryComparison {

    gROOT->LoadMacro("AtlasStyle.C");
    gROOT->LoadMacro("AtlasUtils.C");
    gROOT->LoadMacro("AtlasLabels.C");
    SetAtlasStyle();

    vector<TString> plots = {"p_resX_slice1", "p_resX_slice2", "p_resX_slice3", "p_resX_slice4", "p_resY_slice1", "p_resY_slice2", "p_resY_slice3", "p_resY_slice4", "p_resZ_slice1", "p_resZ_slice2", "p_resZ_slice3", "p_resZ_slice4", "h_nClass_slice1", "h_nClass_slice2", "h_nClass_slice3", "h_nClass_slice4", "p_nTracks_z_slice1", "p_nTracks_z_slice2", "p_nTracks_z_slice3", "p_nTracks_z_slice4", "h_HSCategory", "h_HSRecEff", "p_nTracks_z", "p_recEff_z", "h_HSRecEff", "p_resX", "p_resY", "p_resZ", "p_recEff_dzHS", "p_trackstdz0_eta", "p_tracketa_dz"};

    TFile *_file0 = new TFile("50ns.root");
    TFile *_file1 = new TFile("25ns.root");

    for (int i=0; i<plots.size(); i++) {
        vector<TH1F*> hist = {};
        vector<TString> histName = {};
        hist.push_back((TH1F*)((TCanvas*)_file0->Get(plots[i])));
        histName.push_back("ExtBrl_4");
        hist.push_back((TH1F*)((TCanvas*)_file1->Get(plots[i])));
        histName.push_back("InclBrl_4");
        vector<int> colors = {kRed, kOrange, kGreen, kGray, kBlue, kCyan, kYellow, kBlack};
        THStack *hs = new THStack("hs","");
        std::cout<<plots[i]<<std::endl;
        for (int i=0; i<hist.size(); i++) {
            hist[i]->SetLineColor(colors[i]);
            hs->Add(hist[i]);
        }
        //hs->SetTitle(((TH1F*)((TCanvas*)_file0->Get(plots[i])))->GetTitle());
        hs->SetTitle(hist[0]->GetTitle());
        TCanvas* canvas = new TCanvas("canvas","",696,472);
        hs->Draw("nostack hist e1");
        TLegend* leg = new TLegend(0.75, 0.8, 0.9, 0.9);
        for (int i=0;i<histName.size();i++) {
            leg->AddEntry(hist[i], histName[i], "f");
        }
        leg->Draw();
        ATLASLabel(0.2,0.85,"Simulation Internal");
        //myText(0.2,0.75,1,"Simulation #sqrt{s} = 14 TeV");
        //myText(0.2,0.65,1,"ttbar, <#mu> = 200");
        canvas->Print(plots[i] + ".pdf");
        delete canvas;
    }
}
