// To find correlation between total transverse leakage and total absorbed energy

void AbsLeakCorr()
{
  TFile* tf = new TFile("../MyCheckLeakage/TempOut.root");
  TString HH[6] = {"1","2","3","4","5","6"}; // the index needed for following hists

  for(int i=0;i<6;i++){
    TH1F* h1 = (TH1F*)tf->Get("TrLeakEE_"+HH[i]);
    TH1F* h1 = (TH1F*)tf->Get("TrLeakEE_"+HH[i]);
  }

}

double FindCorr(TH1F* h1,TH1F* h2)
{
  Int_t NN = h1->GetEntries();
  double rho = 0;
  double S1 = h1->

  for(int i=0;i<NN;i++){
    x
  }
}
