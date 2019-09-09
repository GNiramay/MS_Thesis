#ifndef AnalyzeHGCOctTB_H
#define AnalyzeHGCOctTB_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "HGCNtupleVariables.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TProfile.h"
#include "TLorentzVector.h"
#include "TDirectory.h"

class AnalyzeHGCOctTB : public HGCNtupleVariables{

 public:
  AnalyzeHGCOctTB(const TString &inputFileList="foo.txt", const char *outFileName="histo.root",const char *dataset="data", const char *config="alpha", const char* energy = "-1");
  ~AnalyzeHGCOctTB();
  Bool_t   FillChain(TChain *chain, TChain *chain2, TChain *chain3, const TString &inputFileList);
  /* Bool_t   FillChain(TChain *chain, const TString &inputFileList); */
  Long64_t LoadTree(Long64_t entry);
  void     EventLoop(const char *);
  void     BookHistogram(const char *, const char *, const char* energy);

  void moduleMap_init(const char *);
  void Alignment_Map_Init();
  void Noise_Map_Init();

  TFile *oFile;
  
  const char *conf_;  
  int inEnergy_;

  // TH1F* h_particleID;
  // TH1F* h_nTracks;
  // TH1F* h_beamEnergy;
  // TH1F* h_runNumber;
  // TH1F* h_moduleID;
  // TH1F* h_shower_start;
  // TH1F* h_shower_start_reg1;
  // TH1F* h_shower_start_reg2;
  // TH1F* h_shower_start_reg3;
  // TH1F* h_En_Res[40];		// Niramay. Histo to store energy
  // TH2F* h2_Lat_6[7];		// Niramay. Lateral shower profile in Lyr6 when shower starts in nearby layers
  // TH1F* h2_Lat_en_6[7];		// Niramay. Energy in dR=2cm in Lyr6 when shower starts in nearby layers
  // TH1F* h_nrec_6[7];
  // TH1F* h_nrec_26[25];
  // TH1F* h_En_EEnFH;		// Niramay. Total rechit energy EE+FH
  // TH2F* h2_EE_FH[40];		// Niramay. Tot En in EE vs tot En in FH
  // TH1F* h_Reco_En[40];		// Niramay. Reconstructed energy
  // TH1F* h_en_EE2;		// Net en distribution for ss in layer 2
  // TH1F* h_en_EE14;		// Net en distributiom for ss in EE 14
  // TH1F* h_en_EE28;		// Net en distributiom for ss in EE 28
  // TH1F* h_en_FH2;		// Net en distributiom for ss in FH 2

