#include "PlotMaker.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// CONTROL PANEL /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

// To do
// data yield printout is incorrect (always zero)

int flavor=-1;
int cutStep;
int option;

//Calling function
void PlotMaker() {
    //vector<TString> treeNames = {
        //"outputTree",
        //"outputTree_EG_RESOLUTION_ALL__1down",
        //"outputTree_EG_RESOLUTION_ALL__1up",
        //"outputTree_EG_SCALE_ALL__1down",
        //"outputTree_EG_SCALE_ALL__1up",
        //"outputTree_EL_EFF_ID_TotalCorrUncertainty__1down",
        //"outputTree_EL_EFF_ID_TotalCorrUncertainty__1up",
        //"outputTree_EL_EFF_Reco_TotalCorrUncertainty__1down",
        //"outputTree_EL_EFF_Reco_TotalCorrUncertainty__1up",
        //"outputTree_JET_GroupedNP_1__1up",
        //"outputTree_JET_GroupedNP_1__1down",
        //"outputTree_JET_GroupedNP_2__1up",
        //"outputTree_JET_GroupedNP_2__1down",
        //"outputTree_JET_GroupedNP_3__1up",
        //"outputTree_JET_GroupedNP_3__1down",
        //"outputTree_JET_JER_SINGLE_NP__1up",
        //"outputTree_MET_SoftTrk_ResoPara",
        //"outputTree_MET_SoftTrk_ResoPerp",
        //"outputTree_MET_SoftTrk_ScaleDown",
        //"outputTree_MET_SoftTrk_ScaleUp",
        //"outputTree_MUONS_ID__1down",
        //"outputTree_MUONS_ID__1up",
        //"outputTree_MUONS_MS__1down",
        //"outputTree_MUONS_MS__1up",
        //"outputTree_MUONS_SCALE__1down",
        //"outputTree_MUONS_SCALE__1up",
        //"outputTree_MUON_EFF_STAT__1down",
        //"outputTree_MUON_EFF_STAT__1up",
        //"outputTree_MUON_EFF_SYS__1down",
        //"outputTree_MUON_EFF_SYS__1up"
    //};
    //for (TString name:treeNames) {
        //treeName = name;
        //cout << treeName << endl;
        //Plot((string)treeName + "_SRLow", vector<int> {5,15,0});
        //Plot((string)treeName + "_SRMed", vector<int> {5,16,0});
        //Plot((string)treeName + "_SRHigh", vector<int> {5,17,0});
        //Plot((string)treeName + "_VRLow", vector<int> {5,18,0});
        //Plot((string)treeName + "_VRMed", vector<int> {5,19,0});
        //Plot((string)treeName + "_VRHigh", vector<int> {5,20,0});
    //}

	//flavor = 0;
	//std::cout<<"Checkpoint: Flavor is 0"<<std::endl;
	//Plot("diboson_SR_mm_low", vector<int> {5,15,0});
	//Plot("diboson_SR_mm_med", vector<int> {5,16,0});
	//Plot("diboson_SR_mm_high", vector<int> {5,17,0});
	//Plot("diboson_VR_mm_low", vector<int> {5,18,0});
	//Plot("diboson_VR_mm_med", vector<int> {5,19,0});
	//Plot("diboson_VR_mm_high", vector<int> {5,20,0});
	//flavor = 1;
	//std::cout<<"Checkpoint: Flavor is 1"<<std::endl;
	//Plot("diboson_SR_ee_low", vector<int> {5,15,0});
	//Plot("diboson_SR_ee_med", vector<int> {5,16,0});
	//Plot("diboson_SR_ee_high", vector<int> {5,17,0});
	//Plot("diboson_VR_ee_low", vector<int> {5,18,0});
	//Plot("diboson_VR_ee_med", vector<int> {5,19,0});
	//Plot("diboson_VR_ee_high", vector<int> {5,20,0});
	//flavor = 2;
	//std::cout<<"Checkpoint: Flavor is OF"<<std::endl;
	//Plot("diboson_SR_OF_low", vector<int> {5,15,0});
	//Plot("diboson_SR_OF_med", vector<int> {5,16,0});
	//Plot("diboson_SR_OF_high", vector<int> {5,17,0});
	//Plot("diboson_VR_OF_low", vector<int> {5,18,0});
	//Plot("diboson_VR_OF_med", vector<int> {5,19,0});
	//Plot("diboson_VR_OF_high", vector<int> {5,20,0});

    //Plot("MT2", vector<int> {23,25,0});

    //option = 1;
    //Plot("WithPRW_SRLow", vector<int> {5,15,0});
    //Plot("WithPRW_SRMed", vector<int> {5,16,0});
    //Plot("WithPRW_SRHigh", vector<int> {5,17,0});
    //Plot("WithPRW_VRLow", vector<int> {5,18,0});
    //Plot("WithPRW_VRMed", vector<int> {5,19,0});
    //Plot("WithPRW_VRHigh", vector<int> {5,20,0});

    Plot("WZ_ZZ_WMassWZ", vector<int> {0,0,0});
    //Plot("WZ_ZZ_ZMassWZ", vector<int> {1,0,0});
    //Plot("WZ_ZZ_ZMasses", vector<int> {22,1,0});
    //Plot("WZ_ZZ_ZPtZZ", vector<int> {7,1,0});
    //Plot("WZ_ZZ_ZPtWZ", vector<int> {7,0,0});
    //Plot("WZ_ZZ_WPtWZ", vector<int> {6,0,0});
    //Plot("WZ_ZZ_JetNWZ", vector<int> {8,0,0});
    //Plot("WZ_ZZ_JetNZZ", vector<int> {8,1,0});
    //Plot("WZ_ZZ_HTWZ", vector<int> {10,0,0});
    //Plot("WZ_ZZ_HTZZ", vector<int> {10,1,0});
    //Plot("WZ_ZZ_HTinclWZ", vector<int> {9,0,0});
    //Plot("WZ_ZZ_HTinclZZ", vector<int> {9,1,0});
    //Plot("WZ_ZZ_BosonPtWZ", vector<int> {26,0,0});
    //Plot("WZ_ZZ_BosonPtZZ", vector<int> {26,1,0});
    //Plot("WZ_ZZ_JetN3L", vector<int> {8,24,0});

	//Plot("WZ_ZZ_dJetEtaWZ", vector<int> {24,26,0});
	//Plot("WZ_ZZ_MassJet12WZ", vector<int> {25,26,0});
	//Plot("WZ_ZZ_dJetEtaZZ", vector<int> {24,27,0});
	//Plot("WZ_ZZ_MassJet12ZZ", vector<int> {25,27,0});
    
    //Plot("DPhi1_ReverseDPhi", vector<int> {13,23,0});
    //Plot("DPhi2_ReverseDPhi", vector<int> {14,23,0});
    //Plot("Min_ReverseDPhi", vector<int> {15,23,0});
    
    //Plot("HT", vector<int> {10,i,0});
    //Plot("MET", vector<int> {12,i,0});
    //Plot("dPhiMETJet1", vector<int> {13,i,0});
    //Plot("dPhiMETJet2", vector<int> {14,i,0});
    //Plot("dPhiMETJetMin12", vector<int> {15,i,0});
    //Plot("lep1pT", vector<int> {17,i,0});
    //Plot("lep2pT", vector<int> {18,i,0});
    //Plot("dPhiZMET", vector<int> {19,i,0});
    //Plot("dPhil1l2", vector<int> {20,i,0});

    //option=0;
    //Plot("nVtx Without PRW (Inclusive)", vector<int> {21,3,0});
    //Plot("nVtx Without PRW (SRZ)", vector<int> {21,2,0});
    //option=1;
    //Plot("nVtx With PRW and Mu Rescaling (Inclusive)", vector<int> {21,3,0});
    //Plot("nVtx With PRW and Mu Rescaling (SRZ)", vector<int> {21,2,0});
    
    //Plot("nVtx in SRZ1", vector<int> {21,2,0});
    //Plot("nVtx in CRT1", vector<int> {21,6,2});
    //Plot("nVtx in CR-FS1", vector<int> {21,7,2});
    //Plot("nVtx in VRT1", vector<int> {21,8,2});
    //Plot("nVtx in VRS1", vector<int> {21,9,2});
	//Plot("nVtx in VR-3L", vector<int> {21,24,0});
}

