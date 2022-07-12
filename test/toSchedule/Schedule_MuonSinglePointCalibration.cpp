/*
**	Filename : Test_PeakPosition.cpp
**	2022-02-17
**	username : rsehgal
*/
#include <iostream>
#include "MuonPeakAnalyzer.h"
#include "colors.h"
#include <string>
#include <TFile.h>
#include <TTree.h>
#include "Helpers.h"
int main(int argc, char *argv[])
{
  std::string directoryPath = "~/myAmbar/MuonSinglePointCalibration";
  TFile *peakPosFile =
      new TFile((directoryPath + "/MuonPeak_" + ismran::GetBaseName(std::string(argv[1]))).c_str(), "RECREATE");
  TTree *peakPosTree                         = new TTree("MuonPeakPositionsTree", "MuonPeakPositionsTree");
  ismran::MuonPeakAnalyzer *muonPeakAnalyzer = new ismran::MuonPeakAnalyzer;
  peakPosTree->Branch("PeakPositions", "ismran::MuonPeakAnalyzer", &muonPeakAnalyzer);
  muonPeakAnalyzer->SetFileName(argv[1]);
  muonPeakAnalyzer->UpdateFileName();
  peakPosTree->Fill();
  peakPosFile->cd();
  peakPosTree->Write();
  peakPosFile->Close();

  /*  std::vector<unsigned int> vecOfMuonPeaks = mpa.GetVectorOfPeakPositions();

    std::cout << "Size of peak vector : " << vecOfMuonPeaks.size() << std::endl;
    for (unsigned int i = 0; i < vecOfMuonPeaks.size(); i++) {
      if (i == 0) std::cout << vecOfMuonPeaks[i] << " , ";
      if ((i % 9) && i != 0)
        std::cout << vecOfMuonPeaks[i] << " , ";
      else
        std::cout << std::endl;
    }*/
  return 0;
}
