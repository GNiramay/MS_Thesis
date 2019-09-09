// Program to stack energy resolution plots together to get 
// a better understanding of variation of sigma and mu.
TFile* tf;
TCanvas* tc;
TLegend* tl;

TString opng;			// Output png file name
TString opdf;			// Output pdf file name
TString DATE = "23_08_19";	// Today's date

void InitAll();			// Initialise I/O files, canvas
void PlotSigmaMean();		// Plot Sigma vs mean
double Find_EnRes(TH1F*,int);

void Data_EnRes_Stack()
{
  // gStyle->SetStatX(0.9);
  gStyle->SetStatX(0.3);
  InitAll();

  TString HH[6] = {"1","2","3","4","5","6"}; // the index needed for following hists
  Int_t  COL[6] = {1,2,3,4,5,6};
  double xx[6],yy[6];

  for(int CP=0; CP<6; CP++){
    TH1F* hh = (TH1F*)tf->Get("RecEn_"+HH[CP]);
    // hh->Draw("hist sames");
    // gPad->Update();

    // TPaveStats* st1 = (TPaveStats*)hh->FindObject("stats");
    // hh->SetLineColor(COL[CP]);
    // st1->SetTextColor(COL[CP]);
    // st1->SetY1NDC(0.8-0.1*(float)CP);
    // st1->SetY2NDC(0.9-0.1*(float)CP);

    xx[CP]=Find_EnRes(hh,1);
    yy[CP]=Find_EnRes(hh,2);
    // printf("mu : %f\t sigma : %f\n",xx[CP],yy[CP]);
    delete hh;

  }

  TGraph* tg = new TGraph(6,xx,yy);

  tg->GetXaxis()->SetTitle("#mu");
  tg->GetYaxis()->SetTitle("#sigma");
  tg->GetXaxis()->SetLimits(0,300);
  tg->GetYaxis()->SetRangeUser(0,40);

  tg->Draw("AP");
  tg->SetMarkerStyle(21);
  tg->SetMarkerSize(1);
}

void InitAll()
{
  // tf = new TFile("../MyCheckLeakage/TempOut.root");
  tf = new TFile("../MyCheckLeakage/TempOut.root");
  tc = new TCanvas("aa","bb",800,600);

  tl  = new TLegend(0.1,0.6,0.45,0.9);
  tl->SetTextSize(0.025);

  opng = "_"+DATE+".png"; 
  opdf = "_"+DATE+".pdf";
  // Use:(Eg.) tc->SaveAs("h_EnRes_3"+opng);
}

double Find_EnRes(TH1F* HH, int ii)
{
  Double_t hmean = HH->GetMean();
  Double_t hsgm = HH->GetStdDev();
  Double_t rng = 2;

  TFitResultPtr rr2 = HH->Fit("gaus","SQNR","",hmean-rng*hsgm,hmean+rng*hsgm);
  // TFitResultPtr rr2 = HH->Fit("gaus","SQR","",hmean-rng*hsgm,hmean+rng*hsgm);
  // TFitResultPtr rr2 = HH->Fit("gaus","S",hmean-1.2*hsgm,hmean+1.2*hsgm);
  // TFitResultPtr rr2 = HH->Fit("gaus","SQN"); // Quiet fitting

  double MM=rr2->Parameter(1);
  double SS=rr2->Parameter(2);

  if(ii==1) return(MM);
  else return(SS);
}
