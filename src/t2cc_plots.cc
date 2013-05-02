{

  gROOT->Reset();
  
  TFile* f = new TFile("T2ccNoFilter_Total.root");
  TTree* tree = (TTree*)f->Get("outTree");

  tree->SetBranchStatus("*",0);//Deactivate all branches (increase speed)
  tree->SetBranchStatus("mssm",1);//Activating only mssm brach

  float mssm[3];

  tree->SetBranchAddress("mssm", mssm);

  long Nentries = tree->GetEntriesFast();

  std::cout << "N Entries:  " << Nentries << std::endl;
  
  for(long i = 0; i < Nentries; i++){

    tree->GetEntry(i);
    std::cout << mssm[0] << " " << mssm[1] << std::endl; 
    
    
  }

}
