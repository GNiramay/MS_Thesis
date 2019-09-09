#ifndef AnalyzeHGCOctTB_H
#define AnalyzeHGCOctTB_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "HGCNtupleVariables.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TGraph.h"
#include "TF1.h"
#include "TFile.h"
#include "TProfile.h"
#include "TLorentzVector.h"
#include "TDirectory.h"

class AnalyzeHGCOctTB : public HGCNtupleVariables{

 public:
  AnalyzeHGCOctTB(const TString &inputFileList="foo.txt", const char *outFileName="histo.root",const char *dataset="data", const char *config="alpha", const char* energy = "-1");
  ~AnalyzeHGCOctTB();
  //Bool_t   FillChain(TChain *chain, TChain *chain2, TChain *chain3, const TString &inputFileList);
  Bool_t   FillChain(TChain *chain, TChain *chain2, const TString &inputFileList);
  /* Bool_t   FillChain(TChain *chain, const TString &inputFileList); */
  Long64_t LoadTree(Long64_t entry);
  void     EventLoop(const char *);
  void     BookHistogram(const char *, const char *, const char* energy);

  void moduleMap_init(const char *);
  void Alignment_Map_Init();
  void Noise_Map_Init();


  TFile *oFile;
  TDirectory *d_Nrechit_layer;
  TDirectory *d_rechitEn_layer;
  /* TDirectory *d_track_info; */
  //TDirectory *d_rechit_en_layer; 
  /* TDirectory *d_adcHG; */
  TDirectory *d_tracks;
  TDirectory *d_layers[40];

  TH2F* h_trackX_trackY[40];
  TH2F* h_cogX_cogY[40];
  TH2F* h_cogX_trackX[40];
  TH2F* h_cogY_trackY[40];
  TH2F* h_dX_dY[40];
  TH1F* h_dX[40];
  TH1F* h_dY[40];
  TH2F* h_dX_dY_track_vs_rechit[40];
  /* TDirectory *d_EE[28]; */
  // TDirectory *d_FH[12][7];
  TDirectory *d_weightScan;
  TDirectory *d_weightScan_EH;
  TH1F* h_rechit_energy_FB_rel_weightScan[20];
  TH1F* h_rechit_energy_EH_rel_weightScan[50];
  TGraph* h_reso_weights;
  TGraph* h_reso_weights_EH;

  
  const char *conf_;  
  /* TH1F *h_ADChg[128]; */
  /* TH1F *h_adcHG_EE[28][128]; */
  /* TH1F *h_adcHG_EE_track[28][128]; */
  /* TH1F *h_adcHG_FH[12][7][128]; */
  /* TH1F *h_adcHG_FH_track[12][7][128]; */
  TH1F *h_NRechits_EE[28];
  TH1F *h_NRechits_EE_L1_chip0;
  TH1F *h_NRechits_EE_L1_chip1;
  TH1F *h_NRechits_EE_L1_chip2;
  TH1F *h_NRechits_EE_L1_chip3;

  /* TH1F *h_NRechits_FH[12][7]; */
  TH1F *h_NRechits_FH[12];


  TH1F *h_Rechits_En_EE[28];
  TH1F *h_Rechits_En_FH[12];

  // TH1F* h_nrechits;
  // TH1F* h_nrechit_1evt[5];	// Tracking hits in a single event
  TH1F* h_configuration;
  TH1F* h_particleID;
  TH1F* h_nTracks;
  TH1F* h_beamEnergy;
  TH1F* h_runNumber;
  TH1F* h_moduleID;
  TH1F* h_nRechits_layer[28];

  TH1F* h_rechit_energy_raw_all;
  TH1F* h_rechit_energy_raw_EE;
  TH1F* h_rechit_energy_raw_FH;
  TH1F* h_rechit_energy_weighted;
  TH1F* h_rechit_energy_FB_FH_alone_raw;
  TH1F* h_rechit_energy_FH_FB_weighted;


  TH1F* h_rechit_energy_raw_region3;
  TH1F* h_rechit_energy_raw_EE_alone_region3;
  TH1F* h_rechit_energy_raw_FH_AH_alone_region3;
  TH1F* h_rechit_energy_part_weighted_region3;
  TH1F* h_rechit_energy_full_weighted_region3;
  TH1F* h_rechit_energy_full_weighted_inGev_region3;
  TH1F* h_sim_energy_inGev_region3;
  TH1F* h_rechit_energy_full_weighted_inGev_region3_withoutAHCAL;

  TH1F* h_energy_region2_gev;
  TH1F* h_rechit_energy_inEE_region2_mips;
  TH1F* h_sim_energy_inGev_region2;
  TH1F* h_energy_region2_gev_withoutAHCAL;
  TH2F* h_energy_FH_vs_AHCAL_region2_gev;
  TH1F* h_energy_all_gev;
  TH1F* h_sim_energy_all_gev;

  TH1F* h_total_sim_energy;
  

  TH2F* dX_dY_layer_2;

  /* TH1F* h_rechit_energy_weighted_EH; */
  /* TH1F* h_rechit_energy_FB_FH_alone_raw_EH; */
  /* TH1F* h_rechit_energy_FH_FB_weighted_EH; */

