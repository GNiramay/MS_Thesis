// 1D leakage plots
#include "JustPlotIt.C"

TString DATE = "04_09_19";
TString PATH_WWW="/afs/cern.ch/user/n/ngogate/www/PionShower/LeakFr_Abs_"+DATE+"/";

void LeakFr1D()
{
  TString HH[6] = {"1","2","3","4","5","6"}; // the index needed for following hists
  TString DD[6]={"0 to 0.35","0.35 to 0.75","0.75 to 1.03","1.03 to 1.43","1.43 to 2.7","more than 2.7"};// The depth of each compartment
  gStyle->SetOptStat(false);

  for(int i=0;i<6;i++){
    // for(int i=0;i<1;i++){
    TFile* tf = new TFile("../MyCheckLeakage/TempOut.root");
    TCanvas* tc = new TCanvas("aa","bb",900,600);
    TLegend* tl = new TLegend(0.6,0.6,0.9,0.9);

    auto H1 = (TH1F*)tf->Get("TrLeakFrEE_"+HH[i]);
    auto H2 = (TH1F*)tf->Get("TrLeakFrFH_"+HH[i]);
    auto H3 = (TH1F*)tf->Get("TrLeakFrAH_"+HH[i]);
    auto H4 = (TH1F*)tf->Get("TotTrLeakFr_"+HH[i]);

    // void ProperRange(TH1F*,TH1F*,TH1F*,TString);
    void ProperRange(TH1F*,TH1F*,TH1F*,TH1F*,TString);
    
    H1->SetLineColor(1);
    H2->SetLineColor(2);
    H3->SetLineColor(6);
    H4->SetLineColor(3);

    H1->SetLineWidth(2);
    H2->SetLineWidth(2);
    H3->SetLineWidth(2);
    H4->SetLineWidth(2);

    tl->AddEntry(H1,"Trans Leak EE fraction","l");
    tl->AddEntry(H2,"Trans Leak FH fraction","l");
    tl->AddEntry(H3,"Trans Leak AH fraction","l");
    tl->AddEntry(H4,"Total trans leakage","l");

    // H3->SetTitle("Transverse leakage profile | compartment "+HH[i]);
    // H3->GetXaxis()->SetTitle("Leakage (in GeV)");
    // H3->GetYaxis()->SetTitle("No. of events");

    // H3->Draw("hist same");
    // H1->Draw("hist same");
    // H2->Draw("hist same");

    // ProperRange(H1,H2,H3,HH[i]);
    ProperRange(H1,H2,H3,H4,HH[i]);

    tl->Draw();

    tc->SaveAs("PNG/LeakFr1D/Leak_"+HH[i]+"_"+DATE+".png");
    tc->SaveAs("PDF/LeakFr1D/Leak_"+HH[i]+"_"+DATE+".pdf");
    delete tc;

  }
  // gSystem->Exec("scp "+DATE+".png ngogate@lxplus7.cern.ch:"+PATH_WWW);
}


void ProperRange(TH1F* H1,TH1F* H2,TH1F* H3,TH1F* H4,TString cc)
{
  vector<TH1F*>HIST; HIST.clear();
  vector<Double_t>MEAN; MEAN.clear();

  Double_t m1 = H1->GetBinContent(H1->GetMaximumBin());MEAN.push_back(m1);
  Double_t m2 = H2->GetBinContent(H2->GetMaximumBin());MEAN.push_back(m2);
  Double_t m3 = H3->GetBinContent(H3->GetMaximumBin());MEAN.push_back(m3);
  Double_t m4 = H4->GetBinContent(H4->GetMaximumBin());MEAN.push_back(m4);

  HIST.push_back(H1);
  HIST.push_back(H2);
  HIST.push_back(H3);
  HIST.push_back(H4);

  int IMAX=0;
  Double_t VMAX=m1;

  for(int i=1;i<4;i++) if(VMAX<MEAN[i]){IMAX = i;VMAX = MEAN[i];}

  HIST[IMAX]->GetXaxis()->SetTitle("Leakage (in GeV)");
  HIST[IMAX]->GetYaxis()->SetTitle("Leakage Fraction");
  HIST[IMAX]->SetTitle("Transverse Leakage fraction | Compartment "+cc+" | 200 GeV Pion (sim)");
  HIST[IMAX]->Draw("hist same");

  for(int i=0;i<4;i++){if(i!=IMAX) HIST[i]->Draw("hist same");}
}

// void ProperRange(TH1F* H1,TH1F* H2,TH1F* H3,TString cc)
// // void ProperRange()
// {
//   Double_t m1 = H1->GetBinContent(H1->GetMaximumBin());
//   Double_t m2 = H2->GetBinContent(H2->GetMaximumBin());
//   Double_t m3 = H3->GetBinContent(H3->GetMaximumBin());

//   if(m3>m2 && m3>m1){    H3->SetTitle("Transverse leakage profile | compartment "+cc);
//     H3->GetXaxis()->SetTitle("Leakage (in GeV)");
//     H3->GetYaxis()->SetTitle("No. of events");

//     H3->Draw("hist same");
//     H1->Draw("hist same");
//     H2->Draw("hist same");
//   }

//   else if(m2>m3 && m2>m1){    H2->SetTitle("Transverse leakage profile | compartment "+cc);
//     H2->GetXaxis()->SetTitle("Leakage (in GeV)");
//     H2->GetYaxis()->SetTitle("No. of events");

//     H2->Draw("hist same");
//     H1->Draw("hist same");
//     H3->Draw("hist same");
//   }

//   else{    H1->SetTitle("Transverse leakage profile | compartment "+cc);
//     H1->GetXaxis()->SetTitle("Leakage (in GeV)");
//     H1->GetYaxis()->SetTitle("No. of events");

//     H1->Draw("hist same");
//     H2->Draw("hist same");
//     H3->Draw("hist same");
//   }

// }
