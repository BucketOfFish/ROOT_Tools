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

vector<string> noSampleWeight;
vector<string> noEventWeight;

void addWeightsToSample(string sampleID, string pathToNtuples, TString treeName="outputTree");

void addWeight( string pathToNtuples = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/v1_02/MC/") {

  //------------------------------------------------------------------------------------------------------------------
  // ALL SAMPLES
  // Several samples are omitted from the SUSY cross section file:
  // https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/SUSYPhys/SUSYTools/trunk/data/susy_crosssections_13TeV.txt
  // These samples have sampleWeight=0 and are currently omitted, NEED TO ADD THESE BACK IN
  //------------------------------------------------------------------------------------------------------------------

  //vector<TString> treeNamePrefixes = {"EG_RESOLUTION_ALL", "EL_EFF_ID_TotalCorrUncertainty", "EL_EFF_Iso_TotalCorrUncertainty", "EL_EFF_Reco_TotalCorrUncertainty", "EL_EFF_Trigger_TotalCorrUncertainty", "JET_GroupedNP_1", "JET_GroupedNP_2", "JET_GroupedNP_3", "MUONS_ID", "MUONS_MS", "MUONS_SCALE", "MUON_EFF_STAT", "MUON_EFF_STAT_LOWPT", "MUON_EFF_SYS", "MUON_EFF_SYS_LOWPT", "MUON_EFF_TrigStatUncertainty", "MUON_EFF_TrigSystUncertainty", "MUON_ISO_STAT", "MUON_ISO_SYS"};
  vector<TString> treeNames = {"outputTree"};

  //for (int i=0; i<treeNamePrefixes.size(); i++) {
	  //treeNames.push_back("outputTree_" + treeNamePrefixes[i] + "__1up");
	  //treeNames.push_back("outputTree_" + treeNamePrefixes[i] + "__1down");
  //}
  //treeNames.push_back("outputTree_MET_SoftTrk_ResoPara");
  //treeNames.push_back("outputTree_MET_SoftTrk_ResoPerp");
  //treeNames.push_back("outputTree_MET_SoftTrk_ScaleDown");
  //treeNames.push_back("outputTree_MET_SoftTrk_ScaleUp");
  //treeNames.push_back("outputTree_JET_JER_SINGLE_NP__1up");

  //vector<int> samples = {342556, 361377, 361401, 361426, 361475, 361607, 370019, 370043, 372971, 373000, 373024, 410021,
      //361063, 361378, 361402, 361427, 361476, 361608, 370020, 370044, 372972, 373001, 373025, 410022,
      //361064, 361379, 361403, 361428, 361477, 361609, 370021, 370045, 372973, 373002, 373026, 410023,
      //361065, 361380, 361404, 361429, 361478, 361610, 370022, 372950, 372974, 373003, 373027, 410050,
      //361066, 361381, 361405, 361430, 361479, 370023, 372951, 372975, 373004, 373028, 410064,
      //361067, 361382, 361406, 361431, 361480, 370000, 370024, 372952, 372976, 373005, 373029, 410065,
      //361068, 361383, 361407, 361433, 361481, 370001, 370025, 372953, 372977, 373006, 373030, 410066,
      //361069, 361384, 361408, 361434, 361482, 370002, 370026, 372954, 372978, 373007, 373031, 410067,
      //361070, 361385, 361409, 361435, 361483, 370003, 370027, 372955, 372979, 373008, 373032, 410068,
      //361071, 361386, 361410, 361436, 361484, 370004, 370028, 372956, 372980, 373009, 373033, 410081,
      //361072, 361387, 361411, 361437, 361485, 370005, 370029, 372957, 372981, 373010, 373034, 410111,
      //361073, 361388, 361412, 361438, 361486, 370006, 370030, 372958, 372982, 373011, 373035, 410112,
      //361077, 361389, 361414, 361439, 361487, 370007, 370031, 372959, 372983, 373012, 373036, 410113,
      //361084, 361390, 361415, 361440, 361488, 370008, 370032, 372960, 372984, 373013, 373037, 410114,
      //361086, 361391, 361416, 361441, 361489, 370009, 370033, 372961, 372985, 373014, 373038, 410115,
      //361091, 361392, 361417, 361442, 361490, 370010, 370034, 372962, 372986, 373015, 373039, 410116,
      //361093, 361393, 361418, 361443, 361491, 370011, 370035, 372963, 372987, 373016, 373040, 410159,
      //361096, 361394, 361419, 361468, 361600, 370012, 370036, 372964, 372988, 373017, 407012, 410187,
      //361108, 361395, 361420, 361469, 361601, 370013, 370037, 372965, 372989, 373018, 407019, 410188,
      //361372, 361396, 361421, 361470, 361602, 370014, 370038, 372966, 372995, 373019, 407021, 410189,
      //361373, 361397, 361422, 361471, 361603, 370015, 370039, 372967, 372996, 373020, 410000,
      //361374, 361398, 361423, 361472, 361604, 370016, 370040, 372968, 372997, 373021, 410003,
      //361375, 361399, 361424, 361473, 361605, 370017, 370041, 372969, 372998, 373022, 410015,
      //361376, 361400, 361425, 361474, 361606, 370018, 370042, 372970, 372999, 373023, 410016};

  vector<int> samples = {361432};

  for (int i=0; i<treeNames.size(); i++) {

	  TString treeName = treeNames[i];
	  //addWeightsToSample("data",pathToNtuples,treeName);
	  //addWeightsToSample("410000",pathToNtuples,treeName);
	  //addWeightsToSample("410015",pathToNtuples,treeName);
	  //addWeightsToSample("410016",pathToNtuples,treeName);
	  //addWeightsToSample("410064",pathToNtuples,treeName);
	  //addWeightsToSample("410065",pathToNtuples,treeName);
	  //for (int i=361420; i<=361443; i++)
		  //addWeightsToSample(to_string(i),pathToNtuples,treeName);
      //for (int i=361484; i<=361491; i++)
		  //addWeightsToSample(to_string(i),pathToNtuples,treeName);
	  //addWeightsToSample("361077",pathToNtuples,treeName);
	  //addWeightsToSample("372502",pathToNtuples,treeName);
	  //addWeightsToSample("372462",pathToNtuples,treeName);
	  //addWeightsToSample("372466",pathToNtuples,treeName);
      for (int j=0; j<samples.size(); j++) {
          addWeightsToSample(to_string(samples[j]),pathToNtuples,treeName);
      }
      //addWeightsToSample("410000_407012",pathToNtuples,treeName);
      //addWeightsToSample("410000_MET_lt_200",pathToNtuples,treeName);
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



void addWeightsToSample(string sampleID, string pathToNtuples, TString treeName="outputTree") {

  //bool verbose = false;

  //---------------------------------------------
  // open file, get Tree and EventCountHist
  //---------------------------------------------

  string  filename       = Form("%s/%s.root",pathToNtuples.c_str(),sampleID.c_str()); 
  TFile*  f              = new TFile(filename.c_str(),"update");      
  if( !f->IsOpen() ) return;
  TH1F*   EventCountHist = (TH1F*) f->Get("EventCountHist");
  Float_t _nGenEvents    = EventCountHist->GetBinContent(2);
  TTree*  T              = (TTree*)f->Get(treeName);
    
  cout << endl;
  cout << "Opening file           : " << filename        << endl;
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
  double  eetrigweight;
  double  mmtrigweight;
  double  emtrigweight;
  double  trigweight;
  Long64_t  channel;
  Long64_t  lep_n;
  Long64_t  jet_n;
  Long64_t  is_OS;
  double  MET;
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
  T->SetBranchAddress("eetrigweight"    ,&eetrigweight     );
  T->SetBranchAddress("mmtrigweight"    ,&mmtrigweight     );
  T->SetBranchAddress("emtrigweight"    ,&emtrigweight     );
  T->SetBranchAddress("trigweight"      ,&trigweight       );
  T->SetBranchAddress("channel"         ,&channel          );
  T->SetBranchAddress("lep_weight"      ,&lep_weight       );
  T->SetBranchAddress("lep_pdgId"       ,&lep_pdgId        );
  T->SetBranchAddress("mu_isBad"       ,&mu_isBad        );
  T->SetBranchAddress("lep_pT"          ,&lep_pT           );
  //T->SetBranchAddress("el_pT"           ,&el_pT            );
  //T->SetBranchAddress("mu_pT"           ,&mu_pT            );
  T->SetBranchAddress("lep_eta"         ,&lep_eta          );
  T->SetBranchAddress("lep_phi"         ,&lep_phi          );
  T->SetBranchAddress("lep_n"           ,&lep_n            );
  T->SetBranchAddress("mll"             ,&mll              );
  T->SetBranchAddress("MET"             ,&MET              );
  T->SetBranchAddress("HT"              ,&HT               );
  T->SetBranchAddress("HTincl"          ,&HTincl           );
  T->SetBranchAddress("MET"             ,&MET              );
  T->SetBranchAddress("jet_n"           ,&jet_n            );
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

  //Float_t trigweight;
  //Float_t trigweight_noemuSF;
  Float_t nGenEvents;
  Float_t weight1fb;
  Float_t lepweight;

  Float_t eetrigweight_fix;
  Float_t mmtrigweight_fix;
  Float_t emtrigweight_fix;
  Float_t trigweight_fix;
  Float_t emtrigweight_noemusf_fix;
  Float_t trigweight_noemusf_fix;

  Float_t eetrigweight_fix_up;
  Float_t mmtrigweight_fix_up;
  Float_t emtrigweight_fix_up;
  Float_t trigweight_fix_up;
  Float_t emtrigweight_noemusf_fix_up;
  Float_t trigweight_noemusf_fix_up;

  Int_t goodMuons;

  //TBranch *b_trigw       = T->Branch("trigweight"         , &trigweight           ,   "trigweight/F"          );
  //TBranch *b_trigw2      = T->Branch("trigweight_noemuSF" , &trigweight_noemuSF   ,   "trigweight_noemuSF/F"  );
  TBranch *b_weight      = T->Branch("weight1fb"          , &weight1fb            ,   "weight1fb/F"           );
  TBranch *b_lepw        = T->Branch("lepweight"          , &lepweight            ,   "lepweight/F"           );
  TBranch *b_nEvents     = T->Branch("nGenEvents"         , &nGenEvents           ,   "nGenEvents/F"          );

  //TBranch *b_goodMuons      = T->Branch("good_Muons"          , &goodMuons            ,   "goodMuons/I"           );

  TBranch *b_eef         = T->Branch("eetrigweight_fix"         , &eetrigweight_fix          ,   "eetrigweight_fix/F"          );
  TBranch *b_mmf         = T->Branch("mmtrigweight_fix"         , &mmtrigweight_fix          ,   "mmtrigweight_fix/F"          );
  TBranch *b_emf         = T->Branch("emtrigweight_fix"         , &emtrigweight_fix          ,   "emtrigweight_fix/F"          );
  TBranch *b_f           = T->Branch("trigweight_fix"           , &trigweight_fix            ,   "trigweight_fix/F"            );
  TBranch *b_emf2        = T->Branch("emtrigweight_noemusf_fix" , &emtrigweight_noemusf_fix  ,   "emtrigweight_noemusf_fix/F"  );
  TBranch *b_f2          = T->Branch("trigweight_noemusf_fix"   , &trigweight_noemusf_fix    ,   "trigweight_noemusf_fix/F"    );

  TBranch *b_eefup       = T->Branch("eetrigweight_fix_up"         , &eetrigweight_fix_up          ,   "eetrigweight_fix_up/F"          );
  TBranch *b_mmfup       = T->Branch("mmtrigweight_fix_up"         , &mmtrigweight_fix_up          ,   "mmtrigweight_fix_up/F"          );
  TBranch *b_emfup       = T->Branch("emtrigweight_fix_up"         , &emtrigweight_fix_up          ,   "emtrigweight_fix_up/F"          );
  TBranch *b_fup         = T->Branch("trigweight_fix_up"           , &trigweight_fix_up            ,   "trigweight_fix_up/F"            );
  TBranch *b_emf2up      = T->Branch("emtrigweight_noemusf_fix_up" , &emtrigweight_noemusf_fix_up  ,   "emtrigweight_noemusf_fix_up/F"  );
  TBranch *b_f2up        = T->Branch("trigweight_noemusf_fix_up"   , &trigweight_noemusf_fix_up    ,   "trigweight_noemusf_fix_up/F"    );

  //-----------------------------
  // loop over events
  //-----------------------------

  Long64_t nentries = T->GetEntries();

  for (Long64_t i=0;i<nentries;i++) {
  //for (Long64_t i=0;i<10;i++) {
    T->GetEntry(i);

    if( lep_n < 2 ){
      cout << "ERROR! Found only " << lep_n << " leptons" << endl;
      exit(0);
    }

    //------------------------------------------------------------------------
    // NOMINAL: pick two highest pT leptons
    //------------------------------------------------------------------------

    //--- trigger weight
    
    eetrigweight_fix         = 1.0;
    mmtrigweight_fix         = 1.0;
    emtrigweight_fix         = 1.0;
    trigweight_fix           = 1.0;
    emtrigweight_noemusf_fix = 1.0;
    trigweight_noemusf_fix   = 1.0;

    eetrigweight_fix_up         = 1.0;
    mmtrigweight_fix_up         = 1.0;
    emtrigweight_fix_up         = 1.0;
    trigweight_fix_up           = 1.0;
    emtrigweight_noemusf_fix_up = 1.0;
    trigweight_noemusf_fix_up   = 1.0;

    // ee channel
    if( channel == 1 ){
      //if( el_pT->at(0) > 65 ) eetrigweight_fix = sf_trig_HLT_e60_lhmedium; // single electron

      // single electron
      if( lep_pT->at(0) > 65 ){
    eetrigweight_fix    = sf_trig_HLT_e60_lhmedium; 
    eetrigweight_fix_up = sf_trig_HLT_e60_lhmedium + sfunc_trig_HLT_e60_lhmedium; 
      }

      // dielectron
      else{
    eetrigweight_fix    = sf_trig_HLT_2e12_lhloose; 
    eetrigweight_fix_up = sf_trig_HLT_2e12_lhloose + sfunc_trig_HLT_2e12_lhloose;
      }

      // combined
      trigweight_fix            = eetrigweight_fix;
      trigweight_fix_up         = eetrigweight_fix_up;

      trigweight_noemusf_fix    = eetrigweight_fix;
      trigweight_noemusf_fix_up = eetrigweight_fix_up;

      // if( lep_pT->at(0) > 65 ) eetrigweight_fix = sf_trig_HLT_e60_lhmedium; // single electron
      // else                     eetrigweight_fix = sf_trig_HLT_2e12_lhloose; // dielectron

      // trigweight_fix         = eetrigweight_fix;
      // trigweight_noemusf_fix = eetrigweight_fix;
    }

    // mm channel
    else if( channel == 0 ){
      //if( mu_pT->at(0) > 55 ) mmtrigweight_fix = sf_trig_HLT_mu50;         // single muon

      // single muon
      if( lep_pT->at(0) > 55 ){
    mmtrigweight_fix    = sf_trig_HLT_mu50;
    mmtrigweight_fix_up = sf_trig_HLT_mu50 + sfunc_trig_HLT_mu50;
      }

      // dimuon
      else{
    mmtrigweight_fix    = sf_trig_HLT_mu18_mu8noL1; 
    mmtrigweight_fix_up = sf_trig_HLT_mu18_mu8noL1 + sfunc_trig_HLT_mu18_mu8noL1; 
      }

      // combined
      trigweight_fix            = mmtrigweight_fix;
      trigweight_fix_up         = mmtrigweight_fix_up;

      trigweight_noemusf_fix    = mmtrigweight_fix;
      trigweight_noemusf_fix_up = mmtrigweight_fix_up;

      // if( lep_pT->at(0) > 55 ) mmtrigweight_fix = sf_trig_HLT_mu50;         // single muon
      // else                     mmtrigweight_fix = sf_trig_HLT_mu18_mu8noL1; // dimuon

      // trigweight_fix         = mmtrigweight_fix;
      // trigweight_noemusf_fix = mmtrigweight_fix;
    }

    // mm channel
    else if( channel == 2 || channel == 3 ){

      float elpt = lep_pT->at(0);
      float mupt = lep_pT->at(1);

      if( channel == 3 ){
        elpt = lep_pT->at(1);
        mupt = lep_pT->at(0);
      }

      // single electron
      if( elpt > 65 ){
    emtrigweight_fix            = sf_trig_HLT_e60_lhmedium; 
    emtrigweight_noemusf_fix    = sf_trig_HLT_e60_lhmedium; 

    emtrigweight_fix_up         = sf_trig_HLT_e60_lhmedium + sfunc_trig_HLT_e60_lhmedium; 
    emtrigweight_noemusf_fix_up = sf_trig_HLT_e60_lhmedium + sfunc_trig_HLT_e60_lhmedium; 
      }

      // single muon
      else if( mupt > 55 ){
    emtrigweight_fix            = sf_trig_HLT_mu50;        
    emtrigweight_noemusf_fix    = sf_trig_HLT_mu50;        

    emtrigweight_fix_up         = sf_trig_HLT_mu50 + sfunc_trig_HLT_mu50;        
    emtrigweight_noemusf_fix_up = sf_trig_HLT_mu50 + sfunc_trig_HLT_mu50;                
      }

      // electron-muon
      else{

    // e-mu
    if( elpt > mupt ){
      emtrigweight_fix    = sf_trig_HLT_e17_lhloose_mu14; 
      emtrigweight_fix_up = sf_trig_HLT_e17_lhloose_mu14 + sfunc_trig_HLT_e17_lhloose_mu14; 
    }

    // mu-e
    else{
      emtrigweight_fix    = sf_trig_HLT_e7_lhmedium_mu24; 
      emtrigweight_fix_up = sf_trig_HLT_e7_lhmedium_mu24 + sfunc_trig_HLT_e7_lhmedium_mu24; 
    }
      }

      // combined
      trigweight_fix            = emtrigweight_fix;
      trigweight_noemusf_fix    = emtrigweight_noemusf_fix;

      trigweight_fix_up         = emtrigweight_fix_up;
      trigweight_noemusf_fix_up = emtrigweight_noemusf_fix_up;


    
      // // single electron
      // if( elpt > 65.0 ){
      //    emtrigweight_fix         = sf_trig_HLT_e60_lhmedium; 
      //    emtrigweight_noemusf_fix = sf_trig_HLT_e60_lhmedium; 
      // }

      // // single muon
      // else if( mupt > 55.0 ){
      //    emtrigweight_fix         = sf_trig_HLT_mu50;        
      //    emtrigweight_noemusf_fix = sf_trig_HLT_mu50;        
      // }

      // // electron-muon
      // else{
      //    //if( el_pT->at(0) > mu_pT->at(0) ) emtrigweight_fix = sf_trig_HLT_e17_lhloose_mu14; // e-mu
      //    //else                              emtrigweight_fix = sf_trig_HLT_e7_lhmedium_mu24; // mu-e

      //    if( elpt > mupt ) emtrigweight_fix = sf_trig_HLT_e17_lhloose_mu14; // e-mu
      //    else              emtrigweight_fix = sf_trig_HLT_e7_lhmedium_mu24; // mu-e
      // }

      // trigweight_fix         = emtrigweight_fix;
      // trigweight_noemusf_fix = emtrigweight_noemusf_fix;
    }

    // trigweight = 1.0;
    // if     ( channel == 0                 ) trigweight = mmtrigweight;
    // else if( channel == 1                 ) trigweight = eetrigweight;
    // else if( channel == 2 || channel == 3 ) trigweight = emtrigweight;

    // trigweight_noemuSF = trigweight;
    
    // if( ( channel == 2 || channel == 3 ) && el_pT->at(0) < 65.0 && mu_pT->at(0) < 55.0 ) trigweight_noemuSF = 1.0;
    
    //--- number of generated events
    nGenEvents = _nGenEvents;

    //--- lepton SFs
    lepweight = lep_weight->at(0) * lep_weight->at(1);

    //--- weight for 1/fb
    //weight1fb = 1000.0 * sampleWeight * eventWeight * pileupWeight_rew * trigweight * lepweight / nGenEvents; // with PU
    weight1fb = 1000.0 * sampleWeight * eventWeight * lepweight / nGenEvents;                      // without PU

    goodMuons = ((channel==0 && mu_isBad->at(0)==0 && mu_isBad->at(1)==0) || (channel==1) || (channel>=2 && mu_isBad->at(0)==0));

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

    //b_trigw->Fill();       
    //b_trigw2->Fill();       

    b_weight->Fill();      
    b_lepw->Fill();        
    b_nEvents->Fill();     

    //b_goodMuons->Fill();      

    b_eef->Fill();
    b_mmf->Fill();
    b_emf->Fill();
    b_f->Fill();
    b_emf2->Fill();
    b_f2->Fill();

    b_eefup->Fill();
    b_mmfup->Fill();
    b_emfup->Fill();
    b_fup->Fill();
    b_emf2up->Fill();
    b_f2up->Fill();

    // cout << endl;
    // cout << "sampleWeight " << sampleWeight << endl;
    // cout << "eventWeight  " << eventWeight  << endl;
    // cout << "pileupWeight " << pileupWeight_rew << endl;
    // cout << "channel      " << channel      << endl;
    // cout << "trigWeight   " << trigweight   << endl;
    // cout << "lepweight    " << lepweight    << endl;
    // cout << "nGenEvents   " << nGenEvents   << endl;
    // cout << "weight1fb    " << weight1fb    << endl;

  }


  //T->Print();
  T->Write();
  delete f;

}


