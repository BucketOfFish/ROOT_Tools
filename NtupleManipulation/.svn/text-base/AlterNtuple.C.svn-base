#include "CalcGenericMT2/src/MT2_ROOT.h"

// Copy over event count histogram when remaking tree
void CopyEventCountHist(TFile *file, TFile *newfile) {
    TH1F* hist = (TH1F*)file->Get("EventCountHist");
    hist->Write();
}

void KeepEvents(TString filename, TString savefilename, TString treename, int events);
void KeepBranches(TString filename, TString savefilename, TString treename, vector<TString> branches);
void RemoveBranches(TString filename, TString savefilename, TString treename, vector<TString> branches, int events=-1);
void AddBranch(TString filename, TString savefilename, TString treename, int option=-1);
void AddEventCountBranch(TString filename, TString savefilename, TString treename);
void AddTruthLeptonMatchingBranch(TString filename, TString savefilename, TString treename, int option=-1);
void AddMT2Branches(TString filename, TString savefilename, TString treename);
void AddWZFlavorBranches(TString filename, TString savefilename, TString treename, int option=-1);
void CopyEventCountHist(TFile *file, TFile *newfile);

// Keep only the given number of events
void KeepEvents(TString filename, TString savefilename, TString treename, int events) {
    RemoveBranches(filename, savefilename, treename, vector<TString> {}, events);
}

// Keep only the listed branches
void KeepBranches(TString filename, TString savefilename, TString treename, vector<TString> branches) {

    TFile *file = new TFile(filename);
    TTree *tree = (TTree*)file->Get(treename);

    tree->SetBranchStatus("*",0);
    for (int i=0; i<branches.size(); i++) {
        tree->SetBranchStatus(branches[i],1);
    }

    TFile *newfile = new TFile(savefilename, "recreate");
    TTree *newtree = tree->CloneTree();

    CopyEventCountHist(file, newfile);

    //newtree->Print();
    newfile->Write();
    delete file;
    delete newfile;
}

// Remove only the listed branches
void RemoveBranches(TString filename, TString savefilename, TString treename, vector<TString> branches, int events=-1) {

    TFile *file = new TFile(filename);
    TTree *tree = (TTree*)file->Get(treename);

    tree->SetBranchStatus("*",1);
    for (int i=0; i<branches.size(); i++) {
        tree->SetBranchStatus(branches[i],0);
    }

    TFile *newfile = new TFile(savefilename, "recreate");
    if (events>-1)
        TTree *newtree = tree->CloneTree(events);
    else
        TTree *newtree = tree->CloneTree();

    CopyEventCountHist(file, newfile);
    
    //newtree->Print();
    newfile->Write();
    delete file;
    delete newfile;
}

// Add a branch (template)
void AddBranch(TString filename, TString savefilename, TString treename, int option=-1) {

    TFile *file = new TFile(filename);
    TTree *tree = (TTree*)file->Get(treename);

    TFile *newfile = new TFile(savefilename, "recreate");
    TTree *newtree = tree->CloneTree(0);

    //branches from old tree
    int lep_n;
    tree->SetBranchAddress("lep_n",&lep_n);
    vector<double> *lep_pT = 0;
    tree->SetBranchAddress("lep_pT",&lep_pT);

    //new branches
    int pass2LCut=0;
    newtree->Branch("pass2LCut",&pass2LCut);
    newtree->Branch("copy_lep_pT",&lep_pT);
    vector<double> double_lep_pT;
    newtree->Branch("double_lep_pT",&double_lep_pT);

    //fill new branches
    int nentries = tree->GetEntries();
    for (int i=0;i<nentries;i++) {
        tree->GetEntry(i);
        //if (i%10000==0) std::cout<<i/1000<<"k out of "<<nentries/1000<<"k entries"<<std::endl;

        pass2LCut = 0;
        if (lep_n >= 2)
            pass2LCut = 1;
        double_lep_pT = {};
        for (int j=0; j<lep_pT->size(); j++)
            double_lep_pT.push_back(lep_pT->at(j)*2);

        newtree->Fill();
    }

    CopyEventCountHist(file, newfile);

    //newtree->Print();
    newfile->Write();
    delete file;
    delete newfile;
}

