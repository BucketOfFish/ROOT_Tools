#include <SimpleNtuplePlotter.h>

// Wishlist
// Fix MC path setting and allow samples to be set in main function
// Fix replacing TH1 memory leak
// Fix MC weighting, used in PRWPlots() - figure out how to extract sumWeightedEvents without looping over events

/*void LostWZPlots() {

    // Options

    MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/SherpaWZ/WithLepMatching/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/LostWZ3/";
    saveImage = true;

    DefineSampleGroups();
    DefineWeightsAndRegions();
    SetTree("outputTree");

    // Create plots
    
    TCut noMatch = "matchedRecoLeptonIndex==-1 && truthLepton_pdgID!=15";
    TCut pTReq = "truthLepton_pT>20";
    TCut etaReq = "(fabs(truthLepton_eta)<2.47 && truthLepton_pdgID==11) || (fabs(truthLepton_eta)<2.4 && truthLepton_pdgID==13)";

    TCut relaxedVRS1 = trigger + mllMin45 + lepReq5025 + jetReq + OSSF + ZWindow + "MET<300 && HTincl>300" + dPhiJetMET;

    AddGroup(SherpaWZ);
    AddPlot("truthLepton_phi", relaxedVRS1+noMatch, "Truth Phi of Lost Lepton in Relaxed VRS1", 20, -5, 5);
    AddPlot("truthLepton_eta", relaxedVRS1+noMatch+"truthLepton_pdgID==11", "Truth Eta of Lost Electrons in Relaxed VRS1", 50, -5, 5);
    AddPlot("truthLepton_eta", relaxedVRS1+noMatch+"truthLepton_pdgID==13", "Truth Eta of Lost Muons in Relaxed VRS1", 50, -5, 5);
    Plot();

    AddGroup(SherpaWZ);
    AddPlot("lep_n", VRS1, "WZ Reco Lepton Number", 5, 0, 5);
    AddPlot("matchedRecoLeptonIndex", VRS1, "WZ Truth Lepton Matching to Reco", 6, -2, 4);
    AddPlot("matchedRecoLeptonIndex!=-1", VRS1, "Truth Lepton Matched to Reco", 2, 0, 2);
    AddPlot("matchedTruthLeptonIndex", VRS1, "WZ Reco Lepton Matching to Truth", 6, -2, 4);
    AddPlot("matchedTruthLeptonIndex!=-1", VRS1, "Reco Lepton Matched to Truth", 2, 0, 2);
    AddPlot("truthLepton_n", VRS1, "WZ Truth Lepton Number", 5, 0, 5);
    AddPlot("truthLepton_pdgID", VRS1+noMatch, "Truth pdgID of Lost Lepton", 20, 0, 20);
    AddPlot("truthLepton_eta", VRS1+noMatch, "Truth Eta of Lost Lepton", 20, -5, 5);
    AddPlot("truthLepton_phi", VRS1+noMatch, "Truth Phi of Lost Lepton", 20, -5, 5);
    AddPlot("truthLepton_pT", VRS1+noMatch, "Truth pT of Lost Lepton", 20, 0, 200);
    AddPlot("truthLepton_pdgID", VRS1+noMatch+pTReq, "Truth pdgID of Lost Lepton with pT Requirement", 20, 0, 20);
    AddPlot("truthLepton_pdgID", VRS1+noMatch+pTReq+etaReq, "Truth pdgID of Lost Lepton with pT and Eta Requirements", 20, 0, 20);
    AddPlot("truthLepton_eta", VRS1+noMatch+pTReq+etaReq, "Truth Eta of Lost Lepton with pT and Eta Requirements", 20, -5, 5);
    AddPlot("truthLepton_phi", VRS1+noMatch+pTReq+etaReq, "Truth Phi of Lost Lepton with pT and Eta Requirements", 20, -5, 5);
    AddPlot("truthLepton_pT", VRS1+noMatch+pTReq+etaReq, "Truth pT of Lost Lepton with pT and Eta Requirements", 20, 0, 200);
    AddPlot("truthLepton_eta", VRS1+noMatch+pTReq+etaReq+"truthLepton_pdgID==11", "Truth Eta of Lost Electrons with pT and Eta Requirements", 20, -5, 5);
    AddPlot("truthLepton_eta", VRS1+noMatch+pTReq+etaReq+"truthLepton_pdgID==13", "Truth Eta of Lost Muons with pT and Eta Requirements", 20, -5, 5);
    AddPlot("truthLepton_eta", noMatch+"truthLepton_pdgID==11", "Truth Eta of Lost Electrons, No Selections", 200, -5, 5);
    AddPlot("truthLepton_eta", noMatch+"truthLepton_pdgID==13", "Truth Eta of Lost Muons, No Selections", 200, -5, 5);
    Plot();

    AddGroup(SherpaWZ);
    AddPlot("lep_n", VRS1+"Wflav==11 && Zflav==11", "(e, ee)", 10, 0, 10);
    AddPlot("lep_n", VRS1+"Wflav==11 && Zflav==13", "(e, mm)", 10, 0, 10);
    AddPlot("lep_n", VRS1+"Wflav==11 && Zflav==15", "(e, tt)", 10, 0, 10);
    AddPlot("lep_n", VRS1+"Wflav==13 && Zflav==11", "(m, ee)", 10, 0, 10);
    AddPlot("lep_n", VRS1+"Wflav==13 && Zflav==13", "(m, mm)", 10, 0, 10);
    AddPlot("lep_n", VRS1+"Wflav==13 && Zflav==15", "(m, tt)", 10, 0, 10);
    AddPlot("lep_n", VRS1+"Wflav==15 && Zflav==11", "(t, ee)", 10, 0, 10);
    AddPlot("lep_n", VRS1+"Wflav==15 && Zflav==13", "(t, mm)", 10, 0, 10);
    AddPlot("lep_n", VRS1+"Wflav==15 && Zflav==15", "(t, tt)", 10, 0, 10);
    StackPlots("WZ Reco Lepton Number in VRS1, Divided by Flavor");

    AddGroup(SherpaWZ);
    AddPlot("truthLepton_n", VRS1+"Wflav==11 && Zflav==11", "(e, ee)", 10, 0, 10);
    AddPlot("truthLepton_n", VRS1+"Wflav==11 && Zflav==13", "(e, mm)", 10, 0, 10);
    AddPlot("truthLepton_n", VRS1+"Wflav==11 && Zflav==15", "(e, tt)", 10, 0, 10);
    AddPlot("truthLepton_n", VRS1+"Wflav==13 && Zflav==11", "(m, ee)", 10, 0, 10);
    AddPlot("truthLepton_n", VRS1+"Wflav==13 && Zflav==13", "(m, mm)", 10, 0, 10);
    AddPlot("truthLepton_n", VRS1+"Wflav==13 && Zflav==15", "(m, tt)", 10, 0, 10);
    AddPlot("truthLepton_n", VRS1+"Wflav==15 && Zflav==11", "(t, ee)", 10, 0, 10);
    AddPlot("truthLepton_n", VRS1+"Wflav==15 && Zflav==13", "(t, mm)", 10, 0, 10);
    AddPlot("truthLepton_n", VRS1+"Wflav==15 && Zflav==15", "(t, tt)", 10, 0, 10);
    StackPlots("WZ Truth Lepton Number in VRS1, Divided by Flavor");

    AddGroup(SherpaWZ);
    AddPlot("lep_n", SRZ1+"Wflav==11 && Zflav==11", "(e, ee)", 10, 0, 10);
    AddPlot("lep_n", SRZ1+"Wflav==11 && Zflav==13", "(e, mm)", 10, 0, 10);
    AddPlot("lep_n", SRZ1+"Wflav==11 && Zflav==15", "(e, tt)", 10, 0, 10);
    AddPlot("lep_n", SRZ1+"Wflav==13 && Zflav==11", "(m, ee)", 10, 0, 10);
    AddPlot("lep_n", SRZ1+"Wflav==13 && Zflav==13", "(m, mm)", 10, 0, 10);
    AddPlot("lep_n", SRZ1+"Wflav==13 && Zflav==15", "(m, tt)", 10, 0, 10);
    AddPlot("lep_n", SRZ1+"Wflav==15 && Zflav==11", "(t, ee)", 10, 0, 10);
    AddPlot("lep_n", SRZ1+"Wflav==15 && Zflav==13", "(t, mm)", 10, 0, 10);
    AddPlot("lep_n", SRZ1+"Wflav==15 && Zflav==15", "(t, tt)", 10, 0, 10);
    StackPlots("WZ Reco Lepton Number in SRZ1, Divided by Flavor");

    AddGroup(SherpaWZ);
    AddPlot("truthLepton_n", SRZ1+"Wflav==11 && Zflav==11", "(e, ee)", 10, 0, 10);
    AddPlot("truthLepton_n", SRZ1+"Wflav==11 && Zflav==13", "(e, mm)", 10, 0, 10);
    AddPlot("truthLepton_n", SRZ1+"Wflav==11 && Zflav==15", "(e, tt)", 10, 0, 10);
    AddPlot("truthLepton_n", SRZ1+"Wflav==13 && Zflav==11", "(m, ee)", 10, 0, 10);
    AddPlot("truthLepton_n", SRZ1+"Wflav==13 && Zflav==13", "(m, mm)", 10, 0, 10);
    AddPlot("truthLepton_n", SRZ1+"Wflav==13 && Zflav==15", "(m, tt)", 10, 0, 10);
    AddPlot("truthLepton_n", SRZ1+"Wflav==15 && Zflav==11", "(t, ee)", 10, 0, 10);
    AddPlot("truthLepton_n", SRZ1+"Wflav==15 && Zflav==13", "(t, mm)", 10, 0, 10);
    AddPlot("truthLepton_n", SRZ1+"Wflav==15 && Zflav==15", "(t, tt)", 10, 0, 10);
    StackPlots("WZ Truth Lepton Number in SRZ, Divided by Flavor");
}*/

void MT2Plots() {

    // Options

    MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/MT2/";
    dataPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/MT2/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/MT2Final/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    Group g_372462 ("(1200, 500)");
    Group g_372466 ("(1400, 100)");
    Group g_372498 ("(1000, 800)");
    Group g_410000_407012 ("410000_407012");
    g_372462.AddSample("372462");
    g_372466.AddSample("372466");
    g_372498.AddSample("372498");
    g_410000_407012.AddSample("410000_407012");

    AddGroup(g_410000_407012);
    AddPlot("MT2Top", TCut("MT2Top>0") * MCWeight, "MT2Top Distribution for Extended ttbar", 50, 0, 1000);
    Plot(false);

    AddGroup(g_410000_407012);
    AddPlot("MT2Top", TCut("MET>250 && MT2Top>0") * MCWeight, "MT2Top Distribution when MET>250 for Extended ttbar", 50, 0, 1000);
    Plot(false);

    AddGroup(g_410000_407012);
    AddPlot("MT2Top", (EdgeSRMed + "mll<100 && MT2Top>0") * MCWeight, "MT2Top Distribution in SR-Medium with mll<100 for Extended ttbar", 50, 0, 1000);
    Plot(false);

    //AddGroup(ttbar);
    //AddGroup(g_372498);
    //AddGroup(g_372462);
    //AddGroup(g_372466);
    //AddData();
    //AddPlot("MT2W", (EdgeSRMed + "mll<100 && MT2W>0") * MCWeight, "MT2W Distribution in SR-Medium with mll<100", 20, 0, 300);
    //SetDataWeight(EdgeSRMed + "mll<100 && MT2W>0");
    //Plot(false);

    //AddGroup(ttbar);
    //AddGroup(g_372498);
    //AddData();
    //AddPlot("MT2W", (EdgeSRMed + "mll<100 && MT2W>0") * MCWeight, "MT2W Distribution in SR-Medium with mll<100 (Stacked)", 20, 0, 300);
    //SetDataWeight(EdgeSRMed + "mll<100 && MT2W>0");
    //Plot(true);

    //AddGroup(ttbar);
    //AddGroup(g_372498);
    //AddGroup(g_372462);
    //AddGroup(g_372466);
    //AddPlot("MT2Top", (EdgeSRMed + "mll<100 && MT2Top>0") * MCWeight, "MT2Top Distribution in SR-Medium with mll<100", 20, 0, 1000);
    //Plot(false);

    //AddGroup(ttbar);
    //AddGroup(g_372498);
    //AddData();
    //AddPlot("MT2Top", (EdgeSRMed + "mll<100 && MT2Top>0") * MCWeight, "MT2Top Distribution in SR-Medium with mll<100 (Stacked)", 20, 0, 1000);
    //SetDataWeight(EdgeSRMed + "mll<100 && MT2Top>0");
    //Plot(true);
}

