/*
**	Filename : Test_MuonLifeTime.cpp
**	2022-03-09
**	username : rsehgal
*/
#include <iostream>
#include "ScintillatorBar_F.h"
#include "SingleMuonTrack.h"
#include "Analyzer_F.h"
#include "Plotter.h"
#include <TFile.h>

int main(int argc, char *argv[])
{
  unsigned int numOfEvents = 0;
  ismran::Analyzer_F an(argv[1], numOfEvents);
  std::vector<std::shared_ptr<ismran::ScintillatorBar_F>> vecOfScint = an.GetVectorOfScintillators();
  //std::vector<std::shared_ptr<ismran::SingleMuonTrack>> smtVec       = an.ReconstructMuonTrack();
  //std::vector<ismran::SingleMuonTrack*> smtVec       = an.ReconstructMuonTrack();
  
  return 0;
}
