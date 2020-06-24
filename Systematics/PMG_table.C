#include "/home/matt/Projects/PhotonMethod/Main/Settings.cpp"

void PMG_table() {
    // Options
    TChain chain("Zjets_NoSys");
    chain.Add("/public/data/SUSY_Systematics/Skimmed/Zjets/mc16a_Zjets_merged_processed.root");
    chain.Add("/public/data/SUSY_Systematics/Skimmed/Zjets/mc16cd_Zjets_merged_processed.root");
    chain.Add("/public/data/SUSY_Systematics/Skimmed/Zjets/mc16e_Zjets_merged_processed.root");

    double binC[8] = {12,31,46,61,71,81,101,201};
    double binLow[10] = {12,41,61,81,101,141,201,301,401,501};
    double binMed[6] = {12,81,101,201,301,601};
    double binHigh[4] = {12,101,301,1001};
    double binVR3L[6] = {12,81,101,201,301,601};

    vector<string> region_names = {"SRC", "SRLow", "SRMed", "SRHigh", "SRLowZ", "SRMedZ", "SRHighZ",
                                   //"CRC", "CRLow", "CRMed", "CRHigh", "CRLowZ", "CRMedZ", "CRHighZ", 
                                   "VRC", "VRLow", "VRMed", "VRHigh", "VRLowZ", "VRMedZ", "VRHighZ"}; 

    TCut lumi = "(RandomRunNumber<320000 ? 36200 : (RandomRunNumber>320000 && RandomRunNumber<348000) ? 44300 : 58500)";
    TCut MC_weight = "genWeight*eventWeight*leptonWeight*jvtWeight*bTagWeight*pileupWeight*globalDiLepTrigSF";

    vector<string> systematics = {"scale", "PDF"};
    //systematics = {"ttbar_scale", "ttbar_PDF"};

    // Table Production
    vector<pair <TString, TCut>> regions;
    for (auto region_name : region_names) {
        regions.push_back(make_pair(region_name.c_str(), cuts::selections[region_name]));
    }

    for (auto systematic : systematics) {
        vector<string> LHE3Weights;
        if (systematic == "scale") {
            LHE3Weights.push_back("MUR1_MUF1_PDF261000");
            LHE3Weights.push_back("MUR0_5_MUF0_5_PDF261000");
            LHE3Weights.push_back("MUR0_5_MUF1_PDF261000");
            LHE3Weights.push_back("MUR1_MUF0_5_PDF261000");
            LHE3Weights.push_back("MUR1_MUF2_PDF261000");
            LHE3Weights.push_back("MUR2_MUF1_PDF261000");
            LHE3Weights.push_back("MUR2_MUF2_PDF261000");
        }
        else if (systematic == "PDF") {
            LHE3Weights.push_back("MUR1_MUF1_PDF261000");
            LHE3Weights.push_back("MUR1_MUF1_PDF13000");
            LHE3Weights.push_back("MUR1_MUF1_PDF25300");
            //LHE3Weights.push_back("MUR1_MUF1_PDF269000");
            //LHE3Weights.push_back("MUR1_MUF1_PDF270000");
            //for (int i=261001;i<261101;i++) LHE3Weights.push_back("MUR1_MUF1_PDF" + to_string(i));
        }
        else if (systematic == "ttbar_scale") {
            LHE3Weights.push_back("nominal");
            LHE3Weights.push_back("muR0p5,muF0p5");
            LHE3Weights.push_back("muR0p5,muF1");
            LHE3Weights.push_back("muR1,muF0p5");
            LHE3Weights.push_back("muR0p5,muF2");
            LHE3Weights.push_back("muR2,muF0p5");
            LHE3Weights.push_back("muR1,muF2");
            LHE3Weights.push_back("muR2,muF1");
            LHE3Weights.push_back("muR2,muF2");
        }
        else if (systematic == "ttbar_PDF") {
            LHE3Weights.push_back("nominal");
            LHE3Weights.push_back("PDFset265000");
            LHE3Weights.push_back("PDFset266000");
        }

        for (auto region : regions) {
            TCut cut_reg = region.second;
            //cout << "Printing Systematics for Region " << region.first << ": " << cut_reg << endl;
            cout << "Printing Systematics for Region " << region.first << endl;

            vector<TH1F*> hists, hists_err;	

            int binSize = 0;

            if (region.first.Index("RC") != -1) binSize = sizeof(binC)/sizeof(binC[0])-1;
            else if (region.first.Index("Low") != -1) binSize = sizeof(binLow)/sizeof(binLow[0])-1;
            else if (region.first.Index("Med") != -1) binSize = sizeof(binMed)/sizeof(binMed[0])-1;
            else if (region.first.Index("High") != -1) binSize = sizeof(binHigh)/sizeof(binHigh[0])-1;

            for (auto LHE3Weight : LHE3Weights) {
                cout << "Working on Weight " << LHE3Weight << endl;

                TString hist_name = ("hists_" + LHE3Weight).c_str();
                if (region.first.Index("RC") != -1) hists.push_back(new TH1F(hist_name,"",binSize,binC));
                else if (region.first.Index("Low") != -1) hists.push_back(new TH1F(hist_name,"",binSize,binLow));
                else if (region.first.Index("Med") != -1) hists.push_back(new TH1F(hist_name,"",binSize,binMed));
                else if (region.first.Index("High") != -1) hists.push_back(new TH1F(hist_name,"",binSize,binHigh));

                TCut LHE_branch = ("LHE3Weight_" + LHE3Weight).c_str();
                chain.Draw(("mll>>hists_" + LHE3Weight).c_str(), cut_reg*lumi*MC_weight*LHE_branch, "goff");
            }

            int hist_i = 0;
            cout << "Producing Uncertainty Histograms" << endl;
            for (auto hist : hists) {
                if (hist_i == 0) {
                    hist_i++;
                    continue;
                }
                hists_err.push_back((TH1F*)(hist->Clone(("hists_" + LHE3Weights[hist_i++] + "_err").c_str())));
            }

            cout << "Finding Maximum Uncertainty" << endl;
            float err_max_all = 0;
            for (auto hist_err : hists_err) {
                cout << "Finding Uncertainty for Histogram" << endl;
                hist_err->Add(hists[0],-1);
                hist_err->Divide(hists[0]);

                float err_max_single = 0;
                float err_max_single_sec = 0;
                for (int i=0; i<hist_err->GetNbinsX()+1; i++) {
                    cout << "bin " << i << ": " << hist_err->GetBinContent(i+1) << endl;
                    if (fabs(hist_err->GetBinContent(i+1)) > err_max_single) {
                        err_max_single_sec = err_max_single;
                        err_max_single = fabs(hist_err->GetBinContent(i+1));
                    } else if (fabs(hist_err->GetBinContent(i+1)) > err_max_single_sec) {
                        err_max_single_sec = fabs(hist_err->GetBinContent(i+1));
                    }
                    cout << "err_max_single: " << err_max_single << ", err_max_single_sec: " << err_max_single_sec << endl;
                }
                if (err_max_single_sec < err_max_single * .9 && err_max_single_sec > 1e-9)
                    err_max_single = err_max_single_sec;
                if (err_max_single > err_max_all)
                    err_max_all = err_max_single;
            }
            cout << "Region " << region.first << " " << systematic << " uncertainty: " << err_max_all << endl;

            for (auto hist : hists) {delete hist;}
            for (auto hist_err : hists_err) {delete hist_err;}
        }	
    }
}
