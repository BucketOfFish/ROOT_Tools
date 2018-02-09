#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/tools/TReturnCode.h"

#include "TString.h"
#include "TChain.h" // Input files
#include "TFile.h" // Output file
#include "TLorentzVector.h" // Maths
#include "TH1D.h" // Output hists
#include "TH2D.h" // Ouptut hists
#include <vector>
#include <iostream>
#include <cmath>
#include <string>

// Objects I want out of that xAOD
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthParticle.h"

#include <algorithm> // Sorting the vector

//#include "TInterpreter.h"
//#include "TSystem.h"
//#include "AthLinks/ElementLink.h"

int main(int argc, char *argv[]){

// Part of an attempt to deal with those "fatal" problems...
//  gInterpreter->AddIncludePath("/cvmfs/atlas.cern.ch/repo/sw/ASG/AnalysisBase/2.3.2/RootCore/include/");
//  Will these cause crashes on the grid??
  //gSystem->Load("libAthContainers_Reflex");
  //gSystem->Load("libxAODCore_Reflex");
  //gSystem->Load("libAthLinks_Reflex");
  //gInterpreter->AutoParse("ElementLink");
  //gSystem->Load("libxAODTruth_Reflex");

//  gInterpreter->AutoParse("pair<string,string>");
//  gInterpreter->AutoParse("xAOD::TruthParticleAuxContainer");

  bool is8TeV = false;
  int nDebugEvents = 0;

  std::vector<TString> my_files;
  for(int a=1; a<argc; a++) {
    // Input File option
    if (0!=strcmp(argv[a],"--8TeV")){
      std::string argStr = argv[a];
      for (size_t i=0,n; i <= argStr.length(); i=n+1) {
        n = argStr.find_first_of(',',i);
        if (n == std::string::npos) n = argStr.length();
        std::string tmp = argStr.substr(i,n-i);
        my_files.push_back(tmp);
        std::cout << tmp << std::endl;
      }
    } else {
      is8TeV = true;
    }
  }

  if (my_files.size()==0){
    std::cout << "No input files specified.  Exiting." << std::endl;
    return 1;
  }

  TChain ch("CollectionTree");
  for (int i=0;i<my_files.size();i++){
    std::cout << "Adding file " << my_files[i] << std::endl;
    ch.Add( my_files[i].Data() );
  }

  double s_inv = 1. / std::pow( 13000000. , 2 );
  if (is8TeV) s_inv = 1. / std::pow( 8000000. , 2 );

  std::cout << "Initializing analysis..." << std::endl;
  xAOD::Init( "MyTruthxAODAnalysis" ).ignore();
  std::cout << "Setting up event..." << std::endl;
  xAOD::TEvent event(&ch);
  std::cout << "Making histograms..." << std::endl;

//  // MC12 Simulated values
//  const double eta_min = 2.08 , eta_max = 3.83;
  // Run 1 installed values
  const double eta_min = 2.08 , eta_max = 3.75;
//  // Run 2 installed values
//  const double eta_min = 2.07 , eta_max = 3.86;
 
  bool requireCharge = true;

  TH1D * total_xi = new TH1D("total_xi","total_xi",80,-8.,0.);
  TH1D * acc_xi   = new TH1D("acc_xi"  ,"acc_xi"  ,80,-8.,0.);
  TH1D * total_n  = new TH1D("total_n" ,"total_n" ,101,-0.5,100.5);
  TH1D * acc_n    = new TH1D("acc_n"   ,"acc_n"   ,101,-0.5,100.5);
  TH2D * n_xi     = new TH2D("N_xi"    ,"N_xi"    ,101,-0.5,100.5,80,-8.,0.);
  TH2D * eta_xi   = new TH2D("eta_xi"  ,"eta_xi"  ,140,-7.,7.,80,-8.,0.);
  TH2D * nin_xi   = new TH2D("Nin_xi"  ,"Nin_xi"  ,101,-0.5,100.5,80,-8.,0.);

  std::cout << "Making temporary variables..." << std::endl;
  TLorentzVector set1,set2;
  int n_total=0 , n_in_acc=0 ;
  const xAOD::TruthEventContainer* xTruthEventContainer = nullptr;

  long nEvents = event.getEntries();
  std::vector<float> eta_list;
  eta_list.reserve(500);

  std::cout << "Beginning event loop over " << event.getEntries() << " events." << std::endl;
  for (long evt=0;evt<nEvents;++evt){

    event.getEntry(evt);
    if (evt%500000==0) std::cout << "Working on entry " << evt << std::endl;

    if (evt<nDebugEvents) std::cout << "-------------- EVENT -----------" << std::endl;

    // init
    n_total=0; 
    n_in_acc=0 ;
    eta_list.clear();
    if (!event.retrieve( xTruthEventContainer , "TruthEvent" ).isSuccess()){
      std::cerr << "Could not load event " << evt << " from the file!" << std::endl;
      throw;
    }

    // Count the number of particles (and in acceptance), do some bookkeeping
    for (int p=0;p<xTruthEventContainer->at(0)->nTruthParticles();++p){
      const xAOD::TruthParticle* part = xTruthEventContainer->at(0)->truthParticle(p);
      // Acceptance cuts
      if ( part->status() != 1 ) continue;
      if ( requireCharge && std::fabs(part->charge())<0.1 ) continue;

      // Add to the lists
      if (evt<nDebugEvents) std::cout << "Particle " << n_total << " " << part->pt() << " " << part->eta() << " " << part->phi() << " " << part->m() << std::endl;
      if ( part->pt()>100. ) ++n_total;
      if ( std::fabs(part->eta())>eta_min && std::fabs(part->eta())<eta_max ) ++n_in_acc;
      eta_list.push_back( part->eta() );
    }

    // Find the largest gap
    std::sort(eta_list.begin(),eta_list.end());
    double biggest_gap=-1., Avg=-1.;
    for (int p=0;p<eta_list.size()-1;++p){
      if ( eta_list[p+1] - eta_list[p] > biggest_gap ){
        biggest_gap = eta_list[p+1] - eta_list[p];
        Avg = 0.5 * (eta_list[p+1]+eta_list[p]);
      }
    }

    // Construct the two systems
    set1.SetPtEtaPhiM(0,0,0,0);
    set2.SetPtEtaPhiM(0,0,0,0);
    for (int p=0;p<xTruthEventContainer->at(0)->nTruthParticles();++p){
      const xAOD::TruthParticle* part = xTruthEventContainer->at(0)->truthParticle(p);
      if ( part->status() != 1 ) continue;
      if ( requireCharge && std::fabs(part->charge())<0.1 ) continue;

      // Add to the appropriate side of the detector
      if ( part->eta()>Avg ) set1 += part->p4();
      else                   set2 += part->p4();
    }

    // Calculate log10(xi)
    double xi = std::log10( std::max( set1.M2() , set2.M2() ) * s_inv );
//    if (xi < std::log10( 900.*900. * s_inv ) || xi > -0.01 || evt<10) {
//      std::cout << "Here we are: " << set1.M2() << " " << set2.M2() << " " << s_inv << " " << Avg << " " 
//                << biggest_gap << " " << xi << " " << n_total << " " << n_in_acc << " " << mcN << std::endl;
//      throw;  // This really shouldn't happen... the xi>1.6 part never seems to
//    }

    total_xi->Fill( xi , xTruthEventContainer->at(0)->weights()[0] );
    if (n_in_acc>1) acc_xi->Fill( xi , xTruthEventContainer->at(0)->weights()[0] );
    total_n->Fill( n_total , xTruthEventContainer->at(0)->weights()[0] );
    if (n_in_acc>1) acc_n->Fill( n_total , xTruthEventContainer->at(0)->weights()[0] );
    n_xi   ->Fill( n_total , xi , xTruthEventContainer->at(0)->weights()[0] );

    // This is not quite the one in the backup note...
    // That one seems (?) to look at the eta of the particle
    //  assuming that the diffractive side is - eta, so that
    //  large eta means very large opening angles (??)
    eta_xi->Fill( Avg , xi , xTruthEventContainer->at(0)->weights()[0] );

    nin_xi->Fill( n_in_acc , xi , xTruthEventContainer->at(0)->weights()[0] );

  }

  std::cout << "Done with loop, will close file." << std::endl;

  TFile fOut("hist_file.root","RECREATE");
  fOut.cd();

  total_xi->Write("total_xi",TObject::kOverwrite);
  acc_xi  ->Write("acc_xi"  ,TObject::kOverwrite);
  total_n ->Write("total_n" ,TObject::kOverwrite);
  acc_n   ->Write("acc_n"   ,TObject::kOverwrite);
  n_xi    ->Write("N_xi"    ,TObject::kOverwrite);
  eta_xi  ->Write("eta_xi"  ,TObject::kOverwrite);
  nin_xi  ->Write("Nin_xi"  ,TObject::kOverwrite);

  std::cout << "Done writing results, closing up and finishing up." << std::endl;
  fOut.Close();

  return 0;
}

