/*
**	Filename : SingleMuonTrack.cpp
**	2021-10-27
**	username : rsehgal
*/

#include "SingleMuonTrack.h"
#include "ScintillatorBar_F.h"
#include <iterator>
#include "PsBar.h"
//#include "Point3D.h"
#include "HardwareNomenclature.h"
//#include <TVector3.h>
#include "Plotter.h"
#include <algorithm>
//#include <TF1.h>
//#include "HelperFunctions.h"
#include "colors.h"

ClassImp(ismran::SingleMuonTrack)

namespace ismran {

SingleMuonTrack::SingleMuonTrack() {}

SingleMuonTrack::~SingleMuonTrack() {}

SingleMuonTrack::SingleMuonTrack(std::vector<ScintillatorBar_F *> vecOfScintBars)
{
  fVecOfScintillators = vecOfScintBars;
}

SingleMuonTrack::SingleMuonTrack(const SingleMuonTrack &smt)
{
  for (unsigned int i = 0; i < smt.GetMuonTrack().size(); i++) {
    fVecOfScintillators.push_back(new ScintillatorBar_F(*(smt.GetMuonTrack()[i])));
  }
}

std::vector<ScintillatorBar_F *> SingleMuonTrack::GetMuonTrack() const
{
  return fVecOfScintillators;
}

bool SingleMuonTrack::CompareBarIndexInScintillator(ScintillatorBar_F *i1, ScintillatorBar_F *i2)
{
  return (i1->GetBarIndex() > i2->GetBarIndex());
}

void SingleMuonTrack::Sort()
{
  std::sort(fVecOfScintillators.begin(), fVecOfScintillators.end(), CompareBarIndexInScintillator);
}

void SingleMuonTrack::clear()
{
  fVecOfScintillators.clear();
}

unsigned long int SingleMuonTrack::size()
{
  return fVecOfScintillators.size();
}

void SingleMuonTrack::push_back(ScintillatorBar_F *scint)
{
  fVecOfScintillators.push_back(scint);
}

void SingleMuonTrack::Print()
{
  std::cout << "**************************************************************" << std::endl;
  std::vector<ScintillatorBar_F *> scintBarVec = GetMuonTrack();
  for (unsigned int i = 0; i < scintBarVec.size(); i++) {
    scintBarVec[i]->Print();
  }
  std::cout << std::endl;
}
} // namespace ismran
