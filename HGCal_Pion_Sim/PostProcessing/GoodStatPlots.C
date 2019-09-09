// Program to replot 2D hist weighted rechits sum in FH vs EE
// In order to have good statistics, the events will be clubbed
// together as per the output of FindDivisions.m

void GoodStatPlots()
{
  TFile* tf = new TFile("../MyCheckLeakage/TempOut.root");
  char* htitle = new char[100];
  for(int i=0;i<14;i++){
    sprintf(htitle,"GoodStat_%i",i);
    gStyle->SetOptStat(0);
    TCanvas* tc = new TCanvas("aa","bb",800,600);
    TH2F* HH = (TH2F*)tf->Get(htitle);

    HH->Draw("colz");
    HH->GetXaxis()->SetTitle("Total rechit energy in EE");
    HH->GetYaxis()->SetTitle("#beta(Total rechit energy in FH)");
    HH->GetYaxis()->SetTitleOffset(1.46);    

    char* ftitle=new char[200];
    sprintf(ftitle,"PNG/E200_Sim_%s.png",htitle);
    tc->SaveAs(ftitle);
    sprintf(ftitle,"PDF/E200_Sim_%s.pdf",htitle);
    tc->SaveAs(ftitle);
  }
}





// void AddContent(TH2F*,TH2F*);

// void GoodStatPlots()
// {
//   TFile* tf = new TFile("../MyCheckLeakage/TempOut.root");
//   TCanvas* tc = new TCanvas("aa","bb",800,600);
//   // for(int i=0;i<28;i++){
//   for(int i=0;i<1;i++){
//     char* Title1 = new char[100];
//     sprintf(Title1,"WtComp_%i",i+1);

//     TH2F* h1 =(TH2F*)tf->Get(Title1);
//     sprintf(Title1,"WtComp_%i",i+2);
//     TH2F* h2 =(TH2F*)tf->Get(Title1);
//     AddContent(h1,h2);
//     // if(i<4){h2->Draw("colz");delete tc;}
//     // elseif(){}
//   }
// }

// void AddContent(TH2F* h1,TH2F* h2)
// {
//   for(Int_t ii=0;ii<h2->GetEntries();ii++){
//     Int_t xx,yy,zz;
//     // TH1F* ttt = (TH1F*)h2;
//     // ttt->GetBinXYZ(ii,&xx,&yy,&zz);
//     h2->GetBinXYZ(ii,&xx,&yy,&zz);
//     Double_t wt = h2->GetBinContent(ii);
//     // h1->Fill(xx,yy,zz);
//     h1->Fill(xx,yy,wt);
//   }
// }
