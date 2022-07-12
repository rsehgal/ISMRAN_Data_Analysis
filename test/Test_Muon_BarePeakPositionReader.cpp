/*
**	Filename : Test_MuonPeakPositionReader.cpp
**	2022-02-20
**	username : rsehgal
*/
#include <iostream>
#include "ScintillatorBar_F.h"
#include "SingleMuonTrack.h"
#include "Analyzer_F.h"
#include "Plotter.h"
#include <TFile.h>
#include "PsBar.h"
#include "Helpers.h"
#include "MuonPeakAnalyzer.h"
#include "TTree.h"
#include <vector>
#include <string>
#include <TApplication.h>
int main(int argc, char *argv[])
{
  TFile *fp                              = new TFile(argv[1], "r");
  TTree *MuonPeakPositionsTree           = (TTree *)fp->Get("MuonPeakPositionsTree");
  ismran::MuonPeakAnalyzer *peakAnalyzer = new ismran::MuonPeakAnalyzer;
  // Set branch addresses.
  MuonPeakPositionsTree->SetBranchAddress("PeakPositions", &peakAnalyzer);
  Long64_t nentries = MuonPeakPositionsTree->GetEntries();

 Long64_t nbytes = 0;
 MuonPeakPositionsTree->GetEntry(0);
 std::vector<unsigned int> vecOfPeakPos =  peakAnalyzer->GetVectorOfPeakPositions();
  fp->Close();
  for (unsigned int i = 0; i < vecOfPeakPos.size(); i++) {
    std::cout << vecOfPeakPos[i] << " , ";
  }
  std::cout << std::endl;
}
