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

void addWeightsToSample(string sampleID, string pathToNtuples);

void addWeight( string pathToNtuples = "/afs/cern.ch/work/b/benhoob/ZMETSamples/Current_Ntuples/v00-14/MC/" ){
//void addWeight( string pathToNtuples = "test" ){

  //addWeightsToSample(342556,pathToNtuples); // sampleWeight=0
  //addWeightsToSample(361475,pathToNtuples); // sampleWeight=0
  //addWeightsToSample(361483,pathToNtuples); // sampleWeight=0
  //addWeightsToSample(361491,pathToNtuples); // sampleWeight=0
  //addWeightsToSample(361600,pathToNtuples); // sampleWeight=0
  //addWeightsToSample(361601,pathToNtuples); // sampleWeight=0
  //addWeightsToSample(361603,pathToNtuples); // sampleWeight=0
  //addWeightsToSample(361604,pathToNtuples); // sampleWeight=0
  //addWeightsToSample(361607,pathToNtuples); // sampleWeight=0
  //addWeightsToSample(361610,pathToNtuples); // sampleWeight=0
  //addWeightsToSample(410064,pathToNtuples); // sampleWeight=0
  //addWeightsToSample(410065,pathToNtuples); // sampleWeight=0
  //addWeightsToSample(361105,pathToNtuples); // empty, need to add
  //addWeightsToSample(361485,pathToNtuples); // empty, need to add
  //addWeightsToSample(370001,pathToNtuples); // not in spreadsheet

  //------------------------------------------------------------------------------------------------------------------
  // ALL SAMPLES
  // Several samples are omitted from the SUSY cross section file:
  // https://svnweb.cern.ch/trac/atlasoff/browser/PhysicsAnalysis/SUSYPhys/SUSYTools/trunk/data/susy_crosssections_13TeV.txt
  // These samples have sampleWeight=0 and are currently omitted, NEED TO ADD THESE BACK IN
  //------------------------------------------------------------------------------------------------------------------

  vector<string> sampleID;



  sampleID.push_back("361063");
  sampleID.push_back("361064");
  sampleID.push_back("361065");
  sampleID.push_back("361066");
  sampleID.push_back("361067");
  sampleID.push_back("361068");
  sampleID.push_back("361073");
  sampleID.push_back("361077");
  sampleID.push_back("361084");
  sampleID.push_back("361086");
  sampleID.push_back("361100");
  sampleID.push_back("361101");
  sampleID.push_back("361102");
  sampleID.push_back("361103");
  sampleID.push_back("361104");
  sampleID.push_back("361106");
  sampleID.push_back("361107");
  sampleID.push_back("361108");
  sampleID.push_back("361372");
  sampleID.push_back("361373");
  sampleID.push_back("361374");
  sampleID.push_back("361375");
  sampleID.push_back("361376");
  sampleID.push_back("361377");
  sampleID.push_back("361378");
  sampleID.push_back("361379");
  sampleID.push_back("361380");
  sampleID.push_back("361381");
  sampleID.push_back("361382");
  sampleID.push_back("361383");
  sampleID.push_back("361384");
  sampleID.push_back("361385");
  sampleID.push_back("361386");
  sampleID.push_back("361387");
  sampleID.push_back("361388");
  sampleID.push_back("361389");
  sampleID.push_back("361390");
  sampleID.push_back("361391");
  sampleID.push_back("361392");
  sampleID.push_back("361393");
  sampleID.push_back("361394");
  sampleID.push_back("361395");
  sampleID.push_back("361396");
  sampleID.push_back("361397");
  sampleID.push_back("361398");
  sampleID.push_back("361399");
  sampleID.push_back("361400");
  sampleID.push_back("361401");
  sampleID.push_back("361402");
  sampleID.push_back("361403");
  sampleID.push_back("361404");
  sampleID.push_back("361405");
  sampleID.push_back("361406");
  sampleID.push_back("361407");
  sampleID.push_back("361408");
  sampleID.push_back("361409");
  sampleID.push_back("361410");
  sampleID.push_back("361411");
  sampleID.push_back("361412");
  sampleID.push_back("361413");
  sampleID.push_back("361414");
  sampleID.push_back("361415");
  sampleID.push_back("361416");
  sampleID.push_back("361417");
  sampleID.push_back("361418");
  sampleID.push_back("361419");
  sampleID.push_back("361420");
  sampleID.push_back("361421");
  sampleID.push_back("361422");
  sampleID.push_back("361423");
  sampleID.push_back("361424");
  sampleID.push_back("361425");
  sampleID.push_back("361426");
  sampleID.push_back("361427");
  sampleID.push_back("361428");
  sampleID.push_back("361429");
  sampleID.push_back("361430");
  sampleID.push_back("361431");
  sampleID.push_back("361432");
  sampleID.push_back("361433");
  sampleID.push_back("361434");
  sampleID.push_back("361435");
  sampleID.push_back("361436");
  sampleID.push_back("361437");
  sampleID.push_back("361438");
  sampleID.push_back("361439");
  sampleID.push_back("361440");
  sampleID.push_back("361441");
  sampleID.push_back("361442");
  sampleID.push_back("361443");
  sampleID.push_back("361468");
  sampleID.push_back("361469");
  sampleID.push_back("361470");
  sampleID.push_back("361471");
  sampleID.push_back("361472");
  sampleID.push_back("361473");
  sampleID.push_back("361474");
  sampleID.push_back("361475");
  sampleID.push_back("361476");
  sampleID.push_back("361477");
  sampleID.push_back("361478");
  sampleID.push_back("361479");
  sampleID.push_back("361480");
  sampleID.push_back("361481");
  sampleID.push_back("361482");
  sampleID.push_back("361483");
  //sampleID.push_back("361484"); // 0 events in ntuple, need to redo
  //sampleID.push_back("361485"); // no StreamerInfo
  sampleID.push_back("361486");
  sampleID.push_back("361487");
  sampleID.push_back("361488");
  sampleID.push_back("361489");
  sampleID.push_back("361490");
  sampleID.push_back("361491");
  sampleID.push_back("361600");
  sampleID.push_back("361601");
  sampleID.push_back("361603");
  sampleID.push_back("361604");
  sampleID.push_back("361607");
  sampleID.push_back("361610");
  sampleID.push_back("372450");
  sampleID.push_back("372451");
  sampleID.push_back("372452");
  sampleID.push_back("372453");
  sampleID.push_back("372454");
  sampleID.push_back("372455");
  sampleID.push_back("372456");
  sampleID.push_back("372457");
  sampleID.push_back("372458");
  sampleID.push_back("372459");
  sampleID.push_back("372460");
  sampleID.push_back("372461");
  sampleID.push_back("372462");
  sampleID.push_back("372463");
  sampleID.push_back("372464");
  sampleID.push_back("372465");
  sampleID.push_back("372466");
  sampleID.push_back("372467");
  sampleID.push_back("372468");
  sampleID.push_back("372469");
  sampleID.push_back("372470");
  sampleID.push_back("372471");
  sampleID.push_back("372472");
  sampleID.push_back("372473");
  sampleID.push_back("372474");
  sampleID.push_back("372475");
  sampleID.push_back("372476");
  sampleID.push_back("372477");
  sampleID.push_back("372478");
  sampleID.push_back("372479");
  sampleID.push_back("372480");
  sampleID.push_back("372481");
  sampleID.push_back("372482");
  sampleID.push_back("372483");
  sampleID.push_back("372484");
  sampleID.push_back("372485");
  sampleID.push_back("372486");
  sampleID.push_back("372487");
  sampleID.push_back("372488");
  sampleID.push_back("372489");
  sampleID.push_back("372490");
  sampleID.push_back("372491");
  sampleID.push_back("372492");
  sampleID.push_back("372493");
  sampleID.push_back("372494");
  sampleID.push_back("372495");
  sampleID.push_back("372496");
  sampleID.push_back("372497");
  sampleID.push_back("372498");
  sampleID.push_back("372499");
  sampleID.push_back("372500");
  sampleID.push_back("372501");
  sampleID.push_back("372502");
  sampleID.push_back("372503");
  sampleID.push_back("372504");
  sampleID.push_back("372505");
  sampleID.push_back("372506");
  sampleID.push_back("372507");
  sampleID.push_back("372508");
  sampleID.push_back("372509");
  sampleID.push_back("372510");
  sampleID.push_back("372511");
  sampleID.push_back("372525");
  sampleID.push_back("372526");
  sampleID.push_back("372527");
  sampleID.push_back("372528");
  sampleID.push_back("372529");
  sampleID.push_back("372530");
  sampleID.push_back("372531");
  sampleID.push_back("372532");
  sampleID.push_back("372533");
  sampleID.push_back("372534");
  sampleID.push_back("372535");
  sampleID.push_back("372536");
  sampleID.push_back("372537");
  sampleID.push_back("372538");
  sampleID.push_back("372539");
  sampleID.push_back("372540");
  sampleID.push_back("372541");
  sampleID.push_back("372542");
  sampleID.push_back("372543");
  sampleID.push_back("372544");
  sampleID.push_back("372545");
  sampleID.push_back("372546");
  sampleID.push_back("372547");
  sampleID.push_back("372548");
  sampleID.push_back("372549");
  sampleID.push_back("372550");
  sampleID.push_back("372551");
  sampleID.push_back("372552");
  sampleID.push_back("372553");
  sampleID.push_back("372554");
  sampleID.push_back("372555");
  sampleID.push_back("372556");
  sampleID.push_back("372557");
  sampleID.push_back("372558");
  sampleID.push_back("372559");
  sampleID.push_back("372560");
  sampleID.push_back("372561");
  sampleID.push_back("372562");
  sampleID.push_back("372563");
  sampleID.push_back("372564");
  sampleID.push_back("372565");
  sampleID.push_back("372566");
  sampleID.push_back("372567");
  sampleID.push_back("372568");
  sampleID.push_back("372569");
  sampleID.push_back("372570");
  sampleID.push_back("372571");
  sampleID.push_back("372572");
  sampleID.push_back("372573");
  sampleID.push_back("372574");
  sampleID.push_back("372575");
  sampleID.push_back("372576");
  sampleID.push_back("372577");
  sampleID.push_back("372578");
  sampleID.push_back("372579");
  sampleID.push_back("372580");
  sampleID.push_back("372581");
  sampleID.push_back("372582");
  sampleID.push_back("372583");
  sampleID.push_back("372584");
  sampleID.push_back("372585");
  sampleID.push_back("372586");
  sampleID.push_back("372950");
  sampleID.push_back("372951");
  sampleID.push_back("372952");
  sampleID.push_back("372953");
  sampleID.push_back("372954");
  sampleID.push_back("372955");
  sampleID.push_back("372956");
  sampleID.push_back("372957");
  sampleID.push_back("372958");
  sampleID.push_back("372959");
  sampleID.push_back("372960");
  sampleID.push_back("372961");
  sampleID.push_back("372962");
  sampleID.push_back("372963");
  sampleID.push_back("372964");
  sampleID.push_back("372965");
  sampleID.push_back("372966");
  sampleID.push_back("372967");
  sampleID.push_back("372968");
  sampleID.push_back("372969");
  sampleID.push_back("372970");
  sampleID.push_back("372971");
  sampleID.push_back("372972");
  sampleID.push_back("372973");
  sampleID.push_back("372974");
  sampleID.push_back("372975");
  sampleID.push_back("372976");
  sampleID.push_back("372977");
  sampleID.push_back("372978");
  sampleID.push_back("372979");
  sampleID.push_back("372980");
  sampleID.push_back("372981");
  sampleID.push_back("372982");
  sampleID.push_back("372983");
  sampleID.push_back("372984");
  sampleID.push_back("372985");
  sampleID.push_back("372986");
  sampleID.push_back("372987");
  sampleID.push_back("372988");
  sampleID.push_back("372989");
  sampleID.push_back("372995");
  sampleID.push_back("372996");
  sampleID.push_back("372997");
  sampleID.push_back("372998");
  sampleID.push_back("372999");
  sampleID.push_back("373000");
  sampleID.push_back("373001");
  sampleID.push_back("373002");
  sampleID.push_back("373003");
  sampleID.push_back("373004");
  sampleID.push_back("373005");
  sampleID.push_back("373006");
  sampleID.push_back("373007");
  sampleID.push_back("373008");
  sampleID.push_back("373009");
  sampleID.push_back("373010");
  sampleID.push_back("373011");
  sampleID.push_back("373012");
  sampleID.push_back("373013");
  sampleID.push_back("373014");
  sampleID.push_back("373015");
  sampleID.push_back("373016");
  sampleID.push_back("373017");
  sampleID.push_back("373018");
  sampleID.push_back("373019");
  sampleID.push_back("373020");
  sampleID.push_back("373021");
  sampleID.push_back("373022");
  sampleID.push_back("373023");
  sampleID.push_back("373024");
  sampleID.push_back("373025");
  sampleID.push_back("373026");
  sampleID.push_back("373027");
  sampleID.push_back("373028");
  sampleID.push_back("373029");
  sampleID.push_back("373030");
  sampleID.push_back("373031");
  sampleID.push_back("373032");
  sampleID.push_back("373033");
  sampleID.push_back("373034");
  sampleID.push_back("373035");
  sampleID.push_back("373036");
  sampleID.push_back("373037");
  sampleID.push_back("373038");
  sampleID.push_back("373039");
  sampleID.push_back("373040");
  sampleID.push_back("407012");
  sampleID.push_back("410000");
  sampleID.push_back("410015");
  sampleID.push_back("410016");
  //sampleID.push_back("410064"); // 0 events (sample is not needed)
  //sampleID.push_back("410065"); // 0 events (sample is not needed)
  sampleID.push_back("410066");
  sampleID.push_back("410067");
  sampleID.push_back("410068");
  sampleID.push_back("410081");
  sampleID.push_back("410111");
  sampleID.push_back("410112");
  sampleID.push_back("410113");
  sampleID.push_back("410114");
  sampleID.push_back("410115");
  sampleID.push_back("410116");

  for( int i = 0 ; i < sampleID.size() ; i++ ){
    addWeightsToSample( sampleID.at(i) , pathToNtuples );
  }

}