// Add branch for number of weighted events
void AddEventCountBranch(TString filename, TString savefilename, TString treename) {

    //NOT COMPLETE
    //TFile *file = new TFile(filename);
    //TTree *tree = (TTree*)file->Get(treename);

    //TFile *newfile = new TFile(savefilename, "recreate");
    //TTree *newtree = tree->CloneTree(0);

    ////new branches
    //float sumWeightedEvents = 0;
    //newtree->Branch("sumWeightedEvents",&sumWeightedEvents);

    ////fill new branches
    //int nentries = tree->GetEntries();
    //for (int i=0;i<nentries;i++) {
        //tree->GetEntry(i);
        ////if (i%10000==0) std::cout<<i/1000<<"k out of "<<nentries/1000<<"k entries"<<std::endl;

        //pass2LCut = 0;
        //if (lep_n >= 2)
            //pass2LCut = 1;
        //double_lep_pT = {};
        //for (int j=0; j<lep_pT->size(); j++)
            //double_lep_pT.push_back(lep_pT->at(j)*2);

        //newtree->Fill();
    //}

    //CopyEventCountHist(file, newfile);

    ////newtree->Print();
    //newfile->Write();
    //delete file;
    //delete newfile;
}

void AddTruthLeptonMatchingBranch(TString filename, TString savefilename, TString treename, int option=-1) {

    //incomplete function

    TFile *file = new TFile(filename);
    TTree *tree = (TTree*)file->Get(treename);

    TFile *newfile = new TFile(savefilename, "recreate");
    TTree *newtree = tree->CloneTree(0);

    //branches from old tree
    vector<double> *lep_pT = 0;
    tree->SetBranchAddress("lep_pT",&lep_pT);
    vector<double> *lep_phi = 0;
    tree->SetBranchAddress("lep_phi",&lep_phi);
    vector<double> *lep_eta = 0;
    tree->SetBranchAddress("lep_eta",&lep_eta);
    vector<int> *lep_pdgId = 0;
    tree->SetBranchAddress("lep_pdgId",&lep_pdgId);
    vector<double> *truthLepton_pT = 0;
    tree->SetBranchAddress("truthLepton_pT",&truthLepton_pT);
    vector<double> *truthLepton_phi = 0;
    tree->SetBranchAddress("truthLepton_phi",&truthLepton_phi);
    vector<double> *truthLepton_eta = 0;
    tree->SetBranchAddress("truthLepton_eta",&truthLepton_eta);
    vector<int> *truthLepton_pdgId = 0;
    tree->SetBranchAddress("truthLepton_pdgID",&truthLepton_pdgId);

    //new branches
    vector<int> *matchedRecoLeptonIndex =  0;
    newtree->Branch("matchedRecoLeptonIndex",&matchedRecoLeptonIndex);
    vector<int> *matchedTruthLeptonIndex =  0;
    newtree->Branch("matchedTruthLeptonIndex",&matchedTruthLeptonIndex);

    //fill new branches
    int nentries = tree->GetEntries();
    float dRThreshold = 0.2;
    for (int i=0;i<nentries;i++) {
        tree->GetEntry(i);
        //if (i%10000==0) std::cout<<i/1000<<"k out of "<<nentries/1000<<"k entries"<<std::endl;

        matchedRecoLeptonIndex->clear();
        matchedTruthLeptonIndex->clear();
        for (int k=0; k<truthLepton_phi->size(); k++) {
            int recoMatch = -1;
            float minDR = 100;
            TLorentzVector truthLep;
            truthLep.SetPtEtaPhiM(truthLepton_pT->at(k), truthLepton_eta->at(k), truthLepton_phi->at(k), 0);
            for (int j=0; j<lep_phi->size(); j++) {
                TLorentzVector recoLep;
                recoLep.SetPtEtaPhiM(lep_pT->at(j), lep_eta->at(j), lep_phi->at(j), 0);
                float newDR = truthLep.DeltaR(recoLep);
                if (newDR<minDR && newDR<dRThreshold && abs(lep_pdgId->at(j))==abs(truthLepton_pdgId->at(k))) {
                    minDR = newDR;
                    recoMatch = j;
                }
            }
            matchedRecoLeptonIndex->push_back(recoMatch);
        }
        //truth match may not exactly correspond with reco match
        for (int j=0; j<lep_phi->size(); j++) {
            int truthMatch = -1;
            float minDR = 100;
            TLorentzVector recoLep;
            recoLep.SetPtEtaPhiM(lep_pT->at(j), lep_eta->at(j), lep_phi->at(j), 0);
            for (int k=0; k<truthLepton_phi->size(); k++) {
                TLorentzVector truthLep;
                truthLep.SetPtEtaPhiM(truthLepton_pT->at(k), truthLepton_eta->at(k), truthLepton_phi->at(k), 0);
                float newDR = truthLep.DeltaR(recoLep);
                if (newDR<minDR && newDR<dRThreshold && abs(lep_pdgId->at(j))==abs(truthLepton_pdgId->at(k))) {
                    minDR = newDR;
                    truthMatch = k;
                }
            }
            matchedTruthLeptonIndex->push_back(truthMatch);
        }

        newtree->Fill();
    }

    CopyEventCountHist(file, newfile);

    //newtree->Print();
    newfile->Write();
    delete file;
    delete newfile;
}