void MC15abPlots() {

    // Options

    MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/MC15ab/";
    dataPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/MC15ab/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/MC15Compare/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    Group g_361063_a ("361063_MC15a");
    Group g_361063_b ("361063_MC15b");
    g_361063_a.AddSample("361063_a");
    g_361063_b.AddSample("361063_b");

    AddGroup(g_361063_a);
    AddGroup(g_361063_b);
    AddPlot("nVtx", "", "nVtx", 50, 0, 50);
    Plot(false);

    AddGroup(g_361063_a);
    AddGroup(g_361063_b);
    AddPlot("HT", "", "HT", 20, 0, 100);
    Plot(false);

    AddGroup(g_361063_a);
    AddGroup(g_361063_b);
    AddPlot("MET", "", "MET", 20, 0, 100);
    Plot(false);

    AddGroup(g_361063_a);
    AddGroup(g_361063_b);
    AddPlot("jet_n", "", "jet_n", 5, 0, 5);
    Plot(false);
}

void DibosonSystematicsPlots() {

    // Options

    //MCPath = "~/eos/atlas/user/l/longjon/Ntuples/v00-21_Sys/MC/";
    MCPath = "/afs/cern.ch/work/m/mazhang/Data/v21_Sys/";
    dataPath = "";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/DibosonSystematics/";
    saveImage = false;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
	//vector<TCut> regionCut = {EdgeSRLow, EdgeSRMed, EdgeSRHigh};
	//vector<TCut> DFRegionCut = {EdgeCRTLow, EdgeCRTMed, EdgeCRTHigh};
	//vector<TString> regionName = {"EdgeSRLow", "EdgeSRMed", "EdgeSRHigh"};
	//vector<TCut> regionCut = {EdgeVRLow, EdgeVRMed, EdgeVRHigh};
	//vector<TCut> DFRegionCut = {EdgeVRTLow, EdgeVRTMed, EdgeVRTHigh};
	//vector<TString> regionName = {"EdgeVRLow", "EdgeVRMed", "EdgeVRHigh"};
	vector<TCut> regionCut = {VR3L};
	vector<TCut> DFRegionCut = {VR3LDF};
	vector<TString> regionName = {"VR 3L"};
    TCut newWeight = "3.2*weight1fb";

	for (int cutn=0; cutn<regionCut.size(); cutn++) {
    //for (int cutn=8; cutn<12; cutn++) {

        //Checkpoint
        cout<<"New Region: "<<regionName[cutn]<<endl;

        TCut thisRegion = regionCut[cutn];
        TCut thisDFRegion = DFRegionCut[cutn];

        Group SherpaVVSF = SherpaVV;
        SherpaVVSF.SetName("Sherpa VV SF");
        Group SherpaVVDF = SherpaVV;
        SherpaVVDF.SetCustomWeight(thisDFRegion * newWeight);
        SherpaVVDF.SetName("Sherpa VV DF");

        AddGroup(SherpaVVSF);
        AddGroup(SherpaVVDF);
        AddGroup(SherpaWZ);
        AddGroup(SherpaZZ);
        AddGroup(rareTop);
        SetTree("outputTree");
        //Checkpoint
        cout<<treeName;
        AddPlot("mll", thisRegion * newWeight, treeName, 50, 0, 1000);
        Plot(true);

        vector<TString> trees = {"EG_RESOLUTION_ALL", "EL_EFF_ID_TotalCorrUncertainty", "EL_EFF_Iso_TotalCorrUncertainty", "EL_EFF_Reco_TotalCorrUncertainty", "EL_EFF_Trigger_TotalCorrUncertainty", "JET_GroupedNP_1", "JET_GroupedNP_2", "JET_GroupedNP_3", "JET_JER_SINGLE_NP", "MUONS_ID", "MUONS_MS", "MUONS_SCALE", "MUON_EFF_STAT", "MUON_EFF_STAT_LOWPT", "MUON_EFF_SYS", "MUON_EFF_SYS_LOWPT", "MUON_EFF_TrigStatUncertainty", "MUON_EFF_TrigSystUncertainty", "MUON_ISO_STAT", "MUON_ISO_SYS"};

        for (int i=0; i<trees.size(); i++) {

            TString treeName = "outputTree_" + trees[i] + "__1up";
            //Checkpoint
            cout<<treeName;
            AddGroup(SherpaVVSF);
            AddGroup(SherpaVVDF);
            AddGroup(SherpaWZ);
            AddGroup(SherpaZZ);
            AddGroup(rareTop);
            SetTree(treeName);
            AddPlot("mll", thisRegion * "3.2*weight1fb", treeName, 50, 0, 1000);
            Plot(true);


            treeName = "outputTree_" + trees[i] + "__1down";
            //Checkpoint
            cout<<treeName;
            AddGroup(SherpaVVSF);
            AddGroup(SherpaVVDF);
            AddGroup(SherpaWZ);
            AddGroup(SherpaZZ);
            AddGroup(rareTop);
            SetTree(treeName);
            AddPlot("mll", thisRegion * "3.2*weight1fb", treeName, 50, 0, 1000);
            Plot(true);

        }

        AddGroup(SherpaVVSF);
        AddGroup(SherpaVVDF);
        AddGroup(SherpaWZ);
        AddGroup(SherpaZZ);
        AddGroup(rareTop);
        SetTree("outputTree_MET_SoftTrk_ResoPara");
        //Checkpoint
        cout<<treeName;
        AddPlot("mll", thisRegion * "3.2*weight1fb", treeName, 50, 0, 1000);
        Plot(true);

        AddGroup(SherpaVVSF);
        AddGroup(SherpaVVDF);
        AddGroup(SherpaWZ);
        AddGroup(SherpaZZ);
        AddGroup(rareTop);
        SetTree("outputTree_MET_SoftTrk_ResoPerp");
        //Checkpoint
        cout<<treeName;
        AddPlot("mll", thisRegion * "3.2*weight1fb", treeName, 50, 0, 1000);
        Plot(true);

        AddGroup(SherpaVVSF);
        AddGroup(SherpaVVDF);
        AddGroup(SherpaWZ);
        AddGroup(SherpaZZ);
        AddGroup(rareTop);
        SetTree("outputTree_MET_SoftTrk_ScaleDown");
        //Checkpoint
        cout<<treeName;
        AddPlot("mll", thisRegion * "3.2*weight1fb", treeName, 50, 0, 1000);
        Plot(true);

        AddGroup(SherpaVVSF);
        AddGroup(SherpaVVDF);
        AddGroup(SherpaWZ);
        AddGroup(SherpaZZ);
        AddGroup(rareTop);
        SetTree("outputTree_MET_SoftTrk_ScaleUp");
        //Checkpoint
        cout<<treeName;
        AddPlot("mll", thisRegion * "3.2*weight1fb", treeName, 50, 0, 1000);
        Plot(true);
    }
}

void DibosonSystematicsRatioPrePlots() {

    // Options

    MCPath = "/afs/cern.ch/work/m/mazhang/Data/WeightedSyst_v00-17/MC15b/";
    dataPath = "";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/DibosonSystematicsRatiosB/";
    saveImage = true;
    saveExtension = "root";
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    vector<TCut> regionCut = {EdgeSRLow, EdgeSRMed, EdgeSRHigh};
    TCut newWeight = "3.2*weight1fb*trigweight_noemusf_fix";

    for (int cutn=0; cutn<3; cutn++) {

        //Checkpoint
        cout<<"New Region"<<endl;

        TCut thisRegion = regionCut[cutn];

        //Group SherpaVVSF = SherpaVV;
        //SherpaVVSF.SetCustomWeight((thisRegion + "(channel==0 || channel==1)") * newWeight);
        //SherpaVVSF.SetName("Sherpa VV SF");
        //Group SherpaVVDF = SherpaVV;
        //SherpaVVDF.SetCustomWeight((thisRegion + "(channel==2 || channel==3)") * newWeight);
        //SherpaVVDF.SetName("Sherpa VV DF");

        SetTree("outputTree");
        //Checkpoint
        cout<<treeName;
        AddGroup(SherpaVV);
        AddPlot("mll", thisRegion * newWeight, treeName+"_VV", 50, 0, 1000);
        Plot(true);
        AddGroup(SherpaWZ);
        AddPlot("mll", thisRegion * newWeight, treeName+"_WZ", 50, 0, 1000);
        Plot(true);
        AddGroup(rareTop);
        AddPlot("mll", thisRegion * newWeight, treeName+"_RT", 50, 0, 1000);
        Plot(true);

        vector<TString> trees = {"EG_RESOLUTION_ALL", "EL_EFF_ID_TotalCorrUncertainty", "EL_EFF_Iso_TotalCorrUncertainty", "EL_EFF_Reco_TotalCorrUncertainty", "EL_EFF_Trigger_TotalCorrUncertainty", "JET_GroupedNP_1", "JET_GroupedNP_2", "JET_GroupedNP_3", "MUONS_ID", "MUONS_MS", "MUONS_SCALE", "MUON_EFF_STAT", "MUON_EFF_STAT_LOWPT", "MUON_EFF_SYS", "MUON_EFF_SYS_LOWPT", "MUON_EFF_TrigStatUncertainty", "MUON_EFF_TrigSystUncertainty", "MUON_ISO_STAT", "MUON_ISO_SYS"};

        for (int i=0; i<trees.size(); i++) {

            TString treeName = "outputTree_" + trees[i] + "__1up";
            //Checkpoint
            cout<<treeName;
            SetTree(treeName);
            AddGroup(SherpaVV);
            AddPlot("mll", thisRegion * newWeight, treeName+"_VV", 50, 0, 1000);
            Plot(true);
            AddGroup(SherpaWZ);
            AddPlot("mll", thisRegion * newWeight, treeName+"_WZ", 50, 0, 1000);
            Plot(true);
            AddGroup(rareTop);
            AddPlot("mll", thisRegion * newWeight, treeName+"_RT", 50, 0, 1000);
            Plot(true);

            treeName = "outputTree_" + trees[i] + "__1down";
            //Checkpoint
            cout<<treeName;
            SetTree(treeName);
            AddGroup(SherpaVV);
            AddPlot("mll", thisRegion * newWeight, treeName+"_VV", 50, 0, 1000);
            Plot(true);
            AddGroup(SherpaWZ);
            AddPlot("mll", thisRegion * newWeight, treeName+"_WZ", 50, 0, 1000);
            Plot(true);
            AddGroup(rareTop);
            AddPlot("mll", thisRegion * newWeight, treeName+"_RT", 50, 0, 1000);
            Plot(true);
        }

        SetTree("outputTree_JET_JER_SINGLE_NP__1up");
        //Checkpoint
        cout<<treeName;
        AddGroup(SherpaVV);
        AddPlot("mll", thisRegion * newWeight, treeName+"_VV", 50, 0, 1000);
        Plot(true);
        AddGroup(SherpaWZ);
        AddPlot("mll", thisRegion * newWeight, treeName+"_WZ", 50, 0, 1000);
        Plot(true);
        AddGroup(rareTop);
        AddPlot("mll", thisRegion * newWeight, treeName+"_RT", 50, 0, 1000);
        Plot(true);

        SetTree("outputTree_MET_SoftTrk_ResoPara");
        //Checkpoint
        cout<<treeName;
        AddGroup(SherpaVV);
        AddPlot("mll", thisRegion * newWeight, treeName+"_VV", 50, 0, 1000);
        Plot(true);
        AddGroup(SherpaWZ);
        AddPlot("mll", thisRegion * newWeight, treeName+"_WZ", 50, 0, 1000);
        Plot(true);
        AddGroup(rareTop);
        AddPlot("mll", thisRegion * newWeight, treeName+"_RT", 50, 0, 1000);
        Plot(true);

        SetTree("outputTree_MET_SoftTrk_ResoPerp");
        //Checkpoint
        cout<<treeName;
        AddGroup(SherpaVV);
        AddPlot("mll", thisRegion * newWeight, treeName+"_VV", 50, 0, 1000);
        Plot(true);
        AddGroup(SherpaWZ);
        AddPlot("mll", thisRegion * newWeight, treeName+"_WZ", 50, 0, 1000);
        Plot(true);
        AddGroup(rareTop);
        AddPlot("mll", thisRegion * newWeight, treeName+"_RT", 50, 0, 1000);
        Plot(true);

        SetTree("outputTree_MET_SoftTrk_ScaleDown");
        //Checkpoint
        cout<<treeName;
        AddGroup(SherpaVV);
        AddPlot("mll", thisRegion * newWeight, treeName+"_VV", 50, 0, 1000);
        Plot(true);
        AddGroup(SherpaWZ);
        AddPlot("mll", thisRegion * newWeight, treeName+"_WZ", 50, 0, 1000);
        Plot(true);
        AddGroup(rareTop);
        AddPlot("mll", thisRegion * newWeight, treeName+"_RT", 50, 0, 1000);
        Plot(true);

        SetTree("outputTree_MET_SoftTrk_ScaleUp");
        //Checkpoint
        cout<<treeName;
        AddGroup(SherpaVV);
        AddPlot("mll", thisRegion * newWeight, treeName+"_VV", 50, 0, 1000);
        Plot(true);
        AddGroup(SherpaWZ);
        AddPlot("mll", thisRegion * newWeight, treeName+"_WZ", 50, 0, 1000);
        Plot(true);
        AddGroup(rareTop);
        AddPlot("mll", thisRegion * newWeight, treeName+"_RT", 50, 0, 1000);
        Plot(true);
    }
}

