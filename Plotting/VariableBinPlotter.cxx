int flavor; //0=ee, 1=mm, 2=inclusive
int data; //0=MC, 1=data
void PlotRatio();

void VariableBinPlotter() {

    for (int i=0; i<=2; i++) {
        for (int j=0; j<=1; j++) {
            flavor=i;
            data=j;
            PlotRatio();
        }
    }
}

void PerformOverflowBinning(TH1F* hist) {

    int nBins = hist->GetSize()-2;
    hist->SetBinContent(nBins,hist->GetBinContent(nBins)+hist->GetBinContent(nBins+1));
    hist->SetBinContent(nBins+1,0);
    hist->SetBinContent(1,hist->GetBinContent(0)+hist->GetBinContent(1));
    hist->SetBinContent(0,0);
}

void PlotRatio() {

    Float_t binEdges[] = {0,20,40,60,80,100,125,150,175,225,300};
    Int_t binnum = sizeof(binEdges)/sizeof(Float_t) - 1;

    TString histTitle = "Ratio of ";
    if (flavor==0) histTitle += "ee ";
    if (flavor==1) histTitle += "mm ";
    if (data==0) histTitle += "MC Events in SRZ with Z_pT<35";
    if (data==1) histTitle += "Data Events in SRZ with Z_pT<35";
    TH1F* numHist = new TH1F("num", histTitle, binnum, binEdges);
    TH1F* denomHist = new TH1F("denom", histTitle+" - Denominator", binnum, binEdges);

    TChain* MCChain = new TChain("outputTree");
    if (data) {
        TString dataPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-15-nosyst/Data/";
        MCChain->Add(dataPath+"data_blinded.root");
    }
    else {
        TString MCPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-15-nosyst/MC/";
        for (int i=361372; i<=361443; i++) MCChain->Add(MCPath+TString(to_string(i))+".root");
    }

    TCut SRZCut = "(eetrig||mmtrig||emtrig) && mll>45 && lep_n>=2 && lep_pT[0]>50 && lep_pT[1]>25 && jet_n>=2 && lep_pdgId[0]==-lep_pdgId[1] && mll>81 && mll<101 && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && HTincl>600";
    if (flavor==0) SRZCut += "abs(lep_pdgId[0])==11";
    if (flavor==1) SRZCut += "abs(lep_pdgId[0])==13";

    MCChain->Draw("MET>>denom",SRZCut);
    SRZCut += "Z_pt<35";
    MCChain->Draw("MET>>num",SRZCut);

    TH1F ratioHist = (*numHist)/(*denomHist);

    ratioHist.SetStats(0);
    TCanvas *canvas = new TCanvas("canvas","",696,472);
    ratioHist.Draw("e1");

    canvas->Print("~/Plots/ZpTRatio/"+TString(histTitle)+".pdf");

    delete numHist;
    delete denomHist;
    delete canvas;
}
