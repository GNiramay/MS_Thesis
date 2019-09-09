// Program to find scaling weights so that the 
// energy histograms peak at the beam energy
// To write the output to the file, execute:
// root -l -b -q FindWeights.C >>ScalingWeights.txt

Double_t DEnergy[8] = {300,250,200,120,100,80,50,20}; // double_t energy
TString SEnergy[8] = {"300","250","200","120","100","80","50","20"}; // TString energy
TString HH[6] = {"1","2","3","4","5","6"}; // the index needed for following hists

void WriteDown(int E_index,TFile* tf1,TFile* tf2);

void FindWeights()
{

  for(int i = 0;i<8;i++)
    {
      TFile* tf1 = new TFile("../MyCheckLeakage/Pion_Sim_"+SEnergy[i]+"_temp.root");
      TFile* tf2 = new TFile("CERN_Root_Files/All_"+SEnergy[i]+".root");
      WriteDown(i,tf1,tf2);
    }
}

void WriteDown(int E_index,TFile* tf1,TFile* tf2)
{
  for(int i=0;i<6;i++)
    {
      TH1F* ABS1 = (TH1F*)tf1->Get("Sum_Abs_"+HH[i]);
      TH1F* LIK1 = (TH1F*)tf1->Get("Sum_Abs_Leak_"+HH[i]);
      TH1F* WGT1 = (TH1F*)tf1->Get("RecEn_"+HH[i]);
      TH1F* DAT1 = (TH1F*)tf2->Get("RecEn_"+HH[i]);

      Double_t wt1 = DEnergy[E_index]/ABS1->GetMean();
      Double_t wt2 = DEnergy[E_index]/LIK1->GetMean();
      Double_t wt3 = DEnergy[E_index]/WGT1->GetMean();
      Double_t wt4 = DEnergy[E_index]/DAT1->GetMean();

      printf("%.f\t%i\t%f\t%f\t%f\t%f\n",DEnergy[E_index],i,wt1,wt2,wt3,wt4);
    }
}