  TH2F* h_Nrechit_EE_vs_FH_region3; 
  TH2F* h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED;
  TH2F* h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R1;
  TH2F* h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R2;
  TH2F* h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R3;
 

  TH2F* h_Nrechit_EE_vs_FH;
  TH2F* h_Nrechits_EE_FH_FB;

  //TH2F* h_energy_FH_AH_FB;

  TH2F* h_rechit_energy_FH_AHCAL_FB_raw;
  TH2F* h_rechit_energy_FH_AHCAL_FB_weighted;
  TH2F* h_rechit_energy_EE_FHAHCAL_EH_mips;
  TH2F* h_rechit_energy_EE_FHAHCAL_EH_gev;
  TH2F* h_rechit_energy_EE_FHAHCAL_EH_gev_DEBUG;

  TH1F* h_Nrechit_EE;
  TH1F* h_Nrechit_FH;
  TH1F* h_Nrechit_AH;

  TH1F* h_shower_start;
  TH1F* h_shower_start_dN_dLambda;
  
  TH1F* h_shower_start_full_collapsed_EE;
  TH1F* h_shower_start_part_collapsed_EE;

  TH1F* h_shower_start_reg1;
  TH1F* h_shower_start_reg2;
  TH1F* h_shower_start_reg3;
  TH1F* h_shower_start_CHECK_FOR_UNCLASSIFIED;
  TH1F* h_shower_start_reg3_DEBUG;
  TH2F* h_rechit_En_NRechits;

  int inEnergy_;
};
#endif

#ifdef AnalyzeHGCOctTB_cxx

