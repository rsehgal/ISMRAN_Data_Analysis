/*
**	Filename : Test_Analyzer_F_Shots.cpp
**	2021-10-27
**	username : rsehgal
*/
#include <iostream>
#include "Analyzer_F.h"
#include "Plotter.h"
#include <TFile.h>
#include "ScintillatorBar_F.h"
#include "Helpers.h"
#include "colors.h"
#include "HardwareNomenclature.h"
int main(int argc, char *argv[])
{
  std::string fileName = argv[1];
  // std::string peakPosFileLoc = "/home/rsehgal/myAmbar/February2022/muonEnergyCalib";
  // std::string peakPosFileLoc = "/home/rsehgal/myAmbar/MuonSinglePointCalibration";
  std::string peakPosFileLoc = ".";
  // std::string peakPosFileLoc = "../datafiles";
  std::string fullPathPeakPosFile = peakPosFileLoc + "/MuonPeak_" + ismran::GetBaseName(fileName);
  std::cout << RED << fullPathPeakPosFile << RESET << std::endl;

#ifdef USE_EXISTING_MUON_PEAK_FILE
  ismran::vecOfPeakPos = ismran::GetPeakPosVec_Direct(".", "MuonPeak.root");
#else
  ismran::vecOfPeakPos = ismran::GetPeakPosVec();//peakPosFileLoc, ismran::GetBaseName(fileName));
#endif
  std::string outputFileName = argv[2];

  /* Accepting NumOfShots and ShotNo from the caller or a calling shell script*/
  ismran::Analyzer_F::numOfShots = std::atoi(argv[3]);
  ismran::Analyzer_F::shotNo     = std::atoi(argv[4]);

  ismran::Analyzer_F an(fileName);
  std::vector<std::shared_ptr<ismran::ScintillatorBar_F>> vecOfScint = an.GetVectorOfScintillators();
  ismran::InitializeHistograms();
  for (unsigned int i = 0; i < vecOfScint.size(); i++) {
    if (i < 5) {
      std::cout << "--------------------------------------" << std::endl;
      if (vecOfScint[i]->GetBarIndex() < 96) vecOfScint[i]->Print();
    }
  }
  std::vector<std::shared_ptr<TH1F>> vecOfQMeanHist = ismran::GetQMeanPlots(vecOfScint);
  std::vector<std::shared_ptr<TH1F>> vecOfQMeanCorrectedHist =
      ismran::GetQMeanCorrectedPlots(vecOfScint); //,ismran::vecOfPeakPos);
  TFile *fp = new TFile(outputFileName.c_str(), "RECREATE");
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
    vecOfQMeanCorrectedHist[i]->Write();
  }

  fp->cd();
  can->Write();

  fp->Close();
  return 0;
}
