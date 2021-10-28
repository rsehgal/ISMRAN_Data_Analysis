/*
**	Filename : Test_SmallChunk.cpp
**	2021-10-27
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
  std::vector<ismran::ScintillatorBar_F *> vecOfScint = an.GetVectorOfScintillators();
  std::vector<ismran::SingleMuonTrack *> smtVec       = an.ReconstructMuonTrack();
#if (0)
  unsigned int trackCounter = 0;
  for (unsigned int i = 0; i < smtVec.size(); i++) {
    if (trackCounter < 10) {
      if (smtVec[i]->size() > 2) {
        smtVec[i]->Print();
        trackCounter++;
      }
    } else {
      break;
    }
  }
#endif
  return 0;
}
