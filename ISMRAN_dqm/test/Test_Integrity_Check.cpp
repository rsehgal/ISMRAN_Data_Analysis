/*
**	Filename : Test_Integrity_Check.cpp
**	2021-11-05
**	username : rsehgal
*/
#include<iostream>
#include "Database.h"

int main() {

  // ismran::Database d; //Default constructor hardcode in the class
  //ismran::Database d("127.0.0.1", "barcq", "barcq", "barcq");
  ismran::Database d("10.44.11.130", "ismran_db", "ismran", "ismran123");
  d.SetVerbose(true);
  d.Connect();
  //std::string query = "select * from ismran_files";
  //d.Select(query);

  std::cout << "-----------Files to Check ----------------" << std::endl;
  std::vector<std::vector<std::string>> vecOfVecOfUncheckedFiles=d.GetVectorOfFiles_ForIntegrityCheck();
  
  for(unsigned int i = 0 ; i < vecOfVecOfUncheckedFiles[0].size() ; i++){
 	std::string fullName=vecOfVecOfUncheckedFiles[0][i]+"/"+vecOfVecOfUncheckedFiles[1][i];
	d.DoIntegrityCheck(vecOfVecOfUncheckedFiles[0][i],vecOfVecOfUncheckedFiles[1][i]);
	std::cout << fullName << std::endl;
  } 

  return 0;
}
