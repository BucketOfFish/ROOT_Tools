#../../../QFramework/share/tqroot TrigCorrection.root

TH1 *h_data_ee = samples->getHistogram("flavSymee/?/data","Cut_EdgeSR_Low/Mll_low_new")
h_data_ee->SetName("h_data_ee")
TH1 *h_data_mm = samples->getHistogram("flavSymmm/?/data","Cut_EdgeSR_Low/Mll_low_new")
h_data_mm->SetName("h_data_mm")
TH1 *h_bkg_ee = samples->getHistogram("flavSymee/?/bkg","Cut_EdgeSR_Low/Mll_low_new")
h_bkg_ee->SetName("h_bkg_ee")
TH1 *h_bkg_mm = samples->getHistogram("flavSymmm/?/bkg","Cut_EdgeSR_Low/Mll_low_new")
h_bkg_mm->SetName("h_bkg_mm")
TFile *f = new TFile("matt_hists_low.root","recreate")
h_data_ee->SetDirectory(f)
h_data_mm->SetDirectory(f)
h_bkg_ee->SetDirectory(f)
h_bkg_mm->SetDirectory(f)
f->Write()
f->Close()

TH1 *h_data_ee = samples->getHistogram("flavSymee/?/data","Cut_EdgeSR_Med/Mll_med_new")
h_data_ee->SetName("h_data_ee")
TH1 *h_data_mm = samples->getHistogram("flavSymmm/?/data","Cut_EdgeSR_Med/Mll_med_new")
h_data_mm->SetName("h_data_mm")
TH1 *h_bkg_ee = samples->getHistogram("flavSymee/?/bkg","Cut_EdgeSR_Med/Mll_med_new")
h_bkg_ee->SetName("h_bkg_ee")
TH1 *h_bkg_mm = samples->getHistogram("flavSymmm/?/bkg","Cut_EdgeSR_Med/Mll_med_new")
h_bkg_mm->SetName("h_bkg_mm")
TFile *f = new TFile("matt_hists_med.root","recreate")
h_data_ee->SetDirectory(f)
h_data_mm->SetDirectory(f)
h_bkg_ee->SetDirectory(f)
h_bkg_mm->SetDirectory(f)
f->Write()
f->Close()

TH1 *h_data_ee = samples->getHistogram("flavSymee/?/data","Cut_EdgeSR_High/Mll_high")
h_data_ee->SetName("h_data_ee")
TH1 *h_data_mm = samples->getHistogram("flavSymmm/?/data","Cut_EdgeSR_High/Mll_high")
h_data_mm->SetName("h_data_mm")
TH1 *h_bkg_ee = samples->getHistogram("flavSymee/?/bkg","Cut_EdgeSR_High/Mll_high")
h_bkg_ee->SetName("h_bkg_ee")
TH1 *h_bkg_mm = samples->getHistogram("flavSymmm/?/bkg","Cut_EdgeSR_High/Mll_high")
h_bkg_mm->SetName("h_bkg_mm")
TFile *f = new TFile("matt_hists_high.root","recreate")
h_data_ee->SetDirectory(f)
h_data_mm->SetDirectory(f)
h_bkg_ee->SetDirectory(f)
h_bkg_mm->SetDirectory(f)
f->Write()
f->Close()

for (int i=1; i<h_data_ee->GetNbinsX()+3; i++) {
    cout<<h_data_ee->GetXaxis()->GetBinLowEdge(i)<<endl;
}
for (int i=1; i<h_data_ee->GetNbinsX()+2; i++) {
    cout<<h_data_ee->GetBinContent(i)<<",";
}

for (int i=1; i<h_data_mm->GetNbinsX()+3; i++) {
    cout<<h_data_mm->GetXaxis()->GetBinLowEdge(i)<<endl;
}
for (int i=1; i<h_data_mm->GetNbinsX()+2; i++) {
    cout<<h_data_mm->GetBinContent(i)<<",";
}
