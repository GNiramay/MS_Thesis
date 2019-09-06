// Program to overlay 3 plots of energy reconstruction

TString DATE = "31_08_19";
TString PATH_WWW="/afs/cern.ch/user/n/ngogate/www/PionShower/EnRes_Comp_"+DATE+"/";

bool DoShift =false;

void ShiftIt(TH1F*);

void TotReco_En()
{
  int ENERGY=200;
  TString energy = "200";
  gStyle->SetOptStat(11111);
  gStyle->SetStatX(0.9);
  gStyle->SetStatH(0.8);

  TFile* tf1 = new TFile("../MyCheckLeakage/TempOut.root");
  TFile* tf2 = new TFile("CERN_Root_Files/All_200.root");
  TLegend* tl;

  for(int i=0;i<1;i++){
    if(DoShift){
      // TLegend* tl = new TLegend(0.1,0.6,0.45,0.9);
      tl = new TLegend(0.1,0.6,0.45,0.9);
      tl->SetTextSize(0.025);
    }
    else{
      // TLegend* tl = new TLegend(0.1,0.6,0.4,0.9);
      tl = new TLegend(0.1,0.6,0.4,0.9);
      tl->SetTextSize(0.023);
    }

    TCanvas* tc = new TCanvas("aa","bb",800,600);
      
    TH1F* ABS = (TH1F*)tf1->Get("TotSum_Abs");
    TH1F* LIK = (TH1F*)tf1->Get("TotSum_Abs_Leak");
    TH1F* WGT = (TH1F*)tf1->Get("TotRecEn");
    TH1F* DAT = (TH1F*)tf2->Get("TotRecEn");
      
    if(DoShift)
      {
	LIK->Scale(1/LIK->GetEntries());
	ABS->Scale(1/ABS->GetEntries());
	WGT->Scale(1/WGT->GetEntries());
	DAT->Scale(1/DAT->GetEntries());
      
	ShiftIt(ABS);
	ShiftIt(LIK);
	ShiftIt(WGT);
	ShiftIt(DAT);
      }
    LIK->GetYaxis()->SetTitleOffset(1.3);
    LIK->GetXaxis()->SetTitle("Energy (in GeV)");
    LIK->GetYaxis()->SetTitle("Frequency (in arbitrary unit)");
    if(DoShift) LIK->SetTitle("HGCal Energy Response (Inclusive) | Pion 200 GeV ");
    else LIK->SetTitle("HGCal Energy Response (Inclusive) unshifted| Pion 200 GeV ");
  
    ABS->SetLineWidth(2);
    LIK->SetLineWidth(2);
    WGT->SetLineWidth(2);
    DAT->SetLineWidth(2);

    LIK->Draw("hist");
    gPad->Update();
    TPaveStats* st1 = (TPaveStats*)LIK->FindObject("stats");
    LIK->SetLineColor(3);
    st1->SetTextColor(3);
    st1->SetY1NDC(0.75);
    st1->SetY2NDC(0.9);
    tc->Modified();

    ABS->Draw("hist sames");
    gPad->Update();
    TPaveStats* st2 = (TPaveStats*)ABS->FindObject("stats");
    st2->SetY1NDC(0.6);
    st2->SetY2NDC(0.75);
    ABS->SetLineColor(2);
    st2->SetTextColor(2);
    tc->Modified();

    WGT->Draw("hist sames");
    gPad->Update();
    TPaveStats* st3 = (TPaveStats*)WGT->FindObject("stats");
    st3->SetY1NDC(0.45);
    st3->SetY2NDC(0.6);
    WGT->SetLineColor(4); 
    st3->SetTextColor(4);
    tc->Modified();

    DAT->Draw("hist sames");
    gPad->Update();
    TPaveStats* st4 = (TPaveStats*)DAT->FindObject("stats");
    st4->SetY1NDC(0.3);
    st4->SetY2NDC(0.45);
    DAT->SetLineColor(1);
    st4->SetTextColor(1);
    tc->Modified();

    tl->AddEntry(DAT,"Weighted #Sigma rechit_energy (Data)","l");
    tl->AddEntry(WGT,"Weighted #Sigma rechit_energy (Sim)","l");
    tl->AddEntry(ABS,"Total Energy in absorbers","l");
    tl->AddEntry(LIK,"E_abs + Trans. Leakage","l");

    tl->Draw();
    tc->Update();

    if(DoShift){
      tc->SaveAs("PNG/RecoEn/Pion_"+energy+"_RecEn_Inc_"+DATE+".png");
      tc->SaveAs("PDF/RecoEn/Pion_"+energy+"_RecEn_Inc_"+DATE+".pdf");
    }
    else{
      tc->SaveAs("PNG/RecoEn/Pion_"+energy+"_RecEn_Inc_"+DATE+"_unshift.png");
      tc->SaveAs("PDF/RecoEn/Pion_"+energy+"_RecEn_Inc_"+DATE+"_unshift.pdf");
    }

  }
  
  if(DoShift) gSystem->Exec("scp PNG/RecoEn/Pion_"+energy+"_RecEn_Inc_"+DATE+".png  ngogate@lxplus7.cern.ch:"+PATH_WWW);
  else gSystem->Exec("scp PNG/RecoEn/Pion_"+energy+"_RecEn_Inc_"+DATE+"_unshift.png  ngogate@lxplus7.cern.ch:"+PATH_WWW);
}

void ShiftIt(TH1F* h)
{
  // Double_t MM = h->GetMean();
  Double_t MM = h->GetXaxis()->GetBinCenter(h->GetMaximumBin());
  int NN = h->GetNbinsX();
  Double_t EE = h->GetEntries();

  vector<Double_t> xx,yy;

  for(int i=0;i<NN;i++){
    xx.push_back(h->GetBinCenter(i));
    yy.push_back(h->GetBinContent(i));
    h->SetBinContent(i,0);
  }

  for(int i=0;i<NN;i++){
    h->Fill(xx[i]+200-MM,yy[i]);
  }
  h->ResetStats();
  Double_t norm = h->GetEntries();
  // h->Scale(1/norm);
  h->SetEntries(EE);
}