void DibosonSystematicsRatioPlots() {

    // Options

    MCPath = "/afs/cern.ch/user/m/mazhang/Plots/DibosonSystematicsRatiosB/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/DibosonSystematicsRatiosCompleteB/";
    blinded = false;

    // Create plots

    vector<string> files = {"outputTree_EG_RESOLUTION_ALL__1down_RT.root"
        ,"outputTree_EG_RESOLUTION_ALL__1down_VV.root"
        ,"outputTree_EG_RESOLUTION_ALL__1down_WZ.root"
        ,"outputTree_EG_RESOLUTION_ALL__1up_RT.root"
        ,"outputTree_EG_RESOLUTION_ALL__1up_VV.root"
        ,"outputTree_EG_RESOLUTION_ALL__1up_WZ.root"
        ,"outputTree_EL_EFF_ID_TotalCorrUncertainty__1down_RT.root"
        ,"outputTree_EL_EFF_ID_TotalCorrUncertainty__1down_VV.root"
        ,"outputTree_EL_EFF_ID_TotalCorrUncertainty__1down_WZ.root"
        ,"outputTree_EL_EFF_ID_TotalCorrUncertainty__1up_RT.root"
        ,"outputTree_EL_EFF_ID_TotalCorrUncertainty__1up_VV.root"
        ,"outputTree_EL_EFF_ID_TotalCorrUncertainty__1up_WZ.root"
        ,"outputTree_EL_EFF_Iso_TotalCorrUncertainty__1down_RT.root"
        ,"outputTree_EL_EFF_Iso_TotalCorrUncertainty__1down_VV.root"
        ,"outputTree_EL_EFF_Iso_TotalCorrUncertainty__1down_WZ.root"
        ,"outputTree_EL_EFF_Iso_TotalCorrUncertainty__1up_RT.root"
        ,"outputTree_EL_EFF_Iso_TotalCorrUncertainty__1up_VV.root"
        ,"outputTree_EL_EFF_Iso_TotalCorrUncertainty__1up_WZ.root"
        ,"outputTree_EL_EFF_Reco_TotalCorrUncertainty__1down_RT.root"
        ,"outputTree_EL_EFF_Reco_TotalCorrUncertainty__1down_VV.root"
        ,"outputTree_EL_EFF_Reco_TotalCorrUncertainty__1down_WZ.root"
        ,"outputTree_EL_EFF_Reco_TotalCorrUncertainty__1up_RT.root"
        ,"outputTree_EL_EFF_Reco_TotalCorrUncertainty__1up_VV.root"
        ,"outputTree_EL_EFF_Reco_TotalCorrUncertainty__1up_WZ.root"
        ,"outputTree_EL_EFF_Trigger_TotalCorrUncertainty__1down_RT.root"
        ,"outputTree_EL_EFF_Trigger_TotalCorrUncertainty__1down_VV.root"
        ,"outputTree_EL_EFF_Trigger_TotalCorrUncertainty__1down_WZ.root"
        ,"outputTree_EL_EFF_Trigger_TotalCorrUncertainty__1up_RT.root"
        ,"outputTree_EL_EFF_Trigger_TotalCorrUncertainty__1up_VV.root"
        ,"outputTree_EL_EFF_Trigger_TotalCorrUncertainty__1up_WZ.root"
        ,"outputTree_JET_GroupedNP_1__1down_RT.root"
        ,"outputTree_JET_GroupedNP_1__1down_VV.root"
        ,"outputTree_JET_GroupedNP_1__1down_WZ.root"
        ,"outputTree_JET_GroupedNP_1__1up_RT.root"
        ,"outputTree_JET_GroupedNP_1__1up_VV.root"
        ,"outputTree_JET_GroupedNP_1__1up_WZ.root"
        ,"outputTree_JET_GroupedNP_2__1down_RT.root"
        ,"outputTree_JET_GroupedNP_2__1down_VV.root"
        ,"outputTree_JET_GroupedNP_2__1down_WZ.root"
        ,"outputTree_JET_GroupedNP_2__1up_RT.root"
        ,"outputTree_JET_GroupedNP_2__1up_VV.root"
        ,"outputTree_JET_GroupedNP_2__1up_WZ.root"
        ,"outputTree_JET_GroupedNP_3__1down_RT.root"
        ,"outputTree_JET_GroupedNP_3__1down_VV.root"
        ,"outputTree_JET_GroupedNP_3__1down_WZ.root"
        ,"outputTree_JET_GroupedNP_3__1up_RT.root"
        ,"outputTree_JET_GroupedNP_3__1up_VV.root"
        ,"outputTree_JET_GroupedNP_3__1up_WZ.root"
        ,"outputTree_JET_JER_SINGLE_NP__1up_RT.root"
        ,"outputTree_JET_JER_SINGLE_NP__1up_VV.root"
        ,"outputTree_JET_JER_SINGLE_NP__1up_WZ.root"
        ,"outputTree_MET_SoftTrk_ResoPara_RT.root"
        ,"outputTree_MET_SoftTrk_ResoPara_VV.root"
        ,"outputTree_MET_SoftTrk_ResoPara_WZ.root"
        ,"outputTree_MET_SoftTrk_ResoPerp_RT.root"
        ,"outputTree_MET_SoftTrk_ResoPerp_VV.root"
        ,"outputTree_MET_SoftTrk_ResoPerp_WZ.root"
        ,"outputTree_MET_SoftTrk_ScaleDown_RT.root"
        ,"outputTree_MET_SoftTrk_ScaleDown_VV.root"
        ,"outputTree_MET_SoftTrk_ScaleDown_WZ.root"
        ,"outputTree_MET_SoftTrk_ScaleUp_RT.root"
        ,"outputTree_MET_SoftTrk_ScaleUp_VV.root"
        ,"outputTree_MET_SoftTrk_ScaleUp_WZ.root"
        ,"outputTree_MUON_EFF_STAT__1down_RT.root"
        ,"outputTree_MUON_EFF_STAT__1down_VV.root"
        ,"outputTree_MUON_EFF_STAT__1down_WZ.root"
        ,"outputTree_MUON_EFF_STAT__1up_RT.root"
        ,"outputTree_MUON_EFF_STAT__1up_VV.root"
        ,"outputTree_MUON_EFF_STAT__1up_WZ.root"
        ,"outputTree_MUON_EFF_STAT_LOWPT__1down_RT.root"
        ,"outputTree_MUON_EFF_STAT_LOWPT__1down_VV.root"
        ,"outputTree_MUON_EFF_STAT_LOWPT__1down_WZ.root"
        ,"outputTree_MUON_EFF_STAT_LOWPT__1up_RT.root"
        ,"outputTree_MUON_EFF_STAT_LOWPT__1up_VV.root"
        ,"outputTree_MUON_EFF_STAT_LOWPT__1up_WZ.root"
        ,"outputTree_MUON_EFF_SYS__1down_RT.root"
        ,"outputTree_MUON_EFF_SYS__1down_VV.root"
        ,"outputTree_MUON_EFF_SYS__1down_WZ.root"
        ,"outputTree_MUON_EFF_SYS__1up_RT.root"
        ,"outputTree_MUON_EFF_SYS__1up_VV.root"
        ,"outputTree_MUON_EFF_SYS__1up_WZ.root"
        ,"outputTree_MUON_EFF_SYS_LOWPT__1down_RT.root"
        ,"outputTree_MUON_EFF_SYS_LOWPT__1down_VV.root"
        ,"outputTree_MUON_EFF_SYS_LOWPT__1down_WZ.root"
        ,"outputTree_MUON_EFF_SYS_LOWPT__1up_RT.root"
        ,"outputTree_MUON_EFF_SYS_LOWPT__1up_VV.root"
        ,"outputTree_MUON_EFF_SYS_LOWPT__1up_WZ.root"
        ,"outputTree_MUON_EFF_TrigStatUncertainty__1down_RT.root"
        ,"outputTree_MUON_EFF_TrigStatUncertainty__1down_VV.root"
        ,"outputTree_MUON_EFF_TrigStatUncertainty__1down_WZ.root"
        ,"outputTree_MUON_EFF_TrigStatUncertainty__1up_RT.root"
        ,"outputTree_MUON_EFF_TrigStatUncertainty__1up_VV.root"
        ,"outputTree_MUON_EFF_TrigStatUncertainty__1up_WZ.root"
        ,"outputTree_MUON_EFF_TrigSystUncertainty__1down_RT.root"
        ,"outputTree_MUON_EFF_TrigSystUncertainty__1down_VV.root"
        ,"outputTree_MUON_EFF_TrigSystUncertainty__1down_WZ.root"
        ,"outputTree_MUON_EFF_TrigSystUncertainty__1up_RT.root"
        ,"outputTree_MUON_EFF_TrigSystUncertainty__1up_VV.root"
        ,"outputTree_MUON_EFF_TrigSystUncertainty__1up_WZ.root"
        ,"outputTree_MUON_ISO_STAT__1down_RT.root"
        ,"outputTree_MUON_ISO_STAT__1down_VV.root"
        ,"outputTree_MUON_ISO_STAT__1down_WZ.root"
        ,"outputTree_MUON_ISO_STAT__1up_RT.root"
        ,"outputTree_MUON_ISO_STAT__1up_VV.root"
        ,"outputTree_MUON_ISO_STAT__1up_WZ.root"
        ,"outputTree_MUON_ISO_SYS__1down_RT.root"
        ,"outputTree_MUON_ISO_SYS__1down_VV.root"
        ,"outputTree_MUON_ISO_SYS__1down_WZ.root"
        ,"outputTree_MUON_ISO_SYS__1up_RT.root"
        ,"outputTree_MUON_ISO_SYS__1up_VV.root"
        ,"outputTree_MUON_ISO_SYS__1up_WZ.root"
        ,"outputTree_MUONS_ID__1down_RT.root"
        ,"outputTree_MUONS_ID__1down_VV.root"
        ,"outputTree_MUONS_ID__1down_WZ.root"
        ,"outputTree_MUONS_ID__1up_RT.root"
        ,"outputTree_MUONS_ID__1up_VV.root"
        ,"outputTree_MUONS_ID__1up_WZ.root"
        ,"outputTree_MUONS_MS__1down_RT.root"
        ,"outputTree_MUONS_MS__1down_VV.root"
        ,"outputTree_MUONS_MS__1down_WZ.root"
        ,"outputTree_MUONS_MS__1up_RT.root"
        ,"outputTree_MUONS_MS__1up_VV.root"
        ,"outputTree_MUONS_MS__1up_WZ.root"
        ,"outputTree_MUONS_SCALE__1down_RT.root"
        ,"outputTree_MUONS_SCALE__1down_VV.root"
        ,"outputTree_MUONS_SCALE__1down_WZ.root"
        ,"outputTree_MUONS_SCALE__1up_RT.root"
        ,"outputTree_MUONS_SCALE__1up_VV.root"
        ,"outputTree_MUONS_SCALE__1up_WZ.root"
    };

    for (auto fileName:files) {
        TFile *compareFile;
        if (fileName.find("_RT")!=std::string::npos)
            compareFile = new TFile(MCPath+"outputTree_RT.root");
        else if (fileName.find("_VV")!=std::string::npos)
            compareFile = new TFile(MCPath+"outputTree_VV.root");
        else if (fileName.find("_WZ")!=std::string::npos)
            compareFile = new TFile(MCPath+"outputTree_WZ.root");
        TFile *file = new TFile(MCPath+TString(fileName));

        TH1F *numHist = (TH1F*)file->Get("hist");
        TH1F *denomHist = (TH1F*)compareFile->Get("hist");
        numHist->Divide(denomHist);
        for (int i=1; i<=numHist->GetNbinsX(); i++)
            numHist->SetBinError(i,0.01);
        numHist->SetMinimum(0.5);
        numHist->SetMaximum(1.5);

        Mkdir(saveDirectory);
        TFile *newFile = new TFile(saveDirectory+TString(fileName), "recreate");
        numHist->SetDirectory(newFile);
        numHist->Write("hist");
        //TCanvas *canvas = new TCanvas("canvas","",696,472);
        //canvas->Print(saveDirectory+imageName);
    }
}

