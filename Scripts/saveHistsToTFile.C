TFile *f = new TFile("WZ_ZZ_HTZZ.root", "UPDATE");
for (int i=0; i<=7; i++) {
    f->Append(((TH1F*)((THStack*)canvas->GetPrimitive("hs"))->GetHists()->At(i)));
}
f->Append((TH1F*)canvas->GetPrimitive("data"));
f->Write();
