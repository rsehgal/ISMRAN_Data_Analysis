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
  ismran::MuonPeakAnalyzer *muonPeakAnalyzer = new ismran::MuonPeakAnalyzer();
  std::string directoryPath = "/home/rsehgal/ISMRAN_Data_Analysis/datafiles";
  std::vector<std::string> vecOfFileNames = ismran::GetVectorOfFileNameInADirectory(directoryPath);

  for (unsigned int i = 0; i < vecOfFileNames.size(); i++) {

    TTree *peakPosTree = new TTree("MuonPeakPositionsTree", "MuonPeakPositionsTree");
    peakPosTree->Branch("PeakPositions", "ismran::MuonPeakAnalyzer", &muonPeakAnalyzer);
    TFile *peakPosFile = new TFile((directoryPath+"/MuonPeak_"+ismran::GetBaseName(vecOfFileNames[i])).c_str(), "RECREATE");
    std::cout << RED << "Processing file : " << vecOfFileNames[i] << RESET << std::endl;
    muonPeakAnalyzer->SetFileName(vecOfFileNames[i]);
    muonPeakAnalyzer->UpdateFileName();
    peakPosTree->Fill();
    peakPosFile->cd();
    peakPosTree->Write();
    peakPosFile->Close();
    delete peakPosTree;
  }
  return 0;
}
