vector<TString> names = {"p_resX_slice1", "p_resX_slice2", "p_resX_slice3", "p_resX_slice4", "p_resY_slice1", "p_resY_slice2", "p_resY_slice3", "p_resY_slice4", "p_resZ_slice1", "p_resZ_slice2", "p_resZ_slice3", "p_resZ_slice4", "h_nClass_slice1", "h_nClass_slice2", "h_nClass_slice3", "h_nClass_slice4", "p_nTracks_z_slice1", "p_nTracks_z_slice2", "p_nTracks_z_slice3", "p_nTracks_z_slice4", "p_recEff_z_slice1", "p_recEff_z_slice2", "p_recEff_z_slice3", "p_recEff_z_slice4"}

for (auto name:names) {
    std::cout << name << std::endl;
    TH1F* hist = (TH1F*)_file0->Get(name);
    hist->Draw();
    c1->SaveAs(name + ".pdf");
}
