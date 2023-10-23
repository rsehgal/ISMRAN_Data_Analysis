/*
**	Filename : Test_Analyzer_F.cpp
**	2021-10-06
**	username : rsehgal
*/
#include <iostream>
#include "Analyzer_F.h"
#include "Plotter.h"
#include <TFile.h>
#include "ScintillatorBar_F.h"
#include "HardwareNomenclature.h"
#include "Helpers.h"
#include <TApplication.h>
#include <TH1F.h>

int main(int argc, char *argv[])
{
  // ismran::Analyzer_F an(argv[1],10000000);

  TFile *fr   = new TFile("calibration.root", "r");
  TF1 *eCalib = (TF1 *)fr->Get("PS5_S2AB1006_ECalib");
  fr->Close();

  TApplication *fApp = new TApplication("test", NULL, NULL);

  ismran::Analyzer_F an(argv[1], 0);

  std::vector<ismran::ScintillatorBar_F *> vecOfScint = an.GetVectorOfScintillators();
  std::cout << "SIZE of SCINT VECTOR : " << vecOfScint.size() << std::endl;

  TH1F *hist = new TH1F("test", "test", 1000, 0, 2000.);
  for (unsigned int i = 0; i < vecOfScint.size(); i++) {

        hist->Fill(eCalib->Eval(vecOfScint[i]->GetQMean()));
    /*if (vecOfScint[i]->GetBarIndex() >= 0 && vecOfScint[i]->GetBarIndex() < 90)
      if (ismran::vecOfPsBars[vecOfScint[i]->GetBarIndex()] == "PS05_S2AB1006") {
        hist->Fill(eCalib->Eval(vecOfScint[i]->GetQMean()) / 1000.);
      }*/
  }

  /*ismran::InitializeHistograms();
  for (unsigned int i = 0; i < vecOfScint.size(); i++) {
    if (i < 5) {

      std::cout << "--------------------------------------" << std::endl;
      if (vecOfScint[i]->GetBarIndex() < 96) vecOfScint[i]->Print();
    }
  }
  std::vector<TH1F*> vecOfQMeanHist = ismran::GetQMeanCorrectedPlots(vecOfScint);

  TFile *fp = new TFile("hists.root", "RECREATE");
  fp->cd();
  TCanvas *can = new TCanvas("AllBars", "AllBars");

  for (unsigned int i = 0; i < vecOfQMeanHist.size(); i++) {
    can->cd();
    if (i == 0)
      vecOfQMeanHist[i]->Draw();
    else
      vecOfQMeanHist[i]->Draw("same");
    fp->cd();
    vecOfQMeanHist[i]->Write();
  }
  fp->Close();

*/
  hist->Draw();
  fApp->Run();
  return 0;
}
