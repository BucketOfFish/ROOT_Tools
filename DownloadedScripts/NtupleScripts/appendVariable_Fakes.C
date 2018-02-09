/*
 ROOT macro to append variable to TTree.

 Calculate Matrix Method weight for fake backgrounds per event and append it.

 Jonathan Long
 Sept 15, 2015
 */


/////////////////////////////////////
/*
Important notes!  This will need to run on the 'fake' version of the data ntuple, and thus we need to be careful to add the branches we expect to use and make sure existing branches are filled as expected with the fake-flag on.
 */

#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TMatrixD.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"

#include <iostream>

bool DEBUG = false;

enum FLAV {EE, MM, EM, ME};

enum ID {TT, TL, LT, LL};

// Class for one bin of the fake est
class MatrixMethod{

public:
    MatrixMethod();

    //MatrixMethod( const MatrixMethod &obj);

    ~MatrixMethod();

    void Init(double real_eff1, double real_eff2, double fake_eff1, double fake_eff2);
    double getWeight(ID lep_id);
    double getEff(ID lep_id);
    double getEffReal(ID lep_id);

    const TMatrixD getMatrix() const { return *matrix;};

private:

    TMatrixD *matrix;

    double real_eff1;
    double real_eff2;

    double fake_eff1;
    double fake_eff2;

    void fillMatrix(TMatrixD &matrix, double real_eff1, double real_eff2, double fake_eff1, double fake_eff2);

    //    ClassDef(MatrixMethod,1);
};


// Class to hold all bins of fake est
class MM_Holder{

public:

    void init(TString inputFileName_fake, TString inputFileName_real, int variation = 0);
    double getWeight(FLAV flav, ID id, double lepPt1, double lepPt2 );
    double getEff(FLAV flav, ID id, double lepPt1, double lepPt2 );
    double getEffReal(FLAV flav, ID id, double lepPt1, double lepPt2 );

    void  boundEfficiencies(double &y_lead_e_fake, double &y_lead_m_fake, double &y_lead_e_real, double &y_lead_m_real  );

private:

    std::vector<double> binBoundaries;

    // [flavor][leadbin][subleadbin]
    //std::vector< std::vector< std::vector<MatrixMethod> >* > matrices;
    MatrixMethod ***matrices;

    //MatrixMethod ***matrices_el_real_up,***matrices_el_real_down,***matrices_mu_real_up,***matrices_mu_real_down;
    //MatrixMethod ***matrices_el_fake_up,***matrices_el_fake_down,***matrices_mu_fake_up,***matrices_mu_fake_down;

    int getPtBin(double pt);
};


// Code to loop over ntuple and append branches
void addBranchDouble(TTree *tree, double var, TString name);

// Find lepton ID category
ID whichID(TTree *tree);

// Find flavor category
FLAV whichChannel(TTree *tree);

void drawGraph(TGraphAsymmErrors *graph, TString title, TString path="");

