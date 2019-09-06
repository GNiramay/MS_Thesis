// program to overlay nevts vs ss for data and MC

void MakeItOne(TH1F* h, int col);
// TGraph* MakeItOne(TH1F*);

void CheckNevts()
{
  gStyle->SetOptStat(kFALSE);
  TFile* tf1 = new TFile("CERN_Root_Files/All_200.root");   // Data
  TFile* tf2 = new TFile("../MyCheckLeakage/TempOut.root"); // MC
  TLegend* tl = new TLegend(0.8,0.8,0.9,0.9);
  TCanvas* tc = new TCanvas("aa","b",800,600);

  TH1F* hh1 = (TH1F*)tf1->Get("h_shower_start");
  TH1F* hh2 = (TH1F*)tf2->Get("h_shower_start");
  
  hh1->GetYaxis()->SetTitle("Frequency (in arbitrary units)");
  hh2->GetYaxis()->SetTitle("Frequency (in arbitrary units)");
  hh2->SetTitle("HGCal event statistics | Pion 200");

  MakeItOne(hh1,1);
  MakeItOne(hh2,2);

  tl->AddEntry(hh1,"Data","l");
  tl->AddEntry(hh2,"Simulation","l");
  
  // tc->SetLogy();
  hh2->Draw("E");
  hh1->Draw("E same");
  tl->Draw();
  tc->SaveAs("PNG/Nevts_SS.png");
  tc->SaveAs("PDF/Nevts_SS.pdf");
}

void MakeItOne(TH1F* h, int col)
{
  Double_t EE = h->GetEntries();
  h->Scale(1/EE);
  h->SetLineColor(col);
  h->SetMarkerStyle(21);
  h->SetMarkerSize(0.25);
  h->SetMarkerColor(col);
  // h->SetLineWidth(0);
}
