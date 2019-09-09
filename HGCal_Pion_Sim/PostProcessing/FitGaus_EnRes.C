double Find_EnRes(TH1F*,int,TString);
double Res1,Res2,Res3,Res4;

TString HH[6] = {"1","2","3","4","5","6"};
TString DD[6]={"0 to 0.35","0.35 to 0.78","0.78 to 1.12","1.12 to 1.8","1.8 to 2.7","more than 2.7",};// New depth of each compartment
TString energy = "200";

TString DATE = "09_09_19";
TString PATH_WWW="/afs/cern.ch/user/n/ngogate/www/PionShower/EnRes_Fit_"+DATE+"/";

void FitGaus_EnRes()
{
  // printf("Mean\tSigma\n");
  gStyle->SetOptFit(1111);

  TFile* tf1 = new TFile("../MyCheckLeakage/TempOut.root");
  TFile* tf2 = new TFile("CERN_Root_Files/All_200.root");

  for(int i=0;i<6;i++){

    TH1F* ABS1 = (TH1F*)tf1->Get("Sum_Abs_"+HH[i]);
    TH1F* LIK1 = (TH1F*)tf1->Get("Sum_Abs_Leak_"+HH[i]);
    TH1F* WGT1 = (TH1F*)tf1->Get("RecEn_"+HH[i]);
    TH1F* DAT1 = (TH1F*)tf2->Get("RecEn_"+HH[i]);

    ABS1->SetTitle("Total absorber energy | Compartment "+HH[i]+" | Pion "+energy+" GeV");
    LIK1->SetTitle("Absorber + leakage | Compartment "+HH[i]+" | Pion "+energy+" GeV");
    WGT1->SetTitle("Weighted rechit energy (Sim) | Compartment "+HH[i]+" | Pion "+energy+" GeV");
    DAT1->SetTitle("Weighted rechit energy (Data) | Compartment "+HH[i]+" | Pion "+energy+" GeV");

    Res1 = Find_EnRes(ABS1,i,"Absorb");
    Res2 = Find_EnRes(LIK1,i,"AbsLeak");
    Res3 = Find_EnRes(WGT1,i,"RecoSim");
    Res4 = Find_EnRes(DAT1,i,"RecoDat");
  }

  // gSystem->Exec("scp PNG/FitGaus_EnRes/Comp_*_"+DATE+".png ngogate@lxplus7.cern.ch:"+PATH_WWW);

}

double Find_EnRes(TH1F* hh,int ii,TString METH)
{
  Double_t hmean = hh->GetMean();
  Double_t hsgm = hh->GetStdDev();
  Double_t rng = 2;
  TCanvas* tcc = new TCanvas("AA","BB",800,600);

  TFitResultPtr rr2 = hh->Fit("gaus","SQR","",hmean-1.5*hsgm,hmean+1*hsgm);

  double MEAN=rr2->Parameter(1);
  double SIGMA=rr2->Parameter(2);
  // printf("%f\t%f\n",MEAN,SIGMA);
  // if(METH=="RecoSim") hh->SetTitle("Sim Energy Reconstruction | SS at depth "+DD[ii]+" #lambda");
  // else if(METH=="RecoDat") hh->SetTitle("Data Energy Reconstruction | SS at depth "+DD[ii]+" #lambda");
  tcc->SaveAs("PNG/FitGaus_EnRes/Comp_"+HH[ii]+"_"+METH+"_"+DATE+".png");
  tcc->SaveAs("PDF/FitGaus_EnRes/Comp_"+HH[ii]+"_"+METH+"_"+DATE+".pdf");
  // cout<<"PNG/FitGaus_EnRes/Comp_"+HH[ii]+"_"+METH+"_"+DATE+".png"<<endl;
  delete tcc;

  return(SIGMA/MEAN);
}