//void appendVariable_Fakes(TString oldFileName = "data.root", TString treeName = "outputTree",  TString filePath = "mm_inputs/", TString newFilePath = "mm_output/", TString newFileName = "data_fakes_Dec1_prompt.root")
void appendVariable_Fakes(TString oldFileName = "data_v17.root", TString treeName = "outputTree",  TString filePath = "mm_inputs/", TString newFilePath = "mm_output/", TString newFileName = "data_v17_fakes_v0_Jan18.root")
{
    if (newFilePath == "") newFilePath = filePath;


    MM_Holder m_holder;
    MM_Holder m_holder_erup, m_holder_erdown,m_holder_mrup, m_holder_mrdown, m_holder_efup, m_holder_efdown,m_holder_mfup, m_holder_mfdown;
    MM_Holder m_holder_rsystup, m_holder_rsystdown,m_holder_fsystmtup,m_holder_fsystmtdown,m_holder_fsystmetup,m_holder_fsystmetdown;

    // Need to input all of the efficiencies here
    //TString inputFile = "mm_inputs/lepEffs_v16_otilia_v1.root";
    TString inputFile = "mm_inputs/lepEffs_v17_v0.root";
    //TString inputFile = "mm_inputs/lepEffs_lowpt_v0.root";

    // fake lepton systematic, relative on the total yield
    double electron_fake_syst = 0.65;
    double muon_fake_syst     = 0.35;

    //electron_fake_syst = 0;
    //muon_fake_syst     = 0;


    m_holder.init(inputFile, inputFile );

    std::vector< MM_Holder > sys_matrices;
    // stat variations
    m_holder_erup.init(inputFile, inputFile ,1);
    m_holder_erdown.init(inputFile, inputFile ,2);
    m_holder_mrup.init(inputFile, inputFile ,3);
    m_holder_mrdown.init(inputFile, inputFile ,4);

    m_holder_efup.init(inputFile, inputFile ,5);
    m_holder_efdown.init(inputFile, inputFile ,6);
    m_holder_mfup.init(inputFile, inputFile ,7);
    m_holder_mfdown.init(inputFile, inputFile ,8);

    // syst variations
    m_holder_rsystup.init(inputFile, inputFile ,9);
    m_holder_rsystdown.init(inputFile, inputFile ,10);

    /*m_holder_fsystmtup.init(inputFile, inputFile ,11);
    m_holder_fsystmtdown.init(inputFile, inputFile ,12);

    m_holder_fsystmetup.init(inputFile, inputFile ,13);
    m_holder_fsystmetdown.init(inputFile, inputFile ,14);
    */


    //sys_matrices.push_back(m_holder_erup);
    //sys_matrices.push_back(m_holder_erdown);
    //sys_matrices.push_back(m_holder_mrup);
    //sys_matrices.push_back(m_holder_mrdown);
    //sys_matrices.push_back(m_holder_efup);
    //sys_matrices.push_back(m_holder_efdown);
    //sys_matrices.push_back(m_holder_mfup);
    //sys_matrices.push_back(m_holder_mfdown);

    if (DEBUG) std::cout<<"Made it past init"<<std::endl;

    // Open the files etc
    TFile *oldFile = new TFile(filePath + "/" + oldFileName);
    if (!oldFile->IsOpen()) return;
    TTree *tree = (TTree*)oldFile->Get(treeName);

    TFile *newFile = new TFile(newFilePath + "/" + newFileName, "recreate");
    if (!newFile->IsOpen()) return;
    if (DEBUG) std::cout<<"Cloning Tree"<<std::endl;
    TTree * new_tree = tree->CloneTree(-1,"fast");
    //TTree * new_tree = tree->CloneTree(10000,"fast");

    // Setup branches we need here
    vector<double> *lep_pT = NULL;
    new_tree->SetBranchAddress("lep_pT",&lep_pT);

    Long64_t channel;
    FLAV CH;
    new_tree->SetBranchAddress("channel", &channel);

    vector<int> *passedTight = NULL;
    vector<int> *passedLoose = NULL;
    ID lep_id;
    new_tree->SetBranchAddress("lep_tight",&passedTight);
    new_tree->SetBranchAddress("lep_loose",&passedLoose);

    // new branch
    double fake_weight = 0;
    double fake_weight_stat = 0;
    double fake_weight_syst = 0;
    double real_weight = 0;
    //TBranch * new_fake_weight = new_tree->Branch("fake_weight", &fake_weight, "fake_weight/D");
    //new_tree->SetBranchAddress("fake_weight", &fake_weight);


    if (DEBUG) std::cout<<"eventloop"<<std::endl;

    // Loop over entries
    Long64_t nentries = new_tree->GetEntries();
    for (Long64_t i=0; i<nentries; i++) {
        //for (Long64_t i=0; i<10000; i++) {
        if (DEBUG) std::cout<<"Entry: "<<i<<std::endl;
        if (i%5000==0) std::cout<<"Completed " <<i<<" events."<<std::endl;
        new_tree->GetEntry(i);

        if (DEBUG) std::cout<<"Got entry"<<std::endl;

        // Which Channel
        if (channel == 0) CH = MM;
        if (channel == 1) CH = EE;
        if (channel == 2) CH = EM;
        if (channel == 3) CH = ME;

        // which ID
        if      ( (*passedTight)[0] && (*passedTight)[1] ) lep_id = TT;
        else if ( (*passedTight)[0] && ((*passedLoose)[1] && !(*passedTight)[1] ) ) lep_id = TL;
        else if ( ( (*passedLoose)[0] && !(*passedTight)[0]) && (*passedTight)[1] ) lep_id = LT;
        else if ( ( (*passedLoose)[0]&& !(*passedTight)[0]) && ((*passedLoose)[1]&& !(*passedTight)[1]) ) lep_id = LL;


        //getWeight(FLAV flav, ID id, double lepPt1, double lepPt2)


        fake_weight = m_holder.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  ); // jdl normal one here

        //stat
        fake_weight_stat = 0;


        fake_weight_stat += pow( (abs(fake_weight - m_holder_erup.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  )) + abs(fake_weight - m_holder_erdown.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  ) ) ) / 2, 2);
        fake_weight_stat += pow( (abs(fake_weight - m_holder_mrup.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  )) + abs(fake_weight - m_holder_mrdown.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  ) ) ) / 2, 2);

        fake_weight_stat += pow( (abs(fake_weight - m_holder_efup.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  )) + abs(fake_weight - m_holder_efdown.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  ) ) ) / 2, 2);
        fake_weight_stat += pow( (abs(fake_weight - m_holder_mfup.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  )) + abs(fake_weight - m_holder_mfdown.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  ) ) ) / 2, 2);

        //fake_weight_stat; //this is squared



        // syst

        fake_weight_syst = 0;


        fake_weight_syst += pow( (abs(fake_weight - m_holder_rsystup.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  )) + abs(fake_weight - m_holder_rsystdown.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  ) ) ) / 2, 2); // real
        /*fake_weight_syst += pow( (abs(fake_weight - m_holder_fsystmtup.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  )) + abs(fake_weight - m_holder_fsystmtdown.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  ) ) ) / 2, 2); //fake

        fake_weight_syst += pow( (abs(fake_weight - m_holder_fsystmetup.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  )) + abs(fake_weight - m_holder_fsystmetdown.getWeight( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  ) ) ) / 2, 2); //fake
        */


        double test_weight=0;

        // add in fake syst on total
        if (CH==MM || CH==EM) fake_weight_syst += muon_fake_syst*muon_fake_syst*fake_weight*fake_weight;
        if (CH==EE || CH==ME) fake_weight_syst += electron_fake_syst*electron_fake_syst*fake_weight*fake_weight;
        //if (CH==MM || CH==EM) test_weight = fake_weight_syst + muon_fake_syst*muon_fake_syst*fake_weight*fake_weight;
        //if (CH==EE || CH==ME) test_weight = fake_weight_syst + electron_fake_syst*electron_fake_syst*fake_weight*fake_weight;


        fake_weight_syst = sqrt(fake_weight_syst);
        //test_weight = sqrt(test_weight);
        //fake_weight = m_holder.getEff( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  ); // jdl
        //real_weight = m_holder.getEffReal( CH, lep_id, (*lep_pT)[0], (*lep_pT)[1]  ); // jdl

        // Add branch here
        addBranchDouble(new_tree, fake_weight, "qcdWeight");
        addBranchDouble(new_tree, fake_weight_stat, "qcdWeightStat");
        addBranchDouble(new_tree, fake_weight_syst, "qcdWeightSyst");
        //addBranchDouble(new_tree, test_weight, "test");
        //addBranchDouble(new_tree, real_weight, "real_weight");
        //new_fake_weight->Fill();


    }
    //new_tree->SetDirectory(newFile);

    //tree->Write();
    newFile->Write();
    newFile->Close();

}