void VVSystematicPlots() {

    // Options

	MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/v1_01/METMod/MC/";
	dataPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/v1_01/METMod/Data/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/VVSystematic/";
    saveImage = false;
    blinded = false;

    SetTree("outputTree");
    SetSaveExtension("pdf");
    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots

    TCut ZWindow = "mll>61 && mll<121";
    TCut offZWindow = "mll<61 || mll>121";
    TCut newWeight = "3.2*weight1fb";

    AddGroup(SherpaVV);
    AddPlot("mll", (EdgeSRLow + ZWindow) * newWeight, "mll of SF Z-Window VV in EDGE SR Low", 50, 0, 400);
    AddPlot("mll", (EdgeCRTLow + ZWindow) * newWeight, "mll of DF Z-Window VV in EDGE SR Low", 50, 0, 400);
    AddPlot("mll", (EdgeSRLow + offZWindow) * newWeight, "mll of SF Off-Z VV in EDGE SR Low", 50, 0, 400);
    AddPlot("mll", (EdgeCRTLow + offZWindow) * newWeight, "mll of DF Off-Z VV in EDGE SR Low", 50, 0, 400);
    AddPlot("mll", (EdgeSRMed + ZWindow) * newWeight, "mll of SF Z-Window VV in EDGE SR Med", 50, 0, 400);
    AddPlot("mll", (EdgeCRTMed + ZWindow) * newWeight, "mll of DF Z-Window VV in EDGE SR Med", 50, 0, 400);
    AddPlot("mll", (EdgeSRMed + offZWindow) * newWeight, "mll of SF Off-Z VV in EDGE SR Med", 50, 0, 400);
    AddPlot("mll", (EdgeCRTMed + offZWindow) * newWeight, "mll of DF Off-Z VV in EDGE SR Med", 50, 0, 400);
    AddPlot("mll", (EdgeSRHigh + ZWindow) * newWeight, "mll of SF Z-Window VV in EDGE SR High", 50, 0, 400);
    AddPlot("mll", (EdgeCRTHigh + ZWindow) * newWeight, "mll of DF Z-Window VV in EDGE SR High", 50, 0, 400);
    AddPlot("mll", (EdgeSRHigh + offZWindow) * newWeight, "mll of SF Off-Z VV in EDGE SR High", 50, 0, 400);
    AddPlot("mll", (EdgeCRTHigh + offZWindow) * newWeight, "mll of DF Off-Z VV in EDGE SR High", 50, 0, 400);
    AddPlot("mll", (EdgeVRLow + ZWindow) * newWeight, "mll of SF Z-Window VV in EDGE VR Low", 50, 0, 400);
    AddPlot("mll", (EdgeVRTLow + ZWindow) * newWeight, "mll of DF Z-Window VV in EDGE VR Low", 50, 0, 400);
    AddPlot("mll", (EdgeVRLow + offZWindow) * newWeight, "mll of SF Off-Z VV in EDGE VR Low", 50, 0, 400);
    AddPlot("mll", (EdgeVRTLow + offZWindow) * newWeight, "mll of DF Off-Z VV in EDGE VR Low", 50, 0, 400);
    AddPlot("mll", (EdgeVRMed + ZWindow) * newWeight, "mll of SF Z-Window VV in EDGE VR Med", 50, 0, 400);
    AddPlot("mll", (EdgeVRTMed + ZWindow) * newWeight, "mll of DF Z-Window VV in EDGE VR Med", 50, 0, 400);
    AddPlot("mll", (EdgeVRMed + offZWindow) * newWeight, "mll of SF Off-Z VV in EDGE VR Med", 50, 0, 400);
    AddPlot("mll", (EdgeVRTMed + offZWindow) * newWeight, "mll of DF Off-Z VV in EDGE VR Med", 50, 0, 400);
    AddPlot("mll", (EdgeVRHigh + ZWindow) * newWeight, "mll of SF Z-Window VV in EDGE VR High", 50, 0, 400);
    AddPlot("mll", (EdgeVRTHigh + ZWindow) * newWeight, "mll of DF Z-Window VV in EDGE VR High", 50, 0, 400);
    AddPlot("mll", (EdgeVRHigh + offZWindow) * newWeight, "mll of SF Off-Z VV in EDGE VR High", 50, 0, 400);
    AddPlot("mll", (EdgeVRTHigh + offZWindow) * newWeight, "mll of DF Off-Z VV in EDGE VR High", 50, 0, 400);
    Plot();
}

void SignalContaminationPlots(int luminosity) {

    // Options

    MCPath = "/afs/cern.ch/work/m/mazhang/Data/v21/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/SignalContamination/";
    saveImage = true;
    blinded = false;

    SetTree("outputTree");
    SetSaveExtension("eps");
    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots

    //TCut newWeight = "3.2*weight1fb*trigweight_noemusf_fix";
    TCut newWeight = TCut(TString(to_string(luminosity/1000.)+"*weight1fb*trigweight"));

    Group FSBackground = ttbar;
    FSBackground.SetName("Background");
    FSBackground.AddSample("410015"); //Wt
    FSBackground.AddSample("410016"); //Wt
    FSBackground.AddSample("410064"); //Wt
    FSBackground.AddSample("410065"); //Wt
    for (int i=361420; i<=361443; i++)
        FSBackground.AddSample(to_string(i)); //Ztt
    for (int i=361484; i<=361491; i++)
        FSBackground.AddSample(to_string(i)); //Ztt low mass
    FSBackground.AddSample("361077"); //WW

    //for (int signal=370000; signal<=372599; signal++) { // Contains on-Z samples
        //if (signal==370046) signal=372446;
        
    //for (int signal=372446; signal<=372599; signal++) { // EDGE only
        //if (signal==372587) continue;

    // 372512-SLN_400_300, 372513-SLN_400_320, 372514-SLN_400_340, 372588-Z_400_320
	
    //vector<int> signals = {372512, 372513, 372514, 372588};
	//vector<string> sampleNames = {"SLN_400_300", "SLN_400_320", "SLN_400_340", "Z_400_320"};
    vector<int> signals = {372502, 372462, 372466};
	vector<string> sampleNames = {"SLN_1000_840", "SLN_1200_500", "SLN_1400_100"};
    for (int i=0; i<signals.size(); i++) {
        int signal = signals[i];
        string sampleName = sampleNames[i];
        Group g_signal (to_string(signal));
        //g_signal.AddSample(to_string(signal));
        
        g_signal.AddSample(signal);
        g_signal.SetName(sampleName);

        AddGroup(FSBackground);
        AddGroup(g_signal);

        AddPlot("mll", EdgeCRTLow * newWeight, "mll of signal (" + sampleName + ") and background in EDGE CRT Low", 50, 0, 1000);
        AddPlot("mll", EdgeCRTMed * newWeight, "mll of signal (" + sampleName + ") and background in EDGE CRT Med", 50, 0, 1000);
        AddPlot("mll", EdgeCRTHigh * newWeight, "mll of signal (" + sampleName + ") and background in EDGE CRT High", 50, 0, 1000);
        AddPlot("mll", EdgeVRTLow * newWeight, "mll of signal (" + sampleName + ") and background in EDGE VRT Low", 50, 0, 1000);
        AddPlot("mll", EdgeVRTMed * newWeight, "mll of signal (" + sampleName + ") and background in EDGE VRT Med", 50, 0, 1000);
        AddPlot("mll", EdgeVRTHigh * newWeight, "mll of signal (" + sampleName + ") and background in EDGE VRT High", 50, 0, 1000);
        Plot();
    }
}

void SherpaPowhegSystematic() {

    // Options

    MCPath = "/afs/cern.ch/work/m/mazhang/Data/v21_Sys/";
    dataPath = "";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/DibosonSystematics/";
    saveImage = false;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    //vector<TCut> regionCut = {EdgeSRLow, EdgeSRMed, EdgeSRHigh, EdgeVRLow, EdgeVRMed, EdgeVRHigh};
    vector<TCut> regionCut = {VR3L};
    TCut newWeight = "3.2*weight1fb";

    for (int i=0; i<regionCut.size(); i++) {
        AddGroup(PowhegZZ_2l2v);
        AddGroup(PowhegWZ);
        SetTree("outputTree");
        AddPlot("mll", regionCut[i] * newWeight, treeName, 50, 0, 1000);
        Plot(true);
    }
}

void CMSRegionNormalizationCheck() { //This prints out the Z yield in both VRLow and the CMS region. The ratio between these two numbers allows me to change the normalization in Jon's plotting framework.

    // Options

    //MCPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-20-NoSys/MC/";
    MCPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-20-NoSys/MC/";
    dataPath = "";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/NormCheck/";
    saveImage = false;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    TCut newWeight = "3.2*weight1fb";
    TCut CMSRegion = "(channel==0 || channel==1) && ((jet_n>=2 && MET>150) || (jet_n>=3 && MET>100))";

    AddGroup(Zee);
    SetTree("outputTree");
    AddPlot("mll", CMSRegion * newWeight, treeName, 50, 0, 1000);
    AddPlot("mll", EdgeVRLow * newWeight, treeName, 50, 0, 1000);
    Plot(true);
}

void TrueMETPlots() {

    // Options

    //MCPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-20-NoSys/MC/";
    MCPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-20-NoSys/MC/";
    dataPath = "";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/TrueMET/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    TCut newWeight = "3.2*weight1fb*trigweight";

    vector<TCut> regionCut = {EdgeSRLow, EdgeSRMed, EdgeSRHigh, EdgeVRLow, EdgeVRMed, EdgeVRHigh};
    vector<TString> regionName = {"SRLow", "SRMed", "SRHigh", "VRLow", "VRMed", "VRHigh"};

    Group PowhegZee("Powheg Zee");
    Group PowhegZmm("Powheg Zmm");
    Group PowhegZtt("Powheg Ztt");
    PowhegZee.AddSample(361106);
    PowhegZmm.AddSample(361107);
    PowhegZtt.AddSample(361108);

    for (int i=0; i<regionCut.size(); i++) {
        AddGroup(Zee);
        AddGroup(Zmm);
        AddGroup(Ztt);
        SetTree("outputTree");
        AddPlot("truthMET", regionCut[i] * newWeight, "Sherpa "+regionName[i], 20, 0, 200);
        Plot(true);

        //AddGroup(PowhegZee);
        //AddGroup(PowhegZmm);
        //AddGroup(PowhegZtt);
        //SetTree("outputTree");
        //AddPlot("truthMET", regionCut[i] * newWeight, "Powheg "+regionName[i], 20, 0, 200);
        //Plot(true);
    }
}

