// To Analyse transverse leakage
char* InF = new char[400];

void EE_FH_Compare()
{
  sprintf(InF,"../MyCheckLeakage/TempOut.root");
  
  TFile* tf = new TFile(InF);
  gStyle->SetOptStat(0);

  for(int i=0;i<40;i++){
  // for(int i=0;i<1;i++){
    TCanvas* tc = new TCanvas("aa","bb",800,600);
    char* htitle = new char[200];
    sprintf(htitle,"WtComp_%i",i+1);
    TH2F* HH = (TH2F*)tf->Get(htitle);

    // HH->SetTitle("Pion 200 GeV - Simulation");
    HH->GetYaxis()->SetTickLength(0.01);
    HH->Draw("colz");
    HH->GetXaxis()->SetTitle("En_{EE}");
    // HH->GetYaxis()->SetTitle("#beta En_{FH}");
    HH->GetYaxis()->SetTitleOffset(1.7);
    // HH->GetYaxis()->SetRangeUser(0,600);
    // // HH->GetXaxis()->SetRangeUser(0,100);
    TString ll;
    ll.Form("%i",i);
    tc->SaveAs("PNG/WtComp/Layer_"+ll+".png");
    tc->SaveAs("PDF/WtComp/Layer_"+ll+".pdf");
    delete tc;
  }
}