void AnalyzeHGCOctTB::BookHistogram(const char *outFileName, const char* conf,  const char* energy) {
  
  char* hname = new char[200];
  char* dir_name = new char[200];
  double y_max = -1.0;
  double x_2D_max = -1.0;
  double xbin = -1.0;
  double y_2D_max = -1.0;
  double mip_x_max = 3000;
  double mip_y_max = 1500;
  
  if(!strcmp(energy, "20")) {
    y_max = 100.0;
    x_2D_max = 3000;
    xbin = 300;
    y_2D_max = 1500;
    inEnergy_ = 20;
  }
  else if(!strcmp(energy, "50")) {
    y_max = 150.0;
    /* x_2D_max = 5000; */
    /* x_2D_max = 5000; */
    /* xbin = 500; */
    x_2D_max = 10000;
    xbin = 500;
    y_2D_max = 200;
    inEnergy_ = 50;
  }
  else if(!strcmp(energy, "80")) {
    y_max = 200.0;
    /* x_2D_max = 8000; */
    /* xbin = 400; */
    x_2D_max = 12000;
    xbin = 300;
    y_2D_max = 3000;
    inEnergy_ = 80;
  }
  else if(!strcmp(energy, "100")) {
    y_max = 300.0;
    /* x_2D_max = 10000; */
    /* xbin = 500; */
    x_2D_max = 18000;
    xbin = 360;
    y_2D_max = 3000;
    inEnergy_ = 100;
  }
  else if(!strcmp(energy, "120")) {
    y_max = 400.0;
    /* x_2D_max = 12000; */
    /* xbin = 300; */
    x_2D_max = 20000;
    xbin = 400;
    y_2D_max = 3200;
    inEnergy_ = 120;
  }
  else if(!strcmp(energy, "200")) {
    y_max = 600.0;
    /* x_2D_max = 18000; */
    /* xbin = 360; */
    x_2D_max = 40000;
    xbin = 800;
    y_2D_max = 4800;
    inEnergy_ = 200;
  }
  else if(!strcmp(energy, "250")) {
    y_max = 700.0;
    /* x_2D_max = 25000; */
    /* xbin = 500; */
    x_2D_max = 50000;
    xbin = 1000;
    y_2D_max = 6000;
    inEnergy_ = 250;
  }
  else if(!strcmp(energy, "300")) {
    y_max = 800.0;
    x_2D_max = 60000;
    /* x_2D_max = 20000; */
    xbin = 1000;
    y_2D_max = 6000;
    inEnergy_ = 300;
  }
  else {
    cout<<"invalid energy!!!"<<endl; 
    return;
  }
  conf_ = conf;
  oFile = new TFile(outFileName, "recreate");
  h_nTracks = new TH1F("h_nTracks","Tracks",12,-1,5);
  h_nTracks->GetXaxis()->SetTitle("Tracks");

  h_configuration = new TH1F("h_configuration","Configuration",60,-10,50);
  h_particleID = new TH1F("h_particleID","particleID",500,0,500);
  h_beamEnergy = new TH1F("h_beamEnergy","beamEnergy",500,0,500);
  h_runNumber = new TH1F("h_runNumber","RunNumber",2000,0,2000);
  h_moduleID = new TH1F("h_moduleID","moduleID",4,-2,2);
  h_Nrechit_EE = new TH1F("h_Nrechit_EE","NRechits in EE",500,0.0,1000.0);
  h_Nrechit_FH = new TH1F("h_Nrechit_FH","NRechits in FH",500,0.0,1000.0);
  h_Nrechit_AH = new TH1F("h_Nrechit_AH","NRechits in AH",500,0.0,1000.0);


  dX_dY_layer_2 = new TH2F("dX_dY_layer_2","dX_dY_layer_2",160,-8.0,8.0,160,-8.0,8.0);


  h_rechit_energy_raw_EE = new TH1F("h_rechit_energy_raw_EE","h_rechit_energy_raw_EE",xbin,0.0,x_2D_max);
  h_rechit_energy_raw_EE->GetXaxis()->SetTitle("Energy in units of MIPs");

  h_rechit_energy_raw_FH = new TH1F("h_rechit_energy_raw_FH","h_rechit_energy_raw_FH",xbin,0.0,x_2D_max);
  h_rechit_energy_raw_FH->GetXaxis()->SetTitle("Energy in units of MIPs");

  h_rechit_energy_raw_all = new TH1F("h_rechit_energy_raw_all","h_rechit_energy_raw_all",xbin,0.0,x_2D_max);
  h_rechit_energy_raw_all->GetXaxis()->SetTitle("Energy in units of MIPs");


  /* h_rechit_energy_weighted = new TH1F("h_rechit_energy_weighted","h_rechit_energy_weighted",xbin,0.0,x_2D_max); */
  /* h_rechit_energy_weighted->GetXaxis()->SetTitle("Energy in units of MIPs"); */

  h_rechit_energy_raw_region3 = new TH1F("h_rechit_energy_raw_region3","h_rechit_energy_raw_region3",xbin,0.0,x_2D_max);
  h_rechit_energy_raw_region3->GetXaxis()->SetTitle("Energy in units of MIPs");

  h_rechit_energy_part_weighted_region3 = new TH1F("h_rechit_energy_part_weighted_region3","h_rechit_energy_part_weighted_region3",xbin,0.0,x_2D_max);
  h_rechit_energy_part_weighted_region3->GetXaxis()->SetTitle("Energy in units of MIPs");

  h_rechit_energy_full_weighted_region3 = new TH1F("h_rechit_energy_full_weighted_region3","h_rechit_energy_full_weighted_region3",xbin,0.0,x_2D_max);
  h_rechit_energy_full_weighted_region3->GetXaxis()->SetTitle("Energy in units of MIPs");

  h_rechit_energy_full_weighted_inGev_region3 = new TH1F("h_rechit_energy_full_weighted_inGev_region3","h_rechit_energy_full_weighted_inGev_region3",y_max,0.0,y_max);
  h_rechit_energy_full_weighted_inGev_region3->GetXaxis()->SetTitle("Energy(GeV)");

  h_rechit_energy_full_weighted_inGev_region3_withoutAHCAL = new TH1F("h_rechit_energy_full_weighted_inGev_region3_withoutAHCAL","h_rechit_energy_full_weighted_inGev_region3_withoutAHCAL",y_max,0.0,y_max);
  h_rechit_energy_full_weighted_inGev_region3_withoutAHCAL->GetXaxis()->SetTitle("Energy(GeV)");

  h_sim_energy_inGev_region3 = new TH1F("h_sim_energy_inGev_region3","h_sim_energy_inGev_region3",y_max,0.0,y_max);
  h_sim_energy_inGev_region3->GetXaxis()->SetTitle("Sim Energy(GeV)");


  h_energy_region2_gev = new TH1F("h_energy_region2_gev","h_energy_region2_gev",y_max,0.0,y_max);
  h_energy_region2_gev->GetXaxis()->SetTitle("Energy(GeV)");

  h_rechit_energy_inEE_region2_mips = new TH1F("h_rechit_energy_inEE_region2_mips","h_rechit_energy_inEE_region2_mips",xbin,0.0,x_2D_max);
  h_rechit_energy_inEE_region2_mips->GetXaxis()->SetTitle("Energy in units of MIPs");


  h_energy_region2_gev_withoutAHCAL = new TH1F("h_energy_region2_gev_withoutAHCAL","h_energy_region2_gev_withoutAHCAL",y_max,0.0,y_max);
  h_energy_region2_gev_withoutAHCAL->GetXaxis()->SetTitle("Energy(GeV)");

  h_sim_energy_inGev_region2 = new TH1F("h_sim_energy_inGev_region2","h_sim_energy_inGev_region2",y_max,0.0,y_max);
  h_sim_energy_inGev_region2->GetXaxis()->SetTitle("Energy(GeV)");

  h_energy_FH_vs_AHCAL_region2_gev = new TH2F("h_energy_FH_vs_AHCAL_region2_gev","h_energy_FH_vs_AHCAL_region2_gev",y_max,0.0,y_max,y_max,0.0,y_max);
  h_energy_FH_vs_AHCAL_region2_gev->GetXaxis()->SetTitle("FH Energy in GeV");
  h_energy_FH_vs_AHCAL_region2_gev->GetYaxis()->SetTitle("AHCAL sim Energy in GeV");
  h_energy_FH_vs_AHCAL_region2_gev->GetYaxis()->SetTitleOffset(1.0);


  h_energy_all_gev = new TH1F("h_energy_all_gev","h_energy_all_gev",y_max,0.0,y_max);
  h_energy_all_gev->GetXaxis()->SetTitle("Energy(GeV)");

  h_sim_energy_all_gev = new TH1F("h_sim_energy_all_gev","h_sim_energy_all_gev",y_max,0.0,y_max);
  h_sim_energy_all_gev->GetXaxis()->SetTitle("Energy(GeV)");

  h_total_sim_energy = new TH1F("h_total_sim_energy","h_total_sim_energy",y_max,0.0,y_max);
  h_total_sim_energy->GetXaxis()->SetTitle("Energy(GeV)");



  h_rechit_energy_EE_FHAHCAL_EH_mips = new TH2F("h_rechit_energy_EE_FHAHCAL_EH_mips","h_rechit_energy_EE_FHAHCAL_EH_mips",xbin,0.0,x_2D_max,xbin,0.0,x_2D_max);
  h_rechit_energy_EE_FHAHCAL_EH_mips->GetXaxis()->SetTitle("EE (MIPs)");
  h_rechit_energy_EE_FHAHCAL_EH_mips->GetYaxis()->SetTitle("#beta *(FH+#alpha *AH) (MIPs)");

  h_rechit_energy_EE_FHAHCAL_EH_gev = new TH2F("h_rechit_energy_EE_FHAHCAL_EH_gev","h_rechit_energy_EE_FHAHCAL_EH_gev",y_max,0.0,y_max,y_max,0.0,y_max);
  h_rechit_energy_EE_FHAHCAL_EH_gev->GetXaxis()->SetTitle("EE (GeV)");
  h_rechit_energy_EE_FHAHCAL_EH_gev->GetYaxis()->SetTitle("#beta *(FH+#alpha *AH)  (GeV)");

  h_rechit_energy_EE_FHAHCAL_EH_gev_DEBUG = new TH2F("h_rechit_energy_EE_FHAHCAL_EH_gev_DEBUG","h_rechit_energy_EE_FHAHCAL_EH_gev_DEBUG",y_max,0.0,y_max,y_max,0.0,y_max);
  h_rechit_energy_EE_FHAHCAL_EH_gev_DEBUG->GetXaxis()->SetTitle("EE (GeV)");
  h_rechit_energy_EE_FHAHCAL_EH_gev_DEBUG->GetYaxis()->SetTitle("#beta *(FH+#alpha *AH)  (GeV)");



  h_rechit_energy_raw_EE_alone_region3 = new TH1F("h_rechit_energy_raw_EE_alone_region3","h_rechit_energy_raw_EE_alone_region3",xbin,0.0,x_2D_max);
  h_rechit_energy_raw_EE_alone_region3->GetXaxis()->SetTitle("Energy in units of MIPs");

  h_rechit_energy_raw_FH_AH_alone_region3 = new TH1F("h_rechit_energy_raw_FH_AH_alone_region3","h_rechit_energy_raw_FH_AH_alone_region3",xbin,0.0,x_2D_max);
  h_rechit_energy_raw_FH_AH_alone_region3->GetXaxis()->SetTitle("Energy in units of MIPs");





  /* h_rechit_energy_FH_FB_weighted = new TH1F("h_rechit_energy_FH_FB_weighted","h_rechit_energy_FH_FB_weighted",y_max,0.0,y_max); */
  /* h_rechit_energy_FH_FB_weighted->GetXaxis()->SetTitle("Energy in GeV"); */

  /* h_rechit_energy_FB_FH_alone_raw = new TH1F("h_rechit_energy_FB_FH_alone_raw","h_rechit_energy_FB_FH_alone_raw",xbin,0.0,x_2D_max); */
  /* h_rechit_energy_FB_FH_alone_raw->GetXaxis()->SetTitle("Energy in units of MIPs"); */





  h_Nrechit_EE_vs_FH = new TH2F("h_Nrechit_EE_vs_FH","NRechits EE vs FH",500,0.0,1000.0,500,0.0,1000.0);
  h_Nrechit_EE_vs_FH->GetXaxis()->SetTitle("NRechits in EE");
  h_Nrechit_EE_vs_FH->GetYaxis()->SetTitle("NRechits in FH");
  h_Nrechit_EE_vs_FH->GetYaxis()->SetTitleOffset(1.0);

  /* h_Nrechits_EE_FH_FB = new TH2F("h_Nrechits_EE_FH_FB","NRechits EE vs FH",500,0.0,1000.0,500,0.0,1000.0); */
  /* h_Nrechits_EE_FH_FB->GetXaxis()->SetTitle("NRechits in EE"); */
  /* h_Nrechits_EE_FH_FB->GetYaxis()->SetTitle("NRechits in FH"); */
  /* h_Nrechits_EE_FH_FB->GetYaxis()->SetTitleOffset(1.0); */


  /* h_rechit_energy_FH_AHCAL_FB_raw = new TH2F("h_rechit_energy_FH_AHCAL_FB_raw","h_rechit_energy_FH_AHCAL_FB_raw",xbin,0.0,x_2D_max,xbin,0.0,x_2D_max); */
  /* h_rechit_energy_FH_AHCAL_FB_raw->GetXaxis()->SetTitle("FH Energy in units of MIPs"); */
  /* h_rechit_energy_FH_AHCAL_FB_raw->GetYaxis()->SetTitle("AHCAL Energy in units of MIPs"); */
  /* h_rechit_energy_FH_AHCAL_FB_raw->GetYaxis()->SetTitleOffset(1.0); */


  /* h_rechit_energy_FH_AHCAL_FB_weighted = new TH2F("h_rechit_energy_FH_AHCAL_FB_weighted","h_rechit_energy_FH_AHCAL_FB_weighted",y_max,0.0,y_max,y_max,0.0,y_max); */
  /* h_rechit_energy_FH_AHCAL_FB_weighted->GetXaxis()->SetTitle("FH Energy in GeV"); */
  /* h_rechit_energy_FH_AHCAL_FB_weighted->GetYaxis()->SetTitle("AHCAL Energy in GeV"); */
  /* h_rechit_energy_FH_AHCAL_FB_weighted->GetYaxis()->SetTitleOffset(1.0); */
  
  h_shower_start = new TH1F("h_shower_start","h_shower_start",10000,-2.0,5.0);
  h_shower_start->GetXaxis()->SetTitle("#lambda_{0}");
  h_shower_start->Sumw2();

  h_shower_start_dN_dLambda = new TH1F("h_shower_start_dN_dLambda","h_shower_start_dN_dLambda",10000,-2.0,5.0);
  h_shower_start_dN_dLambda->GetXaxis()->SetTitle("#lambda_{0}");
  h_shower_start_dN_dLambda->Sumw2();

  h_shower_start_full_collapsed_EE = new TH1F("h_shower_start_full_collapsed_EE","h_shower_start_full_collapsed_EE",10000,-2.0,5.0);
  h_shower_start_full_collapsed_EE->GetXaxis()->SetTitle("#lambda_{0}");
  h_shower_start_full_collapsed_EE->Sumw2();

  h_shower_start_part_collapsed_EE = new TH1F("h_shower_start_part_collapsed_EE","h_shower_start_part_collapsed_EE",10000,-2.0,5.0);
  h_shower_start_part_collapsed_EE->GetXaxis()->SetTitle("#lambda_{0}");
  h_shower_start_part_collapsed_EE->Sumw2();

  
  h_shower_start_reg1 = new TH1F("h_shower_start_reg1","h_shower_start_reg1",10000,-2.0,5.0);
  h_shower_start_reg1->GetXaxis()->SetTitle("#lambda_{0}");
  h_shower_start_reg1->Sumw2();

  
  h_shower_start_reg2 = new TH1F("h_shower_start_reg2","h_shower_start_reg2",10000,-2.0,5.0);
  h_shower_start_reg2->GetXaxis()->SetTitle("#lambda_{0}");
  h_shower_start_reg2->Sumw2();

  
  h_shower_start_reg3 = new TH1F("h_shower_start_reg3","h_shower_start_reg3",10000,-2.0,5.0);
  h_shower_start_reg3->GetXaxis()->SetTitle("#lambda_{0}");
  h_shower_start_reg3->Sumw2();

  h_shower_start_CHECK_FOR_UNCLASSIFIED = new TH1F("h_shower_start_CHECK_FOR_UNCLASSIFIED","h_shower_start_CHECK_FOR_UNCLASSIFIED",10000,-2.0,5.0);
  h_shower_start_CHECK_FOR_UNCLASSIFIED->GetXaxis()->SetTitle("#lambda_{0}");

  h_Nrechit_EE_vs_FH_region3 = new TH2F("h_Nrechit_EE_vs_FH_region3","NRechits EE vs FH",500,0.0,1000.0,500,0.0,1000.0);
  h_Nrechit_EE_vs_FH_region3->GetXaxis()->SetTitle("NRechits in EE");
  h_Nrechit_EE_vs_FH_region3->GetYaxis()->SetTitle("NRechits in FH");
  h_Nrechit_EE_vs_FH_region3->GetYaxis()->SetTitleOffset(1.0);

  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED = new TH2F("h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED","NRechits EE vs FH",500,0.0,1000.0,500,0.0,1000.0);
  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED->GetXaxis()->SetTitle("NRechits in EE");
  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED->GetYaxis()->SetTitle("NRechits in FH");
  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED->GetYaxis()->SetTitleOffset(1.0);


  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R1 = new TH2F("h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R1","NRechits EE vs FH",500,0.0,1000.0,500,0.0,1000.0);
  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R1->GetXaxis()->SetTitle("NRechits in EE");
  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R1->GetYaxis()->SetTitle("NRechits in FH");
  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R1->GetYaxis()->SetTitleOffset(1.0);

  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R2 = new TH2F("h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R2","NRechits EE vs FH",500,0.0,1000.0,500,0.0,1000.0);
  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R2->GetXaxis()->SetTitle("NRechits in EE");
  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R2->GetYaxis()->SetTitle("NRechits in FH");
  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R2->GetYaxis()->SetTitleOffset(1.0);

  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R3 = new TH2F("h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R3","NRechits EE vs FH",500,0.0,1000.0,500,0.0,1000.0);
  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R3->GetXaxis()->SetTitle("NRechits in EE");
  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R3->GetYaxis()->SetTitle("NRechits in FH");
  h_Nrechit_EE_vs_FH_CHECK_FOR_UNCLASSIFIED_R3->GetYaxis()->SetTitleOffset(1.0);


  h_shower_start_reg3_DEBUG = new TH1F("h_shower_start_reg3_DEBUG","h_shower_start_reg3_DEBUG",10000,-2.0,5.0);
  h_shower_start_reg3_DEBUG->GetXaxis()->SetTitle("#lambda_{0}");
  //h_shower_start_reg3->Sumw2();
 
  
  d_tracks = oFile->mkdir("tacks_cog"); 
  d_tracks->cd();
  char* h_name = new char[200];
  for(int i = 0; i < 40; i++) {
    sprintf(h_name,"layer_%d",i+1);
    d_layers[i] = d_tracks->mkdir(h_name);
    d_layers[i]->cd();
    sprintf(h_name,"h_trackX_trackY_%d",i+1);
    h_trackX_trackY[i] = new TH2F(h_name,h_name,32,-8.0,8.0,32,-8.0,8.0);
    sprintf(h_name,"h_cogX_cogY_%d",i+1);
    h_cogX_cogY[i] = new TH2F(h_name,h_name,32,-8.0,8.0,32,-8.0,8.0);

    sprintf(h_name,"h_cogX_trackX_%d",i+1);
    h_cogX_trackX[i] = new TH2F(h_name,h_name,32,-8.0,8.0,32,-8.0,8.0);

    sprintf(h_name,"h_cogY_trackY_%d",i+1);
    h_cogY_trackY[i] = new TH2F(h_name,h_name,32,-8.0,8.0,32,-8.0,8.0);

    sprintf(h_name,"h_dX_dY_%d",i+1);
    h_dX_dY[i] = new TH2F(h_name,h_name,32,-8.0,8.0,32,-8.0,8.0);

    sprintf(h_name,"h_dX_%d",i+1);
    h_dX[i] = new TH1F(h_name,h_name,32,-8.0,8.0);

    sprintf(h_name,"h_dY_%d",i+1);
    h_dY[i] = new TH1F(h_name,h_name,32,-8.0,8.0);

    sprintf(h_name,"h_dX_dY_track_vs_rechit_%d",i+1);
    h_dX_dY_track_vs_rechit[i] = new TH2F(h_name,h_name,32,-8.0,8.0,32,-8.0,8.0);
 
    
  }
  /* d_weightScan = oFile->mkdir("weight_scan"); */
  /* d_weightScan->cd(); */
  /* for(int i = 0; i < 20; i++) { */
  /*   sprintf(hname,"h_weight_%d",i+1); */
  /*   h_rechit_energy_FB_rel_weightScan[i] = new TH1F(hname,hname,xbin,0.0,x_2D_max); */
  /*   /\* h_rechit_energy_FB_rel_weightScan[i] = new TH1F(hname,hname,y_max,0.0,y_max); *\/ */
  /*   h_rechit_energy_FB_rel_weightScan[i]->GetXaxis()->SetTitle("Energy in units of MIPs"); */
  /*   h_rechit_energy_FB_rel_weightScan[i]->Sumw2(); */
  /* } */

  /* d_weightScan_EH = oFile->mkdir("weight_scan_EH"); */
  /* d_weightScan_EH->cd(); */
  /* for(int i = 0; i < 50; i++) { */
  /*   sprintf(hname,"h_weight_%d_EH",i+1); */
  /*   /\* h_rechit_energy_FB_rel_weightScan[i] = new TH1F(hname,hname,xbin,0.0,x_2D_max); *\/ */
  /*   h_rechit_energy_EH_rel_weightScan[i] = new TH1F(hname,hname,xbin,0.0,x_2D_max); */
  /*   h_rechit_energy_EH_rel_weightScan[i]->GetXaxis()->SetTitle("Energy in units of MIPs"); */
  /*   h_rechit_energy_EH_rel_weightScan[i]->Sumw2(); */
  /* } */
  

  
}