  TH1F* RecEn[6];		// Weighted Reco Energy (in compartments)
  TH1F* TotRecEn;		// Weighted Reco Energy (inclusive)
  
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
    x_2D_max = 5000;
    xbin = 500;
    y_2D_max = 200;
    inEnergy_ = 50;
  }
  else if(!strcmp(energy, "80")) {
    y_max = 200.0;
    x_2D_max = 8000;
    xbin = 400;
    y_2D_max = 3000;
    inEnergy_ = 80;
  }
  else if(!strcmp(energy, "100")) {
    y_max = 300.0;
    x_2D_max = 10000;
    xbin = 500;
    y_2D_max = 3000;
    inEnergy_ = 100;
  }
  else if(!strcmp(energy, "120")) {
    y_max = 400.0;
    x_2D_max = 12000;
    xbin = 300;
    y_2D_max = 3200;
    inEnergy_ = 120;
  }
  else if(!strcmp(energy, "200")) {
    y_max = 600.0;
    x_2D_max = 18000;
    xbin = 360;
    y_2D_max = 4800;
    inEnergy_ = 200;
  }
  else if(!strcmp(energy, "250")) {
    y_max = 700.0;
    x_2D_max = 25000;
    xbin = 500;
    /* x_2D_max = 20000; */
    y_2D_max = 6000;
    inEnergy_ = 250;
  }
  else if(!strcmp(energy, "300")) {
    y_max = 800.0;
    x_2D_max = 25000;
    /* x_2D_max = 20000; */
    xbin = 50;
    y_2D_max = 6000;
    inEnergy_ = 300;
  }
  else {
    cout<<"invalid energy!!!"<<endl; 
    return;
  }
  conf_ = conf;
  oFile = new TFile(outFileName, "recreate");

  // h_nTracks = new TH1F("h_nTracks","Tracks",12,-1,5);
  // h_nTracks->GetXaxis()->SetTitle("Tracks");

  ////////////// Niramay's Histograms
  TString HH[6] = {"1","2","3","4","5","6"}; // the index needed for following hists
  TString DD[6]={"0 to 0.35","0.35 to 0.75","0.75 to 1.03","1.03 to 1.43","1.43 to 2.7","more than 2.7",};// The depth of each compartment
  TString title;
  for(int i=0;i<6;i++)
    {
      title = "RecEn_";
      RecEn[i] = new TH1F(title+HH[i],"Energy Reconstruction | SS at depth "+DD[i]+" #lambda", 100, 0, 2*inEnergy_ );
      RecEn[i]->GetXaxis()->SetTitle("Weighted Reco energy (in GeV)");
      RecEn[i]->GetYaxis()->SetTitle("No. of events");
  }

  title = "TotRecEn";
  TotRecEn = new TH1F(title,"Energy Reconstruction ", 100, 0, 2*inEnergy_ );
  TotRecEn->GetXaxis()->SetTitle("Weighted Reco energy (in GeV)");
  TotRecEn->GetYaxis()->SetTitle("No. of events");

  //////////////////////////// The END

 // /* h_configuration = new TH1F("h_configuration","Configuration",60,-10,50); */
 //  h_particleID = new TH1F("h_particleID","particleID",500,0,500);
 //  h_beamEnergy = new TH1F("h_beamEnergy","beamEnergy",500,0,500);
 //  h_runNumber = new TH1F("h_runNumber","RunNumber",2000,0,2000);
 //  h_moduleID = new TH1F("h_moduleID","moduleID",4,-2,2);
 //  h_En_EEnFH = new TH1F("h_En_EEnFh","Total energy recorded (EE + FH)",300,0,30000);
  
 //  h_shower_start = new TH1F("h_shower_start","h_shower_start",10000,-2.0,5.0);
 //  h_shower_start->GetXaxis()->SetTitle("#lambda_{0}");
 //  h_shower_start->Sumw2();

  
 //  h_shower_start_reg1 = new TH1F("h_shower_start_reg1","h_shower_start_reg1",10000,-2.0,5.0);
 //  h_shower_start_reg1->GetXaxis()->SetTitle("#lambda_{0}");
 //  h_shower_start_reg1->Sumw2();

  
 //  h_shower_start_reg2 = new TH1F("h_shower_start_reg2","h_shower_start_reg2",10000,-2.0,5.0);
 //  h_shower_start_reg2->GetXaxis()->SetTitle("#lambda_{0}");
 //  h_shower_start_reg2->Sumw2();

  
 //  h_shower_start_reg3 = new TH1F("h_shower_start_reg3","h_shower_start_reg3",10000,-2.0,5.0);
 //  h_shower_start_reg3->GetXaxis()->SetTitle("#lambda_{0}");
 //  h_shower_start_reg3->Sumw2();
 
  
 //  for(int i=0;i<40;i++){
 //    char* title=new char[100];
 //    char* title2 = new char[500];
 //    sprintf(title,"h_En_Res_%i",i);
 //    /* h_En_Res[i]=new TH1F(title,"Total rechit energy when shower started in this layer",100,0,20000); */
 //    h_En_Res[i]=new TH1F(title,"Total rechit energy when shower started in this layer",75,0,150*inEnergy_);

 //    sprintf(title,"h2_EE_FH_%i",i);
 //    sprintf(title2,"Total energy in FH vs EE when shower started in Layer %i",i+1);
 //    h2_EE_FH[i] = new TH2F(title,title2,500,0,20000,100,0,20000);

 //    sprintf(title,"h_Reco_En_%i",i);
 //    sprintf(title2,"Reconstructed energy when shower started in layer %i",i+1);
 //    // h_Reco_En[i] = new TH1F(title,title2,100,0,800);
 //    h_Reco_En[i] = new TH1F(title,title2,y_max/5,0,y_max);
 //  }

  // for(int i=2;i<9;i++){
  //   char* title1=new char[50];
  //   char* title2=new char[50];
  //   sprintf(title1,"Lat_Shwr_%i",i);
  //   sprintf(title2,"later shower profile in layer 6 when shower started in layer %i",i);
  //   h2_Lat_6[i-2] = new TH2F(title1,title2,200,-10,10,200,-10,10);
  // }

