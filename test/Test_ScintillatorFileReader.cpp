/*
**	Filename : Test_ScintillatorFileReader.cpp
**	2022-07-08
**	username : rsehgal
*/
#include <iostream>
#include "ScintillatorBar_F.h"
#include "SingleMuonTrack.h"
#include "Analyzer_F.h"
#include "Plotter.h"
#include <TFile.h>
#include "PsBar.h"
#include "Helpers.h"
#include "colors.h"
int main(int argc, char *argv[])
{
  unsigned int numOfEvents = std::atoi(argv[2]);
  ismran::Analyzer_F an(argv[1], numOfEvents);
  std::vector<ismran::ScintillatorBar_F*> scintVec = an.GetVectorOfScintillators();
  unsigned int scintCounter                                        = 0;
  for (unsigned int i = 0; i < scintVec.size(); i++) {
    scintCounter++;
    std::cout << RED;
    scintVec[i]->Print();
    std::cout << RESET << std::endl;
    if (scintCounter > 5) break;
  }

  return 0;
}