void AnalyzeHGCOctTB::Alignment_Map_Init() {
  char* f_name = new char[200];
  sprintf(f_name,"../Alignment_Map.txt");
  std::ifstream in(f_name);
  if(!in) { 
    cout<<"ERROR => "<<f_name<<" Not found"<<endl;
    //return;
    exit(0);
  }

  //int layer;
  std::pair<float,float> dx_dy;
  std::pair<int, std::pair<float,float> > temp;
  int layer;
  float dx,dy;
  while(in>>layer>>dx>>dy) {
    //run_layer = std::make_pair(run,layer);
    dx_dy = std::make_pair(dx,dy);
    temp = std::make_pair(layer,dx_dy);
    align_map.insert(temp);
  }

  std::cout<<"INFO: Alignment MAP initialized successfully!!!"<<endl;
}

void AnalyzeHGCOctTB::Noise_Map_Init() {
  char* f_name = new char[200];
  sprintf(f_name,"../Noise_Map.txt");
  std::ifstream in(f_name);
  //int layer;
  if(!in) { 
    cout<<"ERROR => "<<f_name<<" Not found"<<endl;
    //return;
    exit(0);
  }
  std::pair<int,int> mod_chip;
  std::pair<std::pair<int,int>, float> temp;
  int layer,mod_id,mod_pos,chip;
  float noise;
  while(in>>layer>>mod_id>>mod_pos>>chip>>noise) {
    //run_layer = std::make_pair(run,layer);
    mod_chip = std::make_pair(mod_id,chip);
    temp = std::make_pair(mod_chip,noise);
    noise_map.insert(temp);
  }

  std::cout<<"INFO: Noise MAP initialized successfully!!!"<<endl;
}


