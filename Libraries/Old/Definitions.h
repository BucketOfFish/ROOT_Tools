// #include </afs/cern.ch/user/m/mazhang/Projects/Tools/Libraries/Definitions.h>
// Initialize with DefineSampleGroups() and DefineWeightsAndRegions() before using, or call InitDefinitions() from Functions.h!
 
#ifndef DEFINITIONS_H
#define DEFINITIONS_H
 
// Wishlist
// Make it so we don't use global variables
// Change the fact that you need to call DefineSampleGroups() and DefineRegions()
// GetTree() seems to be fucked up
 
TString MCPath = "";
TString dataPath = "";
bool blinded = false;
int luminosity = 3209;
 
// Classes
 
class Group {
 
    TString name, samplePath;
    vector<TString> samples;
    TCut customWeight = "";
 
public:
 
    Group(TString initName, TString path = MCPath) {
        name = initName;
        samplePath = path;
    }
 
    void AddSample(TString sampleName, TString path = MCPath) {
        samples.push_back(sampleName);
        samplePath = path;
    }
 
    void AddSample(int sampleNumber, TString path = MCPath) {
        AddSample((TString)to_string(sampleNumber), path);
    }
 
    vector<TString> GetSamples() {
        return samples;
    }
 
    void SetName(TString newName) {
        name = newName;
    }

    TString Name() {
        return name;
    }
 
    bool IsData() {
        return (name=="Data" || name=="Blinded Data");
    }
 
    TChain* GetChain(TString treeName = "outputTree") {
        TChain* returnChain = new TChain(treeName);
        for (int i=0; i<samples.size(); i++) {
            returnChain->Add(samplePath+samples[i]+".root");
        }
        return returnChain;
    }
 
    TTree* GetTree(TString treeName = "outputTree") {
        return GetChain(treeName)->CloneTree();
    }
 
    TString GetPath() {
        return samplePath;
    }
 
    void SetPath(TString newPath) {
        samplePath = newPath;
    }

    void SetCustomWeight(TCut cut) {
        customWeight = cut;
    }

    TCut GetCustomWeight() {
        return customWeight;
    }
};
 
vector<Group> groups;
 
// Sample Groups
 
Group Zee ("Zee");
Group Zmm ("Zmm");
Group Ztt ("Ztt");
Group Zee_noDY ("Zee");
Group Zmm_noDY ("Zmm");
Group Ztt_noDY ("Ztt");
Group ttbar ("ttbar");
Group rareTop ("Rare Top");
Group SherpaVV ("Sherpa VV - llvv");
Group SherpaWZ ("Sherpa WZ - lllv");
Group SherpaZZ ("Sherpa ZZ - llll");
Group PowhegWZ ("Powheg WZ - lllv");
Group PowhegZZ_4l ("Powheg ZZ - llll");
Group PowhegZZ_2l2v ("Powheg ZZ - llvv");
Group PowhegWW ("Powheg WW - llvv");
 
Group data ("Data");
Group blindedData ("Blinded Data");
 
void DefineSampleGroups() {
 
    for (int i=361372; i<=361443; i++) {
        if (i<=361395) {
            Zee.AddSample(i);
            Zee_noDY.AddSample(i);
		}
        else if (i<=361419) {
            Zmm.AddSample(i);
            Zmm_noDY.AddSample(i);
		}
        else {
            Ztt.AddSample(i);
            Ztt_noDY.AddSample(i);
		}
    }

    for (int i=361468; i<=361491; i++) { //DY
        if (i<=361475)
            Zee.AddSample(i);
        else if (i<=361483)
            Zmm.AddSample(i);
        else
            Ztt.AddSample(i);
    }
 
    ttbar.AddSample(410000);
 
    //vector<int> Wt = {410015, 410016};
    //for (int i:Wt) {
        //rareTop.AddSample(i);
    //}
    vector<int> ttW = {410066, 410067, 410068};
    for (int i:ttW) {
        rareTop.AddSample(i);
    }
    vector<int> ttZ = {410111, 410112, 410113, 410114, 410115, 410116};//, 410069, 410070};
    for (int i:ttZ) {
        rareTop.AddSample(i);
    }
    rareTop.AddSample("410081"); //tt+WW
 
    SherpaVV.AddSample("361068");  //llvv
    SherpaVV.AddSample("361077");  //llvv (gg)
 
    for (int i=361064; i<=361067; i++) {
        SherpaWZ.AddSample(i);
    }
 
    SherpaZZ.AddSample("361063");  //llll
    SherpaZZ.AddSample("361073");  //llll (gg)
 
    PowhegWZ.AddSample("361601");
    PowhegZZ_4l.AddSample("361603");
    PowhegZZ_2l2v.AddSample("361604");
    PowhegWW.AddSample("361600");
 
    data.AddSample("data", dataPath);
    blindedData.AddSample("data_blinded", dataPath);
}
 
