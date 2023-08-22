/*
**	Filename : Analyzer_F.cpp
**	2021-10-06
**	username : rsehgal
*/
#include <iostream>
#include "Analyzer_F.h"
#include "ScintillatorBar_F.h"
#include "Helpers.h"
#include "Helpers_Dqm.h"
#include "SingleMuonTrack.h"
#include "PairFinder.h"
#include "TreeEntry.h"
#include "colors.h"
namespace ismran {

unsigned int Analyzer_F::numOfShots = 1;
unsigned int Analyzer_F::shotNo     = 1;

Analyzer_F::Analyzer_F() {}
Analyzer_F::Analyzer_F(std::string datafilename, unsigned int numOfEvents)
{
  fDatafileName = datafilename;
  LoadData(numOfEvents);
}
Analyzer_F::~Analyzer_F() {}

unsigned int Analyzer_F::GetFileTime() const
{
  return fFileTime;
}
#ifndef FOLDED_DATA
void Analyzer_F::LoadData(unsigned int numOfEvents)
{
  TFile *fp = new TFile(fDatafileName.c_str(), "r");
  UShort_t fBrCh_prev;
  ULong64_t fTstamp_prev;
  UInt_t fTime_prev;
  UInt_t fQlong_prev;

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
  //  tr->SetBranchAddress("fDelt", &fDelt);

  TTimeStamp *times = new TTimeStamp();
  Long64_t nEntries = tr->GetEntries();
  if (numOfEvents > 0) nEntries = numOfEvents;
  std::cout << "Total number of Entries : " << nEntries << std::endl;
  Long64_t nb = 0;

  /* Injecting shots mechanism */
  unsigned long int numOfEventsInOneShot = nEntries / numOfShots;
  Long64_t startEvNo                     = (shotNo - 1) * numOfEventsInOneShot;
  Long64_t endEvNo                       = shotNo * numOfEventsInOneShot;

  bool newPair = true;
  // for (Long64_t iev = 0; iev < nEntries; iev++) {

  TreeEntry *near = new TreeEntry;
  TreeEntry *far  = new TreeEntry;
  bool pairFound  = true;
  for (Long64_t iev = startEvNo; iev < endEvNo;) {
    if (!(iev % 1000000)) std::cout << "Processed : " << iev << " events........." << std::endl;
    if (pairFound) {
      nb += tr->GetEntry(iev);
      near->Set(fBrCh, fQlong, fTstamp, fTime);
      iev++;

      nb += tr->GetEntry(iev);
      far->Set(fBrCh, fQlong, fTstamp, fTime);
      iev++;
    } else {
      near->Set(far->brch, far->qlong, far->tstamp, far->time);
      nb += tr->GetEntry(iev);
      far->Set(fBrCh, fQlong, fTstamp, fTime);
      iev++;
    }

    pairFound = pf.ValidatePair(near, far);
    if (pairFound) {
      //fVecOfScint_F.push_back(std::shared_ptr<ScintillatorBar_F>(new ScintillatorBar_F(
      fVecOfScint_F.push_back(new ScintillatorBar_F(
          near->brch, near->qlong, far->qlong, near->tstamp, near->time, near->tstamp - far->tstamp));
    }
  }
  fp->Close();
}

/*void Analyzer_F::LoadData(unsigned int numOfEvents)
{
  TFile *fp = new TFile(fDatafileName.c_str(), "r");
  UShort_t fBrCh_prev;
  ULong64_t fTstamp_prev;
  UInt_t fTime_prev;
  UInt_t fQlong_prev;

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
  //  tr->SetBranchAddress("fDelt", &fDelt);

  TTimeStamp *times = new TTimeStamp();
  Long64_t nEntries = tr->GetEntries();
  if (numOfEvents > 0) nEntries = numOfEvents;
  std::cout << "Total number of Entries : " << nEntries << std::endl;
  Long64_t nb = 0;

  // Injecting shots mechanism
  unsigned long int numOfEventsInOneShot = nEntries / numOfShots;
  Long64_t startEvNo                     = (shotNo - 1) * numOfEventsInOneShot;
  Long64_t endEvNo                       = shotNo * numOfEventsInOneShot;

  bool newPair = true;
  // for (Long64_t iev = 0; iev < nEntries; iev++) {
  for (Long64_t iev = startEvNo; iev < endEvNo; iev++) {
    if (!(iev % 1000000)) std::cout << "Processed : " << iev << " events........." << std::endl;
    // std::cout << "inside event loop......." << std::endl;
    nb += tr->GetEntry(iev);
    if ((iev == startEvNo) || newPair) {
      fBrCh_prev   = fBrCh;
      fTstamp_prev = fTstamp;
      fTime_prev   = fTime;
      fQlong_prev  = fQlong;
      newPair      = false;
    } else {
      UShort_t smallBrCh = (fBrCh_prev < fBrCh) ? fBrCh_prev : fBrCh;
      bool pairCond      = (!(smallBrCh % 2)) && (std::fabs(fTstamp_prev - fTstamp) < 25000);
      if (pairCond) {
        //std::cout << "PAIR condition found............." << std::endl;
        if ((fBrCh - fBrCh_prev) == 1) {
          fVecOfScint_F.push_back(std::shared_ptr<ScintillatorBar_F>(
              new ScintillatorBar_F(fBrCh, fQlong_prev, fQlong, fTstamp, fTime, fDelt)));
        } else {
          fVecOfScint_F.push_back(std::shared_ptr<ScintillatorBar_F>(
              new ScintillatorBar_F(fBrCh, fQlong, fQlong_prev, fTstamp, fTime, fDelt)));
        }
        newPair = true;
      } else {
        fBrCh_prev   = fBrCh;
        fTstamp_prev = fTstamp;
        fTime_prev   = fTime;
        fQlong_prev  = fQlong;
      }
    }
  }
  fp->Close();
}*/

#else
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
  if (numOfEvents > 0) nEntries = numOfEvents;
  std::cout << "Total number of Entries : " << nEntries << std::endl;
  Long64_t nb = 0;

