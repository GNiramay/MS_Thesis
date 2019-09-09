// Program to calculate energy resolution for different cases
// The output will be printed on the screen
// since there is only one one graph to be fitted for the 
// whole detector

// The Output will compatible with HTML table format 

double Find_EnRes(TH1F*,int);
double Res1,Res2,Res3,Res4;

void TotRMS_MEAN()
{
  TFile* tf1 = new TFile("../MyCheckLeakage/TempOut.root");
  TFile* tf2 = new TFile("CERN_Root_Files/All_200.root");
  TLegend* tl = new TLegend(0.1,0.7,0.35,0.9);
  TCanvas* tc = new TCanvas("aa","bb",800,600);

  TH1F* ABS1 = (TH1F*)tf1->Get("TotSum_Abs");
  TH1F* LIK1 = (TH1F*)tf1->Get("TotSum_Abs_Leak");
  TH1F* WGT1 = (TH1F*)tf1->Get("TotRecEn");
  TH1F* DAT1 = (TH1F*)tf2->Get("TotRecEn");

  Res1 = Find_EnRes(ABS1,1);
  Res2 = Find_EnRes(LIK1,1);
  Res3 = Find_EnRes(WGT1,1);
  Res4 = Find_EnRes(DAT1,1);

  printf("<tr><td> Method <td> Energy Reslution\n");
  printf("<tr><td>Absorber Energy<td> %.2f\n",Res1);
  printf("<tr><td>E_Abs+ Trans. Leakage<td> %.2f\n",Res2);
  printf("<tr><td>Weighted rechit energy (sim)<td> %.2f\n",Res3);
  printf("<tr><td>Weighted rechit energy (Data)<td> %.2f\n",Res4);
}

double Find_EnRes(TH1F* HH,int ii)
{
  Double_t hmean = HH->GetMean();
  Double_t hsgm = HH->GetStdDev();
  return(hsgm/hmean);
}
