int flavor; //0=ee, 1=mm, 2=inclusive
int data; //0=MC, 1=data
void Plot();

void VariableBins() {

    for (int i=0; i<=2; i++) {
        flavor=i;
        data=0;
        Plot();
        data=1;
        Plot();
    }
}

void Plot() {

    Float_t binEdges[] = {0,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,220,240,280,340,400};
    Int_t binnum = sizeof(binEdges)/sizeof(Float_t) - 1;
    TString histTitle = "Percentage of ";
    if (flavor==0) histTitle += "ee ";
    if (flavor==1) histTitle += "mm ";
    if (data==0) histTitle += "MC Events in SRZ with Z_pT<35";
    if (data==1) histTitle += "Data Events in SRZ with Z_pT<35";
    TH1F* hist = new TH1F("histName",histTitle, binnum, binEdges);

    Float_t numerator[100] = {0};
    Float_t denominator[100] = {0};
    Float_t fraction[100] = {0};

    TChain* MCChain = new TChain("outputTree");
    if (data) {
        TString dataPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-15-nosyst/Data/";
        MCChain->Add(dataPath+"data_blinded.root");
    }
    else {
        TString MCPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-15-nosyst/MC/";
        for (int i=361372; i<=361443; i++) MCChain->Add(MCPath+TString(to_string(i))+".root");
    }

    //Fill histogram
    double Z_pT = 0;
    MCChain->SetBranchAddress("Z_pt", &Z_pT);
    double MET = 0;
    MCChain->SetBranchAddress("MET", &MET);
    int eetrig;
    MCChain->SetBranchAddress("eetrig",&eetrig);
    int mmtrig;
    MCChain->SetBranchAddress("mmtrig",&mmtrig);
    int emtrig;
    MCChain->SetBranchAddress("emtrig",&emtrig);
    double mll;
    MCChain->SetBranchAddress("mll",&mll);
    int lep_n;
    MCChain->SetBranchAddress("lep_n",&lep_n);
    vector<double> *lep_pT = 0;
    MCChain->SetBranchAddress("lep_pT",&lep_pT);
    int jet_n;
    MCChain->SetBranchAddress("jet_n",&jet_n);
    vector<int> *lep_pdgId = 0;
    MCChain->SetBranchAddress("lep_pdgId",&lep_pdgId);
    double DPhi_METJetLeading;
    MCChain->SetBranchAddress("DPhi_METJetLeading",&DPhi_METJetLeading);
    double DPhi_METJetSecond;
    MCChain->SetBranchAddress("DPhi_METJetSecond",&DPhi_METJetSecond);
    double HTincl;
    MCChain->SetBranchAddress("HTincl",&HTincl);

    int nEvents = MCChain->GetEntries();
    int SRZPass = 0;
    for (int i=0; i<nEvents; i++) {

        MCChain->GetEntry(i);
        bool trigger = eetrig || mmtrig || emtrig;
        bool mllMin = mll>45;
        bool lepReq = lep_n>=2 && lep_pT->at(0)>50 && lep_pT->at(1)>25;
        bool jetReq = jet_n>=2;
        bool OSSF = lep_pdgId->at(0) == -lep_pdgId->at(1);
        bool ee = abs(lep_pdgId->at(0)) == 11;
        bool mm = abs(lep_pdgId->at(0)) == 13;
        bool ZWindow = mll>81 && mll<101;
        bool dPhiJetMET = DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4;
        bool HThigh = HTincl>600;
        bool SRZ1NoMET = trigger && mllMin && lepReq && jetReq && OSSF && ZWindow && HThigh && dPhiJetMET;

        if (!(SRZ1NoMET && ee) && flavor==0) continue;
        if (!(SRZ1NoMET && mm) && flavor==1) continue;
        if (!SRZ1NoMET && flavor==2) continue;
        SRZPass++;

        for (int binCount=0; binCount<binnum; binCount++) {
            if (MET<binEdges[binCount+1] || binCount+1==binnum) {
                denominator[binCount]++;
                if (Z_pT<35)
                    numerator[binCount]++;
            }
        }
    }

    std::cout<<to_string(SRZPass)<<" SRZ Events Passed"<<std::endl;

    for (int binCount=0; binCount<binnum; binCount++) {
        if (denominator[binCount]==0) continue;
        fraction[binCount] = numerator[binCount]/denominator[binCount];
        hist->Fill(binEdges[binCount], fraction[binCount]);
        hist->SetBinError(binCount, 1/sqrt(denominator[binCount]));
    }

    hist->SetStats(0);
    TCanvas *canvas = new TCanvas("canvas","",696,472);
    hist->Draw("e1");

    canvas->Print("~/Plots/"+TString(histTitle)+".pdf");
}
