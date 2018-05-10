void data_mc_ratio_plot() {

    ///////////////////////////////////////////////////
    // Set up canvas - pad1 for plot, pad2 for ratio //
    ///////////////////////////////////////////////////

    TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 800);

    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
    pad1->SetBottomMargin(0); // upper and lower plot are joined
    pad1->SetGridx(); // vertical grid
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.2);
    pad2->SetGridx(); // vertical grid

    gStyle->SetOptStat(0); // no stats box
  
    ///////////////////////////////////////
    // Data and cuts - create histograms //
    ///////////////////////////////////////

	TChain * tree_data = new TChain("BaselineTree");
	tree_data->Add("data/data_em.root");
	TChain * tree_tt = new TChain("BaselineTree");
	tree_tt->Add("tt/ttem.root");
	TChain * tree_vv = new TChain("BaselineTree");
	tree_vv->Add("vv/vvem.root");

	TCut mycut = "";
	mycut += "bjet_n==0";
	mycut += "lep_pT[0]>20 && lep_pT[1]>20";
	mycut += "abs(lep_eta[0])<2.5 && abs(lep_eta[1])<2.5";
	mycut += "jet_n>=2";
	mycut += "Z_pt>50";

	TCut weight_z = "totalWeight*36.1*1000";

	tree_data->Draw("MET>>h_data(20,0,400)",mycut); // this is the cut applied to the data, no need for weighting 
	tree_tt->Draw("MET>>h_tt(20,0,400)",mycut*weight_z); // weight for ttbar and VV, change this to h_data, tree_data for GMC closure
	tree_vv->Draw("MET>>h_vv(20,0,400)",mycut*weight_z);

    //////////////////////
    // Draw MC and Data //
    //////////////////////

    pad1->Draw(); // draw the upper pad: pad1
    pad1->cd(); // pad1 becomes the current pad

	THStack *stack = new THStack("stack","em-data");
	h_tt->SetFillColor(kAzure+1);
	stack->Add(h_tt);
	h_vv->SetFillColor(kOrange+1);
	stack->Add(h_vv);
	stack->Draw("hist");
    stack->GetXaxis()->SetTitle("MET (GeV)");
    stack->GetYaxis()->SetTitle("Events/20GeV");
    pad1->SetLogy();

	h_data->SetMarkerStyle(20);
	h_data->Draw("same e1");

    auto legend = new TLegend(0.6,0.7,0.9,0.9);
    legend->AddEntry("h_data","2l data, em-channel","p");
    legend->AddEntry("h_tt","tt(MC), em-channel","f");
    legend->AddEntry("h_vv","VV(MC), em-channel","f");
    legend->Draw();

    /////////////////////
    // Draw ratio plot //
    /////////////////////

    canvas->cd();
    pad2->Draw();
    pad2->cd(); // pad2 becomes the current pad

    float ratioUpper = 2;
    float ratioLower = 0.5;

    TH1D* h_em_ratio = stack->GetStack()->Last()->Clone("h_em_ratio");
	h_em_ratio->Sumw2(); // make error bars correct
	h_em_ratio->Divide(h_data);
    h_em_ratio->SetMaximum(ratioUpper);
    h_em_ratio->SetMinimum(ratioLower);
	h_em_ratio->SetMarkerColor(1);
	h_em_ratio->SetMarkerStyle(20);
	h_em_ratio->Draw("e1");
	h_em_ratio->SetTitle("");
	h_em_ratio->GetYaxis()->SetNdivisions(3);
    h_em_ratio->GetYaxis()->SetLabelSize(0.1);
    h_em_ratio->GetXaxis()->SetLabelSize(0.1);

	TLine* t = new TLine(h_em_ratio->GetXaxis()->GetXmin(), 1, h_em_ratio->GetXaxis()->GetXmax(), 1);
	t->SetLineStyle(7);
	t->Draw("same");

	canvas->SaveAs("excessTest-dataEM-stacked+ratio.pdf");

}
