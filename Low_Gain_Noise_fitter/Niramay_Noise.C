#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TLatex.h>
#include <sstream>
#include <fstream>
#include <TGraphAsymmErrors.h>
#include <iomanip>
#include "helper.h"
#include "MyNoise.h"

TFile* _file0 = TFile::Open("../SNR_analysis/noise.root");

ofstream myfile_all;
// void Loop(int layer,int chip,int channel, int pos_)
char* Loop(int layer,int chip,int channel, int pos_)
{
  TCanvas *cc = new TCanvas();
  setTDRStyle();  
  cc->SetWindowSize(650,600);
  
  bool saveCanvas_ = true;
  
  char* hname = new char[500];
  char *det = new char[20];
  if(pos_ == 0) {
    sprintf(hname,"ADC_distributions/EE_%d/h_TS3LG_EE_L%d_P%d_chip%d_chan%d",layer,layer,pos_,chip,channel);
    sprintf(det,"EE");
  }
  else {
    sprintf(hname,"ADC_distributions/FH_L%d_P%d/h_TS3LG_FH_L%d_P%d_chip%d_chan%d",layer,pos_,layer,pos_,chip,channel);
    sprintf(det,"FH");
  }
  TH1F* h = (TH1F*)_file0->Get(hname);
  
  if(!h) {
    cout<<"Could Not Load hist = "<<hname<<endl;
    char*a=new char[100];
    return(a);
  }

  int entries = h->GetEntries();
  if(entries>0){
    // h->GetXaxis()->SetRangeUser(-50,50);
    h->GetXaxis()->SetRangeUser(-10,10); // Niramay. Low gain noise normal range
    h->SetTitle("yolo");

    // TF1* gaus = new TF1("gaus","gaus(0)",-50.0,50.0);
    TF1* gaus = new TF1("gaus","gaus(0)",-10.0,10.0); // Niramay. Low gain normal noise range
    gaus->SetParameters(100,0.0,5.0);
    // h->Fit(gaus,"QR","",-20.0,20.0);
    h->Fit(gaus,"QR","",-10.0,10.0); // Niramay. Low gain normal noise range

   
    gaus = h->GetFunction("gaus");
    double mean = gaus->GetParameter(1);
    double sigma = gaus->GetParameter(2);

    // h->Fit(gaus,"QR","",mean-2*sigma,mean+2*sigma);
    // gaus = h->GetFunction("gaus");
    // mean = gaus->GetParameter(1);
    // sigma = gaus->GetParameter(2);
    double chi2 = gaus->GetChisquare();
    double ndf = gaus->GetNDF();

    std::ostringstream os(std::ostringstream::ate);   
    os.str("");
    os<<"Layer="<<layer<<" Chip="<<chip<<" Channel="<<channel;

    TLatex *tex=new TLatex();
    tex->SetTextColor(kBlack);
    tex->SetTextSize(0.041);
    //tex->DrawLatexNDC(0.15,0.96,os.str().c_str());
    // os << "Total Entries = "<<entries<<endl;
    tex->DrawLatexNDC(0.15,0.96,os.str().c_str());

    // if(chi2/ndf > 3.0) {
    //   cout<<endl<<endl<<"*********** Look here = "<<mean<<" "<<sigma<<" "<<chi2/ndf<<endl;
    //   cout<< "os = "<<os.str()<<endl;
    // }

    gPad->SetGridx();
    gPad->SetGridy();
    cc->Update();     

    char* canvas_name = new char[100];
   
    if(saveCanvas_) {
      char* canvas_name = new char[200];
      if(pos_!=0 && layer < 10)
	sprintf(canvas_name,"Histograms/%s/Layer0%i/Pos%d/Pos%d_chip%i_chan%i.gif",det,layer,pos_,pos_,chip,channel); // Niramay
      else if(pos_!=0 && layer>9)
	sprintf(canvas_name,"Histograms/%s/Layer%i/Pos%d/Pos%d_chip%i_chan%i.gif",det,layer,pos_,pos_,chip,channel); // Niramay
      if(pos_==0 &&layer<10){
	sprintf(canvas_name,"Histograms/%s/Layer0%i/chip%i_chan%i.gif",det,layer,chip,channel); // Niramay
      }
      else if(pos_==0 && layer>9){
	sprintf(canvas_name,"Histograms/%s/Layer%i/chip%i_chan%i.gif",det,layer,chip,channel); // Niramay
      }
      cc->SaveAs(canvas_name);
      delete cc;			// Niramay. delete the canvas
    }

    // double mean = mean0.getValV();
    // int entries = h->GetEntries();
    // double sigma = sigma0.getValV();
    // double err_sig = sigma0.getError();

    char* line = new char[1000];
    //FOR EE
    if(!strcmp(det,"EE")){sprintf(line,"%d\t%d\t%d\t%.3f\t%.3f\t%.3f\n",layer,chip,channel,mean,sigma,chi2/ndf);}
  
    //FOR FH
    else if(!strcmp(det,"FH")){sprintf(line,"%d\t%d\t%d\t%d\t%.3f\t%.3f\t%.3f\n",layer,pos_,chip,channel,mean,sigma,chi2/ndf);}
  
    // cout<<line<<endl;
    // myfile_all << line;
    return(line);
  }
  else{
    char*a=new char[100];
    sprintf(a,"");
    return(a);
  }
}

void for_all()
{
  int layer_start = 1;
  int layer_end = 28;
  myfile_all.open("./Goodness_EE.txt");
  for(int ilayer = layer_start; ilayer <= layer_end; ilayer++){
    for(int chip = 0; chip < 4; chip++){
      for(int channel = 0; channel < 64; channel+=2) {
	// Loop(ilayer,chip,channel,0);
	// //return;
	// if((ilayer!=2)&&(ilayer!=28)){continue;}			// first looking into Layer 2 and 22
	char* line=Loop(ilayer,chip,channel,0);
	myfile_all<<line;
      }
    }
  }
  myfile_all.close();
}


void for_all_FH()
{
  int layer_start = 1;
  int layer_end = 12;
  myfile_all.open("./Goodness_FH.txt");
  for(int ilayer = layer_start; ilayer <= layer_end; ilayer++){
    for(int ipos = 1; ipos <= 7 ; ipos++) {
      for(int chip = 0; chip < 4; chip++){
	for(int channel = 0; channel < 64; channel+=2) {
	  // if(ilayer==9 && ipos==3 && chip==2)
	  //   {
	  // Loop(ilayer,chip,channel,ipos);
	  char* line=Loop(ilayer,chip,channel,ipos);
	  myfile_all<<line;
	  //return;
	  // }
	  // myfile_all.close();
	  //return;
	  // }
	}
      }
    }
  }
  myfile_all.close();
}
