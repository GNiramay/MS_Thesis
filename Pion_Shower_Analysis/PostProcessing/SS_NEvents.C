// Program to print no. of events per shower start

void SS_NEvents()
{
  TFile* tf = new TFile("../MyCheckLeakage/TempOut.root");
  char* htitle = new char[200];
  for(int i=0;i<40;i++){
    sprintf(htitle,"EE_Leak_%i",i+1);
    TH1F* HH = (TH1F*)tf->Get(htitle);
    cout<<HH->GetEntries()<<endl;
  }
}