void AddWZFlavorBranches(TString filename, TString savefilename, TString treename, int option=-1) {

    //incomplete function

    TFile *file = new TFile(filename);
    TTree *tree = (TTree*)file->Get(treename);

    TFile *newfile = new TFile(savefilename, "recreate");
    TTree *newtree = tree->CloneTree(0);

    //branches from old tree
    vector<int> *truthLepton_pdgId = 0;
    tree->SetBranchAddress("truthLepton_pdgID",&truthLepton_pdgId);
    vector<int> *truthLepton_parent_pdgId = 0;
    tree->SetBranchAddress("truthLepton_parent_pdgID",&truthLepton_parent_pdgId);
    int truthLepton_n = 0;
    tree->SetBranchAddress("truthLepton_n",&truthLepton_n);

    //new branches
    int Zflav =  0;
    newtree->Branch("Zflav",&Zflav);
    int Wflav =  0;
    newtree->Branch("Wflav",&Wflav);

    //fill new branches
    int nentries = tree->GetEntries();
    for (int i=0;i<nentries;i++) {
        tree->GetEntry(i);
        //if (i%10000==0) std::cout<<i/1000<<"k out of "<<nentries/1000<<"k entries"<<std::endl;

        Zflav = 0;
        Wflav = 0;

        if(truthLepton_n != 3) continue;

        if(truthLepton_pdgId->at(0) == truthLepton_pdgId->at(1)) {
            Zflav = truthLepton_pdgId->at(0);
            Wflav = truthLepton_pdgId->at(2);
        }
        if(truthLepton_pdgId->at(0) == truthLepton_pdgId->at(2)) {
            Zflav = truthLepton_pdgId->at(0);
            Wflav = truthLepton_pdgId->at(1);
        }
        if(truthLepton_pdgId->at(1) == truthLepton_pdgId->at(2)) {
            Zflav = truthLepton_pdgId->at(1);
            Wflav = truthLepton_pdgId->at(0);
        }

        newtree->Fill();
    }

    CopyEventCountHist(file, newfile);

    newfile->Write();
    delete file;
    delete newfile;
}