void AddGroup(Group group) {
    groups.push_back(group);
}
 
void AddSMGroups() {
    AddGroup(Zee);
    AddGroup(Zmm);
    AddGroup(Ztt);
    AddGroup(ttbar);
    AddGroup(rareTop);
    AddGroup(SherpaVV);
    AddGroup(SherpaWZ);
    AddGroup(SherpaZZ);
}
 
void AddData() {
    if(blinded)
        AddGroup(blindedData);
    else
        AddGroup(data);
}
 
int NGroups() {
    return groups.size();
}
 
bool IsData(int nGroup) {
    return groups[nGroup].IsData();
}
 
TChain* GetTotalChain(TString treeName = "outputTree") {
    TChain* returnChain = new TChain(treeName);
    for (int groupNumber=0; groupNumber<groups.size(); groupNumber++) {
        if (groups[groupNumber].IsData()) continue;
        returnChain->Add(groups[groupNumber].GetChain());
    }
    return returnChain;
}
 
void ResetGroups() {
    groups.clear();
}
 
// Merge all current groups into a single group
void CombineGroups(TString name = "MC") {
    Group combinedGroup(name);
    for (int i=0; i<NGroups(); i++) {
        vector<TString> samples = groups[i].GetSamples();
        for (int j=0; j<samples.size(); j++) combinedGroup.AddSample(samples[j]);
    }
    ResetGroups();
    combinedGroup.SetPath(MCPath);
    AddGroup(combinedGroup);
}
 
// Weights and selections
 
TCut SRZ, CRT, CRFS, VRT, VRS;
TCut SRZ_DF, CRT_DF, VRT_DF, VRS_DF;
TCut SRZ_noSF, CRT_noSF, CRFS_noSF, VRT_noSF, VRS_noSF;
TCut EdgeSRLow, EdgeSRMed, EdgeSRHigh, EdgeVRLow, EdgeVRMed, EdgeVRHigh, EdgeCRTLow, EdgeCRTMed, EdgeCRTHigh, EdgeVRTLow, EdgeVRTMed, EdgeVRTHigh;
TCut VR3L, VR3LDF;
TCut MCWeight;
TCut trigger, mllMin45, mllMin12, lepReq5025, lepReq2525, jetReq, SF, DF, OSSF, OS, OffZWindow, ZWindow, dPhiJetMET;
TCut HTincl600, goodMuons;
 
