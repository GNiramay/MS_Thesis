// Program to plot histograms of  given property
void Pretty1(TH1F*);
void Pretty2(TH2F*);


// void JustPlotIt(TString Prop, int dim=1)
TCanvas* JustPlotIt(TString Prop, int dim=1)
{
  TFile* tf = new TFile("../MyCheckLeakage/TempOut.root");
  TCanvas* tc = new TCanvas("aa","bb",900,600);

  if(dim==1)
    {
      auto HH = (TH1F*)tf->Get(Prop);
      Pretty1(HH);
      HH->Draw();  
    }  
  else if(dim==2)
    {
      gStyle->SetStatX(0.9);
      gStyle->SetStatY(0.9);
      gStyle->SetStatH(0.2);

      auto HH = (TH2F*)tf->Get(Prop);
      Pretty2(HH);
      HH->Draw("colz");  

      gPad->Update();
      TPaveStats* st1 = (TPaveStats*)HH->FindObject("stats");
      HH->SetLineColor(3);
    }
  return(tc);
}

void Pretty1(TH1F* h)
{
  cout<<"HAha lol";
}

void Pretty2(TH2F* h)
{
  h->GetYaxis()->SetTitleSize(0.03);
  h->GetYaxis()->SetTitleOffset(1.5);
}