/*|||||||||||||||||||||||||||||||||||||||||||||||||||||*/

void addBranchDouble(TTree* tree, double var, TString name){

    TBranch *new_branch = tree->GetBranch(name);
    if (new_branch == NULL) new_branch = tree->Branch(name, &var, name+"/D");

    tree->SetBranchAddress(name, &var);

    new_branch->Fill();

}


/*|||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/*ID whichID(TTree *tree)
{
    if (DEBUG) std::cout<<" in whichID" <<std::endl;

    vector<int> *passedTight = NULL;
    vector<int> *passedLoose = NULL;

    tree->SetBranchAddress("lep_tight",&passedTight);
    tree->SetBranchAddress("lep_loose",&passedLoose);

    if      ( (*passedTight)[0] && (*passedTight)[1] ) return TT;
    else if ( (*passedTight)[0] && (*passedLoose)[1] ) return TL;
    else if ( (*passedLoose)[0] && (*passedTight)[1] ) return LT;
    else if ( (*passedLoose)[0] && (*passedLoose)[1] ) return LL;
}*/

/*|||||||||||||||||||||||||||||||||||||||||||||||||||||*/
 /*FLAV whichChannel(TTree *tree)
{
    if (DEBUG) std::cout<<"whichChannel:"<<std::endl;
    int channel;
    tree->SetBranchAddress("channel", &channel);

    if (channel == 0) return MM;
    if (channel == 1) return EE;
    if (channel == 2) return EM;
    if (channel == 3) return ME;
}*/


