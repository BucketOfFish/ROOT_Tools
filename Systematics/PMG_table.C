void PMG_table() {

	TChain chain("Zjets_NoSys");
	chain.Add("/eos/user/r/rtombs/2Ljets/LHEmerged/SUSY2_Bkgs_mc16a/Zjets_merged_processed.root");
	chain.Add("/eos/user/r/rtombs/2Ljets/LHEmerged/SUSY2_Bkgs_mc16cd/Zjets_merged_processed.root");
	chain.Add("/eos/user/r/rtombs/2Ljets/LHEmerged/SUSY2_Bkgs_mc16e/Zjets_merged_processed.root");

	vector<pair <TString,TString>> Regions;
	vector<TString> LHE3Weight;

	double binC[8] = {12,31,46,61,71,81,101,201};
	double binLow[10] = {12,41,61,81,101,141,201,301,401,501};
	double binMed[6] = {12,81,101,201,301,601};
	double binHigh[4] = {12,101,301,1001};
	double binVR3L[6] = {12,81,101,201,301,601};

	//TString presel_cuts = "nLep_base==2 && mll > 12 && trigMatch_2LTrigOR && lepPt[0] > 25 && lepPt[1] > 25 && nJet30 >= 2 && met_Et > 150 && mt2leplsp_0 > 50 && abs(minDPhi2JetsMet) > 0.4 && Ptll > 40 && lepCharge[0] != lepCharge[1]";
	//new
	TString presel_cuts = "nLep_base==2 && mll > 12 && trigMatch_2LTrigOR && lepPt[0] > 25 && lepPt[1] > 25 && nJet30 >= 2 && met_Et > 150 && mt2leplsp_0 > 50 && abs(minDPhi2JetsMet) < 0.4 && Ptll > 40 && lepCharge[0] != lepCharge[1]";
	TString njet2_cut = "nJet30 >= 2";
	TString njet4_cut = "nJet30 >= 4";
	TString df_cut = "(lepFlavor[0] != lepFlavor[1])";
	TString MC_Cut = "&& (lepIsPR[0] == 1 && lepIsPR[1] == 1) && nLep_signal == 2";

    //Signal Regions
    Regions.push_back(make_pair("SRC", presel_cuts + " && met_Et > 250 && Ptll < 100 && mt2leplsp_0 > 90 && met_Sign > 10 "));
    Regions.push_back(make_pair("CRC", df_cut + " && " + presel_cuts + " && met_Et > 250 && Ptll < 100 && mt2leplsp_0 > 90 && met_Sign > 10 "));
    //>=2 jets
    Regions.push_back(make_pair("SRLow" , presel_cuts + " && " + njet2_cut + " && met_Et > 250 && Ptll < 500 && mt2leplsp_0 > 100 && Ht30 > 250 " ));
    Regions.push_back(make_pair("SRMed" , presel_cuts + " && " + njet2_cut + " && met_Et > 300 && Ptll < 800 && mt2leplsp_0 > 75 && Ht30 > 500 " ));
    Regions.push_back(make_pair("SRHigh", presel_cuts + " && " + njet2_cut + " && met_Et > 300 && mt2leplsp_0 > 75 && Ht30 > 800 " ));
    Regions.push_back(make_pair("CRLow" , df_cut + " && " +presel_cuts + " && " + njet2_cut + " && met_Et > 250 && Ptll < 500 && mt2leplsp_0 > 100 && Ht30 > 250 " ));
    Regions.push_back(make_pair("CRMed" , df_cut + " && " +presel_cuts + " && " + njet2_cut + " && met_Et > 300 && Ptll < 800 && mt2leplsp_0 > 75 && Ht30 > 500 " ));
    Regions.push_back(make_pair("CRHigh", df_cut + " && " +presel_cuts + " && " + njet2_cut + " && met_Et > 300 && mt2leplsp_0 > 75 && Ht30 > 800 " ));
    //on-Z Regions
    Regions.push_back(make_pair("SRZLow" ,  presel_cuts + " && " + njet4_cut + " && met_Et > 250 && Ptll < 500 && mt2leplsp_0 > 100 && Ht30 > 250 && mll>81 && mll < 101 " ));
    Regions.push_back(make_pair("CRZLow" , df_cut + " && " + presel_cuts + " && " + njet4_cut + " && met_Et > 250 && Ptll < 500 && mt2leplsp_0 > 100 && Ht30 > 250 && mll>81 && mll < 101 " ));
    Regions.push_back(make_pair("SRZMed" ,  presel_cuts + " && " + njet4_cut + " && met_Et > 300 && Ptll < 800 && mt2leplsp_0 > 75 && Ht30 > 500 && mll>81 && mll < 101 " ));
    Regions.push_back(make_pair("CRZMed" , df_cut + " && " + presel_cuts + " && " + njet4_cut + " && met_Et > 300 && Ptll < 800 && mt2leplsp_0 > 75 && Ht30 > 500 && mll>81 && mll < 101 " ));
    Regions.push_back(make_pair("SRZHigh",  presel_cuts + " && " + njet4_cut + " && met_Et > 300 && mt2leplsp_0 > 75 && Ht30 > 800 && mll>81 && mll < 101 " ));
    Regions.push_back(make_pair("CRZHigh", df_cut + " && " + presel_cuts + " && " + njet4_cut + " && met_Et > 300 && mt2leplsp_0 > 75 && Ht30 > 800 && mll>81 && mll < 101 " ));
    //Validation Regions
    Regions.push_back(make_pair("VRC"    ,  presel_cuts + " && met_Et >  150 && met_Et < 250 && Ptll < 100 && mt2leplsp_0 > 90 && met_Sign > 10 " ));
    //>=2 jets
    Regions.push_back(make_pair("VRLow"  ,  presel_cuts + " && " + njet2_cut + " && met_Et >  150 && met_Et < 250 && Ptll < 500 && mt2leplsp_0 > 100 && Ht30 > 250 " ));
    Regions.push_back(make_pair("VRMed"  ,  presel_cuts + " && " + njet2_cut + " && met_Et >  150 && met_Et < 250 && Ptll < 800 && mt2leplsp_0 > 75 && Ht30 > 500 " ));
    Regions.push_back(make_pair("VRHigh" ,  presel_cuts + " && " + njet2_cut + " && met_Et >  150 && met_Et < 250 && mt2leplsp_0 > 75 && Ht30 > 800 " ));
    //on-Z Regions >=6 jets
    Regions.push_back(make_pair("VRZLow" ,  presel_cuts + " && " + njet4_cut + " && met_Et >  150 && met_Et < 250 && Ptll < 500 && mt2leplsp_0 > 100 && Ht30 > 250 && mll>81 && mll < 101 " ));
    Regions.push_back(make_pair("VRZMed" ,  presel_cuts + " && " + njet4_cut + " && met_Et >  150 && met_Et < 250 && Ptll < 800 && mt2leplsp_0 > 75 && Ht30 > 500 && mll>81 && mll < 101 " ));
    Regions.push_back(make_pair("VRZHigh",  presel_cuts + " && " + njet4_cut + " && met_Et >  150 && met_Et < 250 && mt2leplsp_0 > 75 && Ht30 > 800 && mll>81 && mll < 101 " ));

	TCut lumi = "(RandomRunNumber < 320000 ? 36200 : (RandomRunNumber > 320000 && RandomRunNumber < 348000) ? 44300 : 58500) * ((lepFlavor[0] == lepFlavor[1]) - (lepFlavor[0] != lepFlavor[1]))";
    TCut weight = "genWeight*eventWeight*leptonWeight*jvtWeight*bTagWeight*pileupWeight*globalDiLepTrigSF";

    //cout << "Lumi: " << lumi << endl;
	//cout << "Weight: " << weight << endl << endl;

	//=======================
	//diboson
	//=======================

	//Varied Scales

	//LHE3Weight.push_back("MUR1_MUF1_PDF261000");
	//LHE3Weight.push_back("MUR0p5_MUF0p5_PDF261000");
	//LHE3Weight.push_back("MUR0p5_MUF1_PDF261000");
	//LHE3Weight.push_back("MUR1_MUF0p5_PDF261000");
	//LHE3Weight.push_back("MUR1_MUF2_PDF261000");
	//LHE3Weight.push_back("MUR2_MUF1_PDF261000");
	//LHE3Weight.push_back("MUR2_MUF2_PDF261000");

	//Varied pdf

	LHE3Weight.push_back("MUR1_MUF1_PDF261000");
    LHE3Weight.push_back("MUR1_MUF1_PDF13000");
    LHE3Weight.push_back("MUR1_MUF1_PDF25300");
	LHE3Weight.push_back("MUR1_MUF1_PDF269000");
	LHE3Weight.push_back("MUR1_MUF1_PDF270000");
	//for (int i=261001;i<261101;i++) LHE3Weight.push_back("MUR1_MUF1_PDF" + to_string(i));

	//=======================
	//ttbar
	//=======================

	//Varied Scales

	//LHE3Weight.push_back("nominal");
	//LHE3Weight.push_back("muR0p5,muF0p5");
	//LHE3Weight.push_back("muR0p5,muF1");
	//LHE3Weight.push_back("muR1,muF0p5");
	//LHE3Weight.push_back("muR0p5,muF2");
	//LHE3Weight.push_back("muR2,muF0p5");
	//LHE3Weight.push_back("muR1,muF2");
	//LHE3Weight.push_back("muR2,muF1");
	//LHE3Weight.push_back("muR2,muF2");

	//Varied pdf

	//LHE3Weight.push_back("nominal");
	//LHE3Weight.push_back("PDFset265000");
	//LHE3Weight.push_back("PDFset266000");


	for (vector<pair <TString,TString>>::iterator it_reg = Regions.begin(); it_reg != Regions.end(); ++it_reg) {

		TCut cut_reg = (TCut)((it_reg->second) + MC_Cut);
        cout << "Region " << it_reg->first << ": " << cut_reg << endl;
	    
		vector<TH1F*> hists;
		vector<TH1F*> hists_err;	

		int binSize = 0;

		if (it_reg->first.Index("RC") != -1) binSize = sizeof(binC)/sizeof(binC[0])-1;
		else if (it_reg->first.Index("Low") != -1) binSize = sizeof(binLow)/sizeof(binLow[0])-1;
		else if (it_reg->first.Index("Med") != -1) binSize = sizeof(binMed)/sizeof(binMed[0])-1;
		else if (it_reg->first.Index("High") != -1) binSize = sizeof(binHigh)/sizeof(binHigh[0])-1;

		for (vector<TString>::iterator it = LHE3Weight.begin(); it != LHE3Weight.end(); ++it) {

			if (it_reg->first.Index("RC") != -1) hists.push_back(new TH1F("hists_" + (*it),"",binSize,binC));
			else if (it_reg->first.Index("Low") != -1) hists.push_back(new TH1F("hists_" + (*it),"",binSize,binLow));
			else if (it_reg->first.Index("Med") != -1) hists.push_back(new TH1F("hists_" + (*it),"",binSize,binMed));
			else if (it_reg->first.Index("High") != -1) hists.push_back(new TH1F("hists_" + (*it),"",binSize,binHigh));

			chain.Draw("mll>>hists_" + (*it),cut_reg*lumi*weight*("LHE3Weight_" + (*it))),"goff";
		}

		for (vector<TH1F*>::iterator it = hists.begin(); it != hists.end(); ++it) {
            if (distance(hists.begin(), it) > 0)
                hists_err.push_back((TH1F*)((*it)->Clone("hists_" + LHE3Weight.at(distance(hists.begin(), it)) + "_err")));
		}

		float err_max_all = 0;

		for (vector<TH1F*>::iterator it = hists_err.begin(); it != hists_err.end(); ++it) {
            (*it)->Add(hists.at(0),-1);
            (*it)->Divide(hists.at(0));

			float err_max_single = 0;
			float err_max_single_sec = 0;
			for (int i=0; i<(*it)->GetNbinsX()+1; i++) {
				cout << "bin " << i << ": " << (*it)->GetBinContent(i+1) << endl;
				if (fabs((*it)->GetBinContent(i+1)) > err_max_single) {
					err_max_single_sec = err_max_single;
					err_max_single = fabs((*it)->GetBinContent(i+1));
				} else if (fabs((*it)->GetBinContent(i+1)) > err_max_single_sec) {
					err_max_single_sec = fabs((*it)->GetBinContent(i+1));
				}
				//cout << "err_max_single: " << err_max_single << ", err_max_single_sec: " << err_max_single_sec << endl;
			}
			if (err_max_single_sec < err_max_single * .9 && err_max_single_sec > 1e-9) err_max_single = err_max_single_sec;
			//cout << LHE3Weight.at(distance(hists_err.begin(), it)+1) + " uncertainty: " << err_max_single << endl;

			if (err_max_single > err_max_all) err_max_all = err_max_single;
		}

		//cout << "Region " << it_reg->first << " scale uncertainty: " << err_max_all << endl;
        cout << "Region " << it_reg->first << " PDF uncertainty: " << err_max_all << endl;

		for(vector<TH1F*>::iterator it = hists.begin(); it != hists.end(); ++it) {
			delete *it;
		}

		for(vector<TH1F*>::iterator it = hists_err.begin(); it != hists_err.end(); ++it) {
			delete *it;
		}

	}	
	
}
