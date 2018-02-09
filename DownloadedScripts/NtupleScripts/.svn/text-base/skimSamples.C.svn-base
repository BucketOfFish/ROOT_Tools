//--------------------------------------------------------------------------------------------------------------------------------
// This script reads in an ntuple, applies some skimming selection, and outputs a new ntuple with events passing the skim
//--------------------------------------------------------------------------------------------------------------------------------

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>

#include "TCanvas.h"
#include "TLegend.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TPad.h"
#include "TCut.h"
#include "TProfile.h"
#include "THStack.h"
#include "TLatex.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TLine.h"
#include "TMath.h"

using namespace std;

void skim(char* path, char* cut, char* label, char* sample, char* treename);

void skimSamples(){

  char* path     = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-21-NoSys/MC";
  char* cut      = "truthMET_Filter<200.0";                                                     // selection to apply, as a TCut
  char* label    = "MET_lt_200";                                                         // label for output ntuple
  char* treename = "outputTree";                                                         // name of tree

  skim(path,cut,label,"410000" , treename );
}



void skim(char* path, char* cut, char* label, char* sample, char* treename){

  //--------------------------------------------------
  // path of input and output files
  //--------------------------------------------------

  char* infilename		= Form("%s/%s.root"   ,path,sample);
  char* outfilename		= Form("%s/%s_%s.root",path,sample,label);

  //char* outpath = (char*) "/afs/cern.ch/user/b/benhoob/workspace/ZMETSamples/Current_Ntuples/v00-16/Photons";
  //char* outfilename		= Form("%s/%s_%s.root",outpath,sample,label);

  //--------------------------------------------------
  // cout stuff
  //--------------------------------------------------

  cout << endl << endl;
  cout << "Reading in : " << infilename     << endl;
  cout << "Writing to : " << outfilename    << " " << cut   << endl;

  //--------------------------------------------------
  // read input file, write to output files
  //--------------------------------------------------
  
  long long max_tree_size = 20000000000000000LL;
  TTree::SetMaxTreeSize(max_tree_size);

  TChain *chain = new TChain(treename);
  chain->Add(infilename);

  //--------------------------------------------------
  // output file and tree
  //--------------------------------------------------

  TFile *file_cut = TFile::Open(outfilename, "RECREATE");
  assert( file_cut != 0 );
  TTree* tree_cut = chain->CopyTree( cut );
  tree_cut->Write();
  file_cut->Close();

  //--------------------------------------------------
  // dummy check
  //--------------------------------------------------

  TChain *chin  = new TChain(treename);
  TChain *chout = new TChain(treename);

  chin->Add(infilename);
  chout->Add(outfilename);

  cout << "Infile  total  entries " << chin->GetEntries()           << endl;
  cout << "Infile  cut    entries " << chin->GetEntries(TCut(cut))  << endl;
  cout << "Outfile total  entries " << chout->GetEntries()          << endl;
  cout << "Outfile cut    entries " << chout->GetEntries(TCut(cut)) << endl;


}
