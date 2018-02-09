#include "Workspace.h"

void ExampleScript() {

    TString MCPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-16-nosyst/MC";
    TString dataPath = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-16-nosyst/Data";
    Workspace wspace(MCPath, dataPath);
    wspace.AddGroup(Zee);
    wspace.AddGroup(Zmm);
    wspace.AddGroup(Ztt);
    wspace.AddGroup(ttbar);
    wspace.GetPlot("Test", "mll", "mll>200", 100, 0 ,1000)->Draw();
}