void SingleVsDileptonTriggerPlots() {

    // Options

    MCPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-20-NoSys/MC/";
    dataPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-20-NoSys/Data/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/SingleDileptonTrigger/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    TCut EdgeSRLowNoTrig = mllMin12 + OS + lepReq2525 + jetReq + dPhiJetMET + "MET>200";
    TCut EdgeSRMedNoTrig = mllMin12 + OS + lepReq2525 + jetReq + dPhiJetMET + "MET>250" + "HT>400";
    TCut EdgeSRHighNoTrig = mllMin12 + OS + lepReq2525 + jetReq + dPhiJetMET + "MET>200" + "HT>700";
    vector<TCut> regionCut = {EdgeSRLowNoTrig, EdgeSRMedNoTrig, EdgeSRHighNoTrig};
    vector<TString> regionName = {"SRLow", "SRMed", "SRHigh"};

    // Just running data by itself creates problems (should fix)
    
    Group data1("pT-Binned Trigger Scheme");
    Group data2("Single Lepton Trigger");
    data1.AddSample("../Data/data");
    data2.AddSample("../Data/data");

    for (int i=0; i<regionCut.size(); i++) {
        data1.SetCustomWeight("channel==0 && mmtrig==1 && mmtrig_match==1" + regionCut[i]);
        data2.SetCustomWeight("channel==0 && (HLT_mu20_iloose_L1MU15==1 && Sum$(lep_match_HLT_mu20_iloose_L1MU15)>=1)" + regionCut[i]);
        AddGroup(data1);
        AddGroup(data2);
        SetTree("outputTree");
        AddPlot("mll", "", "mm_"+regionName[i], 15, 0, 300);
        Plot(false);

        data1.SetCustomWeight("channel==1 && eetrig==1 && eetrig_match==1" + regionCut[i]);
        data2.SetCustomWeight("channel==1 && (HLT_e24_lhmedium_iloose_L1EM20VH==1 && Sum$(lep_match_HLT_e24_lhmedium_iloose_L1EM20VH)>=1)" + regionCut[i]);
        AddGroup(data1);
        AddGroup(data2);
        SetTree("outputTree");
        AddPlot("mll", "", "ee_"+regionName[i], 15, 0, 300);
        Plot(false);

        data1.SetCustomWeight("channel>=2 && emtrig==1 && emtrig_match==1" + regionCut[i]);
        data2.SetCustomWeight("channel>=2 && ((HLT_mu20_iloose_L1MU15==1 && Sum$(lep_match_HLT_mu20_iloose_L1MU15)>=1) || (HLT_e24_lhmedium_iloose_L1EM20VH==1 && Sum$(lep_match_HLT_e24_lhmedium_iloose_L1EM20VH)>=1))" + regionCut[i]);
        AddGroup(data1);
        AddGroup(data2);
        SetTree("outputTree");
        AddPlot("mll", "", "em_"+regionName[i], 15, 0, 300);
        Plot(false);

        data1.SetCustomWeight("(channel==0 && mmtrig==1 && mmtrig_match==1) || (channel==1 && eetrig==1 && eetrig_match==1) || (channel>=2 && emtrig==1 && emtrig_match==1)" + regionCut[i]);
        data2.SetCustomWeight("(channel==0 && (HLT_mu20_iloose_L1MU15==1 && Sum$(lep_match_HLT_mu20_iloose_L1MU15)>=1)) || (channel==1 && (HLT_e24_lhmedium_iloose_L1EM20VH==1 && Sum$(lep_match_HLT_e24_lhmedium_iloose_L1EM20VH)>=1)) || (channel>=2 && ((HLT_mu20_iloose_L1MU15==1 && Sum$(lep_match_HLT_mu20_iloose_L1MU15)>=1) || (HLT_e24_lhmedium_iloose_L1EM20VH==1 && Sum$(lep_match_HLT_e24_lhmedium_iloose_L1EM20VH)>=1)))" + regionCut[i]);
        AddGroup(data1);
        AddGroup(data2);
        SetTree("outputTree");
        AddPlot("mll", "", "full_"+regionName[i], 15, 0, 300);
        Plot(false);
    }
}

void DataORTest() {

    // Options

    //MCPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-20-NoSys/MC/";
    MCPath = "~/eos/atlas/user/m/mazhang/Data/Ntuples/DataComparison/Altered/";
    //dataPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-20-NoSys/Data/";
    dataPath = "~/eos/atlas/user/m/mazhang/Data/xAOD/Data/v20_defaultOR/Data/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/DataORTest/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    //TCut EdgeSRLowNoTrig = mllMin12 + OS + lepReq2525 + jetReq + dPhiJetMET + "MET>200";
    //TCut EdgeSRMedNoTrig = mllMin12 + OS + lepReq2525 + jetReq + dPhiJetMET + "MET>250" + "HT>400";
    //TCut EdgeSRHighNoTrig = mllMin12 + OS + lepReq2525 + jetReq + dPhiJetMET + "MET>200" + "HT>700";
    //vector<TCut> regionCut = {EdgeSRLowNoTrig, EdgeSRMedNoTrig, EdgeSRHighNoTrig};
    vector<TCut> regionCut = {EdgeSRLow, EdgeSRMed, EdgeSRHigh, EdgeVRLow, EdgeVRMed, EdgeVRHigh, ""};
    vector<TString> regionName = {"SRLow", "SRMed", "SRHigh", "VRLow", "VRMed", "VRHigh", "Total"};

    Group data1("Default OR");
    Group data2("SUSY OR");
    data1.AddSample("dataDefaultOR");
    data2.AddSample("dataHooberlap");

    for (int i=0; i<regionCut.size(); i++) {
        //AddGroup(data1);
        //AddGroup(data2);
        //SetTree("outputTree");
        //AddPlot("mll", regionCut[i], regionName[i], 15, 0, 300);
        //Plot(false);

        AddGroup(data1);
        AddGroup(data2);
        SetTree("outputTree");
        AddPlot("mu_jet_dR", regionCut[i], regionName[i] + "_dR", 50, 0, 8);
        Plot(false);
    }
}

void NonFS() {

    // Options

    MCPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-20-NoSys/MC/";
    dataPath = "~/eos/atlas/user/m/mazhang/Data/xAOD/Data/v20_defaultOR/Data/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/NonFS/";
    saveImage = false;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    Group nonFS("Non-FS");
    //nonFS.AddSample(410015);
    //nonFS.AddSample(410016);
    //nonFS.AddSample(361108);
    //Group VV("VV");
    //VV.AddSample(361068);
    nonFS.AddSample(361063);
    nonFS.AddSample(361064);
    nonFS.AddSample(361065);
    nonFS.AddSample(361066);
    nonFS.AddSample(361067);
    nonFS.AddSample(361068);
    nonFS.AddSample(361073);
    nonFS.AddSample(361077);
    nonFS.AddSample(361084);
    nonFS.AddSample(361086);
    nonFS.AddSample(361607);
    nonFS.AddSample(361100);
    nonFS.AddSample(361101);
    nonFS.AddSample(361102);
    nonFS.AddSample(361103);
    nonFS.AddSample(361104);
    nonFS.AddSample(361105);
    nonFS.AddSample(410066);
    nonFS.AddSample(410067);
    nonFS.AddSample(410068);
    nonFS.AddSample(410081);
    nonFS.AddSample(410111);
    nonFS.AddSample(410112);
    nonFS.AddSample(410113);
    nonFS.AddSample(410114);
    nonFS.AddSample(410115);
    nonFS.AddSample(410116);
    for (int i=361372; i<=361419; i++)
        nonFS.AddSample(i);
    for (int i=361468; i<=361483; i++)
        nonFS.AddSample(i);

    TCut newWeight = "3.2*weight1fb*trigweight";

    vector<int> mllBinsLow {0,20,40,60,80,100,125,150,175,200,250,300,350,400,450,500};
    vector<int> mllBinsMed {0,40,80,100,150,250,350,500};
    vector<int> mllBinsHigh {1,31,71,111,151,251,401};

    cout<<"Low"<<endl;

    for (int i=0; i<mllBinsLow.size()-1; i++) {
        AddGroup(nonFS);
        //AddGroup(VV);
        SetTree("outputTree");
        AddPlot("mll", newWeight * (EdgeCRTLow + TCut("mll>" + TString(to_string(mllBinsLow[i])) + " && mll<" + TString(to_string(mllBinsLow[i+1])))), "EdgeSRLow", 50, 0, 8);
        Plot(false);
    }

    cout<<"Med"<<endl;

    for (int i=0; i<mllBinsMed.size()-1; i++) {
        AddGroup(nonFS);
        //AddGroup(VV);
        SetTree("outputTree");
        AddPlot("mll", newWeight * (EdgeCRTMed + TCut("mll>" + TString(to_string(mllBinsMed[i])) + " && mll<" + TString(to_string(mllBinsMed[i+1])))), "EdgeSRMed", 50, 0, 8);
        Plot(false);
    }

    cout<<"High"<<endl;

    for (int i=0; i<mllBinsHigh.size()-1; i++) {
        AddGroup(nonFS);
        //AddGroup(VV);
        SetTree("outputTree");
        AddPlot("mll", newWeight * (EdgeCRTHigh + TCut("mll>" + TString(to_string(mllBinsHigh[i])) + " && mll<" + TString(to_string(mllBinsHigh[i+1])))), "EdgeSRHigh", 50, 0, 8);
        Plot(false);
    }
}