void AddMT2Branches(TString filename, TString savefilename, TString treename) {

    std::cout<<"Copying Tree"<<std::endl;
    if (filename!=savefilename)
        gROOT->ProcessLine(TString(".! cp ")+filename+TString(" ")+savefilename);

    TFile *file = new TFile(filename);
    TTree *tree = (TTree*)file->Get(treename);

    std::cout<<"Cloning Branches"<<std::endl;
    TFile *newfile = new TFile(savefilename, "recreate");
    TTree *newtree = tree->CloneTree(0);
    std::cout<<"Filling New Branches"<<std::endl;

    //branches from old tree
    vector<double> *lep_pT = 0;
    tree->SetBranchAddress("lep_pT",&lep_pT);
    vector<double> *lep_phi = 0;
    tree->SetBranchAddress("lep_phi",&lep_phi);
    vector<double> *lep_eta = 0;
    tree->SetBranchAddress("lep_eta",&lep_eta);
    vector<double> *jet_pT = 0;
    tree->SetBranchAddress("jet_pT",&jet_pT);
    vector<double> *jet_phi = 0;
    tree->SetBranchAddress("jet_phi",&jet_phi);
    vector<double> *jet_eta = 0;
    tree->SetBranchAddress("jet_eta",&jet_eta);
    vector<double> *jet_bMV2Weight = 0;
    tree->SetBranchAddress("jet_bMV2Weight",&jet_bMV2Weight);
    vector<double> *jet_btag = 0;
    tree->SetBranchAddress("jet_btag",&jet_btag);
    double MET;
    tree->SetBranchAddress("MET",&MET);
    double MET_phi;
    tree->SetBranchAddress("MET_phi",&MET_phi);
    vector<float> *BFromT_eta=0, *BFromT_phi=0, *BFromT_pT=0, *BFromT_M=0;
    tree->SetBranchAddress("BFromT_eta",&BFromT_eta);
    tree->SetBranchAddress("BFromT_phi",&BFromT_phi);
    tree->SetBranchAddress("BFromT_pT",&BFromT_pT);
    tree->SetBranchAddress("BFromT_M",&BFromT_M);
    vector<float> *lepFromT_eta=0, *lepFromT_phi=0, *lepFromT_pT=0, *lepFromT_M=0;
    tree->SetBranchAddress("lepFromT_eta",&lepFromT_eta);
    tree->SetBranchAddress("lepFromT_phi",&lepFromT_phi);
    tree->SetBranchAddress("lepFromT_pT",&lepFromT_pT);
    tree->SetBranchAddress("lepFromT_M",&lepFromT_M);

    //new branches
    float MT2W = -1;
    float MT2Top = -1;
    //float MT2Top2 = -1;
    //float MT2Top3 = -1;
    TBranch *b_MT2W = newtree->Branch("MT2W",&MT2W);
    TBranch *b_MT2Top = newtree->Branch("MT2Top",&MT2Top);
    //TBranch *b_MT2Top2 = newtree->Branch("MT2Top2",&MT2Top2);
    //TBranch *b_MT2Top3 = newtree->Branch("MT2Top3",&MT2Top3);
    //float top3lepjet1_pT, top3lepjet1_phi, top3lepjet1_eta, top3lepjet1_m;
    //TBranch *b_top3lepjet1_pT = newtree->Branch("top3lepjet1_pT",&top3lepjet1_pT);
    //TBranch *b_top3lepjet1_phi = newtree->Branch("top3lepjet1_phi",&top3lepjet1_phi);
    //TBranch *b_top3lepjet1_eta = newtree->Branch("top3lepjet1_eta",&top3lepjet1_eta);
    //TBranch *b_top3lepjet1_m = newtree->Branch("top3lepjet1_m",&top3lepjet1_m);
    //float top3lepjet2_pT, top3lepjet2_phi, top3lepjet2_eta, top3lepjet2_m;
    //TBranch *b_top3lepjet2_pT = newtree->Branch("top3lepjet2_pT",&top3lepjet2_pT);
    //TBranch *b_top3lepjet2_phi = newtree->Branch("top3lepjet2_phi",&top3lepjet2_phi);
    //TBranch *b_top3lepjet2_eta = newtree->Branch("top3lepjet2_eta",&top3lepjet2_eta);
    //TBranch *b_top3lepjet2_m = newtree->Branch("top3lepjet2_m",&top3lepjet2_m);
    vector<float> *dRRecoLepJet=0, *dPhiRecoLepJet=0, *dEtaRecoLepJet=0, *dRTruthLepJet=0, *dPhiTruthLepJet=0, *dEtaTruthLepJet=0;
    TBranch *b_dRRecoLepJet = newtree->Branch("dRRecoLepJet",&dRRecoLepJet);
    TBranch *b_dPhiRecoLepJet = newtree->Branch("dPhiRecoLepJet",&dPhiRecoLepJet);
    TBranch *b_dEtaRecoLepJet = newtree->Branch("dEtaRecoLepJet",&dEtaRecoLepJet);
    TBranch *b_dRTruthLepJet = newtree->Branch("dRTruthLepJet",&dRTruthLepJet);
    TBranch *b_dPhiTruthLepJet = newtree->Branch("dPhiTruthLepJet",&dPhiTruthLepJet);
    TBranch *b_dEtaTruthLepJet = newtree->Branch("dEtaTruthLepJet",&dEtaTruthLepJet);
    vector<float> *RecoMT2Top_pT=0, *RecoMT2Top_eta=0, *RecoMT2Top_phi=0, *RecoMT2Top_m=0;
    TBranch *b_RecoMT2Top_pT = newtree->Branch("RecoMT2Top_pT",&RecoMT2Top_pT);
    TBranch *b_RecoMT2Top_eta = newtree->Branch("RecoMT2Top_eta",&RecoMT2Top_eta);
    TBranch *b_RecoMT2Top_phi = newtree->Branch("RecoMT2Top_phi",&RecoMT2Top_phi);
    TBranch *b_RecoMT2Top_m = newtree->Branch("RecoMT2Top_m",&RecoMT2Top_m);


    //fill new branches
    int nentries = tree->GetEntries();
    for (int i=0;i<nentries;i++) {
        tree->GetEntry(i);
        if (i%10000==0) std::cout<<i/1000<<"k out of "<<nentries/1000<<"k entries"<<std::endl;

        MT2W = -1;
        MT2Top = -1;
        //MT2Top2 = -1;
        dRRecoLepJet->clear();
        dPhiRecoLepJet->clear();
        dEtaRecoLepJet->clear();
        dRTruthLepJet->clear();
        dPhiTruthLepJet->clear();
        dEtaTruthLepJet->clear();
        RecoMT2Top_pT->clear();
        RecoMT2Top_eta->clear();
        RecoMT2Top_phi->clear();
        RecoMT2Top_m->clear();


        if (lep_pT->size() < 2 || jet_pT->size() < 2) continue;

        if (lep_pT->size() == 2) {
            TLorentzVector lep1, lep2, METVec;
            lep1.SetPtEtaPhiM(lep_pT->at(0), lep_eta->at(0), lep_phi->at(0), 0);
            lep2.SetPtEtaPhiM(lep_pT->at(1), lep_eta->at(1), lep_phi->at(1), 0);
            METVec.SetPtEtaPhiM(MET, 0, MET_phi, 0);
            //both invisible particles (neutrinos) are assumed to have zero mass
            MT2W = ComputeMT2(lep1, lep2, METVec, 0, 0).Compute();

            //int jet1index = -1;
            //int jet2index = -1;
            int top2index1 = -1;
            int top2index2 = -1;
            //float weight1 = -5;
            //float weight2 = -5;

            for (int i=0; i<jet_pT->size(); i++) {
                if (jet_btag->at(i)>0){ 
                    if (top2index1==-1) top2index1=i;
                    else if (top2index2==-1) {
                        top2index2 = i;
                        break;
                    }
                }
                //if (jet_bMV2Weight->at(i)>weight1) {
                    //jet2index = jet1index;
                    //jet1index = i;
                    //weight2 = weight1;
                    //weight1 = jet_bMV2Weight->at(i);
                //}
                //else if (jet_bMV2Weight->at(i)>weight2) {
                    //jet2index = i;
                    //weight2 = jet_bMV2Weight->at(i);
                //}
            }
            for (int i=0; i<jet_pT->size(); i++) {
                if (jet_btag->at(i)==0) {
                    if (top2index1==-1) top2index1=i;
                    else if (top2index2==-1) {
                        top2index2 = i;
                        break;
                    }
                    else break;
                }
            }

            //TLorentzVector jet1, jet2, top2jet1, top2jet2, lepjet1, lepjet2, top2lepjet1, top2lepjet2, top3lepjet1, top3lepjet2;
            TLorentzVector top2jet1, top2jet2;

            //if (jet2index!=-1) {
                //jet1.SetPtEtaPhiM(jet_pT->at(jet1index), jet_eta->at(jet1index), jet_phi->at(jet1index), 0);
                //jet2.SetPtEtaPhiM(jet_pT->at(jet2index), jet_eta->at(jet2index), jet_phi->at(jet2index), 0);
                //if (jet1.DeltaR(lep1) < jet1.DeltaR(lep2)) {
                    //lepjet1 = jet1+lep1;
                    //lepjet2 = jet2+lep2;
                //}
                //else {
                    //lepjet1 = jet1+lep2;
                    //lepjet2 = jet2+lep1;
                //}
                //MT2Top = ComputeMT2(lepjet1, lepjet2, METVec, 0, 0).Compute();
            //}

            if (top2index2!=-1) {
                top2jet1.SetPtEtaPhiM(jet_pT->at(top2index1), jet_eta->at(top2index1), jet_phi->at(top2index1), 0);
                top2jet2.SetPtEtaPhiM(jet_pT->at(top2index2), jet_eta->at(top2index2), jet_phi->at(top2index2), 0);

                if (top2jet1.DeltaR(lep1) > top2jet1.DeltaR(lep2)) {
                    //top2lepjet1 = top2jet1+lep1;
                    //top2lepjet2 = top2jet2+lep2;
                //}
                //else {
                    //top2lepjet1 = top2jet1+lep2;
                    //top2lepjet2 = top2jet2+lep1;
                //}
                //MT2Top2 = ComputeMT2(top2lepjet1, top2lepjet2, METVec, 0, 0).Compute();

                //if (fabs((top2jet1+lep1).M() + (top2jet2+lep2).M() - 360) > fabs((top2jet2+lep1).M() + (top2jet1+lep2).M() - 360)) {
                    TLorentzVector placeholder = top2jet1;
                    top2jet1 = top2jet2;
                    top2jet2 = placeholder;
                }
                //else {
                    //top3lepjet1 = top2jet1+lep2;
                    //top3lepjet2 = top2jet2+lep1;
                //}
                //top3lepjet1_pT = top3lepjet1.Pt();
                //top3lepjet1_phi = top3lepjet1.Phi();
                //top3lepjet1_eta = top3lepjet1.Eta();
                //top3lepjet1_m = top3lepjet1.M();
                //top3lepjet2_pT = top3lepjet2.Pt();
                //top3lepjet2_phi = top3lepjet2.Phi();
                //top3lepjet2_eta = top3lepjet2.Eta();
                //top3lepjet2_m = top3lepjet2.M();
                //MT2Top3 = ComputeMT2(top3lepjet1, top3lepjet2, METVec, 0, 0).Compute();
            }

            MT2Top = ComputeMT2(top2jet1+lep1, top2jet2+lep2, METVec, 0, 0).Compute();
            if (MT2W<0.05) MT2W=0;
            if (MT2Top<0.05) MT2Top=0;
            //if (MT2Top2<0.05) MT2Top2=0;
            //if (MT2Top3<0.05) MT2Top3=0;

            //if (BFromT_pT->size()<2) continue;
            //if (lepFromT_pT->size()<2) continue;
            //if (top2index2==-1) continue;

            //TLorentzVector truthBjet1, truthBjet2, truthLep1, truthLep2;
            //truthBjet1.SetPtEtaPhiM(BFromT_pT->at(0), BFromT_eta->at(0), BFromT_phi->at(0), BFromT_M->at(0));
            //truthBjet2.SetPtEtaPhiM(BFromT_pT->at(1), BFromT_eta->at(1), BFromT_phi->at(1), BFromT_M->at(1));
            //truthLep1.SetPtEtaPhiM(lepFromT_pT->at(0), lepFromT_eta->at(0), lepFromT_phi->at(0), lepFromT_M->at(0));
            //truthLep2.SetPtEtaPhiM(lepFromT_pT->at(1), lepFromT_eta->at(1), lepFromT_phi->at(1), lepFromT_M->at(1));

            //dRRecoLepJet->push_back(top2jet1.DeltaR(lep1));
            //dRRecoLepJet->push_back(top2jet2.DeltaR(lep2));
            //dPhiRecoLepJet->push_back(top2jet1.DeltaPhi(lep1));
            //dPhiRecoLepJet->push_back(top2jet2.DeltaPhi(lep2));
            //dEtaRecoLepJet->push_back(fabs(top2jet1.Eta() - lep1.Eta()));
            //dEtaRecoLepJet->push_back(fabs(top2jet2.Eta() - lep2.Eta()));

            //dRTruthLepJet->push_back(truthBjet1.DeltaR(truthLep1));
            //dRTruthLepJet->push_back(truthBjet2.DeltaR(truthLep2));
            //dPhiTruthLepJet->push_back(truthBjet1.DeltaPhi(truthLep1));
            //dPhiTruthLepJet->push_back(truthBjet2.DeltaPhi(truthLep2));
            //dEtaTruthLepJet->push_back(fabs(truthBjet1.Eta() - truthLep1.Eta()));
            //dEtaTruthLepJet->push_back(fabs(truthBjet2.Eta() - truthLep2.Eta()));

            //RecoMT2Top_pT->push_back((top2jet1+lep1).Pt());
            //RecoMT2Top_pT->push_back((top2jet2+lep2).Pt());
            //RecoMT2Top_eta->push_back((top2jet1+lep1).Eta());
            //RecoMT2Top_eta->push_back((top2jet2+lep2).Eta());
            //RecoMT2Top_phi->push_back((top2jet1+lep1).Phi());
            //RecoMT2Top_phi->push_back((top2jet2+lep2).Phi());
            //RecoMT2Top_m->push_back((top2jet1+lep1).M());
            //RecoMT2Top_m->push_back((top2jet2+lep2).M());
        }

        newtree->Fill();
    }

    newfile->Write();
    file->Close();
    newfile->Close();
    delete file;
    delete newfile;
}