//Options
void Plot(string plotSaveName, vector<int> options) {

    //Plotting options
    plotValueChoice = options[0];
    plotSecondValueChoice = 8;     //Only for scatter plots
    plotValues = {
        "W Mass",                   //0
        "Z Mass",                   //1
        "Leading Z Mass",           //2
        "Second Z Mass",            //3
        "Z Mllll",                  //4
        "Mll",                      //5
        "Leading W Pt",                   //6
        "Leading Z Pt",                   //7
        "Number of Jets",                   //8
        "HTincl",                  //9
        "HT",                  //10
        "lep_pT(0) + lep_pT(1)",                  //11
        "MET",                  //12
        "DPhi_METJetLeading",                  //13
        "DPhi_METJetSecond",                  //14
        "min(DPhi_METJetLeading, DPhi_METJetSecond)",                  //15
        "Lepton Number",                  //16
        "lep_pT(0)",                  //17
        "lep_pT(1)",                  //18
        "dPhiZMET",                  //19
        "dPhiLeptons",                  //20
        "nVtx",                  //21
        "Z Masses from ZZ",           //22
        "MT2",           //23
        "jet1_eta - jet2_eta",           //24
        "mass(jet1,jet2)",           //25
        "Vector Boson Pt",           //26
    };

    eventTypeChoice = options[1];
    eventTypes = {
        "WZ VR",                //0
        "ZZ VR",                //1
        "SRZ1",      //2
        "All Events",    //3
        "SRZ1, OF Instead of SF",     //4
        "SR-soft",     //5
        "CRT1",     //6
        "CR-FS1",     //7
        "VRT1",     //8
        "VRS1",     //9
        "SR - ee",     //10
        "SR - mm",     //11
        "SRZ1, No Flavor Cut",     //12
        "ZMET VR",    //13
        "VV Estimation",    //14
        "EDGE SR Low",    //15
        "EDGE SR Medium",    //16
        "EDGE SR High",    //17
        "EDGE VR Low",    //18
        "EDGE VR Medium",    //19
        "EDGE VR High",    //20
        "VRT+CRT",    //21
        "VRS+SRZ",    //22
        "SRZ1, No dPhi Cut",     //23
        "VR-3L",     //24
        "EDGE SR Medium with Mll<100",    //25
        "WZ VR with >=2 Jets",                //26
        "ZZ VR with >=2 Jets",                //27
    };

    splitTypeChoice = options[2];
    splitTypes = {
        "Default Categories",       //0
        "Leading Z Flavor Channel",         //1
        "Flavor",         //2
        "Channel"          //3
    };

    plotTypeChoice = 0;
    plotTypes = {
        "Stacked",                  //0
        "Line Comparison",          //1
        "Scatter"                   //2
    };

    setMaxEventsPerFile = false;
    maxEventsPerFile = 100;

    plotData = true;
    plotLogY = false;
    //bug - log y doesn't work for line comparison plots.
    drawLegend = true;
    drawStats = false;

    xBins = 15;
    xRangeLow = 0;
    xRangeHigh = 200;
    if (plotValueChoice==8) {
        xRangeHigh = 8;
        xBins = 8;
    }
    if (plotValueChoice==5)
        xRangeHigh = 400;
    if (plotValueChoice==6 || plotValueChoice==7 || plotValueChoice==26)
        xRangeHigh = 300;
    if (plotValueChoice==9)
        xRangeHigh = 800;
    if (plotValueChoice==10) {
        xBins = 10;
        xRangeHigh = 300;
    }
    if (plotValueChoice>=13 && plotValueChoice<=15) {
        xBins = 30;
        xRangeHigh = 3.14159;
    }
    if (plotValueChoice==16) {
        xRangeHigh = 5;
        xBins = 5;
        //xRangeHigh = 3;
    }
    if (plotValueChoice==21) {
        xRangeHigh = 40;
        xBins = 40;
    }
    if (plotValueChoice==23) {
        xRangeLow = 950;
        xRangeHigh = 1150;
        xBins = 50;
    }
    if (plotValueChoice==24) {
        xRangeLow = -6;
        xRangeHigh = 6;
        xBins = 15;
    }
    if (plotValueChoice==25) {
        xRangeLow = 0;
        xRangeHigh = 1000;
        xBins = 20;
    }
    yBins = 50; //For scatter plot only
    yRangeLow = 0;
    setYHigh = false;
    yRangeHigh = 6000;

    plotRatioBox = false;
    ratioMin = .5;
    ratioMax = 1.5;

    performWeighting = true;
    pileupReweighting = true;
    muRescaling = false;
    useWeight1fb = false; //Doesn't work right

    printCutflow = false;
    printFinalNumbers = true;

    saveDirectory = "~/Plots/dataTotalDibosons/";
    saveTag = plotSaveName;
    saveImage = true;
    filetype = "pdf";

    //luminosity = 3209.05;
    //luminosity = 3500;
    //luminosity = 6500;
    luminosity = 14700;

    //File paths
    MCPath = "/afs/cern.ch/work/y/ycao/public/v1_02/MC/";
    //MCPath = "/afs/cern.ch/user/b/benhoob/workspace/ZMETSamples/Ntuples2016/v01-03/MC/";
    //dataPath = "/afs/cern.ch/work/y/ycao/public/v1_02/Data";
    dataPath = "/afs/cern.ch/work/m/mazhang/Temp/";
    //dataName = "data_2015";
    dataName = "data_2016";
    //dataName = "data_14p7fb";
    blinded = true;
    treeName = "outputTree";

    ///////////////////////////////////////////
    //Definitions used in paper
    ///////////////////////////////////////////

    for (int i=361372; i<=361443; i++) {
        if (i<=361395)
            addSample(i,"Sherpa Zee");
        else if (i<=361419)
            addSample(i,"Sherpa Zmm");
        else
            addSample(i,"Sherpa Ztt");
    }

    for (int i=361468; i<=361491; i++) { //DY
        if (i<=361475)
            addSample(i,"Sherpa Zee");
        else if (i<=361483)
            addSample(i,"Sherpa Zmm");
        else if (i!=361484) //this sample has an issue
            addSample(i,"Sherpa Ztt");
    }
    
    addSample(410000,"Powheg ttbar");
    vector<int> tW = {410015, 410016, 410064, 410065};
    for (int i:tW) {
        addSample(i,"Powheg ttbar");
    }

    vector<int> tZ = {410050};
    for (int i:tZ) {
        addSample(i,"Rare Top");
    }
    vector<int> ttW = {410066, 410067, 410068};
    for (int i:ttW) {
        addSample(i,"Rare Top");
    }
    vector<int> ttZ = {410111, 410112, 410113, 410114, 410115, 410116};
    for (int i:ttZ) {
        addSample(i,"Rare Top");
    }
    addSample(410081,"Rare Top"); //tt+WW

    addSample(361068,"Sherpa VV - llvv");  //llvv
    addSample(361077, "Sherpa VV - llvv"); //llvv (gg)

    addSample(361063,"Sherpa ZZ - llll");  //llll
    addSample(361073, "Sherpa ZZ - llll"); //llll (gg)

    for (int i=361064; i<=361067; i++) {
        addSample(i,"Sherpa WZ - lllv");   //lllv
    }

    ///////////////////////////////////////////
    //Definitions used in paper
    ///////////////////////////////////////////

    ////Samples to use in plot

    //for (int i=361372; i<=361443; i++) {
        //if (i==361413) continue;
        //if (i<=361395)
            //addSample(i,"Sherpa Zee");
        //else if (i<=361419)
            //addSample(i,"Sherpa Zmm");
        //else
            //addSample(i,"Sherpa Ztt");
    //}
    
    ////for (int i=363102; i<=363122; i++) {
        ////addSample(i,"Sherpa 2.2 Ztt");
    ////}
    ////for (int i=363364; i<=363387; i++) {
        ////addSample(i,"Sherpa 2.2 Zmm");
    ////}
    ////for (int i=363388; i<=363411; i++) {
        ////if (i==363393) continue;
        ////if (i==363401) continue;
        ////addSample(i,"Sherpa 2.2 Zee");
    ////}

    //addSample(410000,"Powheg ttbar");
    //vector<int> ttW = {410066, 410067, 410068};
    //for (int i:ttW) {
        //addSample(i,"Rare Top");
    //}
    //addSample(410081,"Rare Top"); //tt+WW
    //vector<int> ttZ = {410111, 410112, 410113, 410114, 410115, 410116};//, 410069, 410070};
    //for (int i:ttZ) {
        //addSample(i,"Rare Top");
    //}
    //addSample(361068,"Sherpa VV - llvv");  //llvv
    //addSample(361077, "Sherpa VV - llvv"); //llvv (gg)
    //addSample(361073, "Sherpa ZZ - llll"); //llll (gg)
    //addSample(361063,"Sherpa ZZ - llll");  //llll
    //for (int i=361064; i<=361067; i++) {
        //addSample(i,"Sherpa WZ - lllv");   //lllv
    //}

	//for (int i=361372; i<=361443; i++) {
		//if (i<=361395)
			//addSample(i,"Z");
		//else if (i<=361419)
			//addSample(i,"Z");
		//else
			//addSample(i,"Z");
	//}
	//addSample(410000,"Top");
	//vector<int> ttW = {410066, 410067, 410068};
	//for (int i:ttW) {
		//addSample(i,"Top");
	//}
	//addSample(410081,"Top"); //tt+WW
	//vector<int> ttZ = {410111, 410112, 410113, 410114, 410115, 410116};//, 410069, 410070};
	//for (int i:ttZ) {
		//addSample(i,"Top");
	//}
	//addSample(361068,"llvv");  //llvv
	//addSample(361077, "llvv"); //llvv (gg)
	//addSample(361073, "llll"); //llll (gg)
	//addSample(361063,"llll");  //llll
	//for (int i=361064; i<=361067; i++) {
		//addSample(i,"lllv");   //lllv
	//}
	//addSample(361068,"Diboson");  //llvv
	//addSample(361077, "Diboson"); //llvv (gg)
	//addSample(361073, "Diboson"); //llll (gg)
	//addSample(361063,"Diboson");  //llll
	//for (int i=361064; i<=361067; i++) {
		//addSample(i,"Diboson");   //lllv
	//}

    //addSample(361601,"Powheg WZ - lllv");
    //addSample(361603,"Powheg ZZ"); //llll
    //addSample(361604,"Powheg ZZ"); //llvv
    //addSample(361600,"Powheg WW - llvv");

	//addSample(341080, "Higgs");
	//addSample(341488, "Higgs");
	//addSample(341471, "Higgs");
	//addSample(341505, "Higgs");
	//addSample(341947, "Higgs");
	//addSample(341964, "Higgs");
	//addSample(341177, "Higgs");
	//addSample(341270, "Higgs");
	//addSample(341271, "Higgs");
	//addSample(341102, "Higgs");
	//addSample(341001, "Higgs");
	//addSample(341155, "Higgs");
	//addSample(341156, "Higgs");
	//addSample(341206, "Higgs");
	//addSample(341254, "Higgs");
	//addSample(341446, "Higgs");
	////addSample(341518, "Higgs");
	////addSample(341564, "Higgs");
	////addSample(341565, "Higgs");
	////addSample(341566, "Higgs");
	////addSample(341974, "Higgs");
	////addSample(341157, "Higgs");

    //addSample(372502,"Slepton (1000,840)");
    //addSample(372462,"Slepton (1200,500)");
    //addSample(372466,"Slepton (1400,100)");
    //addSample(372577,"Z (1000,840)");
    //addSample(372537,"Z (1200,500)");
    //addSample(372541,"Z (1400,100)");

    //addSample(361063,"361063");
    //addSample(361064,"361064");
    //addSample(361065,"361065");
    //addSample(361066,"361066");
    //addSample(361067,"361067");
    //addSample(361068,"361068");
    //addSample(361073,"361073");
    //addSample(361077,"361077");
    //addSample(361084,"361084");
    //addSample(361086,"361086");
    //addSample(361600,"361600");
    //addSample(361601,"361601");
    //addSample(361603,"361603");
    //addSample(361604,"361604");
    //addSample(361607,"361607");
    //addSample(361610,"361610");
    
    //Make plot, then wait 1 second to prevent file overwrite from going too fast
    MakePlot();
    usleep(1000000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// VARIABLES FROM BRANCHES ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

//Variables taken and calculated from branches
Long64_t lep_n;
Long64_t  channel;
vector<double> *lep_pT = 0;
vector<double> *lep_eta = 0;
vector<double> *lep_phi = 0;
vector<double> *jet_pT = 0;
vector<double> *jet_eta = 0;
vector<double> *jet_phi = 0;
vector<double> *jet_m = 0;
vector<double> *lep_pdgID = 0;
double MET;
double MET_phi;
double mll;
float MT2;
Long64_t jet_n;
Long64_t bjet_n;
double HTincl;
double HT;
Long64_t eetrig, eetrigmatch, mmtrig, mmtrigmatch, emtrig, emtrigmatch;
double DPhi_METJetLeading;
double DPhi_METJetSecond;
Long64_t HLT_mu50;
Long64_t nVtx;

Long64_t SRZ, CRT, CRFS, VRT, VRS, CRZ, VRZ, EdgeSRLow, EdgeSRMed, EdgeSRHigh, EdgeVRLow, EdgeVRMed, EdgeVRHigh, EdgeCRTLow, EdgeCRTMed, EdgeCRTHigh, EdgeVRTLow, EdgeVRTMed, EdgeVRTHigh, VR3L, VRWZ, VRZZ;

//Extract branches - happens once per tree 
void GetBranches(TTree* tree) {

    tree->SetBranchStatus("*",0);
    tree->SetBranchStatus("lep_n",1);
    tree->SetBranchAddress("lep_n",&lep_n);
    tree->SetBranchStatus("channel",1);
    tree->SetBranchAddress("channel",&channel);
    tree->SetBranchStatus("lep_pT",1);
    tree->SetBranchAddress("lep_pT",&lep_pT);
    tree->SetBranchStatus("lep_eta",1);
    tree->SetBranchAddress("lep_eta",&lep_eta);
    tree->SetBranchStatus("lep_phi",1);
    tree->SetBranchAddress("lep_phi",&lep_phi);
    tree->SetBranchStatus("jet_pT",1);
    tree->SetBranchAddress("jet_pT",&jet_pT);
    tree->SetBranchStatus("jet_eta",1);
    tree->SetBranchAddress("jet_eta",&jet_eta);
    tree->SetBranchStatus("jet_phi",1);
    tree->SetBranchAddress("jet_phi",&jet_phi);
    tree->SetBranchStatus("jet_m",1);
    tree->SetBranchAddress("jet_m",&jet_m);
    tree->SetBranchStatus("lep_pdgId",1);
    tree->SetBranchAddress("lep_pdgId",&lep_pdgID);
    tree->SetBranchStatus("MET",1);
    tree->SetBranchAddress("MET",&MET);
    //tree->SetBranchStatus("MT2",1);
    //tree->SetBranchAddress("MT2",&MT2);
    tree->SetBranchStatus("MET_phi",1);
    tree->SetBranchAddress("MET_phi",&MET_phi);
    tree->SetBranchStatus("mll",1);
    tree->SetBranchAddress("mll",&mll);
    tree->SetBranchStatus("jet_n",1);
    tree->SetBranchAddress("jet_n",&jet_n);
    tree->SetBranchStatus("bjet_n",1);
    tree->SetBranchAddress("bjet_n",&bjet_n);
    tree->SetBranchStatus("HT",1);
    tree->SetBranchAddress("HT",&HT);
    tree->SetBranchStatus("HTincl",1);
    tree->SetBranchAddress("HTincl",&HTincl);
    tree->SetBranchStatus("eetrig",1);
    tree->SetBranchAddress("eetrig",&eetrig);
    tree->SetBranchStatus("mmtrig",1);
    tree->SetBranchAddress("mmtrig",&mmtrig);
    tree->SetBranchStatus("emtrig",1);
    tree->SetBranchAddress("emtrig",&emtrig);
    tree->SetBranchStatus("eetrig_match",1);
    tree->SetBranchAddress("eetrig_match",&eetrigmatch);
    tree->SetBranchStatus("mmtrig_match",1);
    tree->SetBranchAddress("mmtrig_match",&mmtrigmatch);
    tree->SetBranchStatus("emtrig_match",1);
    tree->SetBranchAddress("emtrig_match",&emtrigmatch);
    tree->SetBranchStatus("DPhi_METJetLeading",1);
    tree->SetBranchAddress("DPhi_METJetLeading",&DPhi_METJetLeading);
    tree->SetBranchStatus("DPhi_METJetSecond",1);
    tree->SetBranchAddress("DPhi_METJetSecond",&DPhi_METJetSecond);
    tree->SetBranchStatus("HLT_mu50",1);
    tree->SetBranchAddress("HLT_mu50",&HLT_mu50);
    tree->SetBranchStatus("nVtx",1);
    tree->SetBranchAddress("nVtx",&nVtx);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// HELPER FUNCTIONS ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

//Global variables
vector<pair<int,int>> OSSFPairs;
pair<int,int> leadingPair;
float WZWMass;
float WZZMass;
float ZZLeadingZMass;
float ZZSecondZMass;
float ZZMass;
float WPT;
float ZPT;
float ZPT2;
int minLepPT = 25;

float invMass(int l1, int l2) {
    if (l1>=lep_eta->size() || l2>=lep_eta->size()) return -999;
    TLorentzVector p1;
    p1.SetPtEtaPhiM((*lep_pT)[l1],(*lep_eta)[l1],(*lep_phi)[l1],0);
    TLorentzVector p2;
    p2.SetPtEtaPhiM((*lep_pT)[l2],(*lep_eta)[l2],(*lep_phi)[l2],0);
    return (p1+p2).M();
}

float invPT(int l1, int l2) {
    if (l1>=lep_eta->size() || l2>=lep_eta->size()) return -999;
    TLorentzVector p1;
    p1.SetPtEtaPhiM((*lep_pT)[l1],(*lep_eta)[l1],(*lep_phi)[l1],0);
    TLorentzVector p2;
    p2.SetPtEtaPhiM((*lep_pT)[l2],(*lep_eta)[l2],(*lep_phi)[l2],0);
    return (p1+p2).Pt();
}

float invMass(int l1, int l2, int l3, int l4) {
    if (l1>=lep_eta->size() || l2>=lep_eta->size() || l3>=lep_eta->size() || l4>=lep_eta->size()) return -999;
    TLorentzVector p1;
    p1.SetPtEtaPhiM((*lep_pT)[l1],(*lep_eta)[l1],(*lep_phi)[l1],0);
    TLorentzVector p2;
    p2.SetPtEtaPhiM((*lep_pT)[l2],(*lep_eta)[l2],(*lep_phi)[l2],0);
    TLorentzVector p3;
    p3.SetPtEtaPhiM((*lep_pT)[l3],(*lep_eta)[l3],(*lep_phi)[l3],0);
    TLorentzVector p4;
    p4.SetPtEtaPhiM((*lep_pT)[l4],(*lep_eta)[l4],(*lep_phi)[l4],0);
    return (p1+p2+p3+p4).M();
}

float transPT(int l1) {
    if (l1>=lep_eta->size()) return -999;
    TLorentzVector p1;
    p1.SetPtEtaPhiM((*lep_pT)[l1],(*lep_eta)[l1],(*lep_phi)[l1],0);
    TLorentzVector p2;
    p2.SetPtEtaPhiM(MET,0,MET_phi,0);
    return (p1+p2).Pt();
}

//Function to find transverse mass of lepton and MET
float transMass(int l1) {
    if (l1>=lep_eta->size()) return -999;
    float ang = (*lep_phi)[l1]-MET_phi;
    float l1p = (*lep_pT)[l1];
    float l2p = MET;
    float mass = sqrt(2*l1p*l2p*(1-cos(ang)));
    return sqrt(2*l1p*l2p*(1-cos(ang)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// PLOT DEFINITIONS ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void defineEvent() {

    switch (eventTypeChoice) {
        case 0: //WZ
        case 26: //WZ with >=2 Jets
            {
                addCut((channel==0 && mmtrig && mmtrigmatch) || (channel==1 && eetrig && eetrigmatch) || (channel>=2 && emtrig && emtrigmatch));
                addCut(lep_n==3);
                if (lep_n==3) {
                    addCut(lep_pT->at(0)>50 && lep_pT->at(1)>minLepPT && lep_pT->at(2)>minLepPT);
                    float closestToZ = 999;
                    pair<int,int> ZPair = make_pair(-1,-1);
                    for (auto pair:OSSFPairs) {
                        float distanceToZ = abs(invMass(pair.first,pair.second)-91.2);
                        if (distanceToZ<closestToZ) {
                            closestToZ = distanceToZ;
                            ZPair = pair;
                        }
                    }
                    addCut(ZPair.first!=-1);
                    if (ZPair.first!=-1) {
                        WZZMass = invMass(ZPair.first,ZPair.second);
                        ZPT = invPT(ZPair.first,ZPair.second);
                        int WLepton = -1;
                        for (int i=0; i<3; i++) {
                            if (ZPair.first!=i && ZPair.second!=i)
                                WLepton = i;
                        }
                        WZWMass = transMass(WLepton);
                        WPT = transPT(WLepton);
                        ZPT = invPT(ZPair.first,ZPair.second);
                        addCut(WZWMass<100);
                        addCut(MET>50 && MET<200);
                        addCut(bjet_n==0);
                        leadingPair = ZPair;
                    }
                }
                if (eventTypeChoice==26)
                    addCut(jet_n>=2);
                break;
            }
        case 1: //ZZ
        case 27: //ZZ with >=2 Jets
            {
                addCut((channel==0 && mmtrig && mmtrigmatch) || (channel==1 && eetrig && eetrigmatch) || (channel>=2 && emtrig && emtrigmatch));
                addCut(lep_n==4);
                if (lep_n==4) {
                    addCut(lep_pT->at(0)>50 && lep_pT->at(1)>minLepPT && lep_pT->at(2)>minLepPT && lep_pT->at(3)>minLepPT);
                    bool OSSF01 = false;
                    bool OSSF02 = false;
                    bool OSSF03 = false;
                    bool OSSF12 = false;
                    bool OSSF13 = false;
                    bool OSSF23 = false;
                    for (auto pair:OSSFPairs) {
                        if (pair==make_pair(0,1))
                            OSSF01 = true;
                        else if (pair==make_pair(0,2))
                            OSSF02 = true;
                        else if (pair==make_pair(0,3))
                            OSSF03 = true;
                        else if (pair==make_pair(1,2))
                            OSSF12 = true;
                        else if (pair==make_pair(1,3))
                            OSSF13 = true;
                        else if (pair==make_pair(2,3))
                            OSSF23 = true;
                    }
                    bool TwoOSSFPairs = (OSSF01 && OSSF23) || (OSSF02 && OSSF13) || (OSSF03 && OSSF12);
                    addCut(TwoOSSFPairs);
                    if (TwoOSSFPairs) {
                        float invMass0123 = invMass(0,1) + invMass(2,3);
                        float invMass0213 = invMass(0,2) + invMass(1,3);
                        float invMass0312 = invMass(0,3) + invMass(1,2);
                        float closestToZZ = 9999;
                        vector<pair<int,int>> ZZPairs = {};
                        if (OSSF01 && OSSF23 && abs(invMass0123-182)<closestToZZ) {
                            closestToZZ = abs(invMass0123-182);
                            ZZPairs.push_back(make_pair(0,1));
                            ZZPairs.push_back(make_pair(2,3));
                        }
                        if (OSSF02 && OSSF13 && abs(invMass0213-182)<closestToZZ) {
                            closestToZZ = abs(invMass0213-182);
                            ZZPairs.clear();
                            ZZPairs.push_back(make_pair(0,2));
                            ZZPairs.push_back(make_pair(1,3));
                        }
                        if (OSSF03 && OSSF12 && abs(invMass0312-182)<closestToZZ) {
                            closestToZZ = abs(invMass0312-182);
                            ZZPairs.clear();
                            ZZPairs.push_back(make_pair(0,3));
                            ZZPairs.push_back(make_pair(1,2));
                        }
                        ZZLeadingZMass = invMass(ZZPairs[0].first,ZZPairs[0].second);
                        ZPT = invPT(ZZPairs[0].first,ZZPairs[0].second);
                        ZZSecondZMass = invMass(ZZPairs[1].first,ZZPairs[1].second);
                        ZPT2 = invPT(ZZPairs[1].first,ZZPairs[1].second);
                        ZZMass = invMass(ZZPairs[0].first,ZZPairs[0].second,ZZPairs[1].first,ZZPairs[1].second);
                        if (ZZLeadingZMass<ZZSecondZMass) {
                            float temp = ZZLeadingZMass;
                            ZZLeadingZMass = ZZSecondZMass;
                            ZZSecondZMass = temp;
                            leadingPair = ZZPairs[1];
                        }
                        else
                            leadingPair = ZZPairs[0];
                        addCut(MET<100); //Increased from 50 by Emma's suggestion
                        addCut(bjet_n==0);
                    }
                }
                if (eventTypeChoice==27)
                    addCut(jet_n>=2);
                break;
            }
            break;
        case 3: //Inclusive
            break;
        case 2: //SRZ1
        case 6: //CRT1
        case 7: //CR-FS1
        case 8: //VRT1
        case 9: //VRS1
        case 21: //VRT+CRT
        case 22: //VRS+SRZ
        case 23: //SRZ1 No dPhi Cut
            addCut("trigger", (channel==0 && mmtrig && mmtrigmatch) || (channel==1 && eetrig && eetrigmatch) || (channel>=2 && emtrig && emtrigmatch));
            addCut("Mll > 45", mll>45);
            addCut("lep_n", lep_n>=2);
            addCut("pT (50,25)", lep_pT->at(0)>50 && lep_pT->at(1)>25);
            addCut("jet_n >= 2", jet_n>=2);

            //addCut("OS", lep_pdgID->at(0)*lep_pdgID->at(1)<0);
            if (eventTypeChoice == 7)
                addCut("OSOF", lep_pdgID->at(0)!=-lep_pdgID->at(1) && lep_pdgID->at(0)*lep_pdgID->at(1)<0);
            else
                addCut("OSSF", lep_pdgID->at(0)==-lep_pdgID->at(1));

            if (eventTypeChoice == 6 || eventTypeChoice == 8 || eventTypeChoice == 21)
                addCut("Mll (<81 or >101)", mll<81 || mll>101);
            else if (eventTypeChoice == 7)
                addCut("Mll (>61 or <121)", mll>61 && mll<121);
            else
                addCut("Mll (>81 and <101)", mll>81 && mll<101);

            if (eventTypeChoice == 8 || eventTypeChoice == 9)
                addCut("MET", MET>100 && MET<200);
            else if (eventTypeChoice==21 || eventTypeChoice==22)
                addCut("MET", MET>100);
            else
                addCut("MET", MET>225);

            addCut("HTincl", HTincl>600);
            if (eventTypeChoice!=23)
                addCut(DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4);
            //else
            //addCut(DPhi_METJetLeading<0.4 || DPhi_METJetSecond<0.4);
            break;
        case 14: //VV Estimation
            if (cutStep<1) break;
            addCut(mll>81 && mll<101);
            if (cutStep<2) break;
            addCut((channel==0 && mmtrig && mmtrigmatch) || (channel==1 && eetrig && eetrigmatch) || (channel>=2 && emtrig && emtrigmatch));
            if (cutStep<3) break;
            addCut(lep_n>=2);
            if (cutStep<4) break;
            addCut(lep_pdgID->at(0)*lep_pdgID->at(1)<0);
            if (cutStep<5) break;
            addCut(lep_pT->at(0)>50 && lep_pT->at(1)>25);
            if (cutStep<6) break;
            addCut(jet_n>=2);
            if (cutStep<7) break;
            addCut(DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4);
            if (cutStep<8) break;
            addCut(HTincl>600);
            if (cutStep<9) break;
            addCut(MET>225);
            break;
        case 15: //EDGE SR Low
        case 16: //EDGE SR Medium
        case 17: //EDGE SR High
        case 18: //EDGE VR Low
        case 19: //EDGE VR Medium
        case 20: //EDGE VR High
        case 25: //EDGE SR Medium with Mll<100
            //if (MET>225 && (lep_pdgID->at(0) = -lep_pdgID->at(1)) && jet_n>=2) //blinding
            //addCut(0);
            //else
            //addCut(1);
            if (flavor==-1) {
                addCut("Channel and Trigger", (channel==0 && mmtrig && mmtrigmatch) || (channel==1 && eetrig && eetrigmatch));
            }
            if (flavor==0) {
                addCut("Channel", channel==0);
                addCut("Trigger", mmtrig==1 && mmtrigmatch==1);
            }
            if (flavor==1) {
                addCut("Channel", channel==1);
                addCut("Trigger", eetrig==1 && eetrigmatch==1);
            }
            if (flavor==2) {
                addCut("Channel", (channel==2 || channel==3));
                addCut("Trigger", emtrig==1 && emtrigmatch==1);
            }
            addCut("Mll > 12", mll>12);
            addCut("OS", lep_pdgID->at(0)*lep_pdgID->at(1)<0);
            if (eventTypeChoice>=15 && eventTypeChoice<=17 && flavor!=2) //SR
                addCut("SF", lep_pdgID->at(0)==-lep_pdgID->at(1));
            addCut("pT (25,25)", lep_pT->at(0)>25 && lep_pT->at(1)>25);
            addCut("jet_n >= 2", jet_n>=2);
            addCut(DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4);

            if (eventTypeChoice>=18 && eventTypeChoice<=20) //VR
                addCut("MET", MET>100 && MET<200);
            if (eventTypeChoice==15 || eventTypeChoice==17 || eventTypeChoice==16 || eventTypeChoice==25)
                addCut("MET", MET>200);

            if (eventTypeChoice==16 || eventTypeChoice==25 || eventTypeChoice==19) //Med
                addCut("HT", HT>400);
            if (eventTypeChoice==17 || eventTypeChoice==20) //High
                addCut("HT", HT>700);

            if (eventTypeChoice==25)
                addCut("mll<100", mll<100);
            break;
        case 24: //VR-3L
            {
                addCut((eetrig && eetrigmatch) || (mmtrig && mmtrigmatch) || (emtrig && emtrigmatch));
                addCut(lep_n==3);
                if (lep_n==3) {
                    addCut(lep_pT->at(0)>50 && lep_pT->at(1)>25 && lep_pT->at(2)>25);
                    addCut(MET>60 && MET<100);
                    addCut(HTincl>200);
                    addCut(jet_n>=2);
                    addCut(DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4);
                    //float invMass01 = invMass(0,1);
                    //float invMass02 = invMass(0,2);
                    //float invMass12 = invMass(1,2);
                    addCut(mll>81 && mll<101);
                    addCut("OSSF", lep_pdgID->at(0)==-lep_pdgID->at(1));
                    //if(invMass01>81 && invMass01<101 && (lep_pdgID->at(0) == -lep_pdgID->at(1))) addCut(true);
                    //else if(invMass02>81 && invMass02<101 && (lep_pdgID->at(0) == -lep_pdgID->at(2))) addCut(true);
                    //else if(invMass12>81 && invMass12<101 && (lep_pdgID->at(1) == -lep_pdgID->at(2))) addCut(true);
                    //else
                    //addCut(false);
                }
                break;
            }
        default:
            cout<<"Undefined event selection!"<<endl;
    }
}

vector<float> definePlotValue(int choice) {

    vector<float> value;
    switch (choice) {
        case 0:
            value.push_back(WZWMass);
            break;
        case 1:
            value.push_back(WZZMass);
            break;
        case 2:
            value.push_back(ZZLeadingZMass);
            break;
        case 3:
            value.push_back(ZZSecondZMass);
            break;
        case 4:
            value.push_back(ZZMass);
            break;
        case 5:
            value.push_back(invMass(0,1));
            break;
        case 6:
            value.push_back(WPT);
            break;
        case 7:
            value.push_back(ZPT);
            break;
        case 8:
            value.push_back(jet_n);
            break;
        case 9:
            value.push_back(HTincl);
            break;
        case 10:
            value.push_back(HT);
            break;
        case 11:
            value.push_back(lep_pT->at(0)+lep_pT->at(1));
            break;
        case 12:
            value.push_back(MET);
            break;
        case 13:
            value.push_back(DPhi_METJetLeading);
            break;
        case 14:
            value.push_back(DPhi_METJetSecond);
            break;
        case 15:
            value.push_back(min(DPhi_METJetLeading, DPhi_METJetSecond));
            break;
        case 16:
            value.push_back(lep_n);
            break;
        case 17:
            value.push_back(lep_pT->at(0));
            break;
        case 18:
            value.push_back(lep_pT->at(1));
            break;
        case 21:
            value.push_back(nVtx);
            break;
        case 22:
            value.push_back(ZZLeadingZMass);
            value.push_back(ZZSecondZMass);
            break;
        case 23:
            value.push_back(MT2);
            break;
        case 24:
            {
                if (jet_eta->size()<2) {
                    value.push_back(-999);
                    break;
                }
                value.push_back(jet_eta->at(0) - jet_eta->at(1));
                break;
            }
        case 25:
            {
                if (jet_eta->size()<2) {
                    value.push_back(-999);
                    break;
                }
                TLorentzVector j1;
                j1.SetPtEtaPhiM((*jet_pT)[0],(*jet_eta)[0],(*jet_phi)[0],(*jet_m)[0]);
                TLorentzVector j2;
                j2.SetPtEtaPhiM((*jet_pT)[1],(*jet_eta)[1],(*jet_phi)[1],(*jet_m)[1]);
                value.push_back((j1+j2).M());
                break;
            }
		case 26:
			value.push_back(ZPT);
			if (eventTypeChoice == 0) {
				value.push_back(WPT);
			}
			else if (eventTypeChoice == 1) {
				value.push_back(ZPT2);
			}
			break;
        default:
            cout<<"Undefined plotting option!"<<endl;
    }
    return value;
}

void SetupSplitting() {

    switch (splitTypeChoice) {
        case 0:
            splitCategories = {};
            for (int i=0; i<defaultCategoryNames.size(); i++) {
                splitCategories.push_back(i);
            }
            splitCategoryNames = defaultCategoryNames;
            break;
        case 1:
            splitCategories = {0, 1, 2, 3}; 
            splitCategoryNames = {"mm", "ee", "em", "me"};
            break;
        case 2:
            splitCategories = {0, 1}; 
            splitCategoryNames = {"OF", "SF"};
            break;
        case 3:
            splitCategories = {0, 1, 2, 3}; 
            splitCategoryNames = {"mm", "ee", "em", "me"};
            break;
        default:
            cout<<"Undefined split!"<<endl;
    }
}

void defineSplitting() {

    switch (splitTypeChoice) {
        case 0:
            //Special case - default splitting
            break;
        case 1:
            if (leadingPair.first==-1)
                break;
            if (abs(lep_pdgID->at(leadingPair.first))==13 && abs(lep_pdgID->at(leadingPair.second))==13)
                splitChannel.push_back(0);
            else if (abs(lep_pdgID->at(leadingPair.first))==11 && abs(lep_pdgID->at(leadingPair.second))==11)
                splitChannel.push_back(1);
            else if (abs(lep_pdgID->at(leadingPair.first))==11 && abs(lep_pdgID->at(leadingPair.second))==13)
                splitChannel.push_back(2);
            else if (abs(lep_pdgID->at(leadingPair.first))==13 && abs(lep_pdgID->at(leadingPair.second))==11)
                splitChannel.push_back(3);
            break;
        case 2:
            //if ((abs(lep_pdgID->at(0))!=11 && abs(lep_pdgID->at(0))!=13) || (abs(lep_pdgID->at(1))!=11 && abs(lep_pdgID->at(1))!=13))
                //break;
            if (abs(lep_pdgID->at(0)) != abs(lep_pdgID->at(1)))
                splitChannel.push_back(0);
            if (abs(lep_pdgID->at(0)) == abs(lep_pdgID->at(1)))
                splitChannel.push_back(1);
            break;
        case 3:
            splitChannel.push_back(channel);
            break;
        default:
            cout<<"Undefined split!"<<endl;
    }
}

//Fill histograms based on options - happens once per event
void FillHistograms() {

    //Reset variables
    OSSFPairs = {};
    leadingPair = make_pair(-1,-1);
    WZWMass = -999;
    WZZMass = -999;
    ZZLeadingZMass = -999;
    ZZSecondZMass = -999;
    ZZMass = -999;
    WPT = -999;
    ZPT = -999;
    ZPT2 = -999;

    //Find all OSSF lepton pairs
    for (int i=0;i<lep_pT->size();i++) {
        for (int j=i+1;j<lep_pT->size();j++) {
            if (lep_pdgID->at(i)==-lep_pdgID->at(j))
                OSSFPairs.push_back(make_pair(i,j));
        }
    }

    defineEvent();
    bool passEvent = (std::find(cuts.begin(), cuts.end(), 0) == cuts.end());

    if (passEvent) {
        fillValue = definePlotValue(plotValueChoice);
        if (plotTypeChoice==2)
            fillSecondValue = definePlotValue(plotSecondValueChoice);
        defineSplitting();
    }
    
    //Stupid shit - don't touch
    trig_mm2 = channel==0 && lep_pT->at(0)>=55 && HLT_mu50; 
}