//   for(int i=0;i<7;i++){
//     char* title1=new char[500];
//     char* title2=new char[500];

//     sprintf(title1,"Lat_Shwr_%i",i+2);
//     sprintf(title2,"later shower profile in layer 6 when shower started in layer %i",i+2);
//     h2_Lat_6[i] = new TH2F(title1,title2,16,-8,8,16,-8,8);

//     sprintf(title1,"h_lat_en_%i",i+2);
//     sprintf(title2,"later energy in R < 2cm when shower in %i",i+2);    
//     h2_Lat_en_6[i] = new TH1F(title1,title1,500,0,1000);

//     sprintf(title1,"h_nrec_6_%i",i+2);
//     sprintf(title2,"Total NRechits in Layer 6 when shower in %i",i+2);    
//     h_nrec_6[i] = new TH1F(title1,title2,100,0,100);
//   }

//   for(int ii=0;ii<25;ii++){
//     char* title1=new char[500];
//     char* title2=new char[500];

//     sprintf(title1,"Tot_nrec26_%i",ii+2);
//     sprintf(title2,"Total energy within dR=2 in Layer 26 when shower in %i",ii+2);    
//     h_nrec_26[ii] = new TH1F(title1,title2,200,0,2000);
//   }

//   h_en_EE2 = new TH1F("EE2_RE","Rechits energy distribution for SS in EE Layer 2",100,0,100*inEnergy_);
//   h_en_EE14 = new TH1F("EE14_RE","Rechits energy distribution for SS in EE Layer 14",100,0,100*inEnergy_);
//   h_en_EE28 = new TH1F("EE28_RE","Rechits energy distribution for SS in EE Layer 28",100,0,100*inEnergy_);
//   h_en_FH2 = new TH1F("FH2_RE","Rechits energy distribution for SS in FH Layer 2",100,0,100*inEnergy_);
}

void AnalyzeHGCOctTB::Alignment_Map_Init() {
  char* f_name = new char[200];
  sprintf(f_name,"MIPalignment_run718.txt");
  std::ifstream in(f_name);
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
  if(!in){
    cout<<"Could not find "<<f_name<<endl;
    return;
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
  TChain *tree3 = new TChain("bigtree");


  if( ! FillChain(tree, tree2, tree3, inputFileList) ) {
    std::cerr << "Cannot get the tree " << std::endl;
  } else {
    std::cout << "Initiating analysis of dataset " << dataset << std::endl;
  }

  /* if( ! FillChain(tree, inputFileList) ) { */
  /*   std::cerr << "Cannot get the tree " << std::endl; */
  /* } else { */
  /*   std::cout << "Initiating analysis of dataset " << dataset << std::endl; */
  /* } */

  HGCNtupleVariables::Init(tree, tree2, tree3);

  BookHistogram(outFileName, config, energy);
  moduleMap_init(config);
  Alignment_Map_Init();
  Noise_Map_Init();

  // offical_calib_init();
  // my_calib_init();
  
}
Bool_t AnalyzeHGCOctTB::FillChain(TChain *chain, TChain *chain2, TChain *chain3, const TString &inputFileList) {
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
    chain3->Add(buffer.c_str());

  }
  std::cout << "No. of Entries in chain  : " << chain->GetEntries() << std::endl;
  std::cout << "No. of Entries in chain2 : " << chain2->GetEntries() << std::endl;
  std::cout << "No. of Entries in chain3 : " << chain3->GetEntries() << std::endl;

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

  if (!fChain3) return -5;
  Long64_t centry3 = fChain3->LoadTree(entry);
  if (centry3 < 0) return centry3;
  if (!fChain3->InheritsFrom(TChain::Class()))  return centry3;
  TChain *chain3 = (TChain*)fChain3;
  if (chain3->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    //    Notify();
  }
  
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