void addWeightsToSample(string sampleID, string pathToNtuples) {

  //bool verbose = false;

  //---------------------------------------------
  // open file, get Tree and EventCountHist
  //---------------------------------------------

  string  filename       = Form("%s/%s.root",pathToNtuples.c_str(),sampleID.c_str()); 
  TFile*  f              = new TFile(filename.c_str(),"update");          
  TH1F*   EventCountHist = (TH1F*) f->Get("EventCountHist");
  Float_t _nGenEvents    = EventCountHist->GetBinContent(2);
  TTree*  T              = (TTree*)f->Get("outputTree");
    
  cout << endl;
  cout << "Opening file           : " << filename        << endl;
  cout << "Events in ntuple       : " << T->GetEntries() << endl;
  cout << "Total generated events : " << _nGenEvents     << endl;

  if( _nGenEvents < 1.0 ) cout << "ERROR 0 EVENTS -----------------------------------------------------" << endl;

  //-----------------------------
  // access existing branches
  //-----------------------------

  double  sampleWeight;
  double  eventWeight;
  double  pileupWeight_rew;
  int     eetrig;
  int     mmtrig;
  int     emtrig;
  double  eetrigweight;
  double  mmtrigweight;
  double  emtrigweight;
  int     channel;
  int     lep_n;
  int     jet_n;
  int     is_OS;
  double  MET;
  double  mll;
  double  HT;
  double  HTincl;
  vector<double> *  lep_weight = 0 ;
  vector<double> *  lep_pT     = 0 ;
  vector<double> *  lep_eta    = 0 ;
  vector<double> *  lep_phi    = 0 ;
  vector<int>    *  lep_pdgId  = 0 ;

  T->SetBranchAddress("sampleWeight"    ,&sampleWeight     );
  T->SetBranchAddress("eventWeight"     ,&eventWeight      );
  T->SetBranchAddress("pileupWeight_rew",&pileupWeight_rew );
  T->SetBranchAddress("eetrig"          ,&eetrig           );
  T->SetBranchAddress("mmtrig"          ,&mmtrig           );
  T->SetBranchAddress("emtrig"          ,&emtrig           );
  T->SetBranchAddress("eetrigweight"    ,&eetrigweight     );
  T->SetBranchAddress("mmtrigweight"    ,&mmtrigweight     );
  T->SetBranchAddress("emtrigweight"    ,&emtrigweight     );
  T->SetBranchAddress("channel"         ,&channel          );
  T->SetBranchAddress("lep_weight"      ,&lep_weight       );
  T->SetBranchAddress("lep_pdgId"       ,&lep_pdgId        );
  T->SetBranchAddress("lep_pT"          ,&lep_pT           );
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

  //-----------------------------
  // add new branches
  //-----------------------------

  Float_t nGenEvents;
  Float_t weight1fb;
  Float_t trigweight;
  Float_t lepweight;

  // Float_t weight1fb_vec;
  // Int_t   channel_vec;

  // Float_t lep1_pT_vec;
  // Float_t lep1_eta_vec;
  // Float_t lep1_phi_vec;
  // Float_t lep1_weight_vec;
  // Int_t   lep1_pdgId_vec;

  // Float_t lep2_pT_vec;
  // Float_t lep2_eta_vec;
  // Float_t lep2_phi_vec;
  // Float_t lep2_weight_vec;
  // Int_t   lep2_pdgId_vec;

  // Float_t mll_vec;
  // Float_t Z_pt_vec;
  // Float_t Z_phi_vec;
  // Float_t dphill_vec;        

  // Float_t trigweight_vec;
  // Float_t lepweight_vec;

  TBranch *b_weight      = T->Branch("weight1fb"        , &weight1fb         ,   "weight1fb/F"       );
  TBranch *b_trigw       = T->Branch("trigweight"       , &trigweight        ,   "trigweight/F"      );
  TBranch *b_lepw        = T->Branch("lepweight"        , &lepweight         ,   "lepweight/F"       );
  TBranch *b_nEvents     = T->Branch("nGenEvents"       , &nGenEvents        ,   "nGenEvents/F"      );

  // TBranch *b_weight_vec  = T->Branch("weight1fb_vec"    , &weight1fb_vec     ,   "weight1fb_vec/F"   );
  // TBranch *b_trigwv      = T->Branch("trigweight_vec"   , &trigweight_vec    ,   "trigweight_vec/F"  );
  // TBranch *b_lepwv       = T->Branch("lepweight_vec"    , &lepweight_vec     ,   "lepweight_vec/F"   );
  // TBranch *b_chan        = T->Branch("channel_vec"      , &channel_vec       ,   "channel_vec/I"     );

  // TBranch *b_pt1         = T->Branch("lep1_pT_vec"      , &lep1_pT_vec	     ,   "lep1_pT_vec/F"     );	   
  // TBranch *b_eta1        = T->Branch("lep1_eta_vec"     , &lep1_eta_vec	     ,   "lep1_eta_vec/F"    );	   
  // TBranch *b_phi1        = T->Branch("lep1_phi_vec"     , &lep1_phi_vec	     ,   "lep1_phi_vec/F"    );	   
  // TBranch *b_weight1     = T->Branch("lep1_weight_vec"  , &lep1_weight_vec   ,   "lep1_weight_vec/F" );	   
  // TBranch *b_pdg1        = T->Branch("lep1_pdgId_vec"   , &lep1_pdgId_vec    ,   "lep1_pdgId_vec/I"  );	   

  // TBranch *b_pt2         = T->Branch("lep2_pT_vec"      , &lep2_pT_vec	     ,   "lep2_pT_vec/F"     );	   
  // TBranch *b_eta2        = T->Branch("lep2_eta_vec"     , &lep2_eta_vec	     ,   "lep2_eta_vec/F"    );	   
  // TBranch *b_phi2        = T->Branch("lep2_phi_vec"     , &lep2_phi_vec	     ,   "lep2_phi_vec/F"    );	   
  // TBranch *b_weight2     = T->Branch("lep2_weight_vec"  , &lep2_weight_vec   ,   "lep2_weight_vec/F" );	   
  // TBranch *b_pdg2        = T->Branch("lep2_pdgId_vec"   , &lep2_pdgId_vec    ,   "lep2_pdgId_vec/I"  );	   

  // TBranch *b_mll         = T->Branch("mll_vec"          , &mll_vec	     ,   "mll_vec/F"         );	   
  // TBranch *b_zpt         = T->Branch("Z_pt_vec"         , &Z_pt_vec	     ,   "Z_pt_vec/F"        );	   
  // TBranch *b_zphi        = T->Branch("Z_phi_vec"        , &Z_phi_vec	     ,   "Z_phi_vec/F"       );	   
  // TBranch *b_dphi        = T->Branch("dphill_vec"       , &dphill_vec        ,   "dphill_vec/F"      );	   

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
    trigweight = 1.0;
    if     ( channel == 0                 ) trigweight = mmtrigweight;
    else if( channel == 1                 ) trigweight = eetrigweight;
    else if( channel == 2 || channel == 3 ) trigweight = emtrigweight;
    
    //--- number of generated events
    nGenEvents = _nGenEvents;

    //--- lepton SFs
    lepweight = lep_weight->at(0) * lep_weight->at(1);

    //--- weight for 1/fb
    //weight1fb = 1000.0 * sampleWeight * eventWeight * pileupWeight_rew * trigweight * lepweight / nGenEvents; // with PU
    weight1fb = 1000.0 * sampleWeight * eventWeight * trigweight * lepweight / nGenEvents;                      // without PU

    if( i == 0 ){
      cout << "sampleWeight           : " << sampleWeight     << endl;
      cout << "eventWeight            : " << eventWeight      << endl;
      cout << "weight1fb              : " << weight1fb        << endl;
      //cout << "weight1fb_vec          : " << weight1fb_vec    << endl;
      if( sampleWeight < 1e-10 ) cout << "<<<<------------------- sampleWeight=0" << endl;
      if( weight1fb    < 1e-10 ) cout << "<<<<<<<<<<<<<<<<<<<<<<< WEIGHT=0"    << endl;
    }

    b_weight->Fill();      
    b_trigw->Fill();       
    b_lepw->Fill();        
    b_nEvents->Fill();     

    //------------------------------------------------------------------------
    // VECTOR SUM PT
    //------------------------------------------------------------------------
    /*
    int   imax  = -1;
    int   jmax  = -1;
    float maxpt = -1;

    TLorentzVector t1;
    TLorentzVector t2;
    TLorentzVector sum;

    if( verbose ){
      cout << endl << endl;
      cout << "-----------------------------------------------------" << endl;
      cout << "Found nleptons " << lep_n << endl;
    }
    
    for( int iL = 0 ; iL < lep_n ; iL++ ){

      for( int jL = iL+1 ; jL < lep_n ; jL++ ){
	
	t1.SetPtEtaPhiM( lep_pT->at(iL) , lep_eta->at(iL) , lep_phi->at(iL) , 0.0 );
	t2.SetPtEtaPhiM( lep_pT->at(jL) , lep_eta->at(jL) , lep_phi->at(jL) , 0.0 );

	sum = (t1+t2);
	float vecpt = sum.Pt();

	if( verbose ){
	  cout << endl;

	  cout << "i pt eta phi  " << setw(10) << iL << setw(10) 
	       << Form("%.1f",lep_pT->at(iL))  << setw(10) 
	       << Form("%.2f",lep_eta->at(iL)) << setw(10) 
	       << Form("%.2f",lep_phi->at(iL)) << endl;

	  cout << "j pt eta phi  " << setw(10) << jL << setw(10) 
	       << Form("%.1f",lep_pT->at(jL))  << setw(10) 
	       << Form("%.2f",lep_eta->at(jL)) << setw(10) 
	       << Form("%.2f",lep_phi->at(jL)) << endl;

	  cout << "vector sum pt " << Form("%.2f",vecpt) << endl;
	}

	if( vecpt > maxpt ){
	  imax  = iL;
	  jmax  = jL;
	  maxpt = vecpt;
	}
      }
    }

    if( imax < 0 || jmax < 0 || maxpt < 0 ){
      cout << "ERROR!!! imax jmax maxpt " << imax << " " << jmax << " " << maxpt << endl;
      exit(0);
    }

    if( verbose ) cout << endl << "Best match: " << imax << " " << jmax << " " << Form("%.2f",maxpt) << endl;

    //--- 1st lepton
    lep1_pT_vec     = lep_pT->at(imax);
    lep1_eta_vec    = lep_eta->at(imax);
    lep1_phi_vec    = lep_phi->at(imax);
    lep1_weight_vec = lep_weight->at(imax);
    lep1_pdgId_vec  = lep_pdgId->at(imax);

    //--- 2nd lepton
    lep2_pT_vec     = lep_pT->at(jmax);
    lep2_eta_vec    = lep_eta->at(jmax);
    lep2_phi_vec    = lep_phi->at(jmax);
    lep2_weight_vec = lep_weight->at(jmax);
    lep2_pdgId_vec  = lep_pdgId->at(jmax);

    //--- dilepton quantities
    mll_vec         = sum.M();
    Z_pt_vec        = sum.Pt();
    Z_phi_vec       = sum.Phi();
    dphill_vec      = acos( cos( lep1_phi_vec - lep2_phi_vec ) );

    //--- channel 
    channel_vec = -1;
    if( abs(lep1_pdgId_vec) == 11 && abs(lep2_pdgId_vec) == 11 ) channel_vec = 1;
    if( abs(lep1_pdgId_vec) == 13 && abs(lep2_pdgId_vec) == 13 ) channel_vec = 0;
    if( abs(lep1_pdgId_vec) == 11 && abs(lep2_pdgId_vec) == 13 ) channel_vec = 2;
    if( abs(lep1_pdgId_vec) == 13 && abs(lep2_pdgId_vec) == 11 ) channel_vec = 3;

    //--- weights: TRIGGER WEIGHT NEEDS TO BE UPDATED
    trigweight_vec = 1.0;
    if     ( channel_vec == 0                     ) trigweight_vec = mmtrigweight;
    else if( channel_vec == 1                     ) trigweight_vec = eetrigweight;
    else if( channel_vec == 2 || channel_vec == 3 ) trigweight_vec = emtrigweight;

    lepweight_vec = lep1_weight_vec * lep2_weight_vec;

    weight1fb_vec = 1000.0 * sampleWeight * eventWeight * trigweight_vec * lepweight_vec / nGenEvents;

    b_weight_vec->Fill();  
    b_trigwv->Fill();      
    b_lepwv->Fill();       
    b_chan->Fill();        

    b_pt1->Fill();         
    b_eta1->Fill();        
    b_phi1->Fill();        
    b_weight1->Fill();     
    b_pdg1->Fill();        

    b_pt2->Fill();         
    b_eta2->Fill();        
    b_phi2->Fill();        
    b_weight2->Fill();     
    b_pdg2->Fill();        

    b_mll->Fill();         
    b_zpt->Fill();         
    b_zphi->Fill();        
    b_dphi->Fill();        

    */

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
