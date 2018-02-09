/*

Script to make empty tree template for merginging ntuples

Jonathan Long
16/01/08

Run:
root -l -b -q makeFileHaddTemplate.C

 */



void makeFileHaddTemplate()
{

    //TString sourceFile = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-16-nosyst/MC/410000.root"; // ttbar should work
    TString sourceFile = "/afs/cern.ch/work/m/mazhang/Data/Dibosons_v00-17/nosyst/MC15a/MC/361063.root";
    TString outputFile = "haddTemplate_v17.root";

    TFile * sourceF = new TFile(sourceFile);
    TFile * outF = new TFile(outputFile,"recreate");

    // Clone tree
    TTree *sourceTree = sourceF->Get("outputTree");
    TTree *newTree = sourceTree->CloneTree(0);

    newTree->SetDirectory(outF);

    // Clone histogram
    TH1D * newHist = sourceF->Get("EventCountHist")->Clone();
    newHist->Reset();
    newHist->SetDirectory(outF);

    outF->Write();
    outF->Close();


}
