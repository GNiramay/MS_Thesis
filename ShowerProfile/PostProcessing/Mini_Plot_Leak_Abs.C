// A mini progrm to plot Leak_Abs 2D hists
#include "JustPlotIt.C"

TString DATE = "26_08_19";
TString PATH_WWW="/afs/cern.ch/user/n/ngogate/www/PionShower/LeakFr_Abs_"+DATE+"/";

void Mini_Plot_Leak_Abs()
{
  TString HH[6] = {"1","2","3","4","5","6"}; // the index needed for following hists
  TString DD[6]={"0 to 0.35","0.35 to 0.75","0.75 to 1.03","1.03 to 1.43","1.43 to 2.7","more than 2.7"};// The depth of each compartment

  for(int i=0;i<6;i++)
  // for(int i=0;i<1;i++)
    {
      TCanvas* aa = JustPlotIt("LeakFr_Abs_"+HH[i],2);

      // aa->SaveAs("PNG/LeakFr_Abs_14_08_19/LeakFr_Abs_"+HH[i]+".png");
      // aa->SaveAs("PDF/LeakFr_Abs_14_08_19/LeakFr_Abs_"+HH[i]+".pdf");

      aa->SaveAs("PNG/LeakFr/LeakFr_Abs_"+HH[i]+"_"+DATE+".png");
      aa->SaveAs("PDF/LeakFr/LeakFr_Abs_"+HH[i]+"_"+DATE+".pdf");

      delete aa;
    }
    // gSystem->Exec("scp PNG/LeakFr/LeakFr_Abs_"+"*"+DATE+".png ngogate@lxplus7.cern.ch:"+PATH_WWW);
    gSystem->Exec("scp PNG/LeakFr/*"+DATE+".png ngogate@lxplus7.cern.ch:"+PATH_WWW);
}
