/*
**	Filename : Analyzer_F.cpp
**	2021-10-06
**	username : rsehgal
*/
#include <iostream>
#include "Analyzer_F.h"
#include "ScintillatorBar_F.h"
#include "Helpers.h"
#include "SingleMuonTrack.h"
namespace ismran {

unsigned int Analyzer_F::numOfShots = 1;
unsigned int Analyzer_F::shotNo     = 1;

Analyzer_F::Analyzer_F() {}
Analyzer_F::Analyzer_F(std::string datafilename,unsigned int numOfEvents)
{
  fDatafileName = datafilename;
  LoadData(numOfEvents);
}
Analyzer_F::~Analyzer_F() {}

/*Function to load the data and in the vector of Scintillator_F*/
void Analyzer_F::LoadData(unsigned int numOfEvents)
{
  TFile *fp = new TFile(fDatafileName.c_str(), "r");

  UShort_t fBrCh;
  ULong64_t fTstamp;
  UInt_t fTime;
  UInt_t fQlong;
  Int_t fDelt;

  TTree *tr = (TTree *)fp->Get("ftree");

  tr->SetBranchAddress("fBrCh", &fBrCh);
  tr->SetBranchAddress("fQlong", &fQlong);
  tr->SetBranchAddress("fTstamp", &fTstamp);
  tr->SetBranchAddress("fTime", &fTime);
  tr->SetBranchAddress("fDelt", &fDelt);

  TTimeStamp *times = new TTimeStamp();
  Long64_t nEntries = tr->GetEntries();
  if(numOfEvents > 0)
	nEntries = numOfEvents;
  std::cout << "Total number of Entries : " << nEntries << std::endl;
  Long64_t nb = 0;

  /* Injecting shots mechanism */
  unsigned long int numOfEventsInOneShot = nEntries / numOfShots;
  Long64_t startEvNo                     = (shotNo - 1) * numOfEventsInOneShot;
  Long64_t endEvNo                       = shotNo * numOfEventsInOneShot;

  // for (Long64_t iev = 0; iev < nEntries; iev++) {
  for (Long64_t iev = startEvNo; iev < endEvNo; iev++) {
    nb += tr->GetEntry(iev);
    if (0) std::cout << fBrCh << " , " << fQlong << " , " << fTstamp << " , " << fTime << " , " << fDelt << std::endl;

    fVecOfScint_F.push_back(new ScintillatorBar_F(fBrCh, fQlong, fTstamp, fTime, fDelt));

    if (iev % 1000000 == 0) {
      // times->Set(time, kTRUE, offset, kFALSE);
      std::cout << " Processing event : " << iev << "\t" << times->GetTimeSpec() << std::endl;
    }

  } //! event loop

  fp->Close();
}

std::vector<SingleMuonTrack*> Analyzer_F::ReconstructMuonTrack()
{
  std::cout << "Going to Create Muon Tracks.................." << std::endl;
  std::sort(fVecOfScint_F.begin(), fVecOfScint_F.end(), CompareTimestampScintillator);
  unsigned int scintVecSize = fVecOfScint_F.size();
  std::cout << "ScintVectSize : " << scintVecSize << std::endl;
  SingleMuonTrack *singleMuonTrack = new SingleMuonTrack();
  std::vector<SingleMuonTrack *> smtVec;

  TFile *tracksFile      = new TFile("MuonTracks.root", "RECREATE");
  TTree *tracksTree      = new TTree("TracksTree", "TracksTree");
  tracksTree->Branch("MuonTracks", "ismran::SingleMuonTrack", &singleMuonTrack);

  ULong64_t tStart                 = fVecOfScint_F[0]->GetTStampSmall();
  for (unsigned int i = 1; i < scintVecSize; i++) {
    if (fVecOfScint_F[i]->GetQMeanCorrected() > qmeanCorrThreshold) {
      if (std::fabs(fVecOfScint_F[i]->GetTStampSmall() - tStart) < 20000) {
        // Within 20ns window
        singleMuonTrack->push_back(fVecOfScint_F[i]);
        if (fVecOfScint_F[i]->GetTStampSmall() < tStart) tStart = fVecOfScint_F[i]->GetTStampSmall();
      } else {
	//Previous muon event over
        singleMuonTrack->Sort();
        //singleMuonTrack->Print();
	smtVec.push_back(new SingleMuonTrack(*singleMuonTrack));
	tracksTree->Fill();
	singleMuonTrack->clear();
     	singleMuonTrack->push_back(fVecOfScint_F[i]);
        tStart = fVecOfScint_F[i]->GetTStampSmall();
        
      }
    }
  }
std::cout << "SmtVec size : " << smtVec.size() << std::endl;
tracksTree->Write();
tracksFile->Close();
return smtVec;
}

std::vector<ScintillatorBar_F *> Analyzer_F::GetVectorOfScintillators()
{
  return fVecOfScint_F;
}
} // namespace ismran
