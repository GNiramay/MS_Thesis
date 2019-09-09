// To overlay total EE and FH rechit energy sum
void FixtheStats(TCanvas*,TH1F*,Double_t,Double_t,int);
TString DATE = "06_09_19";
void RawEn()
{
  TFile* tf = new TFile("../MyCheckLeakage/TempOut.root");
  TString HH[6] = {"1","2","3","4","5","6"}; // the index needed for following hists
  gStyle->SetOptStat(1111);
  gStyle->SetStatX(0.9);

  // for(int i=0;i<6;i++)
  for(int i=0;i<4;i++)
    {
      TCanvas* tc = new TCanvas("aa","bb",800,600);
      TLegend* tl = new TLegend(0.8,0.8,0.9,0.9);

      TH1F* H1 = (TH1F*)tf->Get("EnEE_"+HH[i]);
      TH1F* H2 = (TH1F*)tf->Get("EnFH_"+HH[i]);

      H1->SetName("rechit_energy_EE");
      H2->SetName("#beta*rechit_energy_FH");

      tl->AddEntry(H1,"EE","l");
      tl->AddEntry(H2,"FH","l");

      Double_t m1 = H1->GetBinContent(H1->GetMaximumBin());
      Double_t m2 = H2->GetBinContent(H2->GetMaximumBin());

      if(m1>m2){
	// H1->Draw("hist same");H2->Draw("hist same");
	FixtheStats(tc,H1,0.75,0.9,2);
	H1->SetTitle("Total weighted rechit energy | Compartment "+HH[i]+" | 200 GeV Pion (Sim)");
	FixtheStats(tc,H2,0.6,0.75,4);
      }

      else{
	// H2->Draw("hist same");H1->Draw("hist same");
	FixtheStats(tc,H2,0.6,0.75,4);
	H2->SetTitle("Total weighted rechit energy | Compartment "+HH[i]+" | 200 GeV Pion (Sim)");
	FixtheStats(tc,H1,0.75,0.9,2);
      }
      tc->SaveAs("PNG/RawEn/EE_BFH_raw_Comp"+HH[i]+"_"+DATE+".png");
      tc->SaveAs("PDF/RawEn/EE_BFH_raw_Comp"+HH[i]+"_"+DATE+".pdf");
      // tl->Draw();
      delete tc;
    }

}

void FixtheStats(TCanvas* tc,TH1F* HIST,Double_t ymin,Double_t ymax,int col)
{
  HIST->Draw("hist sames");
  HIST->SetLineColor(col);HIST->SetLineWidth(2);
  gPad->Update();
  TPaveStats* st1 = (TPaveStats*)HIST->FindObject("stats");
  st1->SetTextColor(col);
  st1->SetY1NDC(ymin);
  st1->SetY2NDC(ymax);
  tc->Modified();
}