/*|||||||||||||||||||||||||||||||||||||||||||||||||||||*/
void drawGraph(TGraphAsymmErrors *graph, TString title, TString path)
{

    TCanvas *c = new TCanvas("c","c",800,600);

    graph->SetMaximum(1);
    graph->SetMinimum(0);
    graph->Draw("ALP");
    graph->GetXaxis()->SetTitle("p_{T} [GeV]");
    graph->GetYaxis()->SetTitle("Efficiency");
    graph->SetTitle(title);

    c->Print(path + "/" + title + ".pdf");


}


////////// Matrix Method Class ///////////////

MatrixMethod::MatrixMethod()
{
    matrix = NULL;
}

//MatrixMethod::MatrixMethod( const MatrixMethod &obj)
//{
//
//    matrix = new TMatrixD(4,4);
//    *matrix = obj.getMatrix();
//
//}

MatrixMethod::~MatrixMethod()
{
    if (matrix) delete matrix;
}

void MatrixMethod::Init(double real_eff1, double real_eff2, double fake_eff1, double fake_eff2)
{
    if (DEBUG) std::cout<<"Initializing matrix: "<<real_eff1 << " "<<real_eff2<<" "<<fake_eff1<< " "<<fake_eff2<<std::endl;

    //std::cout<<"REAL EFFICIENCIES ARE SCALED BY 1.10!"<<std::endl;
    this->real_eff1 = real_eff1;
    this->real_eff2 = real_eff2;
    this->fake_eff1 = fake_eff1;
    this->fake_eff2 = fake_eff2;

    matrix = new TMatrixD(4,4);

    fillMatrix(*matrix, this->real_eff1, this->real_eff2, this->fake_eff1, this->fake_eff2);
    //if (DEBUG) matrix->Print();

    matrix->Invert();

    //if (DEBUG) std::cout<<"Inverted!"<<std::endl;
    //if (DEBUG) matrix->Print();
}


// This needs to decide the bin and channel
double MatrixMethod::getWeight(ID lep_id)
{
    // array of delta functions depending onfor lep id
    TMatrixD delta_array = TMatrixD(4,1);

    if (lep_id == TT) { delta_array(0,0) = 1; delta_array(1,0) = 1; delta_array(2,0) = 1; delta_array(3,0) = 1; }
    if (lep_id == TL) { delta_array(0,0) = 0; delta_array(1,0) = 1; delta_array(2,0) = 0; delta_array(3,0) = 1; }
    if (lep_id == LT) { delta_array(0,0) = 0; delta_array(1,0) = 0; delta_array(2,0) = 1; delta_array(3,0) = 1; }
    if (lep_id == LL) { delta_array(0,0) = 0; delta_array(1,0) = 0; delta_array(2,0) = 0; delta_array(3,0) = 1; }


    // Inverted matrix times delta functions

    TMatrixD prod = TMatrixD(*matrix, TMatrixD::kMult, delta_array);
    if (DEBUG) { std::cout<<"Prod:"<<std::endl; prod.Print();}
    if (DEBUG) std::cout<<__LINE__<<std::endl;
    // efficiencies to go from loose to tight, to multiply into the prod to get the total weight
    TMatrixD eff_weight = TMatrixD(1,4);
    eff_weight(0,0) = 0;  eff_weight(0,1) = real_eff1 * fake_eff2;  eff_weight(0,2) = fake_eff1 * real_eff2; eff_weight(0,3) = fake_eff1 * fake_eff2;

    //eff_weight.Print();

    //TMatrixD(eff_weight, TMatrixD::kMult, prod).Print();


    double weight = TMatrixD(eff_weight, TMatrixD::kMult, prod)(0,0);

    return weight;
}


