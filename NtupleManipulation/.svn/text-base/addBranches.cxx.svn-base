//-----------------------------------------------------------------------------------------------
// This script reads in an analysis-level ntuple, and adds branches to the ntuple:
// nGenEvents : the total number of AOD events, returned by EventCountHist->GetBinContent(2)
// weight1fb  : the total MC weight for 1/fb, including PU reweighting, lepton and trigger SFs
// SRZ, CRFS, CRT, VRT1, VRS1: integers indicating whether the event passes the given CR/VR/SR
//
// To use this script, check the list of samples in the 'addWeight' function, then do:
// root -l
// .L addWeight.cc+
// addWeight( [pathToNtuples] )
//-----------------------------------------------------------------------------------------------


#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip> 

#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TChain.h"
#include "TBranch.h"
#include "TLorentzVector.h"

using namespace std;

//gROOT->ProcessLine("#include <vector>");
#pragma link C++ class vector<float>+;

vector<string> noSampleWeight;
vector<string> noEventWeight;

void addBranchesToSample(string sampleID, string pathToNtuples, TString treeName="outputTree");
void addRegionBranchesToSample(string sampleID, string pathToNtuples, TString treeName="outputTree");
void addEventCountBranchToSample(string sampleID, string pathToNtuples, TString treeName="outputTree");

//void addBranches( string pathToNtuples = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/v1_02/TheoryVariations/") {
void addBranches( string pathToNtuples = "root://eosatlas//eos/atlas/user/m/mazhang/Data/Ntuples/v1_02/MCDibosons/") {

    //EOS has stupid bullshit access problems: https://twiki.cern.ch/twiki/bin/view/EOS/EOSErrorMessageUnableToOpenFiles
    //If you're looping over a ton of files, put them on AFS

    vector<TString> treeNames = {"outputTree"};
    //vector<TString> treeNames = {};
    ////vector<TString> treeBases = {"EG_RESOLUTION_ALL", "EG_SCALE_ALL", "JET_GroupedNP_1", "JET_GroupedNP_2", "JET_GroupedNP_3", "JET_EtaIntercalibration_NonClosure", "MUONS_ID", "MUONS_MS", "MUONS_SCALE", "PH_EFF_ID_Uncertainty", "PH_EFF_TRKISO_Uncertainty"};
    ////vector<TString> treeBases = {"EG_RESOLUTION_ALL", "EG_SCALE_ALL"};
    //vector<TString> treeBases = {"JET_GroupedNP_1", "JET_GroupedNP_2", "JET_GroupedNP_3", "JET_EtaIntercalibration_NonClosure", "MUONS_ID", "MUONS_MS", "MUONS_SCALE", "PH_EFF_ID_Uncertainty", "PH_EFF_TRKISO_Uncertainty"};

    //for (int i=0; i<treeBases.size(); i++) {
        //treeNames.push_back("outputTree_" + treeBases[i] + "__1up");
        //treeNames.push_back("outputTree_" + treeBases[i] + "__1down");
    //}
    //treeNames.push_back("outputTree_JET_JER_SINGLE_NP__1up");
    //treeNames.push_back("outputTree_MET_SoftTrk_ResoPara");
    //treeNames.push_back("outputTree_MET_SoftTrk_ResoPerp");
    //treeNames.push_back("outputTree_MET_SoftTrk_ScaleDown");
    //treeNames.push_back("outputTree_MET_SoftTrk_ScaleUp");
    //treeNames.push_back("outputTree_JvtEfficiencyDown");
    //treeNames.push_back("outputTree_JvtEfficiencyUp");

    vector<int> samples = {361372, 361373, 361374, 361375, 361376, 361377, 361378, 361379, 361380, 361381, 361382, 361383, 361384, 361385, 361386, 361387, 361388, 361389, 361390, 361391, 361392, 361393, 361394, 361395};

    //for (int i=0; i<treeNames.size(); i++) {

        //TString treeName = treeNames[i];
        //std::cout<<"Tree: "<<treeName<<std::endl;
        //for (int j=0; j<samples.size(); j++) {
            //addBranchesToSample(to_string(samples[j]),pathToNtuples,treeName);
            ////addEventCountBranchToSample(to_string(samples[j]),pathToNtuples,treeName);
        //}
    //}

    //addBranchesToSample("data",pathToNtuples,"outputTree");
    //addBranchesToSample("data_14p7fb",pathToNtuples,"outputTree");
    //addBranchesToSample("data_2015",pathToNtuples,"outputTree");
    //addBranchesToSample("data_2016",pathToNtuples,"outputTree");

    for (auto sample:samples) {
        //addRegionBranchesToSample(sample,pathToNtuples,"ntupleOutput");
        addBranchesToSample(to_string(sample),pathToNtuples);
    }

    cout << endl;
    cout << "Following samples with 0 sampleWeight" << endl;
    for( unsigned int iS = 0 ; iS < noSampleWeight.size() ; iS++ ){
        cout << noSampleWeight.at(iS) << endl;
    }

    cout << endl;
    cout << "Following samples with 0 eventWeight" << endl;
    for( unsigned int iS = 0 ; iS < noEventWeight.size() ; iS++ ){
        cout << noEventWeight.at(iS) << endl;
    }

}