void AnalyzeHGCOctTB::moduleMap_init(const char* config) {
  char *f_name = new char[200];

  if(strcmp(config,"alpha")==0 || strcmp(config,"config1")==0) {
    sprintf(f_name,"../config_maps/moduleMAP_config1.txt");
    cout<<"\n\nINFO: Mapping module configuration ALPHA (oct10-oct17) "<<endl;
    cout<<"INFO: Mapping EE[0]/FH[1]::Layer #[1-40]::Position on Layer[0 for EE]&[1-7 for FH] consult figure for Daisy structure configuration!!!"<<endl;

  }
  else if(strcmp(config,"bravo")==0 || strcmp(config,"config2")==0) {
    sprintf(f_name,"../config_maps/moduleMAP_config2.txt");
    cout<<"\n\nINFO: Mapping module configuration BRAVO (17oct-22oct) "<<endl;
    cout<<"INFO: Mapping EE[0]/FH[1]::Layer #[1-40]::Position on Layer[0 for EE]&[1-7 for FH] consult figure for Daisy structure configuration!!!"<<endl;

  }
  else if(strcmp(config,"charlie")==0  || strcmp(config,"config3")==0) {
    sprintf(f_name,"../config_maps/moduleMAP_config3.txt");
    cout<<"\n\nINFO: Mapping module configuration CHARLIE (23Oct-4Nov) "<<endl;
    cout<<"INFO: Mapping EE[0]/FH[1]::Layer #[1-40]::Position on Layer[0 for EE]&[1-7 for FH] consult figure for Daisy structure configuration!!!"<<endl;

  }
  else {
    cout<<"\n\nERROR: Incorrect configuration entered "<<endl;
    cout<<" Allowed configuration :\n alpha = Configuration 1 (10Oct-17Nov) \n bravo = Configuration 2 (17Oct-22Oct) \n charlie = Configuration 3 (23Oct-17Nov)"<<endl;
    return;
    
  }

  std::ifstream in(f_name);
  if(!in) { 
    cout<<"ERROR => "<<f_name<<" Not found"<<endl;
    //return;
    exit(0);
  }
  int modID_, part_, layer_, pos_;
  cout<<"File name = "<<f_name<<endl;
  while(in>>modID_>>part_>>layer_>>pos_){
    std::pair<int, std::vector<int>> temp_pair;
    std::vector<int> temp_vector;
    temp_vector.push_back(part_);
    temp_vector.push_back(layer_);
    temp_vector.push_back(pos_);
    temp_pair = std::make_pair(modID_,temp_vector);
    module_map.insert(temp_pair);
  }

  cout<<"INFO: Module Mapping Done!!! "<<endl<<endl;


}
// void AnalyzeHGCOctTB::offical_calib_init() {
//   char *f_name = new char[200];
//   sprintf(f_name,"/home/shubham/work/HGCAL/CERNTB/CERN_5_oct_2018/txt_files/official_calib.txt");
//   std::ifstream in(f_name);
//   if(!in){
//     cout<<"Could not find "<<f_name<<endl;
//     return;
//   }
//   int layer_, module_, chip_, channel_;
//   long en_chan;
//   float adc_;
//   while(in>>layer_>>module_>>chip_>>channel_>>adc_){
//     en_chan = chip_*1000+channel_;
//     std::pair<int, int> temp;
//     temp = std::make_pair(layer_,en_chan);
//     std::pair<std::pair<int,int>, float> temp1;
//     temp1 = std::make_pair(temp, adc_);
//     offical_calib_map.insert(temp1);
//   }
// }

