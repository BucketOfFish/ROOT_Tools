gStyle->SetOptStat(0)
_file0->Get("outputTree")->Draw("MT2W")
TH1F* h0 = ((TH1F*)(gPad->GetListOfPrimitives()->At(1)))
h0->SetLineColor(kRed);
((TTree*)_file1->Get("outputTree"))->Draw("MT2W","","same")
TH1F* h1 = ((TH1F*)(gPad->GetListOfPrimitives()->At(3)))
h1->SetLineColor(kGreen);
((TTree*)_file2->Get("outputTree"))->Draw("MT2W","","same")
TH1F* h2 = ((TH1F*)(gPad->GetListOfPrimitives()->At(4)))
h2->SetLineColor(kBlue);
((TTree*)_file3->Get("outputTree"))->Draw("MT2W","","same")
TH1F* h3 = ((TH1F*)(gPad->GetListOfPrimitives()->At(5)))
h3->SetLineColor(kBlack);
leg = new TLegend(0.6,0.7,0.9,0.9);
leg->AddEntry(h0,"(1200,500)","l");
leg->AddEntry("h1","(1400,100)","l");
leg->AddEntry("h2","(1000,800)","l");
leg->AddEntry("h3","ttbar","l");
leg->Draw();
gPad->SetLogy()
