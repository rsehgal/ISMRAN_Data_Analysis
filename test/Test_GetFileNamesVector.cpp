/*
**	Filename : Test_GetFileNamesVector.cpp
**	2022-02-17
**	username : rsehgal
*/
#include <iostream>
#include "Helpers.h"
#include <string>
#include <vector>
#include "colors.h"
int main(int argc, char *argv[])
{
  std::string directoryPath               = "/home/rsehgal/AmbarData/Dhruva/February2022/data";
  std::vector<std::string> vecOfFileNames = ismran::GetVectorOfFileNameInADirectory(directoryPath);

  for (unsigned int i = 0; i < vecOfFileNames.size(); i++) {
    std::cout << BLUE << vecOfFileNames[i] << RESET << std::endl;
  }
  return 0;
}
