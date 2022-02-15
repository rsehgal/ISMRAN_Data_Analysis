/*
**	Filename : Test_PeakPos.cpp
**	2022-02-15
**	username : rsehgal
*/
#include "HardwareNomenclature.h"
#include <iostream>
int main(int argc, char *argv[])
{
  std::string barName = argv[1];
  double peakPos      = ismran::GetPeakPos(barName);
  std::cout << "PeakPos : " << peakPos << std::endl;
  return 0;
}
