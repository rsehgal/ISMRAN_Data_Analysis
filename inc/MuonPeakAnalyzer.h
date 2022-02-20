/*
**	Filename : MuonPeakAnalyzer.h
**	2022-02-17
**	username : rsehgal
*/
#ifndef MuonPeakAnalyzer_h
#define MuonPeakAnalyzer_h

#include <vector>
#include <TH1F.h>
#include <TROOT.h>
namespace ismran {

class MuonPeakAnalyzer {
  std::string fFileName;
  std::vector<unsigned int> fVecOfPeakPos;
  unsigned int fFileTime;

public:
  MuonPeakAnalyzer();
  virtual ~MuonPeakAnalyzer();
  MuonPeakAnalyzer(std::string filename);
  std::vector<unsigned int> GetVectorOfPeakPositions()const;
  std::string GetFileName()const;
  unsigned int GetRunNumber();
  unsigned int GetFileTime()const;
  unsigned int FindMuonPeakPos(TH1F *hist);
  void FillMuonPeakPosVector();
  void SetFileName(std::string filename); 
  void UpdateFileName(); 
  ClassDef(MuonPeakAnalyzer,1)
};
} // namespace ismran
#endif