double MatrixMethod::getEff(ID lep_id)
{
    // array of delta functions depending onfor lep id
    double eff = 1;
    if (lep_id == TT) { eff = fake_eff2; }
    if (lep_id == TL) { eff = fake_eff2; }
    if (lep_id == LT) { eff = fake_eff1; }
    if (lep_id == LL) { eff = fake_eff1 * fake_eff2; }

    return eff;
}


double MatrixMethod::getEffReal(ID lep_id)
{
    // array of delta functions depending onfor lep id
    double eff = 1;
    if (lep_id == TT) { eff = real_eff2; }
    if (lep_id == TL) { eff = real_eff2; }
    if (lep_id == LT) { eff = real_eff1; }
    if (lep_id == LL) { eff = real_eff1 * real_eff2; }

    return eff;
}



void MatrixMethod::fillMatrix(TMatrixD &matrix, double real_eff1, double real_eff2, double fake_eff1, double fake_eff2)
{

    // (row, col)
//    matrix(0,0) = real_eff1 * real_eff2;           matrix(0,1) = real_eff1 * fake_eff2;            matrix(0,2) = fake_eff1 * real_eff2;          matrix(0,3) = fake_eff1 * fake_eff2;
//
//    matrix(1,0) = real_eff1 * (1-real_eff2);       matrix(1,1) = real_eff1 * (1-fake_eff2);        matrix(1,2) = fake_eff1 * (1-real_eff2);      matrix(1,3) = fake_eff1 * (1-fake_eff2);
//
//    matrix(2,0) = (1-real_eff1) * real_eff2;       matrix(2,1) = (1-real_eff1) * fake_eff2;        matrix(2,2) = (1-fake_eff1) * real_eff2;      matrix(2,3) = (1-fake_eff1) * fake_eff2;
//
//    matrix(3,0) = (1-real_eff1) * (1-real_eff2);   matrix(3,1) = (1-real_eff1) * (1-fake_eff2);    matrix(3,2) = (1-fake_eff1) * (1-real_eff2);  matrix(3,3) = (1-fake_eff1) * (1-fake_eff2);


    matrix(0,0) = real_eff1 * real_eff2;           matrix(0,1) = real_eff1 * fake_eff2;            matrix(0,2) = fake_eff1 * real_eff2;          matrix(0,3) = fake_eff1 * fake_eff2;

    matrix(1,0) = real_eff1 ;       matrix(1,1) = real_eff1 ;        matrix(1,2) = fake_eff1 ;      matrix(1,3) = fake_eff1 ;

    matrix(2,0) =  real_eff2;       matrix(2,1) = fake_eff2;        matrix(2,2) =  real_eff2;      matrix(2,3) =  fake_eff2;

    matrix(3,0) = 1;   matrix(3,1) = 1;    matrix(3,2) = 1;  matrix(3,3) = 1;


}



////////// MM Holder Class ///////////////