// void AnalyzeHGCOctTB::my_calib_init() {
//   char *f_name = new char[200];
//   sprintf(f_name,"/home/shubham/work/HGCAL/CERNTB/CERN_5_oct_2018/txt_files/ADC_MIP_v11.txt");
//   std::ifstream in(f_name);
//   if(!in){
//     cout<<"Could not find "<<f_name<<endl;
//     return;
//   }
//   int layer_, chip_, channel_,entry;
//   long en_chan;
//   float adc_,chi2,mip_err;
//   while(in>>layer_>>chip_>>channel_>>adc_>>chi2>>mip_err>>entry){
//     en_chan = chip_*1000+channel_;
//     std::pair<int,int> temp;
//     temp = std::make_pair(layer_+1,en_chan);
//     std::pair<std::pair<int,int>, float> temp1;
//     temp1 = std::make_pair(temp, adc_);
//     my_calib_map.insert(temp1);
//   }
// }

AnalyzeHGCOctTB::AnalyzeHGCOctTB(const TString &inputFileList, const char *outFileName, const char* dataset, const char* config, const char* energy) {

  TChain *tree = new TChain("rechitntupler/hits");
  TChain *tree2 = new TChain("trackimpactntupler/impactPoints");
  /* TChain *tree3 = new TChain("bigtree"); */


  if( ! FillChain(tree, tree2, inputFileList) ) {
    std::cerr << "Cannot get the tree " << std::endl;
  } else {
    std::cout << "Initiating analysis of dataset " << dataset << std::endl;
  }

  /* if( ! FillChain(tree, tree2, tree3, inputFileList) ) { */
  /*   std::cerr << "Cannot get the tree " << std::endl; */
  /* } else { */
  /*   std::cout << "Initiating analysis of dataset " << dataset << std::endl; */
  /* } */

  /* if( ! FillChain(tree, inputFileList) ) { */
  /*   std::cerr << "Cannot get the tree " << std::endl; */
  /* } else { */
  /*   std::cout << "Initiating analysis of dataset " << dataset << std::endl; */
  /* } */

  //HGCNtupleVariables::Init(tree, tree2, tree3);
  HGCNtupleVariables::Init(tree, tree2);

  BookHistogram(outFileName, config, energy);
  moduleMap_init(config);
  Alignment_Map_Init();
  Noise_Map_Init();
  // offical_calib_init();
  // my_calib_init();
  
}
//Bool_t AnalyzeHGCOctTB::FillChain(TChain *chain, TChain *chain2, TChain *chain3, const TString &inputFileList) {
Bool_t AnalyzeHGCOctTB::FillChain(TChain *chain, TChain *chain2, const TString &inputFileList) {
/* Bool_t AnalyzeHGCOctTB::FillChain(TChain *chain, const TString &inputFileList) { */

  ifstream infile(inputFileList, ifstream::in);
  std::string buffer;

  if(!infile.is_open()) {
    std::cerr << "** ERROR: Can't open '" << inputFileList << "' for input" << std::endl;
    return kFALSE;
  }

  std::cout << "TreeUtilities : FillChain " << std::endl;
  while(1) {
    infile >> buffer;
    if(!infile.good()) break;
    //std::cout << "Adding tree from " << buffer.c_str() << std::endl;                                                              
    chain->Add(buffer.c_str());
    chain2->Add(buffer.c_str());
    /* chain3->Add(buffer.c_str()); */

  }
  std::cout << "No. of Entries in chain  : " << chain->GetEntries() << std::endl;
  std::cout << "No. of Entries in chain2 : " << chain2->GetEntries() << std::endl;
  /* std::cout << "No. of Entries in chain3 : " << chain3->GetEntries() << std::endl; */

  return kTRUE;
}