void ZTruthMETPlots() {

    // Options

    MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/ZTruthMET/";
    dataPath = "";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/ZTruthMETSR/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    TCut newWeight = "3.2*weight1fb*trigweight";
	saveExtension = "root";

	Group Zee_bVeto ("Zee_bVeto");
	Group Zee_bFilter ("Zee_bFilter");

    for (int i=361372; i<=361395; i++) {
		if (i==361374 || i==361377 || i==361380 || i==361383 || i==361386 || i==361389 || i==361392 || i==361395)
			Zee_bFilter.AddSample(i);
		else
			Zee_bVeto.AddSample(i);
    }

	// Inclusive

	//AddGroup(Zee_noDY);
	//SetTree("outputTree");
	//AddPlot("truthMET_NonInt", newWeight, "truthMET_NonInt_Zee", 50, 0, 100);
	//AddPlot("truthMET_IntOut", newWeight, "truthMET_IntOut_Zee", 50, 0, 100);
	//AddPlot("fakeMET", newWeight, "fakeMET_Zee", 50, 0, 100);
	//Plot(false);

	//AddGroup(Zmm_noDY);
	//SetTree("outputTree");
	//AddPlot("truthMET_NonInt", newWeight, "truthMET_NonInt_Zmm", 50, 0, 100);
	//AddPlot("truthMET_IntOut", newWeight, "truthMET_IntOut_Zmm", 50, 0, 100);
	//AddPlot("fakeMET", newWeight, "fakeMET_Zmm", 50, 0, 100);
	//Plot(false);

	//AddGroup(Ztt_noDY);
	//SetTree("outputTree");
	//AddPlot("truthMET_NonInt", newWeight, "truthMET_NonInt_Ztt", 50, 0, 100);
	//AddPlot("truthMET_IntOut", newWeight, "truthMET_IntOut_Ztt", 50, 0, 100);
	//AddPlot("fakeMET", newWeight, "fakeMET_Ztt", 50, 0, 100);
	//Plot(false);

	//AddGroup(Zee_bVeto);
	//SetTree("outputTree");
	//AddPlot("truthMET_NonInt", newWeight, "truthMET_NonInt_Zee_bVeto", 50, 0, 100);
	//AddPlot("truthMET_IntOut", newWeight, "truthMET_IntOut_Zee_bVeto", 50, 0, 100);
	//AddPlot("fakeMET", newWeight, "fakeMET_Zee_bVeto", 50, 0, 100);
	//Plot(false);

	//AddGroup(Zee_bFilter);
	//SetTree("outputTree");
	//AddPlot("truthMET_NonInt", newWeight, "truthMET_NonInt_Zee_bFilter", 50, 0, 100);
	//AddPlot("truthMET_IntOut", newWeight, "truthMET_IntOut_Zee_bFilter", 50, 0, 100);
	//AddPlot("fakeMET", newWeight, "fakeMET_Zee_bFilter", 50, 0, 100);
	//Plot(false);

	// By regions
	
	vector<TCut> regionCut = {EdgeSRLow, EdgeSRMed, EdgeSRHigh, SRZ};//  EdgeVRLow, EdgeVRMed, EdgeVRHigh};
	vector<TString> regionName = {"SRLow", "SRMed", "SRHigh", "SRZ"};// "VRLow", "VRMed", "VRHigh"};

	for (int i=0; i<regionCut.size(); i++) {
		
		AddGroup(Zee_noDY);
		SetTree("outputTree");
		AddPlot("truthMET_NonInt", regionCut[i]*newWeight, regionName[i]+"truthMET_NonInt_Zee", 8, 0, 600);
		AddPlot("truthMET_IntOut", regionCut[i]*newWeight, regionName[i]+"truthMET_IntOut_Zee", 8, 0, 600);
		AddPlot("fakeMET", regionCut[i]*newWeight, regionName[i]+"fakeMET_Zee", 8, 0, 600);
		Plot(false);

		AddGroup(Zmm_noDY);
		SetTree("outputTree");
		AddPlot("truthMET_NonInt", regionCut[i]*newWeight, regionName[i]+"truthMET_NonInt_Zmm", 8, 0, 600);
		AddPlot("truthMET_IntOut", regionCut[i]*newWeight, regionName[i]+"truthMET_IntOut_Zmm", 8, 0, 600);
		AddPlot("fakeMET", regionCut[i]*newWeight, regionName[i]+"fakeMET_Zmm", 8, 0, 600);
		Plot(false);

		AddGroup(Ztt_noDY);
		SetTree("outputTree");
		AddPlot("truthMET_NonInt", regionCut[i]*newWeight, regionName[i]+"truthMET_NonInt_Ztt", 8, 0, 600);
		AddPlot("truthMET_IntOut", regionCut[i]*newWeight, regionName[i]+"truthMET_IntOut_Ztt", 8, 0, 600);
		AddPlot("fakeMET", regionCut[i]*newWeight, regionName[i]+"fakeMET_Ztt", 8, 0, 600);
		Plot(false);

		AddGroup(Zee_bVeto);
		SetTree("outputTree");
		AddPlot("truthMET_NonInt", regionCut[i]*newWeight, regionName[i]+"truthMET_NonInt_Zee_bVeto", 8, 0, 600);
		AddPlot("truthMET_IntOut", regionCut[i]*newWeight, regionName[i]+"truthMET_IntOut_Zee_bVeto", 8, 0, 600);
		AddPlot("fakeMET", regionCut[i]*newWeight, regionName[i]+"fakeMET_Zee_bVeto", 8, 0, 600);
		Plot(false);

		AddGroup(Zee_bFilter);
		SetTree("outputTree");
		AddPlot("truthMET_NonInt", regionCut[i]*newWeight, regionName[i]+"truthMET_NonInt_Zee_bFilter", 8, 0, 600);
		AddPlot("truthMET_IntOut", regionCut[i]*newWeight, regionName[i]+"truthMET_IntOut_Zee_bFilter", 8, 0, 600);
		AddPlot("fakeMET", regionCut[i]*newWeight, regionName[i]+"fakeMET_Zee_bFilter", 8, 0, 600);
		Plot(false);
	}
}

void Table26DibosonPercentages() {

    // Options

	MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/v1_01/METMod/MC/";
	dataPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/v1_01/METMod/Data/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/DibosonPercentages/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    TCut newWeight = TCut(TString(to_string(luminosity/1000.)+"*weight1fb*trigweight"));
	saveExtension = "pdf";

    vector<TCut> regionCut = {SRZ_noSF, CRT_noSF, VRT_noSF, VRS_noSF};
    vector<TString> regionName = {"SRZ", "CRT", "VRT", "VRS"};

    for (int i=0; i<regionCut.size(); i++) {
		AddGroup(SherpaVV);
		SetTree("outputTree");
		AddPlot("mll", newWeight * (regionCut[i] + SF), "Sherpa mll SF " + regionName[i], 50, 0, 200);
		AddPlot("mll", newWeight * (regionCut[i] + DF), "Sherpa mll OF " + regionName[i], 50, 0, 200);
		Plot(false);
		//AddPlot("truthMET_IntOut", regionCut[i]*newWeight, regionName[i]+"truthMET_IntOut", 50, 0, 100);

		AddGroup(PowhegZZ_2l2v);
		AddGroup(PowhegWW);
		SetTree("outputTree");
		AddPlot("mll", newWeight * (regionCut[i] + SF), "Powheg mll SF " + regionName[i], 50, 0, 200);
		AddPlot("mll", newWeight * (regionCut[i] + DF), "Powheg mll OF " + regionName[i], 50, 0, 200);
		Plot(false);
	}
}

void TriggerSystematics() {

    // Options

    MCPath = "/afs/cern.ch/work/m/mazhang/Data/v21_Sys/";
    dataPath = "";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/DibosonSystematics/";
    saveImage = false;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
	vector<TCut> regionCut = {EdgeSRLow, EdgeSRMed, EdgeSRHigh, EdgeVRLow, EdgeVRMed, EdgeVRHigh};
	vector<TCut> DFRegionCut = {EdgeCRTLow, EdgeCRTMed, EdgeCRTHigh, EdgeVRTLow, EdgeVRTMed, EdgeVRTHigh};
	vector<TString> regionName = {"EdgeSRLow", "EdgeSRMed", "EdgeSRHigh", "EdgeVRLow", "EdgeVRMed", "EdgeVRHigh"};
	//vector<TCut> regionCut = {VR3L};
	//vector<TCut> DFRegionCut = {VR3LDF};
	//vector<TString> regionName = {"VR 3L"};
    TCut newWeight = "3.2*weight1fb";

	for (int cutn=0; cutn<regionCut.size(); cutn++) {

        cout<<"New Region: "<<regionName[cutn]<<endl;

        TCut thisRegion = regionCut[cutn];
        TCut thisDFRegion = DFRegionCut[cutn];

        Group SherpaVVSF = SherpaVV;
        SherpaVVSF.SetName("Sherpa VV SF");
        Group SherpaVVDF = SherpaVV;
        SherpaVVDF.SetCustomWeight(thisDFRegion * newWeight * "trigweight");
        SherpaVVDF.SetName("Sherpa VV DF");

        AddGroup(SherpaVVSF);
        AddGroup(SherpaVVDF);
        AddGroup(SherpaWZ);
        AddGroup(SherpaZZ);
        AddGroup(rareTop);
        SetTree("outputTree");
        cout<<"nominal"<<endl;
        AddPlot("mll", thisRegion * newWeight * "trigweight", treeName, 50, 0, 1000);
        Plot(true);

        SherpaVVDF.SetCustomWeight(thisDFRegion * newWeight * "trigweight_down");
        AddGroup(SherpaVVSF);
        AddGroup(SherpaVVDF);
        AddGroup(SherpaWZ);
        AddGroup(SherpaZZ);
        AddGroup(rareTop);
        SetTree("outputTree");
        cout<<"trigweight_down"<<endl;
        AddPlot("mll", thisRegion * newWeight * "trigweight_down", treeName, 50, 0, 1000);
        Plot(true);
	}
}

void MC15cPlots() {

    // Options

    MCPath = "/afs/cern.ch/work/m/mazhang/Data/mc15c/Gorm/";
    dataPath = "/afs/cern.ch/work/m/mazhang/Data/mc15c/Gorm/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/MC15c/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    //TCut newWeight = "3.2*weight1fb*trigweight";

    Group data1("Old Data");
	data1.AddSample("../../../../../../user/m/mazhang/eos/atlas/user/l/longjon/Ntuples/v00-21/Data/data");
    Group data2("New Data");
    data2.AddSample("data");

	vector<TCut> regions = {EdgeSRLow, EdgeSRMed, EdgeSRHigh, EdgeVRLow, EdgeVRMed, EdgeVRHigh};
	vector<TString> regionNames = {"EdgeSRLow", "EdgeSRMed", "EdgeSRHigh", "EdgeVRLow", "EdgeVRMed", "EdgeVRHigh"};

	for (int i=0; i<regions.size(); i++) {
		auto region = regions[i];
		auto regionName = regionNames[i];
		AddGroup(data1);
		AddGroup(data2);
		//AddPlot("MET", region, "MET_"+regionName, 20, 0, 500);
		//AddPlot("jet_n", region, "jet_n_"+regionName, 10, 0, 10);
		AddPlot("HT", region, "HT_"+regionName, 20, 0, 2000);
		//AddPlot("lep_pT[0]", region, "lep_pT[0]_"+regionName, 20, 0, 400);
		//AddPlot("lep_pT[1]", region, "lep_pT[1]_"+regionName, 20, 0, 200);
		//AddPlot("jet_pT[0]", region, "jet_pT[0]_"+regionName, 20, 0, 800);
		//AddPlot("jet_pT[1]", region, "jet_pT[1]_"+regionName, 20, 0, 400);
		//AddPlot("lep_eta[0]", region, "lep_eta[0]_"+regionName, 20, -3, 3);
		//AddPlot("lep_eta[1]", region, "lep_eta[1]_"+regionName, 20, -3, 3);
		//AddPlot("jet_eta[0]", region, "jet_eta[0]_"+regionName, 20, -3, 3);
		//AddPlot("jet_eta[1]", region, "jet_eta[1]_"+regionName, 20, -3, 3);
		Plot(false);
	}
}

void TriggerEfficiencies() {

    // Options

    MCPath = "/afs/cern.ch/work/m/mazhang/Data/mc15c/Gorm/";
    dataPath = "/afs/cern.ch/work/m/mazhang/Data/mc15c/Gorm/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/TriggerEfficiencies/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    Group data1("Data ");
	data1.AddSample("../../../../../../user/m/mazhang/eos/atlas/user/l/longjon/Ntuples/v00-21/Data/data");

    AddGroup(data1);
	vector<TString> triggers = {"HLT_e60_lhmedium", "HLT_2e12_lhloose_L12EM10VH", "HLT_2e17_lhloose", "HLT_mu50", "HLT_mu18_mu8noL1", "HLT_mu24_mu8noL1", "HLT_e17_lhloose_mu14", "HLT_e7_lhmedium_mu24"};

	for (auto trigger: triggers) {
		AddPlot("lep_pT[0]", TCut(trigger), trigger+"_lep_pT[0]", 20, 0, 200);
		AddPlot("lep_pT[1]", TCut(trigger), trigger+"_lep_pT[1]", 20, 0, 200);
		AddPlot("el_pT[0]", TCut(trigger), trigger+"_el_pT[0]", 20, 0, 200);
		AddPlot("el_pT[1]", TCut(trigger), trigger+"_el_pT[1]", 20, 0, 200);
		AddPlot("mu_pT[0]", TCut(trigger), trigger+"_mu_pT[0]", 20, 0, 200);
		AddPlot("mu_pT[1]", TCut(trigger), trigger+"_mu_pT[1]", 20, 0, 200);
	}
    Plot(true);
}

void ZPeak() {

    // Options

    MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/MC15C/MC/";
    dataPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/data16/Data/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/data16ZPeak/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
	AddGroup(ttbar);
	//AddGroup(Zee);
	//AddGroup(Zmm);
	//AddGroup(Ztt);
	AddGroup(rareTop);
	AddGroup(SherpaVV);
	AddGroup(SherpaWZ);
	AddGroup(SherpaZZ);
	data.SetCustomWeight("1");
	AddData();
	AddPlot("mll", MCWeight, "Z peak", 50, 0, 300, true);
	Plot(true);
}

void DataComparisonPlots() {

    // Options

	MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/data16/Data/";
    dataPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/data16/Data/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/dataComparison20.7/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
	Group Data2015 ("20.7 2015 Data");
	Data2015.AddSample("2015datav20_7");
	Data2015.SetCustomWeight("1");
	AddGroup(Data2015);
	Group Data2016 ("Scaled 2016 Data");
	Data2016.AddSample("data");
	AddGroup(Data2016);
	//AddData();
	AddPlot("mll", "3382121/117052", "mll", 30, 0, 300, true);
	AddPlot("lep_pT", "3382121/117052", "lep_pT", 30, 0, 300, true);
	AddPlot("MET", "3382121/117052", "MET", 30, 0, 300, true);
	AddPlot("jet_n", "3382121/117052", "jet_n", 5, 0, 5, true);
	AddPlot("bjet_n", "3382121/117052", "bjet_n", 5, 0, 5, true);
	Plot(false);
}

