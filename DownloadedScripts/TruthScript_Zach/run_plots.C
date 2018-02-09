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

    TH1F * inv_m_ee = new TH1F("inv_m_ee", "inv_m_ee", 80, 0., 160.);
    TH1F * inv_m_em = new TH1F("inv_m_em", "inv_m_em", 80, 0., 160.);
    TH1F * inv_m_mm = new TH1F("inv_m_mm", "inv_m_mm", 80, 0., 160.);

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
        if (evt%1000==0) std::cout << "Working on entry " << evt << std::endl;

        if (evt<nDebugEvents) std::cout << "-------------- EVENT -----------" << std::endl;

        // init
        if (!event.retrieve( xTruthEventContainer , "TruthEvent" ).isSuccess()){
            std::cerr << "Could not load event " << evt << " from the file!" << std::endl;
            throw;
        }

        // Count the number of particles (and in acceptance), do some bookkeeping
        xAOD::TruthParticle part1;
        xAOD::TruthParticle part2;
        TLorentzVector v1;
        TLorentzVector v2;
        float pt1 = 0;
        float pt2 = 0;
        bool isel1 = 0;
        bool isel2 = 0;
        float pt_sum = 0;
        for (int p=0;p<xTruthEventContainer->at(0)->nTruthParticles();++p){
            const xAOD::TruthParticle* part = xTruthEventContainer->at(0)->truthParticle(p);
            // Acceptance cuts
            if ( part->status() != 1 ) continue;
            if ( part->pt() < 15000 ) continue;

            pt_sum += part->pt();
            if ( !part->isMuon() and !part->isElectron()) continue;
        
            // Get two highest pT leptons
            if (part->pt() > pt1){
                pt2 = pt1;
                part2 = part1;
                v2 = v1;
                isel2 = isel1;
                pt1 = part->pt();
                part1 = *part;
                v1 = part->p4();
                isel1 = part->isElectron();
            }
            else if (part->pt() > pt2){
                pt2 = part->pt();
                part2 = *part;
                v2 = part->p4();
                isel2 = part->isElectron();
            }
        }
        if (pt1==0 || pt2==0) continue;
        if (pt_sum < 600000) continue;

        TLorentzVector sum = v1 + v2;

        if (!isel1 && !isel2) inv_m_mm->Fill(sum.M()*.001);
        else if (isel1 && isel2) inv_m_ee->Fill(sum.M()*.001);
        else inv_m_em->Fill(sum.M()*.001);
    }

    std::cout << "Done with loop, will close file." << std::endl;

    TFile fOut("hist_file.root","RECREATE");
    fOut.cd();

    inv_m_mm->Write("inv_m_mm",TObject::kOverwrite);
    inv_m_ee->Write("inv_m_ee",TObject::kOverwrite);
    inv_m_em->Write("inv_m_em",TObject::kOverwrite);

    std::cout << "Done writing results, closing up and finishing up." << std::endl;
    fOut.Close();

    return 0;
}