Long64_t AnalyzeHGCOctTB::LoadTree(Long64_t entry) {
  // Set the environment to read one entry                                                                                          
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    //    Notify();
  }

  if (!fChain2) return -5;
  Long64_t centry2 = fChain2->LoadTree(entry);
  if (centry2 < 0) return centry2;
  if (!fChain2->InheritsFrom(TChain::Class()))  return centry2;
  TChain *chain2 = (TChain*)fChain2;
  if (chain2->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    //    Notify();
  }

  /* if (!fChain3) return -5; */
  /* Long64_t centry3 = fChain3->LoadTree(entry); */
  /* if (centry3 < 0) return centry3; */
  /* if (!fChain3->InheritsFrom(TChain::Class()))  return centry3; */
  /* TChain *chain3 = (TChain*)fChain3; */
  /* if (chain3->GetTreeNumber() != fCurrent) { */
  /*   fCurrent = chain->GetTreeNumber(); */
  /*   //    Notify(); */
  /* } */
  
  //if (centry==centry2)
  return centry;
  // cout<<"centry = "<<centry<<endl;
  // if(centry>0)
  //   return centry;
  // else return -1;
}

AnalyzeHGCOctTB::~AnalyzeHGCOctTB() { 

  // if (!fChain || !fChain2) return;
  // delete fChain->GetCurrentFile();
  // delete fChain2->GetCurrentFile();
  // oFile->cd();
  // oFile->Write();
  // oFile->Close();


  if (!fChain) return;
  delete fChain->GetCurrentFile();
  oFile->cd();
  oFile->Write();
  oFile->Close();

}

#endif

/*  LocalWords:  Nrechit EE R1 FH GetXaxis SetTitle Sumw2 TH2F reg3 NRechits
 */
/*  LocalWords:  GetYaxis SetTitleOffset
 */
