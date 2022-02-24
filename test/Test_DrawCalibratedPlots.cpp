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
  TFile *fp          = new TFile("Combined.root", "r");

  for (unsigned int i = 0; i < ismran::vecOfPsBars.size(); i++) {
    std::string histname = ismran::vecOfPsBars[i] + "_QMeanCorrected";
    if (i == 0)
      ((TH1F *)fp->Get(histname.c_str()))->Draw();
    else
      ((TH1F *)fp->Get(histname.c_str()))->Draw("same");
  }
  fApp->Run();
}