void AddDRMuonJetBranch(TString filename, TString savefilename, TString treename) {

    TFile *file = new TFile(filename);
    TTree *tree = (TTree*)file->Get(treename);

    std::cout<<"Cloning Tree"<<std::endl;
    TFile *newfile = new TFile(savefilename, "recreate");
    TTree *newtree = tree->CloneTree(0);

    //branches from old tree
    vector<double> *mu_phi = 0;
    tree->SetBranchAddress("mu_phi",&mu_phi);
    vector<double> *mu_eta = 0;
    tree->SetBranchAddress("mu_eta",&mu_eta);
    vector<double> *jet_phi = 0;
    tree->SetBranchAddress("jet_phi",&jet_phi);
    vector<double> *jet_eta = 0;
    tree->SetBranchAddress("jet_eta",&jet_eta);

    //new branches
    vector<double> *mu_jet_dR =  0;
    newtree->Branch("mu_jet_dR",&mu_jet_dR);

    //fill new branches
    int nentries = tree->GetEntries();
    for (int i=0;i<nentries;i++) {
        tree->GetEntry(i);
        if (i%10000==0) std::cout<<i/1000<<"k out of "<<nentries/1000<<"k entries"<<std::endl;

        mu_jet_dR->clear();
        double dEta = 0;
        double dPhi = 0;

        for (int j=0; j<jet_phi->size(); j++) {
            for (int m=0; m<mu_phi->size(); m++) {
                dEta = jet_eta->at(j) - mu_eta->at(m);
                dPhi = fmod(abs(jet_phi->at(j) - mu_phi->at(m)), 2*3.14159);
                if (dPhi > 3.14159)
                    dPhi = 2*3.14159 - dPhi;
                double dR = sqrt(pow(dEta,2) + pow(dPhi,2));
                mu_jet_dR->push_back(dR);
            }
        }

        newtree->Fill();
    }

    CopyEventCountHist(file, newfile);

    newfile->Write();
    delete file;
    delete newfile;
}

