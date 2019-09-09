// Program to overlay a single property from all the compartments

TString HH[6] = {"1","2","3","4","5","6"}; // the index needed for following hists
TFile* tf = new TFile("../MyCHeckLeakage/TempOut.root");

void OneProperty()
{
}

TCanvas* PlotIt(TString hname,TString GoodName)
{
  TH1F* hst[6];

  for(int i=0;i<6;i++){
    hst[i]  = (TH1F*)tf->Get(hname+"_"+HH[i]);
    hst[i]->SetLineColor(i+1);
  }
}