void MM_Holder::init(TString inputFileName_fake, TString inputFileName_real, int variation)
{

    // 0 nominal
    // 1 2 el real up / down
    // 3 4 mu real up / down

    // 5 6 el fake up / down
    // 7 8 mu fake up / down

    // graphs of the pt binned efficiencies
    TGraphAsymmErrors * el_fake, *mu_fake, *el_real, *mu_real;

    // string in hist name
    TString histname_fake = "sel_truth_pt";
    TString histname_real = "sel_real_truth_pt";

    // files with input hists
    TFile tempFake(inputFileName_fake);
    TFile tempReal(inputFileName_real);


    // Nominal and stats
    el_fake = (TGraphAsymmErrors*)tempFake.Get("tg_el_fake");
    mu_fake = (TGraphAsymmErrors*)tempFake.Get("tg_mu_fake");

    el_real = (TGraphAsymmErrors*)tempReal.Get("tg_el_real_HT200");
    mu_real = (TGraphAsymmErrors*)tempReal.Get("tg_mu_real_HT200");

    // syst vars
    if (variation == 9){
        el_real = (TGraphAsymmErrors*)tempReal.Get("tg_el_real_HT100");
        mu_real = (TGraphAsymmErrors*)tempReal.Get("tg_mu_real_HT100");
    }
    else if (variation == 10){
        el_real = (TGraphAsymmErrors*)tempReal.Get("tg_el_real_HT300");
        mu_real = (TGraphAsymmErrors*)tempReal.Get("tg_mu_real_HT300");
    }

    if (variation == 11){
        el_fake = (TGraphAsymmErrors*)tempFake.Get("tg_el_fake_mtup");
        mu_fake = (TGraphAsymmErrors*)tempFake.Get("tg_mu_fake_mtup");
    }
    else if (variation == 12){
        el_fake = (TGraphAsymmErrors*)tempFake.Get("tg_el_fake_mtdown");
        mu_fake = (TGraphAsymmErrors*)tempFake.Get("tg_mu_fake_mtdown");
    }

    if (variation == 13){
        el_fake = (TGraphAsymmErrors*)tempFake.Get("tg_el_fake_metup");
        mu_fake = (TGraphAsymmErrors*)tempFake.Get("tg_mu_fake_metup");
    }
    else if (variation == 14){
        el_fake = (TGraphAsymmErrors*)tempFake.Get("tg_el_fake_metdown");
        mu_fake = (TGraphAsymmErrors*)tempFake.Get("tg_mu_fake_metdown");
    }



    // Everything has to have the same binning
    int nBins = el_fake->GetN();

    if (DEBUG) std::cout<<"nBins: "<<nBins<<std::endl;

    matrices = new MatrixMethod**[4];
    // todo put delete in destructor for this stuff

    matrices[EE] = new MatrixMethod*[nBins];
    matrices[EM] = new MatrixMethod*[nBins];
    matrices[ME] = new MatrixMethod*[nBins];
    matrices[MM] = new MatrixMethod*[nBins];

    // init matrices [lead bin][sub lead bin]
    for (int lead = 0; lead< nBins; lead++)
    { // lead bin

        // vector to hold pt binned matrix
        //std::vector<MatrixMethod> ll;
        //matrices[EE]->push_back( ll ); //EE
        //matrices[EM]->push_back( ll ); //EM
        //matrices[ME]->push_back( ll ); //ME
        //matrices[MM]->push_back( ll ); //MM


        matrices[EE][lead] = new MatrixMethod[nBins];
        matrices[EM][lead] = new MatrixMethod[nBins];
        matrices[ME][lead] = new MatrixMethod[nBins];
        matrices[MM][lead] = new MatrixMethod[nBins];


        //binBoundaries.push_back( el_temp_hist->GetBinLowEdge(lead + 1 ) );
        double tempX=0,tempY=0;
        el_fake->GetPoint(lead, tempX, tempY);
        //std::cout<<"pushing back "<<lead<<"th entry into binboundaires"<<std::endl;
        binBoundaries.push_back( tempX - el_fake->GetErrorXlow(lead) );

        // leading pt eff
        double x_lead_e_fake, y_lead_e_fake, x_lead_m_fake, y_lead_m_fake;
        double x_lead_e_real, y_lead_e_real, x_lead_m_real, y_lead_m_real;

        el_fake->GetPoint(lead ,x_lead_e_fake, y_lead_e_fake);
        mu_fake->GetPoint(lead ,x_lead_m_fake, y_lead_m_fake);

        el_real->GetPoint(lead ,x_lead_e_real, y_lead_e_real);
        mu_real->GetPoint(lead ,x_lead_m_real, y_lead_m_real);

        // Lep Eff Stat Uncert
        if (variation==1) // el real up
            y_lead_e_real += el_real->GetErrorYhigh(lead);
        if (variation==2) // el real down
            y_lead_e_real -= el_real->GetErrorYlow(lead);
        if (variation==3) // mu real up
            y_lead_m_real += mu_real->GetErrorYhigh(lead);
        if (variation==4) // mu real down
            y_lead_m_real -= mu_real->GetErrorYlow(lead);
        if (variation==5) // el fake up
            y_lead_e_fake += el_fake->GetErrorYhigh(lead);
        if (variation==6) // el fake down
            y_lead_e_fake -= el_fake->GetErrorYlow(lead);
        if (variation==7) // mu fake up
            y_lead_m_fake += mu_fake->GetErrorYhigh(lead);
        if (variation==8){ // mu fake down
            y_lead_m_fake -= mu_fake->GetErrorYlow(lead);
        }

        // function to bound efficiencies
        //boundEfficiencies(y_lead_e_fake, y_lead_m_fake, y_lead_e_real, y_lead_m_real  );
        if (DEBUG)  std::cout<<"x: "<< x_lead_e_fake<<" "<<x_lead_m_fake<<" "<< x_lead_e_real<<" "<<x_lead_m_real << std::endl;
        if (DEBUG)  std::cout<<"eff: "<< y_lead_e_fake<<" "<<y_lead_m_fake<<" "<< y_lead_e_real<<" "<<y_lead_m_real << std::endl;


        for (int sublead=0; sublead < nBins; sublead++)
        { // sub lead bin
            MatrixMethod mm_ee, mm_em, mm_me, mm_mm;

            // subleading pt eff
            double x_sublead_e_fake, y_sublead_e_fake, x_sublead_m_fake, y_sublead_m_fake;
            double x_sublead_e_real, y_sublead_e_real, x_sublead_m_real, y_sublead_m_real;

            el_fake->GetPoint(sublead ,x_sublead_e_fake, y_sublead_e_fake);
            mu_fake->GetPoint(sublead ,x_sublead_m_fake, y_sublead_m_fake);

            el_real->GetPoint(sublead ,x_sublead_e_real, y_sublead_e_real);
            mu_real->GetPoint(sublead ,x_sublead_m_real, y_sublead_m_real);

            // Lep Eff Stat Uncert
            if (variation==1) // el real up
                y_sublead_e_real += el_real->GetErrorYhigh(sublead);
            if (variation==2) // el real down
                y_sublead_e_real -= el_real->GetErrorYlow(sublead);
            if (variation==3) // mu real up
                y_sublead_m_real += mu_real->GetErrorYhigh(sublead);
            if (variation==4) // mu real down
                y_sublead_m_real -= mu_real->GetErrorYlow(sublead);
            if (variation==5) // el fake up
                y_sublead_e_fake += el_fake->GetErrorYhigh(sublead);
            if (variation==6) // el fake down
                y_sublead_e_fake -= el_fake->GetErrorYlow(sublead);
            if (variation==7) // mu fake up
                y_sublead_m_fake += mu_fake->GetErrorYhigh(sublead);
            if (variation==8) // mu fake down
                y_sublead_m_fake -= mu_fake->GetErrorYlow(sublead);

            boundEfficiencies(y_sublead_e_fake, y_sublead_m_fake, y_sublead_e_real, y_sublead_m_real  );

            if (DEBUG) std::cout<<"init ee"<<std::endl;
            //mm_ee.Init( y_lead_e_real, y_sublead_e_real,  y_lead_e_fake, y_sublead_e_fake);

            //matrices[EE][lead][sublead] = new MatrixMethod();
            matrices[EE][lead][sublead].Init( y_lead_e_real, y_sublead_e_real,  y_lead_e_fake, y_sublead_e_fake);

            if (DEBUG) std::cout<<"init em"<<std::endl;
            mm_em.Init( y_lead_e_real, y_sublead_m_real,  y_lead_e_fake, y_sublead_m_fake);

            //(*matrices[EM])[lead].push_back( mm_em );
            //matrices[EM][lead][sublead] = new MatrixMethod();
            matrices[EM][lead][sublead].Init( y_lead_e_real, y_sublead_m_real,  y_lead_e_fake, y_sublead_m_fake);

            if (DEBUG) std::cout<<"init me"<<std::endl;
            mm_me.Init( y_lead_m_real, y_sublead_e_real,  y_lead_m_fake, y_sublead_e_fake);

            //(*matrices[ME])[lead].push_back( mm_me );
            //matrices[ME][lead][sublead] = new MatrixMethod();
            matrices[ME][lead][sublead].Init( y_lead_m_real, y_sublead_e_real,  y_lead_m_fake, y_sublead_e_fake);

            if (DEBUG) std::cout<<"init mm"<<std::endl;
            mm_mm.Init( y_lead_m_real, y_sublead_m_real,  y_lead_m_fake, y_sublead_m_fake);

            //(*matrices[MM])[lead].push_back( mm_mm );
            //matrices[MM][lead][sublead] = new MatrixMethod();
            matrices[MM][lead][sublead].Init( y_lead_m_real, y_sublead_m_real,  y_lead_m_fake, y_sublead_m_fake);

        }

    }
    if (DEBUG) std::cout<<"Cleaning up holder init"<<std::endl;


    delete el_fake;
    delete mu_fake;
    delete el_real;
    delete mu_real;

    if (DEBUG) std::cout<<"Cleaning up holder init 2"<<std::endl;

    tempFake.Close();
    tempReal.Close();
    if (DEBUG) std::cout<<"Done with holder init"<<std::endl;

    if (DEBUG)
    {
        for (int i = 0; i< binBoundaries.size(); i++){ std::cout<<"bin boundary: "<<binBoundaries[i]<<std::endl;}
    }


}


