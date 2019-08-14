// Script to create plot images directly from the histograms in the root file
// Input: prop : character string defining name of the histogram
// input: lmin : integer defining minimum index of the histogram layer
// input: lmax : integer defining maximum index of the histogram layer
// imupt: dim  : to specify whether it is 1D or 2D hist

// Example1 :
// If you want to plot GoodStat_1,GoodStat_2,GoodStat_3 2D histograms,
// You will use the function as :
// MakeGoodPlots("GoodStat_",1,3,2);

// Example2 :
// If you want to plot only one histogram say WtEn_0,
// You will use the function as :
// MakeGoodPlots("WtEn_0");


void OneDPlot(TH*);

void MakeGoodPlots(char* prop,int lmin=-1,int lmax=-1,int dim=1)
{
  TCanvas* tc =new TCanvas("aaa","bbb",800,600);
  TFile* tf = new TFile("../MyCheckLeakage/TempOut.root");
  if(lmin==-1){
    auto HH = tf->Get(prop);
    if(dim==2) hh->Draw("colz");
    tc->SaveAs("TEMPIMAGE.png");
  }
}
