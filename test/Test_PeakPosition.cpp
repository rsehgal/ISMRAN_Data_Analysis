/*
**	Filename : Test_PeakPosition.cpp
**	2022-02-17
**	username : rsehgal
*/
#include <iostream>
#include "MuonPeakAnalyzer.h"
#include "colors.h"
int main(int argc, char *argv[])
{
  ismran::MuonPeakAnalyzer mpa(argv[1]);
  std::vector<unsigned int> vecOfMuonPeaks = mpa.GetVectorOfPeakPositions();
  std::cout << "Size of peak vector : " << vecOfMuonPeaks.size() << std::endl;
  for (unsigned int i = 0; i < vecOfMuonPeaks.size(); i++) {
    if ((i % 9) && i != 0)
      std::cout << vecOfMuonPeaks[i] << " , ";
    else
      std::cout << std::endl;
  }
  return 0;
}