  /* Injecting shots mechanism */
  unsigned long int numOfEventsInOneShot = nEntries / numOfShots;
  Long64_t startEvNo                     = (shotNo - 1) * numOfEventsInOneShot;
  Long64_t endEvNo                       = shotNo * numOfEventsInOneShot;

  // for (Long64_t iev = 0; iev < nEntries; iev++) {
  for (Long64_t iev = startEvNo; iev < endEvNo; iev++) {
    // std::cout << "inside event loop......." << std::endl;
    nb += tr->GetEntry(iev);
    if (iev == 0) {
      fFileTime = fTime;
      std::cout << "FileTime : " << fFileTime << " : " << __FILE__ << std::endl;
    }

    if (0) std::cout << fBrCh << " , " << fQlong << " , " << fTstamp << " , " << fTime << " , " << fDelt << std::endl;

    fVecOfScint_F.push_back(
        new ScintillatorBar_F(fBrCh, fQlong, fTstamp, fTime, fDelt));
        //std::shared_ptr<ScintillatorBar_F>(new ScintillatorBar_F(fBrCh, fQlong, fTstamp, fTime, fDelt)));

    if (iev % 1000000 == 0) {
      // times->Set(time, kTRUE, offset, kFALSE);
      std::cout << " Processing event : " << iev << "\t" << times->GetTimeSpec() << std::endl;
    }

  } //! event loop

