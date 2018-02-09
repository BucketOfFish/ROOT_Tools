/* Script to dump fakes varations yields

Feb 2, 2016
Jonathan Long
*/

#include <iomanip>

void dumpFakesVariations()
{

    TString inputFileName = "mm_output/data_fakes_v21_Mar23.root";
    TFile *inputFile = new TFile(inputFileName);

    TTree *tree = (TTree*)inputFile->Get("outputTree");

    // cuts
    std::vector< std::pair<TString,TString>> weight_variation;
    weight_variation.push_back(std::make_pair("Nominal","qcdWeight"));
    
    /*    weight_variation.push_back(std::make_pair("EL F Up","fake_weight_stat_efup"));
    weight_variation.push_back(std::make_pair("EL F Down","fake_weight_stat_efdown"));
    weight_variation.push_back(std::make_pair("EL R Up","fake_weight_stat_erup"));
    weight_variation.push_back(std::make_pair("EL R Down","fake_weight_stat_erdown"));

    weight_variation.push_back(std::make_pair("MU F Up","fake_weight_stat_mfup"));
    weight_variation.push_back(std::make_pair("MU F Down","fake_weight_stat_mfdown"));
    weight_variation.push_back(std::make_pair("MU R Up","fake_weight_stat_mrup"));
    weight_variation.push_back(std::make_pair("MU R Down","fake_weight_stat_mrdown"));
    */

    //weight_variation.push_back(std::make_pair("Sys Up","(qcdWeight + qcdWeightSyst)"));
    //weight_variation.push_back(std::make_pair("Sys Down","(qcdWeight - qcdWeightSyst)"));
    

    // make sure there are parenthesis surounding all of the cuts!
    std::vector< std::pair<TString,TString> > regions;
    regions.push_back(std::make_pair("Edge VR Low", "(mll>12 && is_OS==1  && lep_pT[0] > 25 && lep_pT[1] > 25 && ( (channel==0 && mmtrig==1 && mmtrig_match) || (channel==1 && eetrig==1 && eetrig_match) )  && DPhi_METJetLeading > 0.4 && DPhi_METJetSecond > 0.4 && MET > 100 && MET < 200  && HT>0 && lep_n>=2 && jet_n>1 )  ") );
    regions.push_back(std::make_pair("Edge VR Med", "(mll>12 && is_OS==1  && lep_pT[0] > 25 && lep_pT[1] > 25 && ( (channel==0 && mmtrig==1 && mmtrig_match) || (channel==1 && eetrig==1 && eetrig_match) )  && DPhi_METJetLeading > 0.4 && DPhi_METJetSecond > 0.4 && MET > 100 && MET < 200  && HT>400 && lep_n>=2 && jet_n>1 )  ") );
    regions.push_back(std::make_pair("Edge VR High", "(mll>12 && is_OS==1  && lep_pT[0] > 25 && lep_pT[1] > 25 && ( (channel==0 && mmtrig==1 && mmtrig_match) || (channel==1 && eetrig==1 && eetrig_match) )  && DPhi_METJetLeading > 0.4 && DPhi_METJetSecond > 0.4 && MET > 100 && MET < 200  && HT>700 && lep_n>=2 && jet_n>1 )  ") );

    regions.push_back(std::make_pair("Edge SR Low", "(mll>12 && is_OS==1  && lep_pT[0] > 25 && lep_pT[1] > 25 && ( (channel==0 && mmtrig==1 && mmtrig_match) || (channel==1 && eetrig==1 && eetrig_match) )  && DPhi_METJetLeading > 0.4 && DPhi_METJetSecond > 0.4 && MET > 200  && HT>0 && lep_n>=2 && jet_n>1 )  ") );
    regions.push_back(std::make_pair("Edge SR Med", "(mll>12 && is_OS==1  && lep_pT[0] > 25 && lep_pT[1] > 25 && ( (channel==0 && mmtrig==1 && mmtrig_match) || (channel==1 && eetrig==1 && eetrig_match) )  && DPhi_METJetLeading > 0.4 && DPhi_METJetSecond > 0.4 && MET > 250  && HT>400 && lep_n>=2 && jet_n>1 )  ") );
    regions.push_back(std::make_pair("Edge SR High", "(mll>12 && is_OS==1  && lep_pT[0] > 25 && lep_pT[1] > 25 && ( (channel==0 && mmtrig==1 && mmtrig_match) || (channel==1 && eetrig==1 && eetrig_match) )  && DPhi_METJetLeading > 0.4 && DPhi_METJetSecond > 0.4 && MET > 200  && HT>700 && lep_n>=2 && jet_n>1 )  ") );

    regions.push_back(std::make_pair("SRZ", "(mll>81 && mll<101 && is_OS==1  && lep_pT[0] > 50 && lep_pT[1] > 25 && ( (channel==0 && mmtrig==1 && mmtrig_match) || (channel==1 && eetrig==1 && eetrig_match) )  && DPhi_METJetLeading > 0.4 && DPhi_METJetSecond > 0.4 && MET > 225  && HTincl>600 && lep_n>=2 && jet_n>1 )  ") );

    regions.push_back(std::make_pair("CRT", "( (mll<81|| mll>101) && is_OS==1  && lep_pT[0] > 50 && lep_pT[1] > 25 && ( (channel==0 && mmtrig==1 && mmtrig_match) || (channel==1 && eetrig==1 && eetrig_match) )  && DPhi_METJetLeading > 0.4 && DPhi_METJetSecond > 0.4 && MET > 225  && HTincl>600 && lep_n>=2 && jet_n>1 )  ") );
    

    
    regions.push_back(std::make_pair("CRFS", " ((channel == 2 || channel==3) && emtrig==1 && emtrig_match&&  lep_pT[0]>50 && lep_pT[1]>25 && jet_n>1 && mll>45 && is_OS && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET>225 &&    HTincl>600 && mll>61 && mll<121)"));
    regions.push_back(std::make_pair("VRFS", "((channel == 2 || channel==3) && emtrig==1 && emtrig_match && lep_pT[0]>50 && lep_pT[1]>25 && jet_n>1 && mll>45 && is_OS && DPhi_METJetLeading>0.4 && DPhi_METJetSecond>0.4 && MET>100 &&    MET<200 && HTincl>600 && mll>61 && mll<121)"));
                    

    regions.push_back(std::make_pair("VRS", "(mll>81 && mll<101 && is_OS==1  && lep_pT[0] > 50 && lep_pT[1] > 25 && ( (channel==0 && mmtrig==1 && mmtrig_match) || (channel==1 && eetrig==1 && eetrig_match) )  && DPhi_METJetLeading > 0.4 && DPhi_METJetSecond > 0.4 && MET > 100 && MET<200  && HTincl>600 && lep_n>=2 && jet_n>1 )  ") );

    regions.push_back(std::make_pair("VRT", "( (mll<81|| mll>101) && is_OS==1  && lep_pT[0] > 50 && lep_pT[1] > 25 && ( (channel==0 && mmtrig==1 && mmtrig_match) || (channel==1 && eetrig==1 && eetrig_match) )  && DPhi_METJetLeading > 0.4 && DPhi_METJetSecond > 0.4 && MET > 100 && MET < 200  && HTincl>600 && lep_n>=2 && jet_n>1 )  ") );



    // output
    std::vector<double> nominal_yields;
    std::vector<double> sumSqr_regions_up;
    std::vector<double> sumSqr_regions_down;

    TH1F * htemp = new TH1F("htemp","htemp",1,-5,5);
    cout << std::fixed;
    cout << std::setprecision(2);

    cout <<"Variation & ";
    for (size_t i = 0; i < regions.size(); i++) {
        cout << regions[i].first<< " & ";
    }
    cout<<"\\\\"<<endl;

    for (size_t var = 0; var < weight_variation.size(); var++)
    {
        cout<<weight_variation[var].first<<" & ";
        for (size_t reg = 0; reg < regions.size(); reg++) {
            htemp->Reset();
            tree->Draw("1.>>htemp",weight_variation[var].second + " * " + regions[reg].second);

            double yield = htemp->Integral();

            if (var==0)
            {
                nominal_yields.push_back( yield );
                sumSqr_regions_up.push_back(0.);
                sumSqr_regions_down.push_back(0.);
            }
            if (var !=0 )
            {
                if ( (nominal_yields[reg] - yield) < 0)   sumSqr_regions_up[reg]   += pow(nominal_yields[reg] - yield,2);
                else                                   sumSqr_regions_down[reg] += pow(nominal_yields[reg] - yield,2);
            }

            cout<< yield << " & ";


        }
        cout<<" \\\\"<<endl;
    }


    cout <<"Total Sys & ";
    for (size_t i = 0; i < regions.size(); i++) {
        cout << "+"<<sqrt(sumSqr_regions_up[i]) << " -"<<sqrt(sumSqr_regions_down[i])  << " & ";
    }
    cout << "\\\\"<<endl;

}
