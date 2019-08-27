double Find_EnRes(TH1F*,int);
double Res1,Res2,Res3,Res4;
TString HH[6] = {"1","2","3","4","5","6"};

void FitGaus_EnRes()
{
  printf("Mean\tSigma\n");
  gStyle->SetOptFit(1111);
  TFile* tf2 = new TFile("CERN_Root_Files/All_200.root");

  for(int i=0;i<6;i++){
    TH1F* DAT1 = (TH1F*)tf2->Get("RecEn_"+HH[i]);
    Res4 = Find_EnRes(DAT1,i);
  }
}

double Find_EnRes(TH1F* hh,int ii)
{
  Double_t hmean = hh->GetMean();
  Double_t hsgm = hh->GetStdDev();
  Double_t rng = 2;
  TCanvas* tcc = new TCanvas("AA","BB",800,600);

  TFitResultPtr rr2 = hh->Fit("gaus","SQR","",hmean-rng*hsgm,hmean+rng*hsgm);
  // TFitResultPtr rr2 = hh->Fit("gaus","SQR","",hmean-1.25*rng*hsgm,hmean+0.75*rng*hsgm);

  double MEAN=rr2->Parameter(1);
  double SIGMA=rr2->Parameter(2);
  printf("%f\t%f\n",MEAN,SIGMA);

  tcc->SaveAs("PNG/FitGaus_EnRes/Comp_"+HH[ii]+"_24_08_19.png");
  tcc->SaveAs("PDF/FitGaus_EnRes/Comp_"+HH[ii]+"_24_08_19.pdf");
  delete tcc;

  return(SIGMA/MEAN);
}
