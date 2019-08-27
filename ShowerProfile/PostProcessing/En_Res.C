// Program to calculate energy resolution for different cases

TString DATE = "26_08_19";
TString PATH_WWW="/afs/cern.ch/user/n/ngogate/www/PionShower/EnRes_Comp_"+DATE+"/";

double Find_EnRes(TH1F*,int);
double Res1[6],Res2[6],Res3[6],Res4[6];
double Comp[6] = {1,2,3,4,5,6};

void En_Res()
{
  TFile* tf1 = new TFile("../MyCheckLeakage/TempOut.root");
  TFile* tf2 = new TFile("CERN_Root_Files/All_200.root");

  TCanvas* tc = new TCanvas("aa","bb",800,600);

  // TLegend* tl = new TLegend(0.1,0.7,0.35,0.9);
  // TLegend* tl = new TLegend(0.1,0.8,0.9,0.9);
  TLegend* tl = new TLegend(0.1,0.8,0.9,0.9);
  tl->SetNColumns(2);
  tl->SetTextSize(0.0315);
  TString HH[6] = {"1","2","3","4","5","6"}; // the index needed for following hists
  TString DD[6]={"0 to 0.35","0.35 to 0.75","0.75 to 1.03","1.03 to 1.43","1.43 to 2.7","more than 2.7"};// The depth of each compartment

  for(int i=0;i<6;i++)
  // for(int i=0;i<1;i++)
    {       
      TH1F* ABS1 = (TH1F*)tf1->Get("Sum_Abs_"+HH[i]);
      TH1F* LIK1 = (TH1F*)tf1->Get("Sum_Abs_Leak_"+HH[i]);
      TH1F* WGT1 = (TH1F*)tf1->Get("RecEn_"+HH[i]);
      TH1F* DAT1 = (TH1F*)tf2->Get("RecEn_"+HH[i]);

      Res1[i] = Find_EnRes(ABS1,i);
      Res2[i] = Find_EnRes(LIK1,i);
      Res3[i] = Find_EnRes(WGT1,i);
      Res4[i] = Find_EnRes(DAT1,i);

      // cout<<i<<"\t"<<Res1[i]<<"\t"<<Res2[i]<<"\t"<<Res3[i]<<endl;
    }
  TGraph* ABS = new TGraph(6,Comp,Res1);
  TGraph* LIK = new TGraph(6,Comp,Res2);
  TGraph* WGT = new TGraph(6,Comp,Res3);
  TGraph* DAT = new TGraph(6,Comp,Res4);
  
  TMultiGraph* tmg = new TMultiGraph();
  tmg->SetTitle("HGCal Energy resolution | Pion 200 GeV;Compartment number; Energy Resolution ( #frac{#sigma}{#mu} )");

  tl->AddEntry(DAT,"Weighted #Sigma rechit_energy (Data)","p");
  tl->AddEntry(WGT,"Weighted #Sigmarechit_energy(Sim)","p");
  tl->AddEntry(ABS,"Total Energy in absorbers","p");
  tl->AddEntry(LIK,"E_abs + Trans. Leakage","p");

  LIK->SetMarkerColor(3);
  ABS->SetMarkerColor(2);
  WGT->SetMarkerColor(4);
  DAT->SetMarkerColor(1);

  LIK->SetMarkerStyle(21);
  ABS->SetMarkerStyle(21);
  WGT->SetMarkerStyle(21);
  DAT->SetMarkerStyle(21);

  tmg->Add(ABS,"APL");
  tmg->Add(LIK,"APL");
  tmg->Add(WGT,"APL");
  tmg->Add(DAT,"AP");

  tmg->SetMaximum(0.25);
  // tmg->SetMinimum(0);
  tmg->Draw("AP");
  tmg->GetYaxis()->SetTitleOffset(1.3);
  tl->Draw();

  // tc->SaveAs("PNG/RecoEn/Pion_200_En_Res_24_08_19.png");
  // tc->SaveAs("PDF/RecoEn/Pion_200_En_Res_24_08_19.pdf");

  tc->SaveAs("PNG/RecoEn/Pion_200_En_Res_"+DATE+".png");
  tc->SaveAs("PDF/RecoEn/Pion_200_En_Res_"+DATE+".pdf");
  gSystem->Exec("scp PNG/RecoEn/Pion_200_En_Res_"+DATE+".png ngogate@lxplus7.cern.ch:"+PATH_WWW);
}

double Find_EnRes(TH1F* HH,int ii)
{
  Double_t hmean = HH->GetMean();
  Double_t hsgm = HH->GetStdDev();
  Double_t rng = 2;
  TCanvas* tcc = new TCanvas("GausFitting","GausFitting",800,600);

  TFitResultPtr rr2 = HH->Fit("gaus","SQNR","",hmean-rng*hsgm,hmean+rng*hsgm);
  // TFitResultPtr rr2 = HH->Fit("gaus","SQR","",hmean-rng*hsgm,hmean+rng*hsgm);
  // TFitResultPtr rr2 = HH->Fit("gaus","S",hmean-1.2*hsgm,hmean+1.2*hsgm);
  // TFitResultPtr rr2 = HH->Fit("gaus","SQN"); // Quiet fitting

  double MEAN=rr2->Parameter(1);
  double SIGMA=rr2->Parameter(2);
  delete tcc;
  return(SIGMA/MEAN);
  // // double MM = rr2->GetParError(1);
  // // double SS = rr2->GetParError(2);
  // double MM = rr2->Error(1);
  // double SS = rr2->Error(2);

  // ERR[ii] = sqrt(pow(SS/MEAN,2)+pow(SIGMA*MM/(MEAN*MEAN),2));

  // AxisStyle(HH->GetYaxis());
  // AxisStyle(HH->GetXaxis());
  // HH->GetXaxis()->SetTitle("Weighted energy (in MIPs)");
  // HH->GetYaxis()->SetTitle("No. of events");
  // HH->GetYaxis()->SetTitleOffset(1);
  // HH->SetTitle("Weighted Energy Distribution");
  // HH->GetXaxis()->SetRange(0,80000); // ONLY FOR 300 GEV

  // char* ll[50];

  // sprintf(ll,"%i",ii));

  // char* ll = new char[200];
  // sprintf(ll,"%sLayer_%i.png",FitG,ii+1);
  // // tcc->SaveAs("../Output_PNG/GaussFitting/Layer_"+ll+OutPNG);

  // tcc->SaveAs(ll);
  // sprintf(ll,"%sLayer_%i.pdf",FitG2,ii+1);
  // tcc->SaveAs(ll);
  // delete tcc;

  // return(SIGMA/MEAN);
}