void DataMCComparisonPlots() {

    // Options

	MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/MC15C/MC/";
	//dataPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/MC15C/Data/";
    dataPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/data16/Reprocessed2015Data/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/data15ReprocessedMCComparison/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    Group Sherpa22Zee("Sherpa 2.2 Zee");
    Group Sherpa22Zmm("Sherpa 2.2 Zmm");
    Group Sherpa22Ztt("Sherpa 2.2 Ztt");
	for (int i=363102; i<=363122; i++) {
        Sherpa22Ztt.AddSample(i);
    }
    for (int i=363364; i<=363387; i++) {
        Sherpa22Zmm.AddSample(i);
    }
    for (int i=363388; i<=363411; i++) {
        if (i==363393) continue;
        if (i==363401) continue;
        Sherpa22Zee.AddSample(i);
    }

	AddGroup(Sherpa22Zee);
	AddGroup(Sherpa22Zmm);
	AddGroup(Sherpa22Ztt);
	AddGroup(ttbar);
	AddGroup(rareTop);
	AddGroup(SherpaVV);
	AddGroup(SherpaWZ);
	AddGroup(SherpaZZ);
	data.SetCustomWeight("1");
	AddData();

    //TCut newWeight = ".335*weight1fb";
    TCut newWeight = "3.209*weight1fb";
	AddPlot("mll", newWeight, "mll", 30, 0, 300, true);
	AddPlot("lep_pT", newWeight, "lep_pT", 30, 0, 300, true);
	AddPlot("MET", newWeight, "MET", 30, 0, 300, true);
	AddPlot("jet_n", newWeight, "jet_n", 5, 0, 5, true);
	AddPlot("bjet_n", newWeight, "bjet_n", 5, 0, 5, true);
	Plot(true);
}

void MCYields() {

    // Options

	MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/MC15C/MC/";
	dataPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/MC15C/Data/";
    //dataPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/data16/Reprocessed2015Data/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/MC15CYields/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    Group Sherpa22Zee("Sherpa 2.2 Zee");
    Group Sherpa22Zmm("Sherpa 2.2 Zmm");
    Group Sherpa22Ztt("Sherpa 2.2 Ztt");
	for (int i=363102; i<=363122; i++) {
        Sherpa22Ztt.AddSample(i);
    }
    for (int i=363364; i<=363387; i++) {
        Sherpa22Zmm.AddSample(i);
    }
    for (int i=363388; i<=363411; i++) {
        if (i==363393) continue;
        if (i==363401) continue;
        Sherpa22Zee.AddSample(i);
    }

	//vector<TCut> regionCut = {EdgeSRLow, EdgeSRMed, EdgeSRHigh, SRZ, VRT, VRS, EdgeVRLow, EdgeVRMed, EdgeVRHigh};
	//vector<TString> regionName = {"EdgeSRLow", "EdgeSRMed", "EdgeSRHigh", "SRZ", "VRT", "VRS", "EdgeVRLow", "EdgeVRMed", "EdgeVRHigh"};
	vector<TCut> regionCut = {EdgeSRLow, EdgeSRMed, EdgeSRHigh};
	vector<TString> regionName = {"EdgeSRLow", "EdgeSRMed", "EdgeSRHigh"};

	for (int cutn=0; cutn<regionCut.size(); cutn++) {

        TCut thisRegion = regionCut[cutn];
		TCut newWeight = thisRegion * ".335*weight1fb";
        TString thisRegionName = regionName[cutn];

		AddGroup(Sherpa22Zee);
		AddGroup(Sherpa22Zmm);
		AddGroup(Sherpa22Ztt);
		AddGroup(ttbar);
		AddGroup(rareTop);
		AddGroup(SherpaVV);
		AddGroup(SherpaWZ);
		AddGroup(SherpaZZ);
		data.SetCustomWeight(thisRegion);
		//if (cutn>=4)
			//AddData();

		//AddPlot("mll", newWeight, thisRegionName + " mll", 30, 0, 300, false);
		//AddPlot("lep_pT", newWeight, thisRegionName + " lep_pT", 50, 0, 500, false);
		AddPlot("MET", newWeight, thisRegionName + " MET", 50, 0, 1000, false);
		//AddPlot("jet_n", newWeight, thisRegionName + " jet_n", 10, 0, 10, false);
		Plot(true);
	}
}

void MET_OR() {

    // Options

	MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/MET_OR/";
	dataPath = "";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/MET_OR/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    Group Zee_0("ufrac >= 0.0");
    Group Zee_1("ufrac >= 0.1");
    Group Zee_2("ufrac >= 0.2");
    Group Zee_3("ufrac >= 0.3");
    Group Zee_4("ufrac >= 0.4");
    Group Zee_5("ufrac >= 0.5 (normal)");

    Zee_0.AddSample("Zee/0.0/361106");
    Zee_1.AddSample("Zee/0.1/361106");
    Zee_2.AddSample("Zee/0.2/361106");
    Zee_3.AddSample("Zee/0.3/361106");
    Zee_4.AddSample("Zee/0.4/361106");
    Zee_5.AddSample("Zee/0.5/361106");

    Group Photon_0("ufrac >= 0.0");
    Group Photon_1("ufrac >= 0.1");
    Group Photon_2("ufrac >= 0.2");
    Group Photon_3("ufrac >= 0.3");
    Group Photon_4("ufrac >= 0.4");
    Group Photon_5("ufrac >= 0.5 (normal)");

    Photon_0.AddSample("PhotonsHigh/0.0/361060");
    Photon_0.AddSample("PhotonsHigh/0.0/361061");
    Photon_0.AddSample("PhotonsHigh/0.0/361062");
    Photon_1.AddSample("PhotonsHigh/0.1/361060");
    Photon_1.AddSample("PhotonsHigh/0.1/361061");
    Photon_1.AddSample("PhotonsHigh/0.1/361062");
    Photon_2.AddSample("PhotonsHigh/0.2/361060");
    Photon_2.AddSample("PhotonsHigh/0.2/361061");
    Photon_2.AddSample("PhotonsHigh/0.2/361062");
    Photon_3.AddSample("PhotonsHigh/0.3/361060");
    Photon_3.AddSample("PhotonsHigh/0.3/361061");
    Photon_3.AddSample("PhotonsHigh/0.3/361062");
    Photon_4.AddSample("PhotonsHigh/0.4/361060");
    Photon_4.AddSample("PhotonsHigh/0.4/361061");
    Photon_4.AddSample("PhotonsHigh/0.4/361062");
    Photon_5.AddSample("PhotonsHigh/0.5/361060");
    Photon_5.AddSample("PhotonsHigh/0.5/361061");
    Photon_5.AddSample("PhotonsHigh/0.5/361062");

    Group PhotonMed_0("ufrac >= 0.0");
    Group PhotonMed_1("ufrac >= 0.1");
    Group PhotonMed_2("ufrac >= 0.2");
    Group PhotonMed_3("ufrac >= 0.3");
    Group PhotonMed_4("ufrac >= 0.4");
    Group PhotonMed_5("ufrac >= 0.5 (normal)");

    PhotonMed_0.AddSample("PhotonsMed/0.0/361042");
    PhotonMed_0.AddSample("PhotonsMed/0.0/361043");
    PhotonMed_0.AddSample("PhotonsMed/0.0/361044");
    PhotonMed_1.AddSample("PhotonsMed/0.1/361042");
    PhotonMed_1.AddSample("PhotonsMed/0.1/361043");
    PhotonMed_1.AddSample("PhotonsMed/0.1/361044");
    PhotonMed_2.AddSample("PhotonsMed/0.2/361042");
    PhotonMed_2.AddSample("PhotonsMed/0.2/361043");
    PhotonMed_2.AddSample("PhotonsMed/0.2/361044");
    PhotonMed_3.AddSample("PhotonsMed/0.3/361042");
    PhotonMed_3.AddSample("PhotonsMed/0.3/361043");
    PhotonMed_3.AddSample("PhotonsMed/0.3/361044");
    PhotonMed_4.AddSample("PhotonsMed/0.4/361042");
    PhotonMed_4.AddSample("PhotonsMed/0.4/361043");
    PhotonMed_4.AddSample("PhotonsMed/0.4/361044");
    PhotonMed_5.AddSample("PhotonsMed/0.5/361042");
    PhotonMed_5.AddSample("PhotonsMed/0.5/361043");
    PhotonMed_5.AddSample("PhotonsMed/0.5/361044");

    Group PhotonLow_0("ufrac >= 0.0");
    Group PhotonLow_1("ufrac >= 0.1");
    Group PhotonLow_2("ufrac >= 0.2");
    Group PhotonLow_3("ufrac >= 0.3");
    Group PhotonLow_4("ufrac >= 0.4");
    Group PhotonLow_5("ufrac >= 0.5 (normal)");

    PhotonLow_0.AddSample("PhotonsLow/0.0");
    PhotonLow_1.AddSample("PhotonsLow/0.1");
    PhotonLow_2.AddSample("PhotonsLow/0.2");
    PhotonLow_3.AddSample("PhotonsLow/0.3");
    PhotonLow_4.AddSample("PhotonsLow/0.4");
    PhotonLow_5.AddSample("PhotonsLow/0.5");

    vector<TCut> myCuts = {"1", "jet_n==0", "jet_n==1", "jet_n==2"};
    //vector<TCut> myCuts = {VRS};
    //TCut blah = trigger + mllMin45 + lepReq5025 + jetReq + OS + ZWindow + "MET>100 && MET<200" + HTincl600 + dPhiJetMET + SF;
    TCut blah = jetReq + "MET>225" + HTincl600 + dPhiJetMET;

    for (auto myCut:myCuts) {

        TString cutName = TString(myCut);
        if (cutName=="1") cutName = "Inclusive";
        //TString cutName = "SRZ";

        //AddGroup(Zee_5);
        //AddGroup(Zee_4);
        //AddGroup(Zee_3);
        //AddGroup(Zee_2);
        //AddGroup(Zee_1);
        ////AddGroup(Zee_0);

        //AddPlot("MET", myCut, "Zee MET - " + cutName, 25, 0, 250, true, false);
        //AddPlot("MET_softTerm", myCut, "Zee MET soft term - " + cutName, 25, 0, 100, true, false);
        //AddPlot("abs(MET-truthMET)", myCut, "Zee MET residual - " + cutName, 25, 0, 250, true, false);
        //Plot(false);

        //AddGroup(Photon_5);
        //AddGroup(Photon_4);
        //AddGroup(Photon_3);
        //AddGroup(Photon_2);
        //AddGroup(Photon_1);
        //AddGroup(Photon_0);

        //AddPlot("MET", myCut, "Photon pT>4000 MET - " + cutName, 25, 0, 2000, true, false);
        //AddPlot("MET_softTerm", myCut, "Photon pT>4000 MET soft term - " + cutName, 25, 0, 400, true, false);
        //AddPlot("abs(MET-truthMET)", myCut, "Photon pT>4000 MET residual - " + cutName, 25, 0, 2000, true, false);
        //Plot(false);

        AddGroup(PhotonMed_5);
        AddGroup(PhotonMed_4);
        AddGroup(PhotonMed_3);
        AddGroup(PhotonMed_2);
        AddGroup(PhotonMed_1);
        AddGroup(PhotonMed_0);

        AddPlot("MET", myCut, "Photon pT 70-140 MET - " + cutName, 25, 0, 500, true, false);
        AddPlot("MET_softTerm", myCut, "Photon pT 70-140 MET soft term - " + cutName, 25, 0, 150, true, false);
        AddPlot("abs(MET-truthMET)", myCut, "Photon pT 70-140 MET residual - " + cutName, 25, 0, 500, true, false);
        Plot(false);

        //AddPlot("MET", myCut, "Photon pT>4000 MET - " + cutName, 25, 0, 2500, true, false);
        //AddPlot("MET_softTerm", myCut, "Photon pT>4000 MET soft term - " + cutName, 25, 0, 100, true, false);
        //AddPlot("abs(MET-truthMET)", myCut, "Photon pT>4000 MET residual - " + cutName, 25, 0, 2500, true, false);
        //Plot(false);

        //AddGroup(PhotonLow_5);
        //AddGroup(PhotonLow_4);
        //AddGroup(PhotonLow_3);
        //AddGroup(PhotonLow_2);
        //AddGroup(PhotonLow_1);
        //AddGroup(PhotonLow_0);

        //AddPlot("MET", myCut, "Photon pT 35-70 (C Veto B Veto) MET - " + cutName, 25, 0, 250, true, false);
        //AddPlot("MET_softTerm", myCut, "Photon pT 35-70 (C Veto B Veto) MET soft term - " + cutName, 25, 0, 100, true, false);
        //AddPlot("abs(MET-truthMET)", myCut, "Photon pT 35-70 (C Veto B Veto) MET residual - " + cutName, 25, 0, 250, true, false);
        //Plot(false);
    }
}

