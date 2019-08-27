// Program to overlay 3 plots of energy reconstruction

TString DATE = "27_08_19";
// TString PATH_WWW="/afs/cern.ch/user/n/ngogate/www/PionShower/EnRes_Comp_26_08_19/";
TString PATH_WWW="/afs/cern.ch/user/n/ngogate/www/PionShower/EnRes_Comp_"+DATE+"/";

void ShiftIt(TH1F*);

void Reco_En()
{
  int ENERGY=200;
  TString energy = "200";
  gStyle->SetOptStat(11111);
  gStyle->SetStatX(0.9);
  gStyle->SetStatH(0.8);

  TFile* tf1 = new TFile("../MyCheckLeakage/TempOut.root");
  TFile* tf2 = new TFile("CERN_Root_Files/All_200.root");

  TString HH[6] = {"1","2","3","4","5","6"}; // the index needed for following hists
  TString DD[6]={"0 to 0.35","0.35 to 0.75","0.75 to 1.03","1.03 to 1.43","1.43 to 2.7","more than 2.7"};// The depth of each compartment

  // for(int i=0;i<1;i++)
  for(int i=0;i<6;i++)
    {

      TLegend* tl = new TLegend(0.1,0.6,0.45,0.9);
      tl->SetTextSize(0.025);

      TCanvas* tc = new TCanvas("aa","bb",800,600);
      
      TH1F* ABS = (TH1F*)tf1->Get("Sum_Abs_"+HH[i]);
      TH1F* LIK = (TH1F*)tf1->Get("Sum_Abs_Leak_"+HH[i]);
      TH1F* WGT = (TH1F*)tf1->Get("RecEn_"+HH[i]);
      TH1F* DAT = (TH1F*)tf2->Get("RecEn_"+HH[i]);

      LIK->Scale(1/LIK->GetEntries());
      ABS->Scale(1/ABS->GetEntries());
      WGT->Scale(1/WGT->GetEntries());
      DAT->Scale(1/DAT->GetEntries());
      
      ShiftIt(ABS);
      ShiftIt(LIK);
      ShiftIt(WGT);
      ShiftIt(DAT);

      LIK->GetYaxis()->SetTitleOffset(1.3);
      LIK->GetXaxis()->SetTitle("Energy (in GeV)");
      LIK->SetTitle("HGCal Energy Response | Pion 200 GeV | Compartment "+HH[i]);

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

      // TLine* ln1 = new TLine(ENERGY,0,ENERGY,tc->GetUymax());
      // ln1->SetLineStyle(9);
      // ln1->SetLineWidth(2);
      // ln1->draw("hist same");
      // tc->Update();

      tc->SaveAs("PNG/RecoEn/Pion_"+energy+"_RecEn_"+HH[i]+"_"+DATE+".png");
      tc->SaveAs("PDF/RecoEn/Pion_"+energy+"_RecEn_"+HH[i]+"_"+DATE+".pdf");

      delete tc;
    }
  gSystem->Exec("scp PNG/RecoEn/Pion_"+energy+"_RecEn_"+"*_"+DATE+".png ngogate@lxplus7.cern.ch:"+PATH_WWW);
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
    // for(int j = 0 ; j<yy[i] ; j++){h->Fill(xx[i]+200-MM);}
  }
  h->ResetStats();
  Double_t norm = h->GetEntries();
  // h->Scale(1/norm);
  // h->Scale(1/EE);
  h->SetEntries(EE);

  // Double_t MM = h->GetMean();
  // int NN = h->GetNbinsX();
  // Double_t MIN = h->GetMinimumBin();
  // Double_t MAX = h->GetMaximumBin();

  // TH1F* h2 = new TH1F("aa","bb",NNMIN,MAX);

}

// void ShiftIt(TH1F* h)
// {
//   Double_t MM = h->GetMean();
//   // Int_t NN = h->GetNbinsX();
//   int NN = h->GetNbinsX();

//   // Double_t xx[NN],yy[NN];
//   vector<Double_t> xx,yy;

//   // for(Int_t i=0;i<NN;i++){
//   for(int i=0;i<NN;i++){
//     // xx[i]=GetBinCenter(i);
//     // yy[i]=GetBinContent(i);
//     xx.push_back(h->GetBinCenter(i));
//     yy.push_back(h->GetBinContent(i));
//     h->SetBinContent(i,0);
//   }
//   // for(Int_t i=0;i<NN;i++){
//   for(int i=0;i<NN;i++){
//     h->Fill(xx[i]+200-MM,yy[i]);
//   }
//   h->ResetStats();
// }