  fp->Close();
}
#endif
// std::vector<std::shared_ptr<SingleMuonTrack>> Analyzer_F::ReconstructMuonTrack()
std::vector<SingleMuonTrack *> Analyzer_F::ReconstructMuonTrack()
{
  // std::vector<unsigned int> vecOfPeakPos = GetPeakPosVec();
  std::cout << "Going to Create Muon Tracks.................." << std::endl;
  std::sort(fVecOfScint_F.begin(), fVecOfScint_F.end(), CompareTimestampScintillator);
  unsigned int scintVecSize = fVecOfScint_F.size();
  std::cout << "ScintVectSize : " << scintVecSize << std::endl;
  SingleMuonTrack *singleMuonTrack = new SingleMuonTrack();
  // std::shared_ptr<SingleMuonTrack> singleMuonTrack = std::shared_ptr<SingleMuonTrack>(new SingleMuonTrack());
  std::vector<SingleMuonTrack *> smtVec;
  // std::vector<std::shared_ptr<SingleMuonTrack>> smtVec;

  // std::string
  // outfileName="/home/rsehgal/myAmbar/MuonTracks/Muon_Tracks_"+ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName))+".root";
  std::string outfileName = //"/home/rsehgal/MuonTracks/Muon_Tracks_" +
      "MuonTracks_" + ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName)) + ".root";
  // TFile *tracksFile = new TFile("MuonTracks.root", "RECREATE");
  TFile *tracksFile = new TFile(outfileName.c_str(), "RECREATE");
  tracksFile->cd();
  TTree *tracksTree = new TTree("TracksTree", "TracksTree");
  // tracksTree->SetDirectory(0);
  tracksTree->Branch("MuonTracks", "ismran::SingleMuonTrack", &singleMuonTrack);

  ULong64_t tStart = fVecOfScint_F[0]->GetTStampSmall();
  for (unsigned int i = 1; i < scintVecSize; i++) {
    // if (fVecOfScint_F[i]->GetQMeanCorrected(vecOfPeakPos[fVecOfScint_F[i]->GetBarIndex()]) > qmeanCorrThreshold) {
    if (fVecOfScint_F[i]->GetQMeanCorrected() > qmeanCorrThreshold) {
      if (std::fabs(fVecOfScint_F[i]->GetTStampSmall() - tStart) < 20000) {
        // Within 20ns window
        singleMuonTrack->push_back(fVecOfScint_F[i]);
        //singleMuonTrack->push_back(fVecOfScint_F[i].get());
        if (fVecOfScint_F[i]->GetTStampSmall() < tStart) tStart = fVecOfScint_F[i]->GetTStampSmall();
      } else {
        // Previous muon event over
        singleMuonTrack->Sort();
        // singleMuonTrack->Print();
        // smtVec.push_back(std::shared_ptr<SingleMuonTrack>(new SingleMuonTrack(*singleMuonTrack)));
        // smtVec.push_back(new SingleMuonTrack(*singleMuonTrack));
        tracksTree->Fill();
        singleMuonTrack->clear();
        singleMuonTrack->push_back(fVecOfScint_F[i]);
        //singleMuonTrack->push_back(fVecOfScint_F[i].get());
        tStart = fVecOfScint_F[i]->GetTStampSmall();
      }
    }
  }
  std::cout << "SmtVec size : " << smtVec.size() << std::endl;
  tracksTree->Write();
  tracksFile->Close();
  return smtVec;
}

std::vector<unsigned int> Analyzer_F::GetPeakPosVec(std::string peakPosFileLoc)
{
  return ismran::GetPeakPosVec(peakPosFileLoc, ismran::GetBaseName(fDatafileName));
}
std::vector<unsigned int> Analyzer_F::GetPeakPosVec_Direct(std::string peakPosFile)
{
#ifdef VERBOSE
  std::cout << RED << "PEAK pos file : " << peakPosFile << RESET << std::endl;
#endif
  return ismran::GetPeakPosVec_Direct(".", peakPosFile);
}

//std::vector<std::shared_ptr<ScintillatorBar_F>> Analyzer_F::GetVectorOfScintillators()
std::vector<ScintillatorBar_F*> Analyzer_F::GetVectorOfScintillators()
{
  return fVecOfScint_F;
}
} // namespace ismran
