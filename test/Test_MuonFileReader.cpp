/*
**	Filename : Test_MuonFileReader.cpp
**	2021-10-28
**	username : rsehgal
**
**      Description : Demo to read the Muon tracks store in the root file
*/
#include <iostream>
#include "ScintillatorBar_F.h"
#include "SingleMuonTrack.h"
#include "Analyzer_F.h"
#include "Plotter.h"
#include <TFile.h>
#include "PsBar.h"
#include "Helpers.h"
#include "colors.h"
int main(int argc, char *argv[])
{

  std::vector<ismran::SingleMuonTrack *> smtVec = ismran::GetMuonTracksVector(argv[1]);
  // std::vector<ismran::SingleMuonTrack *> smtVec = ismran::GetMuonTracksVector("MuonTracks.root");
  unsigned int muonCounter = 0;
  for (unsigned int i = 0; i < smtVec.size(); i++) {
    if ((smtVec[i]->size() > 4 ) && muonCounter < 5) {
      muonCounter++;
      std::cout << RED;
      smtVec[i]->Print();
      std::cout << RESET << std::endl;
    }
  }

  /*=====================================================================
   * Below is the Raw code to read the root file containing muon tracks *
   * The code is wrapped in a function called GetMuonTracksVector() in  *
   * Helper.cpp file, which can be called straight forward to get the   *
   * Vector of muon tracks stored in root file, as shown above          *
   *=====================================================================
   */

  /*
  TFile *fp         = new TFile("MuonTracks.root", "r");
  TTree *TracksTree = (TTree *)fp->Get("TracksTree");
  ismran::SingleMuonTrack *smt = new ismran::SingleMuonTrack;
  // Set branch addresses.
  TracksTree->SetBranchAddress("MuonTracks", &smt);
  Long64_t nentries = TracksTree->GetEntries();
  std::cout << "Num. of Muon tracks store in file : " << nentries << std::endl;
  Long64_t nbytes = 0;
  std::vector<ismran::SingleMuonTrack *> smtVec;
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += TracksTree->GetEntry(i);
    smtVec.push_back(new ismran::SingleMuonTrack(*smt));
   if(i<10)
    smt->Print();
  }
  fp->Close();
  */

  return 0;
}