void addBranchesToSample(string sampleID, string pathToNtuples, TString treeName="outputTree") {

    //bool verbose = false;

    //---------------------------------------------
    // open file, get Tree and EventCountHist
    //---------------------------------------------

    string  filename       = Form("%s/%s.root",pathToNtuples.c_str(),sampleID.c_str()); 

    cout << endl;
    cout << "Opening file           : " << filename        << endl;

    //TFile*  f              = new TFile(filename.c_str(),"update");      
    TFile*  f              = TFile::Open(filename.c_str(),"update");      
    if( !f->IsOpen() ) return;
    TH1F*   EventCountHist = (TH1F*) f->Get("EventCountHist");
    Float_t _nGenEvents    = EventCountHist->GetBinContent(2);
    TTree*  T              = (TTree*)f->Get(treeName);

    cout << "Events in ntuple       : " << T->GetEntries() << endl;
    cout << "Total generated events : " << _nGenEvents     << endl;
    if( _nGenEvents < 1e-10 ) cout << "ERROR 0 EVENTS -----------------------------------------------------" << endl;

    //-----------------------------
    // access existing branches
    //-----------------------------

    double  sampleWeight;
    double  eventWeight;
    //double  pileupWeight_rew;
    //int     eetrig;
    //int     mmtrig;
    //int     emtrig;
    Long64_t  eetrig;
    Long64_t  mmtrig;
    Long64_t  emtrig;
    Long64_t  eetrig_match;
    Long64_t  mmtrig_match;
    Long64_t  emtrig_match;
    double  eetrigweight;
    double  mmtrigweight;
    double  emtrigweight;
    double  trigweight;
    Long64_t  channel;
    Long64_t  lep_n;
    Long64_t  jet_n;
    Long64_t  bjet_n;
    Long64_t  is_OS;
    double  MET;
    double  MET_phi;
    double  mll;
    double  HT;
    double  HTincl;
    vector<double> *  lep_weight = 0 ;
    vector<double> *  lep_pT     = 0 ;
    //vector<double> *  el_pT      = 0 ;
    //vector<double> *  mu_pT      = 0 ;
    vector<double> *  lep_eta    = 0 ;
    vector<double> *  lep_phi    = 0 ;
    vector<int>    *  lep_pdgId  = 0 ;
    vector<int>    *  mu_isBad  = 0 ;
    vector<double> *  jet_pT     = 0 ;

    double DPhi_METJetLeading;
    double DPhi_METJetSecond;

    double sf_trig_HLT_e60_lhmedium;
    double sf_trig_HLT_mu50;
    double sf_trig_HLT_2e12_lhloose;
    double sf_trig_HLT_mu18_mu8noL1;
    double sf_trig_HLT_e17_lhloose_mu14;
    double sf_trig_HLT_e7_lhmedium_mu24;

    double sfunc_trig_HLT_e60_lhmedium;
    double sfunc_trig_HLT_mu50;
    double sfunc_trig_HLT_2e12_lhloose;
    double sfunc_trig_HLT_mu18_mu8noL1;
    double sfunc_trig_HLT_e17_lhloose_mu14;
    double sfunc_trig_HLT_e7_lhmedium_mu24;

    T->SetBranchAddress("sampleWeight"    ,&sampleWeight     );
    T->SetBranchAddress("eventWeight"     ,&eventWeight      );
    //T->SetBranchAddress("pileupWeight_rew",&pileupWeight_rew );
    T->SetBranchAddress("eetrig"          ,&eetrig           );
    T->SetBranchAddress("mmtrig"          ,&mmtrig           );
    T->SetBranchAddress("emtrig"          ,&emtrig           );
    T->SetBranchAddress("eetrig_match"          ,&eetrig_match           );
    T->SetBranchAddress("mmtrig_match"          ,&mmtrig_match           );
    T->SetBranchAddress("emtrig_match"          ,&emtrig_match           );
    T->SetBranchAddress("eetrigweight"    ,&eetrigweight     );
    T->SetBranchAddress("mmtrigweight"    ,&mmtrigweight     );
    T->SetBranchAddress("emtrigweight"    ,&emtrigweight     );
    T->SetBranchAddress("trigweight"      ,&trigweight       );
    T->SetBranchAddress("channel"         ,&channel          );
    T->SetBranchAddress("lep_weight"      ,&lep_weight       );
    T->SetBranchAddress("lep_pdgId"       ,&lep_pdgId        );
    T->SetBranchAddress("mu_isBad"       ,&mu_isBad        );
    T->SetBranchAddress("DPhi_METJetLeading"       ,&DPhi_METJetLeading        );
    T->SetBranchAddress("DPhi_METJetSecond"       ,&DPhi_METJetSecond        );
    T->SetBranchAddress("lep_pT"          ,&lep_pT           );
    //T->SetBranchAddress("el_pT"           ,&el_pT            );
    //T->SetBranchAddress("mu_pT"           ,&mu_pT            );
    T->SetBranchAddress("lep_eta"         ,&lep_eta          );
    T->SetBranchAddress("lep_phi"         ,&lep_phi          );
    T->SetBranchAddress("lep_n"           ,&lep_n            );
    T->SetBranchAddress("jet_pT"          ,&jet_pT           );
    T->SetBranchAddress("mll"             ,&mll              );
    T->SetBranchAddress("MET"             ,&MET              );
    T->SetBranchAddress("HT"              ,&HT               );
    T->SetBranchAddress("HTincl"          ,&HTincl           );
    T->SetBranchAddress("MET_phi"             ,&MET_phi              );
    T->SetBranchAddress("jet_n"           ,&jet_n            );
    T->SetBranchAddress("bjet_n"           ,&bjet_n            );
    T->SetBranchAddress("is_OS"           ,&is_OS            );

    T->SetBranchAddress("sf_trig_HLT_e60_lhmedium"           ,&sf_trig_HLT_e60_lhmedium        );
    T->SetBranchAddress("sf_trig_HLT_mu50"                   ,&sf_trig_HLT_mu50                );
    T->SetBranchAddress("sf_trig_HLT_2e12_lhloose"           ,&sf_trig_HLT_2e12_lhloose        );
    T->SetBranchAddress("sf_trig_HLT_mu18_mu8noL1"           ,&sf_trig_HLT_mu18_mu8noL1        );
    T->SetBranchAddress("sf_trig_HLT_e17_lhloose_mu14"       ,&sf_trig_HLT_e17_lhloose_mu14    );
    T->SetBranchAddress("sf_trig_HLT_e7_lhmedium_mu24"       ,&sf_trig_HLT_e7_lhmedium_mu24    );

    T->SetBranchAddress("sfunc_trig_HLT_e60_lhmedium"        ,&sfunc_trig_HLT_e60_lhmedium        );
    T->SetBranchAddress("sfunc_trig_HLT_mu50"                ,&sfunc_trig_HLT_mu50                );
    T->SetBranchAddress("sfunc_trig_HLT_2e12_lhloose"        ,&sfunc_trig_HLT_2e12_lhloose        );
    T->SetBranchAddress("sfunc_trig_HLT_mu18_mu8noL1"        ,&sfunc_trig_HLT_mu18_mu8noL1        );
    T->SetBranchAddress("sfunc_trig_HLT_e17_lhloose_mu14"    ,&sfunc_trig_HLT_e17_lhloose_mu14    );
    T->SetBranchAddress("sfunc_trig_HLT_e7_lhmedium_mu24"    ,&sfunc_trig_HLT_e7_lhmedium_mu24    );

    //-----------------------------
    // add new branches
    //-----------------------------

    Float_t nGenEvents;
    Float_t weight1fb;
    Float_t lepweight;

    TBranch *b_weight      = T->Branch("weight1fb"          , &weight1fb            ,   "weight1fb/F"           );
    TBranch *b_lepw        = T->Branch("lepweight"          , &lepweight            ,   "lepweight/F"           );
    TBranch *b_nEvents     = T->Branch("nGenEvents"         , &nGenEvents           ,   "nGenEvents/F"          );

    Long64_t goodMuons;

    TBranch *b_goodMuons      = T->Branch("good_Muons"          , &goodMuons            ,   "goodMuons/I"           );

    Long64_t SRZ, CRT, CRFS, VRT, VRS, CRZ, VRZ, EdgeSRLow, EdgeSRMed, EdgeSRHigh, EdgeVRLow, EdgeVRMed, EdgeVRHigh, EdgeCRTLow, EdgeCRTMed, EdgeCRTHigh, EdgeVRTLow, EdgeVRTMed, EdgeVRTHigh, VR3L, VRWZ, VRZZ;

    TBranch *b_SRZ      = T->Branch("SRZ"          , &SRZ            ,   "SRZ/I"           );
    TBranch *b_CRT      = T->Branch("CRT"          , &CRT            ,   "CRT/I"           );
    TBranch *b_CRFS      = T->Branch("CRFS"          , &CRFS            ,   "CRFS/I"           );
    TBranch *b_VRT      = T->Branch("VRT"          , &VRT            ,   "VRT/I"           );
    TBranch *b_VRS      = T->Branch("VRS"          , &VRS            ,   "VRS/I"           );
    TBranch *b_CRZ      = T->Branch("CRZ"          , &CRZ            ,   "CRZ/I"           );
    TBranch *b_VRZ      = T->Branch("VRZ"          , &VRZ            ,   "VRZ/I"           );
    TBranch *b_EdgeSRLow      = T->Branch("EdgeSRLow"          , &EdgeSRLow            ,   "EdgeSRLow/I"           );
    TBranch *b_EdgeSRMed      = T->Branch("EdgeSRMed"          , &EdgeSRMed            ,   "EdgeSRMed/I"           );
    TBranch *b_EdgeSRHigh      = T->Branch("EdgeSRHigh"          , &EdgeSRHigh            ,   "EdgeSRHigh/I"           );
    TBranch *b_EdgeVRLow      = T->Branch("EdgeVRLow"          , &EdgeVRLow            ,   "EdgeVRLow/I"           );
    TBranch *b_EdgeVRMed      = T->Branch("EdgeVRMed"          , &EdgeVRMed            ,   "EdgeVRMed/I"           );
    TBranch *b_EdgeVRHigh      = T->Branch("EdgeVRHigh"          , &EdgeVRHigh            ,   "EdgeVRHigh/I"           );
    TBranch *b_EdgeCRTLow      = T->Branch("EdgeCRTLow"          , &EdgeCRTLow            ,   "EdgeCRTLow/I"           );
    TBranch *b_EdgeCRTMed      = T->Branch("EdgeCRTMed"          , &EdgeCRTMed            ,   "EdgeCRTMed/I"           );
    TBranch *b_EdgeCRTHigh      = T->Branch("EdgeCRTHigh"          , &EdgeCRTHigh            ,   "EdgeCRTHigh/I"           );
    TBranch *b_EdgeVRTLow      = T->Branch("EdgeVRTLow"          , &EdgeVRTLow            ,   "EdgeVRTLow/I"           );
    TBranch *b_EdgeVRTMed      = T->Branch("EdgeVRTMed"          , &EdgeVRTMed            ,   "EdgeVRTMed/I"           );
    TBranch *b_EdgeVRTHigh      = T->Branch("EdgeVRTHigh"          , &EdgeVRTHigh            ,   "EdgeVRTHigh/I"           );
    TBranch *b_VRWZ      = T->Branch("VRWZ"          , &VRWZ            ,   "VRWZ/I"           );
    TBranch *b_VRZZ      = T->Branch("VRZZ"          , &VRZZ            ,   "VRZZ/I"           );
    TBranch *b_VR3L      = T->Branch("VR3L"          , &VR3L            ,   "VR3L/I"           );

    Float_t WZ_WMass, WZ_ZMass, WZ_WPt, WZ_ZPt;
    //float ZZ_ZMass, ZZ_ZPt;
    vector<float> *ZZ_ZMass = new std::vector<float>(), *ZZ_ZPt = new std::vector<float>();
    Float_t ZZ_totalMass, ZZ_ZMass1, ZZ_ZMass2, ZZ_ZPt1, ZZ_ZPt2;

    TBranch *b_WZ_WMass      = T->Branch("WZ_WMass"          , &WZ_WMass            ,   "WZ_WMass/F"           );
    TBranch *b_WZ_ZMass      = T->Branch("WZ_ZMass"          , &WZ_ZMass            ,   "WZ_ZMass/F"           );
    TBranch *b_WZ_WPt      = T->Branch("WZ_WPt"          , &WZ_WPt            ,   "WZ_WPt/F"           );
    TBranch *b_WZ_ZPt      = T->Branch("WZ_ZPt"          , &WZ_ZPt            ,   "WZ_ZPt/F"           );
    //TBranch *b_ZZ_ZMass      = T->Branch("ZZ_ZMass"          , &ZZ_ZMass     );
    //TBranch *b_ZZ_ZPt      = T->Branch("ZZ_ZPt"          , &ZZ_ZPt         );
    TBranch *b_ZZ_totalMass      = T->Branch("ZZ_totalMass"          , &ZZ_totalMass            ,   "ZZ_totalMass/F"           );
    TBranch *b_ZZ_ZMass      = T->Branch("ZZ_ZMass"          , &ZZ_ZMass      );
    TBranch *b_ZZ_ZPt      = T->Branch("ZZ_ZPt"          , &ZZ_ZPt      );
    //TBranch *b_ZZ_ZMass1      = T->Branch("ZZ_ZMass1"          , &ZZ_ZMass1            ,   "ZZ_ZMass1/F"           );
    //TBranch *b_ZZ_ZMass2      = T->Branch("ZZ_ZMass2"          , &ZZ_ZMass2            ,   "ZZ_ZMass2/F"           );
    //TBranch *b_ZZ_ZPt1      = T->Branch("ZZ_ZPt1"          , &ZZ_ZPt1            ,   "ZZ_ZPt1/F"           );
    //TBranch *b_ZZ_ZPt2      = T->Branch("ZZ_ZPt2"          , &ZZ_ZPt2            ,   "ZZ_ZPt2/F"           );

    //-----------------------------
    // loop over events
    //-----------------------------

    Long64_t nentries = T->GetEntries();
    //nentries=100000;

    for (Long64_t i=0;i<nentries;i++) {

        T->GetEntry(i);

        if( lep_n < 2 ){
            cout << "ERROR! Found only " << lep_n << " leptons" << endl;
            exit(0);
        }

        // trigweight = 1.0;
        // if     ( channel == 0                 ) trigweight = mmtrigweight;
        // else if( channel == 1                 ) trigweight = eetrigweight;
        // else if( channel == 2 || channel == 3 ) trigweight = emtrigweight;

        // trigweight_noemuSF = trigweight;

        // if( ( channel == 2 || channel == 3 ) && el_pT->at(0) < 65.0 && mu_pT->at(0) < 55.0 ) trigweight_noemuSF = 1.0;

        //-----------------------------
        // weight for 1/fb
        //-----------------------------
        
        //if not data
        if (sampleID.find("data") == std::string::npos) {

            nGenEvents = _nGenEvents;
            lepweight = lep_weight->at(0) * lep_weight->at(1);
            //weight1fb = 1000.0 * sampleWeight * eventWeight * pileupWeight_rew * trigweight * lepweight / nGenEvents; // with PU
            weight1fb = 1000.0 * sampleWeight * eventWeight * lepweight / nGenEvents;                      // without PU

            if( i == 0 ){
                cout << "sampleWeight           : " << sampleWeight     << endl;
                cout << "eventWeight            : " << eventWeight      << endl;
                cout << "weight1fb              : " << weight1fb        << endl;
                //cout << "weight1fb_vec          : " << weight1fb_vec    << endl;

                if( sampleWeight    < 1e-10 ){
                    cout << "<<<<------------------- sampleWeight=0" << endl;
                    noSampleWeight.push_back(sampleID);
                }
                if( fabs(weight1fb) < 1e-10 ){
                    cout << "<<<<<<<<<<<<<<<<<<<<<<< WEIGHT=0"    << endl;
                    noEventWeight.push_back(sampleID);
                }
            }

            b_weight->Fill();      
            b_lepw->Fill();        
            b_nEvents->Fill();     
        }

        //-----------------------------
        // good muons
        //-----------------------------
        
        if (channel==0 && mu_isBad->size()>=2) {
            goodMuons = (mu_isBad->at(0)==0 && mu_isBad->at(1)==0);
        }
        else if (channel==1) {
            goodMuons = 1;
        }
        else if (channel>=2 && mu_isBad->size()>=1) {
            goodMuons = (mu_isBad->at(0)==0);
        }
        else {
            goodMuons = 0;
        }

        b_goodMuons->Fill();      

        //-----------------------------
        // regions
        //-----------------------------
        
        int trigger = ((channel==0 && mmtrig && mmtrig_match) || (channel==1 && eetrig && eetrig_match) || (channel>=2 && emtrig && emtrig_match));
        int mllMin40 = (mll>40);
        int mllMin12 = (mll>12);
        int ZWindow = (mll>81 && mll<101);
        int OffZWindow = (mll<81 || mll>101);
        int dPhiJetMET = (DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4);
        int HTincl600 = (HTincl>600);
        int lepReq5025 = 0;
        int lepReq2525 = 0;
        int OS = 0;
        int DS = 0;
        int SF = (channel==0 || channel==1);
        int DF = (channel==2 || channel==3);

        if (lep_pT->size()>=2) {
            lepReq5025 = (lep_pT->at(0)>50 && lep_pT->at(1)>25);
            lepReq2525 = (lep_pT->at(0)>25 && lep_pT->at(1)>25);
            OS = (lep_pdgId->at(0)*lep_pdgId->at(1) < 0);
            DS = !OS;
            //SF = (abs(lep_pdgId->at(0)) == abs(lep_pdgId->at(1)));
            //DF = !SF;
        }

        int jetReq = 0;
        if (jet_pT->size()>=2) {
            jetReq = (jet_pT->at(0)>30 && jet_pT->at(1)>30);
        }

        //EDGE regions

        int edgeReq = trigger * goodMuons * mllMin12 * lepReq2525 * jetReq * dPhiJetMET * OS;

        EdgeSRLow = edgeReq * SF * (MET>200);
        EdgeSRMed = edgeReq * SF * (MET>200) * (HT>400);
        EdgeSRHigh = edgeReq * SF * (MET>200) * (HT>700);
        EdgeVRLow = edgeReq * SF * (MET>100 && MET<200);
        EdgeVRMed = edgeReq * SF * (MET>100 && MET<200) * (HT>400);
        EdgeVRHigh = edgeReq * SF * (MET>100 && MET<200) * (HT>700);

        EdgeCRTLow = edgeReq * DF * (MET>200);
        EdgeCRTMed = edgeReq * DF * (MET>200) * (HT>400);
        EdgeCRTHigh = edgeReq * DF * (MET>200) * (HT>700);
        EdgeVRTLow = edgeReq * DF * (MET>100 && MET<200);
        EdgeVRTMed = edgeReq * DF * (MET>100 && MET<200) * (HT>400);
        EdgeVRTHigh = edgeReq * DF * (MET>100 && MET<200) * (HT>700);

        b_EdgeSRLow->Fill();
        b_EdgeSRMed->Fill();
        b_EdgeSRHigh->Fill();
        b_EdgeVRLow->Fill();
        b_EdgeVRMed->Fill();
        b_EdgeVRHigh->Fill();
        b_EdgeCRTLow->Fill();
        b_EdgeCRTMed->Fill();
        b_EdgeCRTHigh->Fill();
        b_EdgeVRTLow->Fill();
        b_EdgeVRTMed->Fill();
        b_EdgeVRTHigh->Fill();

        //Z regions
        
        int ZReq = trigger * goodMuons * mllMin40 * lepReq5025 * jetReq * dPhiJetMET * OS * HTincl600;

        SRZ = ZReq * ZWindow * SF * (MET>225);
        CRZ = ZReq * ZWindow * SF * (MET<60);

        VRZ = ZReq * ZWindow * SF * (MET<225);
        VRS = ZReq * ZWindow * SF * (MET>100 && MET<200);

        CRT = ZReq * OffZWindow * SF * (MET>225);
        VRT = ZReq * OffZWindow * SF * (MET>100 && MET<200);

        b_SRZ->Fill();
        b_CRT->Fill();
        b_CRFS->Fill();
        b_VRT->Fill();
        b_VRS->Fill();
        b_CRZ->Fill();
        b_VRZ->Fill();

        //Diboson regions
        
        VRWZ = trigger * goodMuons * (lep_n==3) * (MET>50 && MET<200) * (bjet_n==0);

        if (VRWZ) {

            VRWZ *= (lep_pT->at(0)>50 && lep_pT->at(1)>25 && lep_pT->at(2)>25);

            TLorentzVector p0;
            p0.SetPtEtaPhiM(lep_pT->at(0),lep_eta->at(0),lep_phi->at(0),0);
            TLorentzVector p1;
            p1.SetPtEtaPhiM(lep_pT->at(1),lep_eta->at(1),lep_phi->at(1),0);
            TLorentzVector p2;
            p2.SetPtEtaPhiM(lep_pT->at(2),lep_eta->at(2),lep_phi->at(2),0);
            TLorentzVector pMET;
            pMET.SetPtEtaPhiM(MET,0,MET_phi,0);

            float m_01 = (p0+p1).M();
            float m_02 = (p0+p2).M();
            float m_12 = (p1+p2).M();

            float pt_01 = (p0+p1).Pt();
            float pt_02 = (p0+p2).Pt();
            float pt_12 = (p1+p2).Pt();

            float dmZ_01 = abs((p0+p1).M() - 91.2);
            float dmZ_02 = abs((p0+p2).M() - 91.2);
            float dmZ_12 = abs((p1+p2).M() - 91.2);

            // If there is not an OSSF pair, the event is false
            if ((lep_pdgId->at(0) != -lep_pdgId->at(1)) && (lep_pdgId->at(0) != -lep_pdgId->at(2)) && (lep_pdgId->at(1) != -lep_pdgId->at(2)))
                VRWZ=0;

            // If a pair is not OSSF, take it out of the running for best Z pair
            if (lep_pdgId->at(0) != -lep_pdgId->at(1))
                dmZ_01 = 999999999;
            if (lep_pdgId->at(0) != -lep_pdgId->at(2))
                dmZ_02 = 999999999;
            if (lep_pdgId->at(1) != -lep_pdgId->at(2))
                dmZ_12 = 999999999;

            if ((dmZ_01 <= dmZ_02) && (dmZ_01 <= dmZ_12)) {
                WZ_WMass = sqrt(2*p2.Pt()*MET*(1-cos(p2.Phi()-MET_phi)));
                WZ_ZMass = m_01;
                WZ_WPt = (p2+pMET).Pt();
                WZ_ZPt = pt_01;
            }
            else if ((dmZ_02 <= dmZ_01) && (dmZ_02 <= dmZ_12)) {
                WZ_WMass = sqrt(2*p1.Pt()*MET*(1-cos(p1.Phi()-MET_phi)));
                WZ_ZMass = m_02;
                WZ_WPt = (p1+pMET).Pt();
                WZ_ZPt = pt_02;
            }
            else {
                WZ_WMass = sqrt(2*p0.Pt()*MET*(1-cos(p0.Phi()-MET_phi)));
                WZ_ZMass = m_12;
                WZ_WPt = (p0+pMET).Pt();
                WZ_ZPt = pt_12;
            }

            VRWZ *= (WZ_WMass<100);
        }

        if (!VRWZ) {
            WZ_WMass = 0;
            WZ_ZMass = 0;
            WZ_WPt = 0;
            WZ_ZPt = 0;
        }

        b_VRWZ->Fill();
        b_WZ_WMass->Fill();
        b_WZ_ZMass->Fill();
        b_WZ_WPt->Fill();
        b_WZ_ZPt->Fill();

        //VR-ZZ

        VRZZ = trigger * goodMuons * (lep_n==4) * (MET<100) * (bjet_n==0); 

        if (VRZZ) {

            VRZZ *= (lep_pT->at(0)>50 && lep_pT->at(1)>25 && lep_pT->at(2)>25 && lep_pT->at(3)>25); 

            TLorentzVector p0;
            p0.SetPtEtaPhiM(lep_pT->at(0),lep_eta->at(0),lep_phi->at(0),0);
            TLorentzVector p1;
            p1.SetPtEtaPhiM(lep_pT->at(1),lep_eta->at(1),lep_phi->at(1),0);
            TLorentzVector p2;
            p2.SetPtEtaPhiM(lep_pT->at(2),lep_eta->at(2),lep_phi->at(2),0);
            TLorentzVector p3;
            p3.SetPtEtaPhiM(lep_pT->at(3),lep_eta->at(3),lep_phi->at(3),0);
            TLorentzVector pMET;
            pMET.SetPtEtaPhiM(MET,0,MET_phi,0);

            float m_01 = (p0+p1).M();
            float m_02 = (p0+p2).M();
            float m_03 = (p0+p3).M();
            float m_12 = (p1+p2).M();
            float m_13 = (p1+p3).M();
            float m_23 = (p2+p3).M();

            float m_0123 = (p0+p1+p2+p3).M();

            float pt_01 = (p0+p1).Pt();
            float pt_02 = (p0+p2).Pt();
            float pt_03 = (p0+p3).Pt();
            float pt_12 = (p1+p2).Pt();
            float pt_13 = (p1+p3).Pt();
            float pt_23 = (p2+p3).Pt();

            float dmZ_01 = abs((p0+p1).M() - 91.2);
            float dmZ_02 = abs((p0+p2).M() - 91.2);
            float dmZ_03 = abs((p0+p3).M() - 91.2);
            float dmZ_12 = abs((p1+p2).M() - 91.2);
            float dmZ_13 = abs((p1+p3).M() - 91.2);
            float dmZ_23 = abs((p2+p3).M() - 91.2);

            int OSSF_01 = (lep_pdgId->at(0)==-lep_pdgId->at(1));
            int OSSF_02 = (lep_pdgId->at(0)==-lep_pdgId->at(2));
            int OSSF_03 = (lep_pdgId->at(0)==-lep_pdgId->at(3));
            int OSSF_12 = (lep_pdgId->at(1)==-lep_pdgId->at(2));
            int OSSF_13 = (lep_pdgId->at(1)==-lep_pdgId->at(3));
            int OSSF_23 = (lep_pdgId->at(2)==-lep_pdgId->at(3));

            int twoOSSFPairs = ((OSSF_01 && OSSF_23) || (OSSF_02 && OSSF_13) || (OSSF_03 && OSSF_12));
            int A0 = abs(lep_pdgId->at(0));
            int A1 = abs(lep_pdgId->at(1));
            int A2 = abs(lep_pdgId->at(2));
            int A3 = abs(lep_pdgId->at(3));
            int allSF = (A0==A1 && A1==A2 && A2==A3);
            VRZZ *= twoOSSFPairs;

            //vector<float> vec_ZZ_ZMass, vec_ZZ_ZPt;

            if (twoOSSFPairs) {

                float mass1, mass2, pt1, pt2;

                if (OSSF_01 && OSSF_23) {
                    if (m_01>m_23) {
                        mass1 = m_01;
                        pt1 = pt_01;
                        mass2 = m_23;
                        pt2 = pt_23;
                    }
                    else {
                        mass1 = m_23;
                        pt1 = pt_23;
                        mass2 = m_01;
                        pt2 = pt_01;
                    }
                }
                else if (OSSF_02 && OSSF_13) {
                    if (m_02>m_13) {
                        mass1 = m_02;
                        pt1 = pt_02;
                        mass2 = m_13;
                        pt2 = pt_13;
                    }
                    else {
                        mass1 = m_13;
                        pt1 = pt_13;
                        mass2 = m_02;
                        pt2 = pt_02;
                    }
                }
                else if (OSSF_03 && OSSF_12) {
                    if (m_03>m_12) {
                        mass1 = m_03;
                        pt1 = pt_03;
                        mass2 = m_12;
                        pt2 = pt_12;
                    }
                    else {
                        mass1 = m_12;
                        pt1 = pt_12;
                        mass2 = m_03;
                        pt2 = pt_03;
                    }
                }
                if (allSF) {
                    if (OSSF_01) {
                        if (OSSF_02) {
                            if (dmZ_01+dmZ_23 < dmZ_02+dmZ_13) {
                                if (m_01>m_23) {
                                    mass1 = m_01;
                                    pt1 = pt_01;
                                    mass2 = m_23;
                                    pt2 = pt_23;
                                }
                                else {
                                    mass1 = m_23;
                                    pt1 = pt_23;
                                    mass2 = m_01;
                                    pt2 = pt_01;
                                }
                            }
                            else {
                                if (m_02>m_13) {
                                    mass1 = m_02;
                                    pt1 = pt_02;
                                    mass2 = m_13;
                                    pt2 = pt_13;
                                }
                                else {
                                    mass1 = m_13;
                                    pt1 = pt_13;
                                    mass2 = m_02;
                                    pt2 = pt_02;
                                }
                            }
                        }
                        else {
                            if (dmZ_01+dmZ_23 < dmZ_03+dmZ_12) {
                                if (m_01>m_23) {
                                    mass1 = m_01;
                                    pt1 = pt_01;
                                    mass2 = m_23;
                                    pt2 = pt_23;
                                }
                                else {
                                    mass1 = m_23;
                                    pt1 = pt_23;
                                    mass2 = m_01;
                                    pt2 = pt_01;
                                }
                            }
                            else {
                                if (m_03>m_12) {
                                    mass1 = m_03;
                                    pt1 = pt_03;
                                    mass2 = m_12;
                                    pt2 = pt_12;
                                }
                                else {
                                    mass1 = m_12;
                                    pt1 = pt_12;
                                    mass2 = m_03;
                                    pt2 = pt_03;
                                }
                            }
                        }
                    }
                    else {
                        if (dmZ_02+dmZ_13 < dmZ_03+dmZ_12) {
                            if (m_02>m_13) {
                                mass1 = m_02;
                                pt1 = pt_02;
                                mass2 = m_13;
                                pt2 = pt_13;
                            }
                            else {
                                mass1 = m_13;
                                pt1 = pt_13;
                                mass2 = m_02;
                                pt2 = pt_02;
                            }
                        }
                        else {
                            if (m_03>m_12) {
                                mass1 = m_03;
                                pt1 = pt_03;
                                mass2 = m_12;
                                pt2 = pt_12;
                            }
                            else {
                                mass1 = m_12;
                                pt1 = pt_12;
                                mass2 = m_03;
                                pt2 = pt_03;
                            }
                        }
                    }
                }

                ZZ_ZMass->clear();
                ZZ_ZMass->push_back(mass1);
                ZZ_ZMass->push_back(mass2);
                ZZ_ZPt->clear();
                ZZ_ZPt->push_back(pt1);
                ZZ_ZPt->push_back(pt2);

                //ZZ_ZMass = {mass1, mass2};
                //ZZ_ZPt = {pt1, pt2};

                //ZZ_ZMass1 = mass1;
                //ZZ_ZMass2 = mass2;
                //ZZ_ZPt1 = pt1;
                //ZZ_ZPt2 = pt2;
                
                ZZ_totalMass = m_0123;
            }
        }

        if(!VRZZ) {
            //ZZ_ZMass1 = 0;
            //ZZ_ZMass2 = 0;
            //ZZ_ZPt1 = 0;
            //ZZ_ZPt2 = 0;
            ZZ_totalMass = 0;
            ZZ_ZMass->clear();
            ZZ_ZPt->clear();
        }

        b_VRZZ->Fill();
        //b_ZZ_ZMass1->Fill();
        //b_ZZ_ZMass2->Fill();
        //b_ZZ_ZPt1->Fill();
        //b_ZZ_ZPt2->Fill();
        b_ZZ_totalMass->Fill();
        b_ZZ_ZMass->Fill();
        b_ZZ_ZPt->Fill();

        //VR-3L
        VR3L = trigger * goodMuons * (lep_n>=3) * (MET>60 && MET<100) * (HTincl>200) * (jet_n>=2) * ZWindow * OS * SF * dPhiJetMET;
        if (VR3L) {
            VR3L *= (lep_pT->at(0)>50 && lep_pT->at(1)>25 && lep_pT->at(2)>25); 
        }
        b_VR3L->Fill();
    }

    //T->Print();
    T->Write();
    delete f;
}