void DefineWeightsAndRegions() {
 
    trigger = "(channel==1 && eetrig && eetrig_match) || (channel==0 && mmtrig && mmtrig_match) || (channel>=2 && emtrig && emtrig_match)";
    //goodMuons = "!(mu_isBad[0] || mu_isBad[1])";
    goodMuons = "1";
    mllMin45 = "mll>45";
    mllMin12 = "mll>12";
    lepReq5025 = "lep_n>=2 && lep_pT[0]>50 && lep_pT[1]>25";
    lepReq2525 = "lep_n>=2 && lep_pT[0]>25 && lep_pT[1]>25";
    jetReq = "jet_n>=2 && jet_pT[0]>30 && jet_pT[1]>30";
    OSSF = "lep_pdgId[0] == -lep_pdgId[1]";
    OS = "lep_pdgId[0]*lep_pdgId[1] < 0";
	SF = "channel==0 || channel==1";
    DF = "channel==2 || channel==3";
    ZWindow = "mll>81 && mll<101";
    OffZWindow = "mll<81 || mll>101";
    dPhiJetMET = "DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4";
    HTincl600 = "HTincl>600";
 
    VRS_noSF = trigger + goodMuons + mllMin45 + lepReq5025 + jetReq + OS + ZWindow + "MET>100 && MET<200" + HTincl600 + dPhiJetMET;
    SRZ_noSF = trigger + goodMuons + mllMin45 + lepReq5025 + jetReq + OS + ZWindow + "MET>225" + HTincl600 + dPhiJetMET;
    VRT_noSF = trigger + goodMuons + mllMin45 + lepReq5025 + jetReq + OS + OffZWindow + "MET>100 && MET<200" + HTincl600 + dPhiJetMET;
    CRT_noSF = trigger + goodMuons + mllMin45 + lepReq5025 + jetReq + OS + OffZWindow + "MET>225" + HTincl600 + dPhiJetMET;

	VRS = VRS_noSF + SF;
	SRZ = SRZ_noSF + SF;
	CRT = CRT_noSF + SF;
	VRT = VRT_noSF + SF;

	VRS_DF = VRS_noSF + DF;
	SRZ_DF = SRZ_noSF + DF;
	CRT_DF = CRT_noSF + DF;
	VRT_DF = VRT_noSF + DF;
 
    EdgeSRLow = trigger + goodMuons + mllMin12 + OSSF + lepReq2525 + jetReq + dPhiJetMET + "MET>200";
    EdgeSRMed = trigger + goodMuons + mllMin12 + OSSF + lepReq2525 + jetReq + dPhiJetMET + "MET>200" + "HT>400";
    EdgeSRHigh = trigger + goodMuons + mllMin12 + OSSF + lepReq2525 + jetReq + dPhiJetMET + "MET>200" + "HT>700";
 
    //flavor-symmetric control regions
    EdgeCRTLow = trigger + goodMuons + mllMin12 + OS + DF + lepReq2525 + jetReq + dPhiJetMET + "MET>200";
    EdgeCRTMed = trigger + goodMuons + mllMin12 + OS + DF + lepReq2525 + jetReq + dPhiJetMET + "MET>200" + "HT>400";
    EdgeCRTHigh = trigger + goodMuons + mllMin12 + OS + DF + lepReq2525 + jetReq + dPhiJetMET + "MET>200" + "HT>700";
 
    EdgeVRLow = trigger + goodMuons + mllMin12 + OSSF + lepReq2525 + jetReq + dPhiJetMET + "MET>100 && MET<200";
    EdgeVRMed = trigger + goodMuons + mllMin12 + OSSF + lepReq2525 + jetReq + dPhiJetMET + "MET>100 && MET<200" + "HT>400";
    EdgeVRHigh = trigger + goodMuons + mllMin12 + OSSF + lepReq2525 + jetReq + dPhiJetMET + "MET>100 && MET<200" + "HT>700";
 
    //flavor-symmetric regions for VR (I don't think we call them VRT but whatever)
    EdgeVRTLow = trigger + goodMuons + mllMin12 + OS + DF + lepReq2525 + jetReq + dPhiJetMET + "MET>100 && MET<200";
    EdgeVRTMed = trigger + goodMuons + mllMin12 + OS + DF + lepReq2525 + jetReq + dPhiJetMET + "MET>100 && MET<200" + "HT>400";
    EdgeVRTHigh = trigger + goodMuons + mllMin12 + OS + DF + lepReq2525 + jetReq + dPhiJetMET + "MET>100 && MET<200" + "HT>700";

	VR3L = trigger + goodMuons + "lep_n>=3 && lep_pT[0]>50 && lep_pT[1]>25 && lep_pT[2]>25 && MET>60 && MET<100 && HT>200 && jet_n>=2" + ZWindow + OS + dPhiJetMET;
	VR3LDF = VR3L + DF;
	VR3L = VR3L + SF;

    //EdgeSRLow = "(eetrig || mmtrig || emtrig) && mll>12 && lep_n>=2 && lep_pT[0]>25 && lep_pT[1]>25 && jet_n>=2 && jet_pT[0]>30 && jet_pT[1]>30 && lep_pdgId[0]*lep_pdgId[1] < 0 && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET>200";

    MCWeight = "weight1fb/1000*"+TString(to_string(luminosity));
}

void SetLuminosity(int lum) {

	luminosity = lum;
    MCWeight = "weight1fb/1000*"+TString(to_string(lum));
}
 
#endif //DEFINITIONS_H
