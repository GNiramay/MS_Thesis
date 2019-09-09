
void TempAbs()
{
  TFile* tf = new TFile("../MyCheckLeakage/TempOut.root");
  TCanvas* tc = new TCanvas();
  TString HH[6] = {"1","2","3","4","5","6"}; // the index needed for following hists
  TH1F* hst[6];
  for(int i=0;i<6;i++){
    hst[i] = (TH1F*)tf->Get("Sum_Abs_"+HH[i]);
    hst[i]->SetLineColor(i+1);
    hst[i]->Draw("hist same");
  }

  //     hst[0]->Draw("hist same");
  //     hst[1]->Draw("hist same");
  //     hst[2]->Draw("hist same");
  //     hst[3]->Draw("hist same");
  //     hst[4]->Draw("hist same");
  //     hst[5]->Draw("hist same");

}
