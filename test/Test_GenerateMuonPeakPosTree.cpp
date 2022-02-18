/*
**	Filename : Test_GenerateMuonPeakPosTree.cpp
**	2022-02-17
**	username : rsehgal
*/
#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include <vector>
#include <string>
#include "MuonPeakAnalyzer.h"
#include <TROOT.h>
#include "Helpers.h"
#include "colors.h"
int main(int argc, char *argv[])
{
  // TFile *peakPosFile                         = new TFile("MuonPeakPositions.root", "RECREATE");
  std::string filename                       = argv[1];
  TFile *peakPosFile                         = new TFile(argv[2], "RECREATE");
  TTree *peakPosTree                         = new TTree("MuonPeakPositionsTree", "MuonPeakPositionsTree");
  ismran::MuonPeakAnalyzer *muonPeakAnalyzer = new ismran::MuonPeakAnalyzer();
  peakPosTree->Branch("PeakPositions", "ismran::MuonPeakAnalyzer", &muonPeakAnalyzer);

  // std::string filename =
  //  "/home/rsehgal/AmbarData/Dhruva/February2022/data/ISMRAN_digiROOT_RON_14hrs25mins54secs_08Feb2022_Run2235.root";

  /*std::string directoryPath               = "/home/rsehgal/AmbarData/Dhruva/February2022/data";
  std::vector<std::string> vecOfFileNames = ismran::GetVectorOfFileNameInADirectory(directoryPath);

  for (unsigned int i = 0; i < vecOfFileNames.size(); i++) {
    std::cout << RED << "Processing file : " << vecOfFileNames[i] << RESET << std::endl;
    muonPeakAnalyzer->SetFileName(vecOfFileNames[i]);
    peakPosTree->Fill();
  }*/

  muonPeakAnalyzer->SetFileName(filename);
  muonPeakAnalyzer->UpdateFileName();
  peakPosTree->Fill();
  peakPosFile->cd();
  peakPosTree->Write();
  peakPosFile->Close();
  return 0;
}
