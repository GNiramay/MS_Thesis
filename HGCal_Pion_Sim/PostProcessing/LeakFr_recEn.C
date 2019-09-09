// Program to plot total leakage fraction vs total rechit energy

void LeakFr_recEn()
{
  TFile* tf = new TFile("../MyCheckLeakage/TempOut.root");
  TCanvas* tc = new TCanvas("aa","bb",800,600);

  TH2F* EE = (TH2F*)tf->Get("Tot_Leak_Fr_EE_1");
  TH2F* FH = (TH2F*)tf->Get("Tot_Leak_Fr_FH_1");
  EE->Add(FH);
  EE->Draw("colz");
}
