/* 
ROOT macro to compare the contents of two ntuples to see if they're different
Assumptions:
  + 

Jonathan Long 
Apr 4, 2013   
*/

void compareNtuple( 
//TString ntupleOne = "HWWSkimmedNTUP_ref_tightpp.root",
//TString ntupleOne = "HWWSkimmedNTUP_ref_ttbar.root",
TString ntupleOne = "Susy_fakes/data-ntupleOutput/mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.DAOD_SUSY2.e3698_s2608_s2183_r6630_r6264_p2375_tid05892244_00.root",
TString ntupleTwo = "SusyZMETjetsOutput_20150717_125419/data-ntupleOutput/mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.DAOD_SUSY2.e3698_s2608_s2183_r6630_r6264_p2375_tid05892244_00.root"
//TString ntupleTwo = "/afs/cern.ch/user/l/longjon/eos/atlas/user/l/longjon/Ntuples/v00-04/MC/410000.root"
){

    cout<<"================================="<<endl<<"This works with ROOT 5 not 6 :("<<endl<<"==========================="<<endl;

  // Settings
  int nEvents = 100;  // Number of events to loop over when checking variables
  double epsilon = 0.001; // min absolute diff
  vector<TString> variablesF;

  vector<TString> variablesI;
  variablesI.push_back("electron_n");

  vector<TString> variablesD;
  variablesD.push_back("EventWeight");

  vector<TString> variablesVecD;
  variablesVecD.push_back("electron_pT");


  vector<TString> th1dToCheck; // Shouldn't need to touch this
  th1dToCheck.push_back("EventCountHist");
  


  ////////////////////////
  TFile fileOne(ntupleOne);
  TFile fileTwo(ntupleTwo);

  cout << "N1: " << ntupleOne << endl
       << "N2: " << ntupleTwo << endl << endl;

  // Check histograms
  cout <<  "Histograms...." << endl;
  TH1D *histOne, *histTwo;
  bool flagOK;

  for (int i = 0; i < th1dToCheck.size(); i++)
  {
      histOne = (TH1D*)fileOne.Get(th1dToCheck[i]);
      histTwo = (TH1D*)fileTwo.Get(th1dToCheck[i]);

      flagOK = true;

      if (histOne == NULL) {
	cout<<th1dToCheck[i] << " bad in " << ntupleOne <<endl; continue;}
      if (histTwo == NULL) {
	cout<<th1dToCheck[i] << " bad in " << ntupleTwo <<endl; continue;}


      for (int iBin = 1; iBin < histOne->GetNbinsX(); iBin++)
      {
	 if ( fabs(histOne->GetBinContent(iBin) - histTwo->GetBinContent(iBin))  > epsilon )
	 {
	   flagOK = false;
	   cout << "Bin " << iBin << ": " << histOne->GetBinContent(iBin) << " N1 -----> N2 " << histTwo->GetBinContent(iBin) << endl;
	 }
      }
      if (flagOK)
	  cout << th1dToCheck[i] << " is the Same\n" << endl;
      else
	  cout << th1dToCheck[i] << " is Different\n" << endl;
  }

  // TTrees
  cout << "Trees...." << endl;

  TTree * tempTree1;
  TTree * tempTree2;

  float tempValue1F;
  float tempValue2F;

  int tempValue1I;
  int tempValue2I;

  double tempValue1D;
  double tempValue2D;

  vector<double> *tempValue1VecD;
  vector<double> *tempValue2VecD;




  Int_t tempEventNumber1, tempEventNumber2;

  vector<TString> treeNames;
/*  treeNames.push_back("HWWTree_ee");
  treeNames.push_back("HWWTree_em");
  treeNames.push_back("HWWTree_me");
  treeNames.push_back("HWWTree_mm");*/
  treeNames.push_back("outputTree");

  for (int z = 0; z < treeNames.size(); z++)
  {
    tempTree1 = (TTree*)fileOne.Get(treeNames[z]);
    tempTree2 = (TTree*)fileTwo.Get(treeNames[z]);

    if (tempTree1->GetEntries() != tempTree2->GetEntries())
      cout << treeNames[z] << " have a different number of entries. " << tempTree1->GetEntries() << " 1--->2 " <<  tempTree2->GetEntries() << endl;

    if (tempTree1->GetNbranches() != tempTree2->GetNbranches())
      cout << treeNames[z] << " have a different number of branches. " << tempTree1->GetNbranches() << " 1--->2 " <<  tempTree2->GetNbranches() << endl;
  }

  cout << endl;

  // loop over double variables
  for (unsigned int k = 0; k < variablesD.size(); k++)
  {
    flagOK = true;
    for (unsigned int j = 0; j < treeNames.size(); j++)
    {

      tempTree1 = (TTree*)fileOne.Get(treeNames[j]);
      tempTree2 = (TTree*)fileTwo.Get(treeNames[j]);
      
      tempTree1->SetBranchAddress("EventNumber", &tempEventNumber1);
      tempTree2->SetBranchAddress("EventNumber", &tempEventNumber2);

      tempTree1->SetBranchAddress(variablesD[k], &tempValue1D);
      tempTree2->SetBranchAddress(variablesD[k], &tempValue2D);

      for (int entry = 0; entry < nEvents && entry < tempTree1->GetEntries() && tempTree2->GetEntries(); entry++)
      {
	tempTree1->GetEntry(entry);
	tempTree2->GetEntry(entry);

	if ( TMath::Abs(tempValue1D - tempValue2D)  > epsilon)
	{
	  flagOK = false;
	  
	  if (tempEventNumber1 != tempEventNumber2)
	    cout << "EventNumbers do no match!" << endl;

	  cout << treeNames[j] << " "  << variablesD[k] << ": " << tempValue1D << " N1 ---> N2 " << tempValue2D <<endl; 
	}

      }
      
      tempTree1->ResetBranchAddresses();
      tempTree2->ResetBranchAddresses();
    }

    if (flagOK)
      cout << variablesD[k] << " is the Same\n" << endl;
    else
      cout << variablesD[k] << " is Different\n" << endl;

  }



  // loop over vector double variables
  for (unsigned int k = 0; k < variablesVecD.size(); k++)
  {
    flagOK = true;

    for (unsigned int j = 0; j < treeNames.size(); j++)
    {

      tempTree1 = (TTree*)fileOne.Get(treeNames[j]);
      tempTree2 = (TTree*)fileTwo.Get(treeNames[j]);
      
      tempTree1->SetBranchAddress("EventNumber", &tempEventNumber1);
      tempTree2->SetBranchAddress("EventNumber", &tempEventNumber2);

      tempTree1->SetBranchAddress(variablesVecD[k], &tempValue1VecD);
      tempTree2->SetBranchAddress(variablesVecD[k], &tempValue2VecD);

      for (int entry = 0; entry < nEvents && entry < tempTree1->GetEntries() && tempTree2->GetEntries(); entry++)
      {
	tempTree1->GetEntry(entry);
	tempTree2->GetEntry(entry);

	if (tempValue1VecD->size() != tempValue2VecD->size() ){ std::cout<<"Different vec size for "<<variablesVecD[k]<<std::endl; continue;}


	for (int i = 0; i<tempValue1VecD->size(); i++){



	    if ( TMath::Abs((*tempValue1VecD)[i] - (*tempValue2VecD)[i])  > epsilon) 
	    {
		flagOK = false;

		if (tempEventNumber1 != tempEventNumber2)   
		    cout << "EventNumbers do no match!" << endl;
	    
		cout << treeNames[j] << " "  << variablesVecD[k] << ": " << (*tempValue1VecD)[i] << " N1 ---> N2 " << (*tempValue2VecD)[i] <<endl;

	    }
	}

	/*if ( TMath::Abs(tempValue1VecD - tempValue2VecD)  > epsilon)
	{
	  flagOK = false;
	  
	  if (tempEventNumber1 != tempEventNumber2)
	    cout << "EventNumbers do no match!" << endl;

	  cout << treeNames[j] << " "  << variablesVecD[k] << ": " << tempValue1VecD << " N1 ---> N2 " << tempValue2VecD <<endl; 
	  }*/

      }

      tempTree1->ResetBranchAddresses();
      tempTree2->ResetBranchAddresses();
    }

    if (flagOK)
      cout << variablesVecD[k] << " is the Same\n" << endl;
    else
      cout << variablesVecD[k] << " is Different\n" << endl;

  }




  // loop over float variables

  for (unsigned int k = 0; k < variablesF.size(); k++)
  {
    flagOK = true;
    for (unsigned int j = 0; j < treeNames.size(); j++)
    {

      tempTree1 = (TTree*)fileOne.Get(treeNames[j]);
      tempTree2 = (TTree*)fileTwo.Get(treeNames[j]);
      
      tempTree1->SetBranchAddress("EventNumber", &tempEventNumber1);
      tempTree2->SetBranchAddress("EventNumber", &tempEventNumber2);

      tempTree1->SetBranchAddress(variablesF[k], &tempValue1F);
      tempTree2->SetBranchAddress(variablesF[k], &tempValue2F);

      for (int entry = 0; entry < nEvents && entry < tempTree1->GetEntries() && tempTree2->GetEntries(); entry++)
      {
	tempTree1->GetEntry(entry);
	tempTree2->GetEntry(entry);

	if ( TMath::Abs(tempValue1F - tempValue2F)  > epsilon)
	{
	  flagOK = false;

	  if (tempEventNumber1 != tempEventNumber2)
	    cout << "EventNumbers do no match!" << endl;

	  cout << treeNames[j] << " "  << variablesF[k] << ": " << tempValue1F << " N1 ---> N2 " << tempValue2F <<endl; 
	}

      }
      
      tempTree1->ResetBranchAddresses();
      tempTree2->ResetBranchAddresses();
    }

    if (flagOK)
      cout << variablesF[k] << " is the Same\n" << endl;
    else
      cout << variablesF[k] << " is Different\n" << endl;

  }


 // loop over int variables

  for (unsigned int k = 0; k < variablesI.size(); k++)
  {
    flagOK = true;
    for (unsigned int j = 0; j < treeNames.size(); j++)
    {

      tempTree1 = (TTree*)fileOne.Get(treeNames[j]);
      tempTree2 = (TTree*)fileTwo.Get(treeNames[j]);
      
      tempTree1->SetBranchAddress("EventNumber", &tempEventNumber1);
      tempTree2->SetBranchAddress("EventNumber", &tempEventNumber2);

      tempTree1->SetBranchAddress(variablesI[k], &tempValue1I);
      tempTree2->SetBranchAddress(variablesI[k], &tempValue2I);

      for (int entry = 0; entry < nEvents && entry < tempTree1->GetEntries() && tempTree2->GetEntries(); entry++)
      {
	tempTree1->GetEntry(entry);
	tempTree2->GetEntry(entry);

	if ( TMath::Abs(tempValue1I - tempValue2I)  > epsilon)
	{
	  flagOK = false;

	  if (tempEventNumber1 != tempEventNumber2)
	    cout << "EventNumbers do no match!" << endl;

	  cout << treeNames[j] << " "  << variablesI[k] << ": " << tempValue1I << " N1 ---> N2 " << tempValue2I <<endl; 
	}

      }
      
      tempTree1->ResetBranchAddresses();
      tempTree2->ResetBranchAddresses();
    }

    if (flagOK)
      cout << variablesI[k] << " is the Same\n" << endl;
    else
      cout << variablesI[k] << " is Different\n" << endl;

  }





  cout << "I'm finished!" << endl;
}