/*
void addRegionBranchesToSample(string sampleID, string pathToNtuples, TString treeName="outputTree") {

    //bool verbose = false;

    //---------------------------------------------
    // open file, get Tree and EventCountHist
    //---------------------------------------------

    string  filename       = Form("%s/%s.root",pathToNtuples.c_str(),sampleID.c_str()); 
    TFile*  f              = new TFile(filename.c_str(),"update");      
    if( !f->IsOpen() ) return;
    TTree*  T              = (TTree*)f->Get(treeName);

    cout << endl;
    cout << "Opening file           : " << filename        << endl;
    cout << "Events in ntuple       : " << T->GetEntries() << endl;

    //-----------------------------
    // access existing branches
    //-----------------------------

    //Long64_t  eetrig;
    //Long64_t  mmtrig;
    //Long64_t  emtrig;
    //Long64_t  eetrig_match;
    //Long64_t  mmtrig_match;
    //Long64_t  emtrig_match;
    Long64_t  channel;
    Long64_t  lep_n, mu_n, el_n;
    Long64_t  jet_n;
    //Long64_t  bjet_n;
    Long64_t  is_OS;
    vector<double> *  MET_vec = 0;
    double MET;
    vector<double> *  MET_phi = 0;
    double  mll;
    double  HT;
    double  HTincl;
    //vector<double> *  lep_weight = 0 ;
    vector<double> *  lep_pT     = 0 ;
    vector<double> *  lep_eta    = 0 ;
    vector<double> *  lep_phi    = 0 ;
    //vector<int>    *  lep_pdgId  = 0 ;
    //vector<int>    *  mu_isBad  = 0 ;
    vector<double> *  jet_pT     = 0 ;

    double DPhi_METJetLeading;
    double DPhi_METJetSecond;

    //T->SetBranchAddress("eetrig"          ,&eetrig           );
    //T->SetBranchAddress("mmtrig"          ,&mmtrig           );
    //T->SetBranchAddress("emtrig"          ,&emtrig           );
    //T->SetBranchAddress("eetrig_match"          ,&eetrig_match           );
    //T->SetBranchAddress("mmtrig_match"          ,&mmtrig_match           );
    //T->SetBranchAddress("emtrig_match"          ,&emtrig_match           );
    T->SetBranchAddress("channel"         ,&channel          );
    //T->SetBranchAddress("lep_weight"      ,&lep_weight       );
    //T->SetBranchAddress("lep_pdgId"       ,&lep_pdgId        );
    //T->SetBranchAddress("mu_isBad"       ,&mu_isBad        );
    T->SetBranchAddress("DPhi_METJetLeading"       ,&DPhi_METJetLeading        );
    T->SetBranchAddress("DPhi_METJetSecond"       ,&DPhi_METJetSecond        );
    T->SetBranchAddress("lep_pT"          ,&lep_pT           );
    T->SetBranchAddress("lep_eta"         ,&lep_eta          );
    T->SetBranchAddress("lep_phi"         ,&lep_phi          );
    //T->SetBranchAddress("lep_n"           ,&lep_n            );
    T->SetBranchAddress("mu_n"           ,&mu_n            );
    T->SetBranchAddress("el_n"           ,&el_n            );
    T->SetBranchAddress("jet_pT"          ,&jet_pT           );
    T->SetBranchAddress("mll"             ,&mll              );
    T->SetBranchAddress("MET_NonInt"             ,&MET_vec              );
    T->SetBranchAddress("HT"              ,&HT               );
    T->SetBranchAddress("HTincl"          ,&HTincl           );
    T->SetBranchAddress("METPhi_NonInt"             ,&MET_phi              );
    T->SetBranchAddress("jet_n"           ,&jet_n            );
    //T->SetBranchAddress("bjet_n"           ,&bjet_n            );
    T->SetBranchAddress("is_OS"           ,&is_OS            );

    //-----------------------------
    // add new branches
    //-----------------------------

    Long64_t goodMuons;

    TBranch *b_goodMuons      = T->Branch("good_Muons"          , &goodMuons            ,   "goodMuons/I"           );

    Long64_t SRZ, CRT, CRFS, VRT, VRS, CRZ, VRZ, EdgeSRLow, EdgeSRMed, EdgeSRHigh, EdgeVRLow, EdgeVRMed, EdgeVRHigh, EdgeCRTLow, EdgeCRTMed, EdgeCRTHigh, EdgeVRTLow, EdgeVRTMed, EdgeVRTHigh, VR3L, VRWZ, VRZZ;

    TBranch *b_SRZ      = T->Branch("SRZ"          , &SRZ            ,   "SRZ/I"           );
    TBranch *b_CRT      = T->Branch("CRT"          , &CRT            ,   "CRT/I"           );
    TBranch *b_CRFS      = T->Branch("CRFS"          , &CRFS            ,   "CRFS/I"           );
    TBranch *b_VRT      = T->Branch("VRT"          , &VRT            ,   "VRT/I"           );
    TBranch *b_VRS      = T->Branch("VRS"          , &VRS            ,   "VRS/I"           );
    TBranch *b_CRZ      = T->Branch("CRZ"          , &CRZ            ,   "CRZ/I"           );
    TBranch *b_VRZ      = T->Branch("VRZ"          , &VRZ            ,   "VRZ/I"           );
    TBranch *b_EdgeSRLow      = T->Branch("EdgeSRLow"          , &EdgeSRLow            ,   "EdgeSRLow/I"           );
    TBranch *b_EdgeSRMed      = T->Branch("EdgeSRMed"          , &EdgeSRMed            ,   "EdgeSRMed/I"           );
    TBranch *b_EdgeSRHigh      = T->Branch("EdgeSRHigh"          , &EdgeSRHigh            ,   "EdgeSRHigh/I"           );
    TBranch *b_EdgeVRLow      = T->Branch("EdgeVRLow"          , &EdgeVRLow            ,   "EdgeVRLow/I"           );
    TBranch *b_EdgeVRMed      = T->Branch("EdgeVRMed"          , &EdgeVRMed            ,   "EdgeVRMed/I"           );
    TBranch *b_EdgeVRHigh      = T->Branch("EdgeVRHigh"          , &EdgeVRHigh            ,   "EdgeVRHigh/I"           );
    TBranch *b_EdgeCRTLow      = T->Branch("EdgeCRTLow"          , &EdgeCRTLow            ,   "EdgeCRTLow/I"           );
    TBranch *b_EdgeCRTMed      = T->Branch("EdgeCRTMed"          , &EdgeCRTMed            ,   "EdgeCRTMed/I"           );
    TBranch *b_EdgeCRTHigh      = T->Branch("EdgeCRTHigh"          , &EdgeCRTHigh            ,   "EdgeCRTHigh/I"           );
    TBranch *b_EdgeVRTLow      = T->Branch("EdgeVRTLow"          , &EdgeVRTLow            ,   "EdgeVRTLow/I"           );
    TBranch *b_EdgeVRTMed      = T->Branch("EdgeVRTMed"          , &EdgeVRTMed            ,   "EdgeVRTMed/I"           );
    TBranch *b_EdgeVRTHigh      = T->Branch("EdgeVRTHigh"          , &EdgeVRTHigh            ,   "EdgeVRTHigh/I"           );
    TBranch *b_VRWZ      = T->Branch("VRWZ"          , &VRWZ            ,   "VRWZ/I"           );
    TBranch *b_VRZZ      = T->Branch("VRZZ"          , &VRZZ            ,   "VRZZ/I"           );
    TBranch *b_VR3L      = T->Branch("VR3L"          , &VR3L            ,   "VR3L/I"           );

    Float_t WZ_WMass, WZ_ZMass, WZ_WPt, WZ_ZPt;
    vector<float> *ZZ_ZMass = new std::vector<float>(), *ZZ_ZPt = new std::vector<float>();
    Float_t ZZ_totalMass, ZZ_ZMass1, ZZ_ZMass2, ZZ_ZPt1, ZZ_ZPt2;

    TBranch *b_WZ_WMass      = T->Branch("WZ_WMass"          , &WZ_WMass            ,   "WZ_WMass/F"           );
    TBranch *b_WZ_ZMass      = T->Branch("WZ_ZMass"          , &WZ_ZMass            ,   "WZ_ZMass/F"           );
    TBranch *b_WZ_WPt      = T->Branch("WZ_WPt"          , &WZ_WPt            ,   "WZ_WPt/F"           );
    TBranch *b_WZ_ZPt      = T->Branch("WZ_ZPt"          , &WZ_ZPt            ,   "WZ_ZPt/F"           );
    TBranch *b_ZZ_totalMass      = T->Branch("ZZ_totalMass"          , &ZZ_totalMass            ,   "ZZ_totalMass/F"           );
    TBranch *b_ZZ_ZMass      = T->Branch("ZZ_ZMass"          , &ZZ_ZMass      );
    TBranch *b_ZZ_ZPt      = T->Branch("ZZ_ZPt"          , &ZZ_ZPt      );

    //-----------------------------
    // loop over events
    //-----------------------------

    Long64_t nentries = T->GetEntries();

    for (Long64_t i=0;i<nentries;i++) {

        if (i%10000 == 1)
            cout << "Processing event " << i << endl;

        T->GetEntry(i);

        //if( lep_n < 2 ){
            ////cout << "ERROR! Found only " << lep_n << " leptons" << endl;
            ////exit(0);
            //// Make sure this doesn't pass event selection
            //mmtrig = 0;
            //eetrig = 0;
            //emtrig = 0;
            //// Fill everything with zeros
            //SRZ = 0;
            //CRT = 0;
            //CRFS = 0;
            //VRT = 0;
            //VRS = 0;
            //CRZ = 0;
            //VRZ = 0;
            //EdgeSRLow = 0;
            //EdgeSRMed = 0;
            //EdgeSRHigh = 0;
            //EdgeVRLow = 0;
            //EdgeVRMed = 0;
            //EdgeVRHigh = 0;
            //EdgeCRTLow = 0;
            //EdgeCRTMed = 0;
            //EdgeCRTHigh = 0;
            //EdgeVRTLow = 0;
            //EdgeVRTMed = 0;
            //EdgeVRTHigh = 0;
            //VR3L = 0;
            //VRWZ = 0;
            //VRZZ = 0;
            //b_goodMuons->Fill();      
            //b_EdgeSRLow->Fill();
            //b_EdgeSRMed->Fill();
            //b_EdgeSRHigh->Fill();
            //b_EdgeVRLow->Fill();
            //b_EdgeVRMed->Fill();
            //b_EdgeVRHigh->Fill();
            //b_EdgeCRTLow->Fill();
            //b_EdgeCRTMed->Fill();
            //b_EdgeCRTHigh->Fill();
            //b_EdgeVRTLow->Fill();
            //b_EdgeVRTMed->Fill();
            //b_EdgeVRTHigh->Fill();
            //b_SRZ->Fill();
            //b_CRT->Fill();
            //b_CRFS->Fill();
            //b_VRT->Fill();
            //b_VRS->Fill();
            //b_CRZ->Fill();
            //b_VRZ->Fill();
            //b_VRWZ->Fill();
            //b_WZ_WMass->Fill();
            //b_WZ_ZMass->Fill();
            //b_WZ_WPt->Fill();
            //b_WZ_ZPt->Fill();
            //b_VRZZ->Fill();
            //b_ZZ_totalMass->Fill();
            //b_ZZ_ZMass->Fill();
            //b_ZZ_ZPt->Fill();
            //b_VR3L->Fill();
            //continue;
        //}

        //-----------------------------
        // good muons
        //-----------------------------
        
        //if (channel==0 && mu_isBad->size()>=2) {
            //goodMuons = (mu_isBad->at(0)==0 && mu_isBad->at(1)==0);
        //}
        //else if (channel==1) {
            //goodMuons = 1;
        //}
        //else if (channel>=2 && mu_isBad->size()>=1) {
            //goodMuons = (mu_isBad->at(0)==0);
        //}
        //else {
            //goodMuons = 0;
        //}

        goodMuons = 1;
        b_goodMuons->Fill();      

        //-----------------------------
        // regions
        //-----------------------------
        
        //int trigger = ((channel==0 && mmtrig && mmtrig_match) || (channel==1 && eetrig && eetrig_match) || (channel>=2 && emtrig && emtrig_match));
        int trigger = 1;
        int mllMin40 = (mll>40);
        int mllMin12 = (mll>12);
        int ZWindow = (mll>81 && mll<101);
        int OffZWindow = (mll<81 || mll>101);
        int dPhiJetMET = (DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4);
        int HTincl600 = (HTincl>600);
        int lepReq5025 = 0;
        int lepReq2525 = 0;
        int OS = is_OS;
        int DS = !is_OS;
        int SF = (channel==0 || channel==1);
        int DF = (channel==2 || channel==3);

        if (lep_pT->size()>=2) {
            lepReq5025 = (lep_pT->at(0)>50 && lep_pT->at(1)>25);
            lepReq2525 = (lep_pT->at(0)>25 && lep_pT->at(1)>25);
            //OS = (lep_pdgId->at(0)*lep_pdgId->at(1) < 0);
            //SF = (abs(lep_pdgId->at(0)) == abs(lep_pdgId->at(1)));
            //DF = !SF;
        }

        int jetReq = 0;
        if (jet_pT->size()>=2) {
            jetReq = (jet_pT->at(0)>30 && jet_pT->at(1)>30);
        }

        //EDGE regions

        int edgeReq = trigger * goodMuons * mllMin12 * lepReq2525 * jetReq * dPhiJetMET * OS;

        MET = MET_vec->at(0);

    //std::cout<<"Checkpoint "<<__LINE__<<" "<<trigger<<std::endl;
    //std::cout<<"Checkpoint "<<__LINE__<<" "<<goodMuons<<std::endl;
    //std::cout<<"Checkpoint "<<__LINE__<<" "<<mllMin12<<std::endl;
    //std::cout<<"Checkpoint "<<__LINE__<<" "<<lepReq2525<<std::endl;
    //std::cout<<"Checkpoint "<<__LINE__<<" "<<jetReq<<std::endl;
    //std::cout<<"Checkpoint "<<__LINE__<<" "<<dPhiJetMET<<std::endl;
    //std::cout<<"Checkpoint "<<__LINE__<<" "<<OS<<std::endl;
    //std::cout<<"Checkpoint "<<__LINE__<<" "<<edgeReq<<std::endl;

        EdgeSRLow = edgeReq * SF * (MET>200);
        EdgeSRMed = edgeReq * SF * (MET>200) * (HT>400);
        EdgeSRHigh = edgeReq * SF * (MET>200) * (HT>700);
        EdgeVRLow = edgeReq * SF * (MET>100 && MET<200);
        EdgeVRMed = edgeReq * SF * (MET>100 && MET<200) * (HT>400);
        EdgeVRHigh = edgeReq * SF * (MET>100 && MET<200) * (HT>700);

        EdgeCRTLow = edgeReq * DF * (MET>200);
        EdgeCRTMed = edgeReq * DF * (MET>200) * (HT>400);
        EdgeCRTHigh = edgeReq * DF * (MET>200) * (HT>700);
        EdgeVRTLow = edgeReq * DF * (MET>100 && MET<200);
        EdgeVRTMed = edgeReq * DF * (MET>100 && MET<200) * (HT>400);
        EdgeVRTHigh = edgeReq * DF * (MET>100 && MET<200) * (HT>700);

        b_EdgeSRLow->Fill();
        b_EdgeSRMed->Fill();
        b_EdgeSRHigh->Fill();
        b_EdgeVRLow->Fill();
        b_EdgeVRMed->Fill();
        b_EdgeVRHigh->Fill();
        b_EdgeCRTLow->Fill();
        b_EdgeCRTMed->Fill();
        b_EdgeCRTHigh->Fill();
        b_EdgeVRTLow->Fill();
        b_EdgeVRTMed->Fill();
        b_EdgeVRTHigh->Fill();

        //Z regions
        
        int ZReq = trigger * goodMuons * mllMin40 * lepReq5025 * jetReq * dPhiJetMET * OS * HTincl600;

        SRZ = ZReq * ZWindow * SF * (MET>225);
        CRZ = ZReq * ZWindow * SF * (MET<60);

        VRZ = ZReq * ZWindow * SF * (MET<225);
        VRS = ZReq * ZWindow * SF * (MET>100 && MET<200);

        CRT = ZReq * OffZWindow * SF * (MET>225);
        VRT = ZReq * OffZWindow * SF * (MET>100 && MET<200);

        b_SRZ->Fill();
        b_CRT->Fill();
        b_CRFS->Fill();
        b_VRT->Fill();
        b_VRS->Fill();
        b_CRZ->Fill();
        b_VRZ->Fill();

        //Diboson regions
        
        //VRWZ = trigger * goodMuons * (lep_n==3) * (MET>50 && MET<200) * (bjet_n==0);
        VRWZ = trigger * goodMuons * (mu_n+el_n==3) * (MET>50 && MET<200);

        if (VRWZ) {

            VRWZ *= (lep_pT->at(0)>50 && lep_pT->at(1)>25 && lep_pT->at(2)>25);

            TLorentzVector p0;
            p0.SetPtEtaPhiM(lep_pT->at(0),lep_eta->at(0),lep_phi->at(0),0);
            TLorentzVector p1;
            p1.SetPtEtaPhiM(lep_pT->at(1),lep_eta->at(1),lep_phi->at(1),0);
            TLorentzVector p2;
            p2.SetPtEtaPhiM(lep_pT->at(2),lep_eta->at(2),lep_phi->at(2),0);
            TLorentzVector pMET;
            pMET.SetPtEtaPhiM(MET,0,MET_phi->at(0),0);

            float m_01 = (p0+p1).M();
            float m_02 = (p0+p2).M();
            float m_12 = (p1+p2).M();

            float pt_01 = (p0+p1).Pt();
            float pt_02 = (p0+p2).Pt();
            float pt_12 = (p1+p2).Pt();

            float dmZ_01 = abs((p0+p1).M() - 91.2);
            float dmZ_02 = abs((p0+p2).M() - 91.2);
            float dmZ_12 = abs((p1+p2).M() - 91.2);

            // This section was commented out for some reason
            // If there is not an OSSF pair, the event is false
            if ((lep_pdgId->at(0) != -lep_pdgId->at(1)) && (lep_pdgId->at(0) != -lep_pdgId->at(2)) && (lep_pdgId->at(1) != -lep_pdgId->at(2)))
                VRWZ=0;

            // If a pair is not OSSF, take it out of the running for best Z pair
            if (lep_pdgId->at(0) != -lep_pdgId->at(1))
                dmZ_01 = 999999999;
            if (lep_pdgId->at(0) != -lep_pdgId->at(2))
                dmZ_02 = 999999999;
            if (lep_pdgId->at(1) != -lep_pdgId->at(2))
                dmZ_12 = 999999999;
            // This section was commented out for some reason

            if ((dmZ_01 <= dmZ_02) && (dmZ_01 <= dmZ_12)) {
                WZ_WMass = sqrt(2*p2.Pt()*MET*(1-cos(p2.Phi()-MET_phi->at(0))));
                WZ_ZMass = m_01;
                WZ_WPt = (p2+pMET).Pt();
                WZ_ZPt = pt_01;
            }
            else if ((dmZ_02 <= dmZ_01) && (dmZ_02 <= dmZ_12)) {
                WZ_WMass = sqrt(2*p1.Pt()*MET*(1-cos(p1.Phi()-MET_phi->at(0))));
                WZ_ZMass = m_02;
                WZ_WPt = (p1+pMET).Pt();
                WZ_ZPt = pt_02;
            }
            else {
                WZ_WMass = sqrt(2*p0.Pt()*MET*(1-cos(p0.Phi()-MET_phi->at(0))));
                WZ_ZMass = m_12;
                WZ_WPt = (p0+pMET).Pt();
                WZ_ZPt = pt_12;
            }

            VRWZ *= (WZ_WMass<100);
        }

        if (!VRWZ) {
            WZ_WMass = 0;
            WZ_ZMass = 0;
            WZ_WPt = 0;
            WZ_ZPt = 0;
        }

        b_VRWZ->Fill();
        b_WZ_WMass->Fill();
        b_WZ_ZMass->Fill();
        b_WZ_WPt->Fill();
        b_WZ_ZPt->Fill();

        //VR-ZZ

        //VRZZ = trigger * goodMuons * (lep_n==4) * (MET<100) * (bjet_n==0); 
        VRZZ = trigger * goodMuons * (mu_n+el_n==4) * (MET<100);

        if (VRZZ) {

            VRZZ *= (lep_pT->at(0)>50 && lep_pT->at(1)>25 && lep_pT->at(2)>25 && lep_pT->at(3)>25); 

            TLorentzVector p0;
            p0.SetPtEtaPhiM(lep_pT->at(0),lep_eta->at(0),lep_phi->at(0),0);
            TLorentzVector p1;
            p1.SetPtEtaPhiM(lep_pT->at(1),lep_eta->at(1),lep_phi->at(1),0);
            TLorentzVector p2;
            p2.SetPtEtaPhiM(lep_pT->at(2),lep_eta->at(2),lep_phi->at(2),0);
            TLorentzVector p3;
            p3.SetPtEtaPhiM(lep_pT->at(3),lep_eta->at(3),lep_phi->at(3),0);
            TLorentzVector pMET;
            pMET.SetPtEtaPhiM(MET,0,MET_phi->at(0),0);

            float m_01 = (p0+p1).M();
            float m_02 = (p0+p2).M();
            float m_03 = (p0+p3).M();
            float m_12 = (p1+p2).M();
            float m_13 = (p1+p3).M();
            float m_23 = (p2+p3).M();

            float m_0123 = (p0+p1+p2+p3).M();

            float pt_01 = (p0+p1).Pt();
            float pt_02 = (p0+p2).Pt();
            float pt_03 = (p0+p3).Pt();
            float pt_12 = (p1+p2).Pt();
            float pt_13 = (p1+p3).Pt();
            float pt_23 = (p2+p3).Pt();

            float dmZ_01 = abs((p0+p1).M() - 91.2);
            float dmZ_02 = abs((p0+p2).M() - 91.2);
            float dmZ_03 = abs((p0+p3).M() - 91.2);
            float dmZ_12 = abs((p1+p2).M() - 91.2);
            float dmZ_13 = abs((p1+p3).M() - 91.2);
            float dmZ_23 = abs((p2+p3).M() - 91.2);

            //int OSSF_01 = (lep_pdgId->at(0)==-lep_pdgId->at(1));
            //int OSSF_02 = (lep_pdgId->at(0)==-lep_pdgId->at(2));
            //int OSSF_03 = (lep_pdgId->at(0)==-lep_pdgId->at(3));
            //int OSSF_12 = (lep_pdgId->at(1)==-lep_pdgId->at(2));
            //int OSSF_13 = (lep_pdgId->at(1)==-lep_pdgId->at(3));
            //int OSSF_23 = (lep_pdgId->at(2)==-lep_pdgId->at(3));

            //int twoOSSFPairs = ((OSSF_01 && OSSF_23) || (OSSF_02 && OSSF_13) || (OSSF_03 && OSSF_12));
            //int allSF = (abs(lep_pdgId->at(0)) == abs(lep_pdgId->at(1)) == abs(lep_pdgId->at(2)) == abs(lep_pdgId->at(3)));
            //VRZZ *= twoOSSFPairs;

            //vector<float> vec_ZZ_ZMass, vec_ZZ_ZPt;

            //if (twoOSSFPairs) {

                //float mass1, mass2, pt1, pt2;

                //if (OSSF_01 && OSSF_23) {
                    //if (m_01>m_23) {
                        //mass1 = m_01;
                        //pt1 = pt_01;
                        //mass2 = m_23;
                        //pt2 = pt_23;
                    //}
                    //else {
                        //mass1 = m_23;
                        //pt1 = pt_23;
                        //mass2 = m_01;
                        //pt2 = pt_01;
                    //}
                //}
                //else if (OSSF_02 && OSSF_13) {
                    //if (m_02>m_13) {
                        //mass1 = m_02;
                        //pt1 = pt_02;
                        //mass2 = m_13;
                        //pt2 = pt_13;
                    //}
                    //else {
                        //mass1 = m_13;
                        //pt1 = pt_13;
                        //mass2 = m_02;
                        //pt2 = pt_02;
                    //}
                //}
                //else if (OSSF_03 && OSSF_12) {
                    //if (m_03>m_12) {
                        //mass1 = m_03;
                        //pt1 = pt_03;
                        //mass2 = m_12;
                        //pt2 = pt_12;
                    //}
                    //else {
                        //mass1 = m_12;
                        //pt1 = pt_12;
                        //mass2 = m_03;
                        //pt2 = pt_03;
                    //}
                //}
                //if (allSF) {
                    //if (OSSF_01) {
                        //if (OSSF_02) {
                            //if (dmZ_01+dmZ_23 < dmZ_02+dmZ_13) {
                                //if (m_01>m_23) {
                                    //mass1 = m_01;
                                    //pt1 = pt_01;
                                    //mass2 = m_23;
                                    //pt2 = pt_23;
                                //}
                                //else {
                                    //mass1 = m_23;
                                    //pt1 = pt_23;
                                    //mass2 = m_01;
                                    //pt2 = pt_01;
                                //}
                            //}
                            //else {
                                //if (m_02>m_13) {
                                    //mass1 = m_02;
                                    //pt1 = pt_02;
                                    //mass2 = m_13;
                                    //pt2 = pt_13;
                                //}
                                //else {
                                    //mass1 = m_13;
                                    //pt1 = pt_13;
                                    //mass2 = m_02;
                                    //pt2 = pt_02;
                                //}
                            //}
                        //}
                        //else {
                            //if (dmZ_01+dmZ_23 < dmZ_03+dmZ_12) {
                                //if (m_01>m_23) {
                                    //mass1 = m_01;
                                    //pt1 = pt_01;
                                    //mass2 = m_23;
                                    //pt2 = pt_23;
                                //}
                                //else {
                                    //mass1 = m_23;
                                    //pt1 = pt_23;
                                    //mass2 = m_01;
                                    //pt2 = pt_01;
                                //}
                            //}
                            //else {
                                //if (m_03>m_12) {
                                    //mass1 = m_03;
                                    //pt1 = pt_03;
                                    //mass2 = m_12;
                                    //pt2 = pt_12;
                                //}
                                //else {
                                    //mass1 = m_12;
                                    //pt1 = pt_12;
                                    //mass2 = m_03;
                                    //pt2 = pt_03;
                                //}
                            //}
                        //}
                    //}
                    //else {
                        //if (dmZ_02+dmZ_13 < dmZ_03+dmZ_12) {
                            //if (m_02>m_13) {
                                //mass1 = m_02;
                                //pt1 = pt_02;
                                //mass2 = m_13;
                                //pt2 = pt_13;
                            //}
                            //else {
                                //mass1 = m_13;
                                //pt1 = pt_13;
                                //mass2 = m_02;
                                //pt2 = pt_02;
                            //}
                        //}
                        //else {
                            //if (m_03>m_12) {
                                //mass1 = m_03;
                                //pt1 = pt_03;
                                //mass2 = m_12;
                                //pt2 = pt_12;
                            //}
                            //else {
                                //mass1 = m_12;
                                //pt1 = pt_12;
                                //mass2 = m_03;
                                //pt2 = pt_03;
                            //}
                        //}
                    //}
                //}

                //ZZ_ZMass->clear();
                //ZZ_ZMass->push_back(mass1);
                //ZZ_ZMass->push_back(mass2);
                //ZZ_ZPt->clear();
                //ZZ_ZPt->push_back(pt1);
                //ZZ_ZPt->push_back(pt2);

                ////ZZ_ZMass = {mass1, mass2};
                ////ZZ_ZPt = {pt1, pt2};

                ////ZZ_ZMass1 = mass1;
                ////ZZ_ZMass2 = mass2;
                ////ZZ_ZPt1 = pt1;
                ////ZZ_ZPt2 = pt2;
                
                //ZZ_totalMass = m_0123;
            //}
        }

        if(!VRZZ) {
            //ZZ_ZMass1 = 0;
            //ZZ_ZMass2 = 0;
            //ZZ_ZPt1 = 0;
            //ZZ_ZPt2 = 0;
            ZZ_totalMass = 0;
            ZZ_ZMass->clear();
            ZZ_ZPt->clear();
        }

        b_VRZZ->Fill();
        //b_ZZ_ZMass1->Fill();
        //b_ZZ_ZMass2->Fill();
        //b_ZZ_ZPt1->Fill();
        //b_ZZ_ZPt2->Fill();
        b_ZZ_totalMass->Fill();
        b_ZZ_ZMass->Fill();
        b_ZZ_ZPt->Fill();

        //VR-3L
        //VR3L = trigger * goodMuons * (lep_n>=3) * (MET>60 && MET<100) * (HTincl>200) * (jet_n>=2) * ZWindow * OS * SF * dPhiJetMET;
        VR3L = trigger * goodMuons * (mu_n+el_n>=3) * (MET>60 && MET<100) * (HTincl>200) * (jet_n>=2) * ZWindow * OS * SF * dPhiJetMET;
        if (VR3L) {
            VR3L *= (lep_pT->at(0)>50 && lep_pT->at(1)>25 && lep_pT->at(2)>25); 
        }
        b_VR3L->Fill();
    }

    //T->Print();
    T->Write();
    delete f;
}
*/