void WeightCheck() {

    // Options

	MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/v1_01/METMod/MC/";
	dataPath = "";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/MET_OR/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    // Create plots
    
    //vector<int> samples = {342556, 361386, 361419, 361476, 363107, 363378, 363411,
        //361063, 361387, 361420, 361477, 363108, 363379, 407012,
        //361064, 361388, 361421, 361478, 363109, 363380, 407019,
        //361065, 361389, 361422, 361479, 363110, 363381, 407021,
        //361066, 361390, 361423, 361480, 363111, 363382, 410000,
        //361067, 361391, 361424, 361481, 363112, 363383, 410003,
        //361068, 361392, 361425, 361482, 363113, 363384, 410015,
        //361069, 361393, 361426, 361483, 363114, 363385, 410016,
        //361070, 361394, 361427, 361484, 363115, 363386, 410021,
        //361071, 361395, 361428, 361485, 363116, 363387, 410022,
        //361072, 361396, 361429, 361486, 363117, 363388, 410023,
        //361073, 361397, 361430, 361487, 363118, 363389, 410050,
        //361077, 361398, 361431, 361488, 363119, 363390, 410064,
        //361086, 361399, 361432, 361489, 363120, 363391, 410065,
        //361091, 361400, 361433, 361490, 363121, 363392, 410066,
        //361096, 361401, 361434, 361491, 363122, 363393, 410067,
        //361106, 361402, 361435, 361600, 363361, 363394, 410068,
        //361107, 361403, 361436, 361601, 363362, 363395, 410081,
        //361108, 361404, 361437, 361602, 363363, 363396, 410111,
        //361372, 361405, 361438, 361603, 363364, 363397, 410112,
        //361373, 361406, 361439, 361604, 363365, 363398, 410113,
        //361374, 361407, 361440, 361605, 363366, 363399, 410114,
        //361375, 361408, 361441, 361606, 363367, 363400, 410115,
        //361376, 361409, 361442, 361607, 363368, 363401, 410116,
        //361377, 361410, 361443, 361608, 363369, 363402, 410159,
        //361378, 361411, 361468, 361609, 363370, 363403, 410187,
        //361379, 361412, 361469, 361610, 363371, 363404, 410188,
        //361380, 361413, 361470, 361611, 363372, 363405, 410189,
        //361381, 361414, 361471, 363102, 363373, 363406,
        //361382, 361415, 361472, 363103, 363374, 363407,
        //361383, 361416, 361473, 363104, 363375, 363408,
        //361384, 361417, 361474, 363105, 363376, 363409,
        //361385, 361418, 361475, 363106, 363377, 363410};

    vector<int> samples = {363411, 363110, 361392, 361485, 410022,
        361397, 361086, 410066, 363122, 361106, 361107, 361108,
        363363, 363398, 410113, 361440, 361605, 363366, 363399,
        361608, 410159, 410187, 361412, 410188, 361380, 361611,
        410189, 363102, 363376, 363377};

    for (int sample:samples) {
        Group Test("Test");
        Test.AddSample(sample);
        AddGroup(Test);
        std::cout<<"Checkpoint "<<sample<<std::endl;
        AddPlot("weight1fb", "weight1fb", "weight1fb", 25, 0, 500, true, false);
        Plot(false);
    }
}

void ZPtStitching() {

    // Options

	MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/v1_01/METMod/MC/";
	dataPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/v1_01/METMod/Data/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/ZCheck/";
    saveImage = true;
    blinded = false;

    DefineSampleGroups();
    DefineWeightsAndRegions();

    AddGroup(Zee);
    AddPlot("Z_pt", "weight1fb", "Zee_pt", 25, 0, 2500, true, false);
    Plot(false);

    AddGroup(Zmm);
    AddPlot("Z_pt", "weight1fb", "Zmm_pt", 25, 0, 2500, true, false);
    Plot(false);

    AddGroup(Ztt);
    AddPlot("Z_pt", "weight1fb", "Ztt_pt", 25, 0, 2500, true, false);
    Plot(false);
}

void MCRegionYieldsTable() {

    // Options

	MCPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/v1_02/MC/";
	dataPath = "/afs/cern.ch/user/m/mazhang/eos/atlas/user/m/mazhang/Data/Ntuples/v1_02/Data/";
    saveDirectory = "/afs/cern.ch/user/m/mazhang/Plots/RegionYields/";
    saveImage = false;
    blinded = false;

    //SetLuminosity(8586);
    SetLuminosity(6700);
    //SetLuminosity(3209);
    //SetLuminosity(3500);

    DefineSampleGroups();
    DefineWeightsAndRegions();

    vector<TCut> regionCut = {EdgeSRLow, EdgeSRMed, EdgeSRHigh, EdgeVRLow, EdgeVRMed, EdgeVRHigh, SRZ, CRT, VRT, VRS};
	vector<TCut> DFRegionCut = {EdgeCRTLow, EdgeCRTMed, EdgeCRTHigh, EdgeVRTLow, EdgeVRTMed, EdgeVRTHigh, SRZ_DF, CRT_DF, VRT_DF, VRS_DF};
    vector<TString> regionName = {"SR Low", "SR Med", "SR High", "VR Low", "VR Med", "VR High", "SRZ", "CRT", "VRT", "VRS"};

    dataTable emptyTable = {{},{},{},{}};
    dataTables emptyTables = std::make_pair(emptyTable, emptyTable);
    dataTables eeTables=emptyTables, mmTables=emptyTables, DFTables=emptyTables, totalTables=emptyTables;

    cout<<"\\begin{table}[hbt]"<<endl;
    cout<<"\\centering"<<endl;
    cout<<"\\caption{Expected number of weighted events at $"<<luminosity/1000<<"~\\mathrm{fb}^{-1}$ for rare top and Sherpa diboson MC in various signal regions. The number of $ZZ$ events in each region is obtained by subtracting the number of opposite-flavor $VV$ events from the number of same-flavor events. This method is not applicable for the $WZ$ or rare top estimation, so the DF events for these regions are grayed out in the table. Final expected numbers in each region are shown at the bottom of the table. The uncertainties given here are statistical only. Expected MC yields are shown against observed 2015+2016 data.}"<<endl;
    cout<<"\\begin{tabular}{l|c|c|c|c} \\\\"<<endl;

    for (int channel=0; channel<=3; channel++) {

        if (channel==0)
            cout<<"$\\mu\\mu$ & $WZ$ & $VV$ & Rare Top & Data \\\\"<<endl;
        else if (channel==1)
            cout<<"ee & $WZ$ & $VV$ & Rare Top & Data \\\\"<<endl;
        else if (channel==2)
            cout<<"DF & $WZ$ & $VV$ & Rare Top & Data \\\\"<<endl;
        else if (channel==3)
            cout<<"Total & $WZ$ & $ZZ$ ($VV_{SF}$-$VV_{DF}$) & Rare Top & Data \\\\"<<endl;
        cout<<"\\hline"<<endl;

        for (int cutn=0; cutn<regionCut.size(); cutn++) {

            cout<<regionName[cutn];

            TCut thisRegion = regionCut[cutn];
            TCut thisDFRegion = DFRegionCut[cutn];

            Group AllData ("2015+2016 Data");
            AllData.AddSample("../Data/data_2015");
            AllData.AddSample("../Data/data_2016");
            AllData.SetCustomWeight(TCut(TString("(channel==")+TString(to_string(channel))+")") * thisRegion);
            if (channel==2)
                AllData.SetCustomWeight(TCut(TString("(channel==")+TString(to_string(channel))+")") * thisDFRegion);

            AddGroup(SherpaWZ);
            AddGroup(SherpaVV);
            AddGroup(rareTop);
            AddGroup(AllData);

            if (channel<2)
                AddPlot("mll", TCut(TString(to_string(luminosity/1000.)+"*weight1fb*(channel=="+TString(to_string(channel))+")")) * thisRegion, "mll", 25, 0, 2500, true, false);
            else if (channel==2)
                AddPlot("mll", TCut(TString(to_string(luminosity/1000.)+"*weight1fb*(channel>=2)")) * thisDFRegion, "mll", 25, 0, 2500, true, false);

            dataTables yieldsAndErrors;
            if (channel<3) {
                yieldsAndErrors = Plot(true);
                dataTable part1, part3;
                auto part2 = yieldsAndErrors.first;
                auto part4 = yieldsAndErrors.second;
                if (channel==0) {
                    part1 = mmTables.first;
                    part3 = mmTables.second;
                }
                else if (channel==1) {
                    part1 = eeTables.first;
                    part3 = eeTables.second;
                }
                else if (channel==2) {
                    part1 = DFTables.first;
                    part3 = DFTables.second;
                }
                for (int group=0; group<yieldsAndErrors.first.size(); group++) {
                    part1[group].insert(part1[group].end(),part2[group].begin(),part2[group].end());
                    part3[group].insert(part3[group].end(),part4[group].begin(),part4[group].end());
                }
                if (channel==0) {
                    mmTables.first = part1;
                    mmTables.second = part3;
                }
                else if (channel==1) {
                    eeTables.first = part1;
                    eeTables.second = part3;
                }
                else if (channel==2) {
                    DFTables.first = part1;
                    DFTables.second = part3;
                }
            }
            else {
                dataTable yields = {}, errors = {};
                for (int i=0; i<eeTables.first.size(); i++) {
                    vector<double> yield = {eeTables.first[i][cutn]+mmTables.first[i][cutn]};
                    vector<double> error = {sqrt(pow(eeTables.second[i][cutn],2) + pow(mmTables.second[i][cutn],2))};
                    if (i==1) {
                        yield = {eeTables.first[i][cutn]+mmTables.first[i][cutn]-DFTables.first[i][cutn]};
                        error = {sqrt(pow(DFTables.second[i][cutn],2) + pow(eeTables.second[i][cutn],2) + pow(mmTables.second[i][cutn],2))};
                    }
                    yields.push_back(yield);
                    errors.push_back(error);
                }
                yieldsAndErrors.first = yields;
                yieldsAndErrors.second = errors;
            }

            std::cout << std::fixed;
            dataTable yields = yieldsAndErrors.first;
            dataTable errors = yieldsAndErrors.second;

            for (int i=0; i<yields.size(); i++) {
                for (int j=0; j<yields[i].size(); j++) {

                    double integral = yields[i][j];
                    double error = errors[i][j];

                    int precision = 2;
                    if (i==3) precision=0;

                    if (i==3) {
                        if (channel==2)
                            cout<<setprecision(precision)<<" & \\cellcolor{gray}$"<<integral<<"$";
                        else
                            cout<<setprecision(precision)<<" & $"<<integral<<"$";
                    }
                    else {
                        if (channel==2 && i!=1)
                            cout<<setprecision(precision)<<" & \\cellcolor{gray}$"<<integral<<"\\pm"<<error<<"$";
                        else
                            cout<<setprecision(precision)<<" & $"<<integral<<"\\pm"<<error<<"$";
                    }
                }
            }

            cout<<" \\\\"<<endl;
        }

        if (channel==3) {
            cout<<"\\end{tabular}"<<endl;
            cout<<"\\label{tab:regionYields}"<<endl;
            cout<<"\\end{table}"<<endl;
        }
        else
            cout<<"\\hline\n\\hline"<<endl;
    }
}

// Calling function
void SimpleNtuplePlotter() {
    //SetLuminosity(3209);
    //SetLuminosity(3500);
	//DataMCComparisonPlots();
    MCRegionYieldsTable();
}
