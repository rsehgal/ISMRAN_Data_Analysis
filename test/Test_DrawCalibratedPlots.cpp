/*
**	Filename : Test_DrawCalibratedPlots.cpp
**	2022-02-24
**	username : rsehgal
*/
#include <iostream>
#include "Helpers.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "HardwareNomenclature.h"
#include <string>
#include "TApplication.h"
int main(int argc, char *argv[])
{
  TApplication *fApp = new TApplication("TEST", NULL, NULL);
  TFile *fp          = new TFile(argv[1], "r");
  // TFile *fp          = new TFile("Combined.root", "r");

  for (unsigned int i = 0; i < ismran::vecOfPsBars.size(); i++) {
/*    if (ismran::vecOfPsBars[i] == "PS63_S3AA1778" || ismran::vecOfPsBars[i] == "PS66_S1AA6639" ||
        ismran::vecOfPsBars[i] == "PS68_S3AA1780" || ismran::vecOfPsBars[i] == "PS20_S2AB0718" ||
        ismran::vecOfPsBars[i] == "PS65_S3AA1782" || ismran::vecOfPsBars[i] == "PS70_S3AA1785" ||
        ismran::vecOfPsBars[i] == "PS44_S1AA6524" || ismran::vecOfPsBars[i] == "PS03_S3AA1783" ||
        ismran::vecOfPsBars[i] == "PS17_S1AA6527" || ismran::vecOfPsBars[i] == "PS71_SF874") */

     //if(i==1 || i==2 || i==8 || i==11 || i==18 || i==32 || i==42 || i==45 || i==48 || i==49|| i==53 || i==54 || i==58 || i==61 || i==69 || i==80)
if(0)
continue;
else
{
      std::string histname = ismran::vecOfPsBars[i] + "_QMeanCorrected";
      // std::string histname = ismran::vecOfPsBars[i] + "_QMean";
      TH1F *hist = ((TH1F *)fp->Get(histname.c_str()));
      // hist->Scale(1. / hist->Integral());
      // hist->SetLineColor(i + 1);
      // hist->Rebin(4);
      if (i == 0) hist->Draw();
      //((TH1F *)fp->Get(histname.c_str()))->Draw();
      else
        hist->Draw("same");
      //((TH1F *)fp->Get(histname.c_str()))->Draw("same");
    }

   // else
      //continue;
  }
  fApp->Run();
}
