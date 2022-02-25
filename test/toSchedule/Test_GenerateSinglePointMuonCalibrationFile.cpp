/*
**	Filename : Test_GenerateSinglePointMuonCalibrationFile.cpp
**	2022-02-25
**	username : rsehgal
*/
#include<iostream>
#include "Database.h"
#include "colors.h"
#include "Helpers_Dqm.h"
int main()
{

  // ismran::Database d; //Default constructor hardcode in the class
  // ismran::Database d("127.0.0.1","ismran_db","ismran","ismran123");
  ismran::Database d("10.44.11.130", "ismran_db", "ismran", "ismran123");
  d.SetVerbose(true);
  d.Connect();

  std::cout << "-----------Files to Check ----------------" << std::endl;
  std::vector<std::vector<std::string>> vecOfVecOfUncheckedFiles = d.GetVectorOfFiles_ForSinglePointCalibration();

  for (unsigned int i = 0; i < vecOfVecOfUncheckedFiles[0].size(); i++) {
    // if (i == 1) break;
    std::string fullName = ismran::GetAmbarMountPoint_ParentDir() +
                           ismran::GetPath_StartingFromMountPoint(vecOfVecOfUncheckedFiles[0][i]) + "/" +
                           vecOfVecOfUncheckedFiles[1][i];
    std::cout << RED << fullName << RESET << std::endl;
    system(("./Schedule_MuonSinglePointCalibration " + fullName).c_str());
    // d.DoIntegrityCheck(vecOfVecOfUncheckedFiles[0][i], vecOfVecOfUncheckedFiles[1][i]);

    std::string query =
        "update ismran_files set singlePointCalib=1 where fileName='" + vecOfVecOfUncheckedFiles[1][i] + "'";
    d.Update(query);
  }

  return 0;
}
