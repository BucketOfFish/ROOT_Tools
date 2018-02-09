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

void addWeightsToSample(string sampleID, string pathToNtuples);

//void addZPhi( string pathToNtuples = "/Users/benhoob/atlas-benhoob/Run2Analysis/trunk/ntuples/v00-16-nosyst/MC"){
void addZPhi( string pathToNtuples = "./"){

  vector<string> sampleID;

  //////////////////////////////////////////////////////
  // ADD HERE THE LIST OF DATASET IDS TO RUN ON
  //////////////////////////////////////////////////////

  // // data samples
  sampleID.push_back( "data" );

  // Z samples
  for( int i = 361372 ; i <= 361443 ; i++ ){
    stringstream s;
    s << i;
    string mystring = s.str();
    sampleID.push_back(mystring);
  }

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

  //if( _nGenEvents < 1.0 ) cout << "ERROR 0 EVENTS -----------------------------------------------------" << endl;

  //-----------------------------
  // access existing branches
  //-----------------------------
  
  
  vector<double> *  lep_pT     = 0 ;
  vector<double> *  lep_eta    = 0 ;
  vector<double> *  lep_phi    = 0 ;

  T->SetBranchAddress("lep_pT"          ,&lep_pT           );
  T->SetBranchAddress("lep_eta"         ,&lep_eta          );
  T->SetBranchAddress("lep_phi"         ,&lep_phi          );

  //-----------------------------
  // add new branches
  //-----------------------------

  Float_t Z_phi_correct;

  TBranch *b_zphi        = T->Branch("Z_phi_correct"    , &Z_phi_correct     ,   "Z_phi_correct/F" );

  //-----------------------------
  // loop over events
  //-----------------------------

  Long64_t nentries = T->GetEntries();

  TLorentzVector t1;
  TLorentzVector t2;


  for (Long64_t i=0;i<nentries;i++) {
    //for (Long64_t i=0;i<10;i++) {

    T->GetEntry(i);

    t1.SetPtEtaPhiM( lep_pT->at(0) , lep_eta->at(0) , lep_phi->at(0) , 0.0 );
    t2.SetPtEtaPhiM( lep_pT->at(1) , lep_eta->at(1) , lep_phi->at(1) , 0.0 );

    Z_phi_correct = ( t1 + t2 ).Phi();

    b_zphi->Fill();     

  }

  //T->Print();
  T->Write();
  delete f;

}
