/*
**	Filename : SingleMuonTrack.h
**	2021-10-27
**	username : rsehgal
*/

#ifndef SingleMuonTrack_h
#define SingleMuonTrack_h

#include <vector>
#pragma once
#include <TROOT.h>

namespace ismran {

class ScintillatorBar_F;

class SingleMuonTrack {
private:
  std::vector<ScintillatorBar_F *> fVecOfScintillators;

public:
  /*
   * Various constructors
   */
  SingleMuonTrack();
  SingleMuonTrack(std::vector<ScintillatorBar_F *> vecOfScintBars);
  SingleMuonTrack(const SingleMuonTrack &smt);

  /*
   * Sorting related functions
   */
  static bool CompareBarIndexInScintillator(ScintillatorBar_F *i1, ScintillatorBar_F *i2);
  void Sort();

  /*
   * Function similar to std::vector
   */
  void push_back(ScintillatorBar_F *hittedBar);
  void clear();
  unsigned long int size();

  /*
   * Required Getters
   */
  std::vector<ScintillatorBar_F *> GetMuonTrack() const;

  /*
   * Some Critical Helper fuction of Muon Track
   */
  bool SingleHitInEachLayer();
  bool SingleHitInLayer(unsigned int layerIndex);
  unsigned int NumOfHitsInLayer(unsigned int layerNum);

  /*
   * Print functions
   */
  void Print();

  ~SingleMuonTrack();

  ClassDef(SingleMuonTrack, 1)
};

} // namespace ismran

#endif
