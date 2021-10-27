/*
**	Filename : Analyzer_F.h
**	2021-10-06
**	username : rsehgal
*/
#ifndef Analyzer_F_h
#define Analyzer_F_h

#include <vector>
#include <string>

namespace ismran {

class ScintillatorBar_F;
class SingleMuonTrack;

class Analyzer_F {

private:
  std::string fDatafileName;
  std::vector<ScintillatorBar_F *> fVecOfScint_F;

public:
  Analyzer_F();
  Analyzer_F(std::string datafilename,unsigned int numOfEvents=0);
  ~Analyzer_F();
  void LoadData(unsigned int numOfEvents);
  std::vector<ScintillatorBar_F *> GetVectorOfScintillators();
  std::vector<SingleMuonTrack *> ReconstructMuonTrack();

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
