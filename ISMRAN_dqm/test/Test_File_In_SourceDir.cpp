/*
**	Filename : Test_File_In_SourceDir.cpp
**	2021-11-08
**	username : rsehgal
*/
#include<iostream>
#include "Database.h"

int main() {

  // ismran::Database d; //Default constructor hardcode in the class
  //ismran::Database d("127.0.0.1", "barcq", "barcq", "barcq");
  ismran::Database d("127.0.0.1", "ismran_db", "ismran", "ismran123");
  d.SetVerbose(true);
  d.Connect();
  std::string query = "select * from ismran_files";
  d.Select(query);
  // std::string insertQuery = "insert into ismran_files values
  // ('/home/rsehgal/test2','test2.root',0,'8908jkjjlkjl',1)"; d.Insert(insertQuery); d.Select(query);

  std::cout << "-----------Files to Copy ----------------" << std::endl;
  std::vector<std::vector<std::string>> vecOfVecOfUncopiedFiles=d.GetVectorOfUnCopiedFiles();
  
  for(unsigned int i = 0 ; i < vecOfVecOfUncopiedFiles[0].size() ; i++){
 	std::string fullName=vecOfVecOfUncopiedFiles[0][i]+"/"+vecOfVecOfUncopiedFiles[1][i];
	//std::cout << vecOfUncopiedFiles[i] << std::endl;

		std::cout << "--------------- Calculating Hash and Copying file -----------------------" << std::endl;
	d.CalculateHashAndCopyFile(vecOfVecOfUncopiedFiles[0][i],vecOfVecOfUncopiedFiles[1][i]);
	std::cout << fullName << std::endl;
  } 

  //d.InsertFileNameAndPath("/home/rsehgal/test3", "test3.root");
  //d.Select(query);

  
  
  /*
  int numOfRecords = d.GetNumOfRows("scatteringdata");
  std::cout<<"Num of Records : " << numOfRecords << std::endl;

  int numOfColumns = d.GetNumOfColumns("scatteringdata");
  std::cout<< "Num of Columns : " << numOfColumns << std::endl;

  double energy = 2.6;
  std::string material = "Fe";
  double thickness = 20.5;
  double fwhm = 30.6;
  query = "insert into scatteringdata
  values("+std::to_string(energy)+",'"+material+"',"+std::to_string(thickness)+","+std::to_string(fwhm)+")"; std::cout
  << "Final Query : " << query << std::endl;

  d.Insert(query);

  //d.Delete("scatteringdata");*/
  return 0;
}
