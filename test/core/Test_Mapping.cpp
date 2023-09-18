/*
**	Filename : Test_Mapping.cpp
**	2022-07-06
**	username : rsehgal
*/
#include <iostream>
#include "colors.h"
#include "ScintillatorBar_F.h"
#include "Helpers.h"
#include "HardwareNomenclature.h"
#include "Analyzer_F.h"
#include <iostream>

int main(int argc, char *argv[])
{

  unsigned int numOfEvents = std::atoi(argv[2]);
  ismran::Analyzer_F an(argv[1], numOfEvents);
  ismran::vecOfPeakPos = an.GetPeakPosVec();

  std::vector<ismran::ScintillatorBar_F*> vecOfScint = an.GetVectorOfScintillators();
  unsigned int barIndex                                              = 12;
  unsigned int layerIndex                                            = 9;

  for (unsigned int i = 0; i < vecOfScint.size(); i++) {
    // if (vecOfScint[i]->GetBarIndex() == barIndex) {
    if (vecOfScint[i]->GetLayerIndex() == layerIndex) {
      std::cout << RED << vecOfScint[i]->GetBarIndex() << " : " << vecOfScint[i]->GetLayerIndex() << " : "
                << vecOfScint[i]->GetBarIndexInLayer() << std::endl;
      //break;
    }
  }
  return 0;
}