double MM_Holder::getWeight(FLAV flav, ID id, double lepPt1, double lepPt2)
{
    if (DEBUG)
    {
        std::cout<<"Getting weight from: "<<flav << " "<< getPtBin(lepPt1)<< " "<< getPtBin(lepPt2)<<std::endl;
    }
    double weight = matrices[flav][ getPtBin(lepPt1) ][ getPtBin(lepPt2) ].getWeight(id);

    return weight;
}


double MM_Holder::getEff(FLAV flav, ID id, double lepPt1, double lepPt2)
{
    if (DEBUG)
    {
        std::cout<<"Getting weight from: "<<flav << " "<< getPtBin(lepPt1)<< " "<< getPtBin(lepPt2)<<std::endl;
    }
    double eff = matrices[flav][ getPtBin(lepPt1) ][ getPtBin(lepPt2) ].getEff( id );

    return eff;
}

double MM_Holder::getEffReal(FLAV flav, ID id, double lepPt1, double lepPt2)
{
    if (DEBUG)
    {
        std::cout<<"Getting weight from: "<<flav << " "<< getPtBin(lepPt1)<< " "<< getPtBin(lepPt2)<<std::endl;
    }
    double eff = matrices[flav][ getPtBin(lepPt1) ][ getPtBin(lepPt2) ].getEffReal( id );

    return eff;
}



