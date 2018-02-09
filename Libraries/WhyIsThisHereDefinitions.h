#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "Group.h"

// Sample Groups

Group Zee ("Zee");
Group Zmm ("Zmm");
Group Ztt ("Ztt");
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

void DefineSampleGroups(TString MCPath, TString dataPath) {

    Zee.SetPath(MCPath);
    Zmm.SetPath(MCPath);
    Ztt.SetPath(MCPath);
    for (int i=361372; i<=361443; i++) {
        if (i<=361395)
            Zee.AddSample(i);
        else if (i<=361419)
            Zmm.AddSample(i);
        else
            Ztt.AddSample(i);
    }

    ttbar.SetPath(MCPath);
    ttbar.AddSample(410000);

    rareTop.SetPath(MCPath);
    vector<int> Wt = {410015, 410016};
    for (int i:Wt) {
        rareTop.AddSample(i);
    }
    vector<int> ttW = {410066, 410067, 410068};
    for (int i:ttW) {
        rareTop.AddSample(i);
    }
    vector<int> ttZ = {410111, 410112, 410113, 410114, 410115, 410116};//, 410069, 410070};
    for (int i:ttZ) {
        rareTop.AddSample(i);
    }
    rareTop.AddSample("410081"); //tt+WW

    SherpaVV.SetPath(MCPath);
    SherpaVV.AddSample("361068");  //llvv
    SherpaVV.AddSample("361077");  //llvv (gg)

    SherpaWZ.SetPath(MCPath);
    for (int i=361064; i<=361067; i++) {
        SherpaWZ.AddSample(i);
    }

    SherpaZZ.SetPath(MCPath);
    SherpaZZ.AddSample("361063");  //llll
    SherpaZZ.AddSample("361073");  //llll (gg)

    PowhegWZ.SetPath(MCPath);
    PowhegWZ.AddSample("361601");

    PowhegZZ_4l.SetPath(MCPath);
    PowhegZZ_4l.AddSample("361603");

    PowhegZZ_2l2v.SetPath(MCPath);
    PowhegZZ_2l2v.AddSample("361604");

    PowhegWW.SetPath(MCPath);
    PowhegWW.AddSample("361600");

    data.SetPath(dataPath);
    data.AddSample("data");

    blindedData.SetPath(dataPath);
    blindedData.AddSample("data_blinded");
}

// Weights and selections

TCut SRZ1, CRT1, CRFS1, VRT1, VRS1;
TCut EdgeSRLow, EdgeSRMed, EdgeSRHigh;
TCut MCWeightNoPRW, MCWeightPRW;
TCut trigger, mllMin45, mllMin12, lepReq5025, lepReq2525, jetReq, OSOF, OSSF, OS, ZWindow, dPhiJetMET; 

void DefineWeightsAndRegions() {

    trigger = "(channel==1 && eetrig && eetrigmatch) || (channel==0 && mmtrig && mmtrigmatch) || (channel>=2 && emtrig && emtrigmatch)";
    mllMin45 = "mll>45";
    mllMin12 = "mll>12";
    lepReq5025 = "lep_n>=2 && lep_pT[0]>50 && lep_pT[1]>25";
    lepReq2525 = "lep_n>=2 && lep_pT[0]>25 && lep_pT[1]>25";
    jetReq = "jet_n>=2";
    OSSF = "lep_pdgId[0] == -lep_pdgId[1]";
    OS = "lep_pdgId[0]*lep_pdgId[1] < 0";
    ZWindow = "mll>81 && mll<101";
    dPhiJetMET = "DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4";

    TCut HTincl600 = "HTincl>600";

    VRS1 = trigger + mllMin45 + lepReq5025 + jetReq + OSSF + ZWindow + "MET>100 && MET<200" + HTincl600 + dPhiJetMET;
    SRZ1 = trigger + mllMin45 + lepReq5025 + jetReq + OSSF + ZWindow + "MET>225" + HTincl600 + dPhiJetMET;

    EdgeSRLow = trigger + mllMin12 + OS + lepReq2525 + jetReq + dPhiJetMET + "MET>200";
    EdgeSRMed = trigger + mllMin12 + OS + lepReq2525 + jetReq + dPhiJetMET + "MET>250" + "HT>400";
    EdgeSRHigh = trigger + mllMin12 + OS + lepReq2525 + jetReq + dPhiJetMET + "MET>200" + "HT>700";

    //MCWeightNoPRW = "sampleWeight*eventWeight*pileupWeight*lep_weight[0]*lep_weight[1]*(1+(mmtrigweight-1)*(channel==0 && lep_pT[0]>=55 && HLT_mu50))*sumWeightedEvents*"+TString(to_string(luminosity));
    //MCWeightPRW = "sampleWeight*eventWeight*pileupWeight_rew*lep_weight[0]*lep_weight[1]*(1+(mmtrigweight-1)*(channel==0 && lep_pT[0]>=55 && HLT_mu50))*sumWeightedEvents*"+TString(to_string(luminosity));
}

#endif //DEFINITIONS_H
