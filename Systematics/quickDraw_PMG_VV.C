void quickDraw_PMG_VV() {

	TChain chain("Zjets_NoSys");
	chain.Add("/eos/user/r/rtombs/2Ljets/LHEmerged/SUSY2_Bkgs_mc16a/Zjets_merged_processed.root");
	chain.Add("/eos/user/r/rtombs/2Ljets/LHEmerged/SUSY2_Bkgs_mc16cd/Zjets_merged_processed.root");
	chain.Add("/eos/user/r/rtombs/2Ljets/LHEmerged/SUSY2_Bkgs_mc16e/Zjets_merged_processed.root");

	vector<TH1F*> hist;
	vector<TH1F*> error;	

	TCut l_Base = "trigMatch_2LTrigOR && nJet30 >= 1 && lepPt[1] > 25.";
	TCut l_2lep = l_Base + "nLep_signal == 2 && nLep_base == 2 && lepCharge[0] != lepCharge[1] && met_Sign > 6. && 12. < mll && mll < 150.";
	TCut l_SF = "lepFlavor[0] == lepFlavor[1]";
	TCut l_may_b = "nBJet20_MV2c10_FixedCutBEff_77 <= 1";
	TCut MC_Cut = "(lepIsPR[0] == 1 && lepIsPR[1] == 1) && nLep_signal == 2";

	TCut mycut = l_2lep + l_SF + l_may_b + MC_Cut;

	TCut lumi = "(RandomRunNumber < 320000 ? 36200 : (RandomRunNumber > 320000 && RandomRunNumber < 348000) ? 44300 : 58500) * ((lepFlavor[0] == lepFlavor[1]) - (lepFlavor[0] != lepFlavor[1]))";
    TCut weight = "genWeight*eventWeight*leptonWeight*jvtWeight*bTagWeight*pileupWeight*globalDiLepTrigSF";

    cout << "Cut: " << mycut << endl;
    cout << "Lumi: " << lumi << endl;
	cout << "Weight: " << weight << endl;

	TCanvas* c1 = new TCanvas();
	TPad *pad1 = new TPad("pad1", "pad1", 0, 0.2, 1, 1.0);
	pad1->SetBottomMargin(0.1); // Upper and lower plot are joined
	pad1->SetGridx();         // Vertical grid
	pad1->Draw("GOFF");             // Draw the upper pad: pad1
	pad1->cd();               // pad1 becomes the current pad

	// =======================
	// Varied Scales
	// =======================

     vector<TString> LHE3Weight_Scale;

     LHE3Weight_Scale.push_back("MUR1_MUF1_PDF261000");
     LHE3Weight_Scale.push_back("MUR0p5_MUF0p5_PDF261000");
     LHE3Weight_Scale.push_back("MUR0p5_MUF1_PDF261000");
     LHE3Weight_Scale.push_back("MUR1_MUF0p5_PDF261000");
     LHE3Weight_Scale.push_back("MUR1_MUF2_PDF261000");
     LHE3Weight_Scale.push_back("MUR2_MUF1_PDF261000");
     LHE3Weight_Scale.push_back("MUR2_MUF2_PDF261000");
    
     TLegend* leg = new TLegend(0.7,0.5,1,0.8);

     for(vector<TString>::iterator it = LHE3Weight_Scale.begin(); it != LHE3Weight_Scale.end(); ++it) {
         hist.push_back(new TH1F("hVV_" + (*it),"",30,0,160));
         tVV.Draw("mll>>hVV_" + (*it),mycut*lumi*weight*("LHE3Weight_" + (*it)));
     }

     for(vector<TH1F*>::iterator it = hist.begin(); it != hist.end(); ++it) {
         (*it)->SetLineColor(distance(hist.begin(), it) + 1);
         leg->AddEntry(*it,LHE3Weight_Scale.at(distance(hist.begin(), it)),"lp");
         if (distance(hist.begin(), it) == 0) {
             (*it)->SetStats(0);
             (*it)->Draw("PFC HIST");
             (*it)->SetTitle("Diboson - Varied Scales"); // Varied Scales
             (*it)->GetXaxis()->SetTitle("m(ll) [GeV]");
         }
         else {
             (*it)->Draw("HIST SAME");
             error.push_back((TH1F*)((*it)->Clone("hVV_" + LHE3Weight_Scale.at(distance(hist.begin(), it)) + "_err")));
         }
     }

	// =======================
	// Varied pdf
	// =======================

	vector<TString> LHE3Weight_PDF;

	LHE3Weight_PDF.push_back("MUR1_MUF1_PDF261000");
	LHE3Weight_PDF.push_back("MUR1_MUF1_PDF13000");
	LHE3Weight_PDF.push_back("MUR1_MUF1_PDF25300");
	LHE3Weight_PDF.push_back("MUR1_MUF1_PDF269000");
	LHE3Weight_PDF.push_back("MUR1_MUF1_PDF270000");

	for (int i=261001;i<261101;i++) LHE3Weight_PDF.push_back("MUR1_MUF1_PDF" + to_string(i));
	
	TLegend* leg = new TLegend(0.6,0.65,1,0.8); 

	for(vector<TString>::iterator it = LHE3Weight_PDF.begin(); it != LHE3Weight_PDF.end(); ++it) {
		hist.push_back(new TH1F("hVV_" + (*it),"",30,0,160));
		chain.Draw("mll>>hVV_" + (*it),mycut*lumi*weight*("LHE3Weight_" + (*it))),"GOFF";
	}

	for(vector<TH1F*>::iterator it = hist.begin(); it != hist.end(); ++it) {
		// (*it)->SetLineColor(distance(hist.begin(), it) + 1);
		leg->AddEntry(*it,LHE3Weight_PDF.at(distance(hist.begin(), it)),"lp");
		if (distance(hist.begin(), it) == 0) {
			(*it)->SetStats(0);
			(*it)->Draw("PFC HIST GOFF");
			(*it)->SetTitle("Diboson - Varied PDF"); // Varied PDF
			(*it)->GetXaxis()->SetTitle("m(ll) [GeV]");
		}
		else {
			(*it)->Draw("HIST SAME GOFF");
			error.push_back((TH1F*)((*it)->Clone("hVV_" + LHE3Weight_PDF.at(distance(hist.begin(), it)) + "_err")));
		}
	}

	leg->Draw("GOFF");

	c1->cd();
	TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.2);
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.2);
	pad2->SetGridx();
	pad2->Draw("GOFF");
	pad2->cd();

	float err_max_all = 0;

	for(vector<TH1F*>::iterator it = error.begin(); it != error.end(); ++it) {
		(*it)->Add(hist.at(0),-1);
		(*it)->Divide(hist.at(0));
		(*it)->SetLineColor(distance(error.begin(), it)+2);

		if (distance(erroerror.begin(), it) == 0) {
			// (*it)->SetMinimum(-0.4); // Varied Scale
			// (*it)->SetMaximum(0.4);

			(*it)->SetMinimum(-0.15); // Varied PDF
			(*it)->SetMaximum(0.15);
			(*it)->Sumw2();
			(*it)->SetStats(0);

			(*it)->Draw("EP GOFF");

			(*it)->SetTitle("");
			(*it)->GetYaxis()->SetNdivisions(505);
			(*it)->GetYaxis()->SetTitleSize(20);
			(*it)->GetYaxis()->SetTitleFont(43);
			(*it)->GetYaxis()->SetTitleOffset(1.55);
			(*it)->GetYaxis()->SetLabelFont(43);
			(*it)->GetYaxis()->SetLabelSize(15);

			(*it)->GetXaxis()->SetTitleSize(20);
			(*it)->GetXaxis()->SetTitleFont(43);
			(*it)->GetXaxis()->SetTitleOffset(4.);
			(*it)->GetXaxis()->SetLabelFont(43);
			(*it)->GetXaxis()->SetLabelSize(15);
		}
		else (*it)->Draw("EP SAME GOFF");

		float err_max_single, err_max_single_sec = 0;
		for (int i=0; i<(*it)->GetNbinsX()+1; i++) {
			if (fabs((*it)->GetBinContent(i+1)) > err_max_single) {
				err_max_single_sec = err_max_single;
				err_max_single = fabs((*it)->GetBinContent(i+1));
			} else if (fabs((*it)->GetBinContent(i+1)) > err_max_single_sec) {
				err_max_single_sec = fabs((*it)->GetBinContent(i+1));
			}
			// cout << "bin " << i << ": " << (*it)->GetBinContent(i+1) << ", err_max_single: " << err_max_single << ", err_max_single_sec: " << err_max_single_sec << endl; 
		}
		if (err_max_single_sec < err_max_single * .9) err_max_single = err_max_single_sec;
		// cout << LHE3Weight_Scale.at(distance(error.begin(), it)+1) + " uncertainty: " << err_max_single << endl << endl << endl; // Varied Scales
		cout << LHE3Weight_PDF.at(distance(error.begin(), it)+1) + " uncertainty: " << err_max_single << endl << endl << endl; // Varied PDF

		if (err_max_single > err_max_all) err_max_all = err_max_single;

	}

     cout << "scale uncertainty: " << err_max_all << endl;
	cout << "PDF uncertainty: " << err_max_all << endl;
}
