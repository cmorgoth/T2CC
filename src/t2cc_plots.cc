#include <iostream>

#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TROOT.h"
#include "TCanvas.h"
#include <map>
#include <vector>
#include <utility>


int main(){
  
  gROOT->Reset();
  
  TFile* f = new TFile("/media/data/Documents/cmorgoth/caltech/CERN/DM/Data/T2ccNoFilter_Total.root");
  TTree* tree = (TTree*)f->Get("outTree");
  
  tree->SetBranchStatus("*",0);//Deactivate all branches (increase speed)
  tree->SetBranchStatus("mssm",1);//Activating only mssm brach
  
  float mssm[3];

  tree->SetBranchAddress("mssm", mssm);
  
  
  long Nentries = tree->GetEntriesFast();
  
  std::cout << "N Entries:  " << Nentries << std::endl;
  
  
  //std::vector< std::pair <float,float> > vec;
  std::map<std::pair <float,float>, int> map1;
  
  for(long i = 0; i < Nentries; i++){
    
    tree->GetEntry(i);
    std::pair <float, float> pair1 (mssm[0], mssm[1]);
    map1[pair1]++;
    //    std::cout << mssm[0] << " " << mssm[1] << std::endl; 
    
    
  }
  
  std::map<std::pair <float,float>, int>::iterator it1;
  std::map<std::pair <float,float>, int>::iterator it2;
  
  int ctr = 0;
  TH2F* h2 = new TH2F("h2", "NEvents", 60, 10, 260, 60, 80, 280);
  TCanvas* c = new TCanvas("c","c", 640, 640);
  
  for(it2 = map1.begin(); it2 != map1.end(); ++it2){
    std::cout << "(" << it2->first.first << ", " <<  it2->first.second << ")" <<  " => " << it2->second << '\n';
    h2->Fill(it2->first.second, it2->first.first, it2->second);
    ctr++;
  }

  c->cd();
  h2->SetTitle("");
  h2->SetStats(0);
  h2->SetXTitle("m_{#chi}");
  h2->SetYTitle("m_{#tilde{t}}");
  h2->Draw("colztext45");
  c->SaveAs("nentries_2d.pdf");
  c->SaveAs("nentries_2d.png");
  return 0;

}