int MM_Holder::getPtBin(double pt)
{

    int bin = -1;

    // pt is <= to lowest bin

    if (pt < binBoundaries[0] ) return 0;


    // pt is >= to highest bin
    if (pt >= binBoundaries[ binBoundaries.size() - 1 ] ) return binBoundaries.size() - 1;

    // rest of bins
    for (int i = 1; i < binBoundaries.size(); i++)
    {

        if (pt < binBoundaries[i] )
        {

            bin = i - 1;
            break;
        }

    }

    if (bin == -1) std::cout<<"Warning: didn't find a bin for "<<pt <<std::endl;

    return bin;
}



void MM_Holder::boundEfficiencies(double &y_lead_e_fake, double &y_lead_m_fake, double &y_lead_e_real, double &y_lead_m_real  )
{


    if (y_lead_e_fake < 0) y_lead_e_fake = 0;
    if (y_lead_m_fake < 0) y_lead_m_fake = 0;

    if (y_lead_e_real < 0) y_lead_e_real = 0;
    if (y_lead_m_real < 0) y_lead_m_real = 0;

    if (y_lead_e_fake > 1) y_lead_e_fake = 1;
    if (y_lead_m_fake > 1) y_lead_m_fake = 1;

    if (y_lead_e_real > 1) y_lead_e_real = 1;
    if (y_lead_m_real > 1) y_lead_m_real = 1;




}
