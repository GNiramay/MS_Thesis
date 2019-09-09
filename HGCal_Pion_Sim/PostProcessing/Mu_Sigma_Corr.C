// Program to check correlation between mu and sigma for different methods

double mu[4][6];		// Index: method,comp
double si[4][6];

void Find_EnRes(TH1F*,int,int);

void Mu_Sigma_Corr()
{

  TFile* tf1 = new TFile("../MyCheckLeakage/TempOut.root");
  TFile* tf2 = new TFile("CERN_Root_Files/All_200.root");
  TString HH[6] = {"1","2","3","4","5","6"}; // the index needed for following hists
  TCanvas* tc = new TCanvas("aa","bb",800,600);

  TLegend* tl = new TLegend(0.1,0.6,0.45,0.9);
  tl->SetTextSize(0.0315);

  TMultiGraph* tmg = new TMultiGraph();
  tmg->SetTitle("Sigma-mu correlation | Pion 200 GeV; #mu; #sigma");
  printf("\tComp\t  mu\tSigma\n");
  for(int i=0;i<6;i++){
    TH1F* ABS1 = (TH1F*)tf1->Get("Sum_Abs_"+HH[i]);
    TH1F* LIK1 = (TH1F*)tf1->Get("Sum_Abs_Leak_"+HH[i]);
    TH1F* WGT1 = (TH1F*)tf1->Get("RecEn_"+HH[i]);
    TH1F* DAT1 = (TH1F*)tf2->Get("RecEn_"+HH[i]);

    Find_EnRes(ABS1,0,i);
    Find_EnRes(LIK1,1,i);
    Find_EnRes(WGT1,2,i);
    Find_EnRes(DAT1,3,i);

    printf("sim\t %i\t%.3f\t%.3f\n",i+1,mu[2][i],si[2][i]);
    printf("Data\t %i\t%.3f\t%.3f\n",i+1,mu[3][i],si[3][i]);
  }
  
  TGraph* tg0 = new TGraph(6,mu[0],si[0]);
  TGraph* tg1 = new TGraph(6,mu[1],si[1]);
  TGraph* tg2 = new TGraph(6,mu[2],si[2]);
  TGraph* tg3 = new TGraph(6,mu[3],si[3]);

  tg0->SetMarkerStyle(21);
  tg1->SetMarkerStyle(21);
  tg2->SetMarkerStyle(21);
  tg3->SetMarkerStyle(21);

  tg0->SetMarkerSize(0.7);
  tg1->SetMarkerSize(0.7);
  tg2->SetMarkerSize(0.7);
  tg3->SetMarkerSize(0.7);

  tg0->SetMarkerColor(1);
  tg1->SetMarkerColor(2);
  tg2->SetMarkerColor(3);
  tg3->SetMarkerColor(4);

  // tmg->Add(tg0,"AP");
  // tmg->Add(tg1,"AP");
  tmg->Add(tg2,"AP");
  tmg->Add(tg3,"AP");

  tl->AddEntry(tg0,"Absorber","p");
  tl->AddEntry(tg1,"Absorber + Leakage","p");
  tl->AddEntry(tg2,"Reco energy (sim)","p");
  tl->AddEntry(tg3,"Reco energy (Data)","p");

  // tg0->Draw("AP");
  tmg->Draw("AP");
  tl->Draw();
}

void Find_EnRes(TH1F* HH,int mm,int cc)
{
  Double_t hmean = HH->GetMean();
  Double_t hsgm = HH->GetStdDev();
  Double_t rng = 2;
  TFitResultPtr rr2 = HH->Fit("gaus","SQNR","",hmean-1.5*hsgm,hmean+1*hsgm);

  mu[mm][cc]=rr2->Parameter(1);
  si[mm][cc]=rr2->Parameter(2);
}