void RemoveDFEvents(TString filename, TString savefilename, TString treename) {

    TFile *file = new TFile(filename);
    TTree *tree = (TTree*)file->Get(treename);

    std::cout<<"Cloning Tree"<<std::endl;
    TFile *newfile = new TFile(savefilename, "recreate");
    TTree *newtree = tree->CloneTree(0);

    //branches from old tree
    Long64_t is_OS;
    tree->SetBranchAddress("is_OS",&is_OS);

    //fill new branches
    int nentries = tree->GetEntries();
    for (int i=0;i<nentries;i++) {
        tree->GetEntry(i);
        if (i%10000==0) std::cout<<i/1000<<"k out of "<<nentries/1000<<"k entries"<<std::endl;
        if (is_OS)
            newtree->Fill();
    }

    CopyEventCountHist(file, newfile);

    newfile->Write();
    delete file;
    delete newfile;
}

void AddMETBranches(TString filename, TString savefilename, TString treename) {

    std::cout<<"Copying Tree"<<std::endl;
    if (filename!=savefilename)
        gROOT->ProcessLine(TString(".! cp ")+filename+TString(" ")+savefilename);

    TFile *file = new TFile(filename);
    TTree *tree = (TTree*)file->Get(treename);

    std::cout<<"Cloning Branches"<<std::endl;
    TFile *newfile = new TFile(savefilename, "recreate");
    TTree *newtree = tree->CloneTree(0);
    std::cout<<"Filling New Branches"<<std::endl;

    //branches from old tree
    double MET, MET_phi, truthMET, truthMET_Phi, truthMET_NonInt, truthMET_NonIntPhi;
    tree->SetBranchAddress("MET",&MET);
    tree->SetBranchAddress("MET_phi",&MET_phi);
    tree->SetBranchAddress("truthMET",&truthMET);
    tree->SetBranchAddress("truthMET_Phi",&truthMET_Phi);
    tree->SetBranchAddress("truthMET_NonInt",&truthMET_NonInt);
    tree->SetBranchAddress("truthMET_NonIntPhi",&truthMET_NonIntPhi);

    //new branches
    float truthMET_IntOut = -999;
    float truthMET_IntOutPhi = -999;
    float fakeMET = -999;
    float fakeMET_Phi = -999;
    TBranch *b_truthMET_IntOut = newtree->Branch("truthMET_IntOut",&truthMET_IntOut);
    TBranch *b_truthMET_IntOutPhi = newtree->Branch("truthMET_IntOutPhi",&truthMET_IntOutPhi);
    TBranch *b_fakeMET = newtree->Branch("fakeMET",&fakeMET);
    TBranch *b_fakeMET_Phi = newtree->Branch("fakeMET_Phi",&fakeMET_Phi);

    //fill new branches
    int nentries = tree->GetEntries();
    for (int i=0;i<nentries;i++) {
        tree->GetEntry(i);
        if (i%10000==0) std::cout<<i/1000<<"k out of "<<nentries/1000<<"k entries"<<std::endl;

		float x = truthMET*cos(truthMET_Phi) - truthMET_NonInt*cos(truthMET_NonIntPhi);
		float y = truthMET*sin(truthMET_Phi) - truthMET_NonInt*sin(truthMET_NonIntPhi);
		truthMET_IntOut = sqrt(x*x + y*y);
		truthMET_IntOutPhi = atan(y/x);
		x = MET*cos(MET_phi) - truthMET*cos(truthMET_Phi);
		y = MET*sin(MET_phi) - truthMET*sin(truthMET_Phi);
		fakeMET = sqrt(x*x + y*y);
		fakeMET_Phi = atan(y/x);

        newtree->Fill();
    }

    CopyEventCountHist(file, newfile);

    newfile->Write();
    file->Close();
    newfile->Close();
    delete file;
    delete newfile;
}

// Run function
void AlterNtuple() {

    TString directory = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-21-NoSys/MC/";
    TString savedirectory = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/ZTruthMET/";

	for (int i=361372; i<=361443; i++)
	//for (int i=361396; i<=361397; i++)
		AddMETBranches(directory+TString(to_string(i))+".root", savedirectory+TString(to_string(i))+".root", "outputTree");
}
