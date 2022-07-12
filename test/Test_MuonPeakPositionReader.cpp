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
  TApplication *fApp                     = new TApplication("Test", NULL, NULL);
  //TFile *fp                              = new TFile("MuonPeak_Feb2022.root", "r");
  TFile *fp                              = new TFile(argv[1], "r");
  TTree *MuonPeakPositionsTree           = (TTree *)fp->Get("MuonPeakPositionsTree");
  ismran::MuonPeakAnalyzer *peakAnalyzer = new ismran::MuonPeakAnalyzer;
  // Set branch addresses.
  MuonPeakPositionsTree->SetBranchAddress("PeakPositions", &peakAnalyzer);
  Long64_t nentries = MuonPeakPositionsTree->GetEntries();

  TFile *fpOut = new TFile("out.root", "RECREATE");
  std::vector<TH1F *> vecOfHistOfPeakShift;

  for (unsigned int i = 0; i < 96; i++) {
    std::string histName = "HistPeakShift" + std::to_string(i);
    vecOfHistOfPeakShift.push_back(new TH1F(histName.c_str(), histName.c_str(), 7000, 8000, 15000));
  }
  Long64_t nbytes = 0;
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += MuonPeakPositionsTree->GetEntry(i);

    for (unsigned int j = 0; j < 96; j++) {
      vecOfHistOfPeakShift[j]->Fill(peakAnalyzer->GetVectorOfPeakPositions()[j]);
	std::cout <<"BarIndex : " << (j+1) <<" : PeakPos : " << peakAnalyzer->GetVectorOfPeakPositions()[j] << std::endl;
    }
    // std::cout << "FileName  ; " << peakAnalyzer->GetFileName() << std::endl;
  }
  fp->Close();
  fpOut->cd();
  for (unsigned int i = 0; i < 96; i++) {
    vecOfHistOfPeakShift[i]->Write();
  }
  fpOut->Close();
  // fApp->Run();
}
