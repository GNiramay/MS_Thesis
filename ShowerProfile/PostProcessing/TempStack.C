void MyPlot(TString en);
void TempStack()
{
  gStyle->SetOptStat(0);
  // MyPlot("50");
  MyPlot("200");
}

void MyPlot(TString en)
{
  TCanvas* tc =new TCanvas("aaa","Rechits energy distribution ("+en+" GeV)",800,600);
  // TFile* tf = new TFile("../New_All_"+en+".root");
  TFile* tf = new TFile("../MyCheckLeakage/TempOut.root");

  // TH1F* h1=(TH1F*)tf->Get("RecEn_1");
  // TH1F* h2=(TH1F*)tf->Get("RecEn_13");
  // TH1F* h3=(TH1F*)tf->Get("RecEn_27");
  // TH1F* h4=(TH1F*)tf->Get("RecEn_29");

  TH1F* h1=(TH1F*)tf->Get("RecEn_2");
  TH1F* h2=(TH1F*)tf->Get("RecEn_14");
  TH1F* h3=(TH1F*)tf->Get("RecEn_28");
  TH1F* h4=(TH1F*)tf->Get("RecEn_30");

  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h3->SetLineColor(3);
  h4->SetLineColor(4);

  h1->SetTitle("Pion "+en+" GeV - Simulation");
  h2->SetTitle("Pion "+en+" GeV - Simulation");
  h3->SetTitle("Pion "+en+" GeV - Simulation");
  h4->SetTitle("Pion "+en+" GeV - Simulation");
  tc->SetTitle("Pion "+en+" GeV - Simulation");

  h1->GetXaxis()->SetTitle("Total rechits energy (EE + FH)");
  h2->GetXaxis()->SetTitle("Total rechits energy (EE + FH)");
  h3->GetXaxis()->SetTitle("Total rechits energy (EE + FH)");
  h4->GetXaxis()->SetTitle("Total rechits energy (EE + FH)");

  h1->GetYaxis()->SetTitle("No. of events");
  h2->GetYaxis()->SetTitle("No. of events");
  h3->GetYaxis()->SetTitle("No. of events");
  h4->GetYaxis()->SetTitle("No. of events");

  h1->GetYaxis()->SetTitleOffset(1.2);
  h2->GetYaxis()->SetTitleOffset(1.2);
  h3->GetYaxis()->SetTitleOffset(1.2);
  h4->GetYaxis()->SetTitleOffset(1.2);

  h4->Draw("hist same");
  h1->Draw("hist same");
  h2->Draw("hist same");
  h3->Draw("hist same");
  
  TLegend* tl = new TLegend(0.7,0.6,0.9,0.9);
  tl->AddEntry(h1,"EE 2","f");
  tl->AddEntry(h2,"EE 14","f");
  tl->AddEntry(h3,"EE 28","f");
  tl->AddEntry(h4,"FH 2","f");

  tl->Draw();
  tc->SaveAs("RecEn_"+en+".png");
  delete tc;
}
