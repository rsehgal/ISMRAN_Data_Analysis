/*
**	Filename : Helpers.cpp
**	2021-10-27
**	username : rsehgal
*/

#include "Helpers.h"
#include "SingleMuonTrack.h"
namespace ismran {

bool CompareTimestampScintillator(ScintillatorBar_F *i1, ScintillatorBar_F *i2)
{
  return (i1->GetTStampSmall() < i2->GetTStampSmall());
}

std::vector<ismran::SingleMuonTrack *> GetMuonTracksVector(std::string filename, std::string treeName,
                                                           unsigned int numOfEvents)
{
  TFile *fp         = new TFile(filename.c_str(), "r");
  TTree *TracksTree = (TTree *)fp->Get(treeName.c_str());
  // Declaration of leaves types
  ismran::SingleMuonTrack *smt = new ismran::SingleMuonTrack;
  // Set branch addresses.
  TracksTree->SetBranchAddress("MuonTracks", &smt);
  Long64_t nentries = TracksTree->GetEntries();
  if (numOfEvents > 0) nentries = numOfEvents;
  std::cout << "Num. of Muon tracks store in file : " << nentries << std::endl;
  Long64_t nbytes = 0;
  std::vector<ismran::SingleMuonTrack *> smtVec;
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += TracksTree->GetEntry(i);
    smtVec.push_back(new ismran::SingleMuonTrack(*smt));
    // if (i < 10) smt->Print();
  }
  fp->Close();
  return smtVec;
}

} // namespace ismran
