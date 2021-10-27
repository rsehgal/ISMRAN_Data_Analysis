/*
**	Filename : SingleMuonTrack.h
**	2021-10-27
**	username : rsehgal
*/

#include <vector>

#ifndef SingleMuonTrack_h
#define SingleMuonTrack_h

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
   * Print functions
   */
  void Print();

  ~SingleMuonTrack();
};

} // namespace ismran

#endif