void addEventCountBranchToSample(string sampleID, string pathToNtuples, TString treeName="outputTree") {

    string filename = Form("%s/%s.root",pathToNtuples.c_str(),sampleID.c_str()); 
    TFile* f = new TFile(filename.c_str(), "update");
    if( !f->IsOpen() ) return;
    Float_t _nGenEvents = ((TH1F*) f->Get("EventCountHist"))->GetBinContent(2);
    TTree* T = (TTree*)f->Get(treeName);

    cout << endl;
    cout << "Opening file           : " << filename        << endl;
    cout << "Events in ntuple       : " << T->GetEntries() << endl;
    cout << "Total generated events : " << _nGenEvents     << endl;

    if( _nGenEvents < 1e-10 ) cout << "ERROR 0 EVENTS -----------------------------------------------------" << endl;

    //-----------------------------
    // add new branch
    //-----------------------------

    Float_t nGenEvents;

    TBranch *b_nEvents = T->Branch("nGenEvents", &nGenEvents, "nGenEvents/F");

    Long64_t nentries = T->GetEntries();

    for (Long64_t i=0;i<nentries;i++) {

        T->GetEntry(i);

        //if not data
        if (sampleID.find("data") == std::string::npos) {

            nGenEvents = _nGenEvents;
            b_nEvents->Fill();     
        }
    }

    T->Write();
    delete f;
}
