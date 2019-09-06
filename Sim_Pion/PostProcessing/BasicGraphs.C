// program to plot sim energy graphs
TString DATE = "02_09_19";
bool IsLog = true;

void BasicGraphs()
{
  gStyle->SetOptStat(0);
  TFile* tf = new TFile("../MyCheckLeakage/AAAA.root");
  TCanvas* tc = new TCanvas("aa","bb",800,600);
  TLegend* tl;
  if(IsLog) tl = new TLegend(0.29,0.65,0.54,0.9);
  else tl = new TLegend(0.65,0.65,0.9,0.9);
  
  TH1F* H1 = (TH1F*)tf->Get("h_Eabs");
  TH1F* H2 = (TH1F*)tf->Get("h_TLEak");
  TH1F* H3 = (TH1F*)tf->Get("h_LLeak");
  TH1F* H4 = (TH1F*)tf->Get("h_TotSim");

  H1->SetLineColor(1);
  H2->SetLineColor(2);
  H3->SetLineColor(6);
  H4->SetLineColor(4);

  H1->SetLineWidth(2);
  H2->SetLineWidth(2);
  H3->SetLineWidth(2);
  H4->SetLineWidth(2);

  tl->AddEntry(H3,"Longitudinal Leakage","l");
  tl->AddEntry(H2,"Transverse Leakage","l");
  tl->AddEntry(H1,"Absorber Energy","l");
  tl->AddEntry(H4,"Absorber + Leakage","l");

  H3->GetXaxis()->SetRange(0,220);
  H3->GetXaxis()->SetTitle("Pion Energy (in GeV)");
  H3->GetYaxis()->SetTitle("No. of events");
  H3->GetYaxis()->SetTitleOffset(1.5);
  H3->SetTitle("HGCal simulation | 200 GeV Pion");

  H3->Draw("hist same");
  H1->Draw("hist same");
  H2->Draw("hist same");
  H4->Draw("hist same");
  
  tl->Draw();

  if(IsLog){
    tc->SetLogy();
    tc->SaveAs("PNG/SimEn_"+DATE+"_logy.png");
    tc->SaveAs("PDF/SimEn_"+DATE+"_logy.pdf");
  }
  else{
    tc->SaveAs("PNG/SimEn_"+DATE+".png");
    tc->SaveAs("PDF/SimEn_"+DATE+".pdf");
  }

}
