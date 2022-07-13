/*
**	Filename : Analyzer_F.h
**	2021-10-06
**	username : rsehgal
*/
#ifndef Analyzer_F_h
#define Analyzer_F_h

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "PairFinder.h"
namespace ismran {

class ScintillatorBar_F;
class SingleMuonTrack;

class Analyzer_F {

private:
  std::string fDatafileName;
  std::vector<std::shared_ptr<ScintillatorBar_F>> fVecOfScint_F;
  unsigned int fFileTime;
  PairFinder pf;

public:
  Analyzer_F();
  Analyzer_F(std::string datafilename,unsigned int numOfEvents=0);
  ~Analyzer_F();
  void LoadData(unsigned int numOfEvents);
  std::vector<std::shared_ptr<ScintillatorBar_F>> GetVectorOfScintillators();
  std::vector<SingleMuonTrack*> ReconstructMuonTrack();
  //std::vector<std::shared_ptr<SingleMuonTrack>> ReconstructMuonTrack();
  //std::vector<SingleMuonTrack *> ReconstructMuonTrack();
  unsigned int GetFileTime()const;
  //std::vector<unsigned int> GetPeakPosVec(std::string peakPosFileLoc="/home/rsehgal/myAmbar/MuonSinglePointCalibration");
  std::vector<unsigned int> GetPeakPosVec(std::string peakPosFileLoc=".");
#ifdef FOLDED_DATA
  std::vector<unsigned int> GetPeakPosVec_Direct(std::string peakPosFile="MuonPeak.root");
#else
  std::vector<unsigned int> GetPeakPosVec_Direct(std::string peakPosFile="MuonPeak_H9.root");
#endif

public:
  /*
   * Variable for Shots mechanism
   * useful for batch submission and process big
   * data files in chunks
   */
  static unsigned int numOfShots;
  static unsigned int shotNo;
};
} // namespace ismran

#endif
