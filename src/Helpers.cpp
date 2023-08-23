/*
**	Filename : Helpers.cpp
**	2021-10-27
**	username : rsehgal
*/

#include "Helpers.h"
#include "SingleMuonTrack.h"
#include <iostream>
#include <vector>
#include <string>
#include <experimental/filesystem>
#include "colors.h"
#include "MuonPeakAnalyzer.h"
#ifndef USHRT_MAX
#define USHRT_MAX 65535
#endif
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::experimental::filesystem::directory_iterator;

namespace ismran {

std::string GetBaseName(std::string const &path)
{
  return path.substr(path.find_last_of("/\\") + 1);
}

bool CompareTimestampScintillator(ScintillatorBar_F *i1, ScintillatorBar_F *i2)
//bool CompareTimestampScintillator(std::shared_ptr<ScintillatorBar_F> i1, std::shared_ptr<ScintillatorBar_F> i2)
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
  std::cout << "Num. of Muon tracks stored in file : " << nentries << std::endl;
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

std::vector<std::string> GetVectorOfFileNameInADirectory(std::string directoryPath)
{
  std::vector<std::string> vecOfFileNames;
  for (const auto &file : directory_iterator(directoryPath)) {
    std::experimental::filesystem::path filepath = file.path();
    vecOfFileNames.push_back(filepath.string());
  }
  return vecOfFileNames;
}

std::vector<unsigned int> GetPeakPosVec(std::string filename)
{
  TFile *fp                              = new TFile(("MuonPeak_" + filename).c_str(), "r");
  TTree *MuonPeakPositionsTree           = (TTree *)fp->Get("MuonPeakPositionsTree");
  ismran::MuonPeakAnalyzer *peakAnalyzer = new ismran::MuonPeakAnalyzer;
  MuonPeakPositionsTree->SetBranchAddress("PeakPositions", &peakAnalyzer);
  MuonPeakPositionsTree->GetEntry(0);
  fp->Close();
  return peakAnalyzer->GetVectorOfPeakPositions();
}
std::vector<unsigned int> GetPeakPosVec_Direct(std::string dirpath, std::string filename)
{
#ifdef VERBOSE
  std::cout << BLUE << "Peak pos file name from Helpers : " << filename << RESET << std::endl;
#endif
  TFile *fp                              = new TFile((dirpath + "/" + filename).c_str(), "r");
  TTree *MuonPeakPositionsTree           = (TTree *)fp->Get("MuonPeakPositionsTree");
  ismran::MuonPeakAnalyzer *peakAnalyzer = new ismran::MuonPeakAnalyzer;
  MuonPeakPositionsTree->SetBranchAddress("PeakPositions", &peakAnalyzer);
  MuonPeakPositionsTree->GetEntry(0);
  fp->Close();
  return peakAnalyzer->GetVectorOfPeakPositions();
}

std::vector<unsigned int> GetPeakPosVec(std::string dirpath, std::string filename)
{
  TFile *fp                              = new TFile((dirpath + "/MuonPeak_" + filename).c_str(), "r");
  TTree *MuonPeakPositionsTree           = (TTree *)fp->Get("MuonPeakPositionsTree");
  ismran::MuonPeakAnalyzer *peakAnalyzer = new ismran::MuonPeakAnalyzer;
  MuonPeakPositionsTree->SetBranchAddress("PeakPositions", &peakAnalyzer);
  MuonPeakPositionsTree->GetEntry(0);
  fp->Close();
  return peakAnalyzer->GetVectorOfPeakPositions();
}

unsigned int GetPeakPos(std::string filename, std::vector<std::string> vecofbarnames, std::string barName)
{
  std::vector<std::string>::iterator it;
  unsigned int peakPos = 0;
  it                   = std::find(vecofbarnames.begin(), vecofbarnames.end(), barName);
  if (it != vecofbarnames.end()) {
    unsigned int index                   = it - vecofbarnames.begin();
    std::vector<unsigned int> peakPosVec = GetPeakPosVec(filename);
    peakPos                              = peakPosVec[index]; // vecOfPeakPos[index];
  }
  return peakPos;
}

unsigned int GetFoldedQNearQFar(unsigned int qnear, unsigned int qfar)
{
  return ((qnear << 16) | qfar);
}

unsigned int GetUnFoldedQNear(unsigned int qlong)
{
  return (qlong >> 16);
}
unsigned int GetUnFoldedQFar(unsigned int qlong)
{
  unsigned short int maxU_16bits = USHRT_MAX;
  UInt_t maskingVal              = maxU_16bits;
  return (qlong & maskingVal);
}
} // namespace ismran
