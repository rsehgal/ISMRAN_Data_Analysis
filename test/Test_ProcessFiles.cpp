/*
**	Filename : Test_ProcessFiles.cpp
**	2023-08-23
**	username : rsehgal
*/
#include <iostream>
#include "Database.h"
#include "colors.h"
#include "Helpers_Dqm.h"
int main()
{

  ismran::Database d("127.0.0.1", "ismran_db", "ismran", "ismran123");
  d.SetVerbose(true);
  d.Connect();

  std::cout << "-----------Files to Check ----------------" << std::endl;
  std::string query = "select FileName from ismran_files where processed=0";

  std::vector<MYSQL_ROW> vecOfMysqlRows = d.GetVectorOfFiles_FromQuery(query);
  unsigned short rowLen = 1;// d.GetMySqlRowLength(vecOfMysqlRows[0]);
  std::cout << "Length of MySQL row : " << rowLen << std::endl;
  std::cout << "FileName : " << vecOfMysqlRows[0][0] << std::endl;

  unsigned int counter=0;
	char delim='_';
  for(unsigned int i = 0 ; i < vecOfMysqlRows.size() ; i++){
	counter++;
	
	for(unsigned int j = 0 ; j < rowLen ; j++){
	//std::cout << vecOfMysqlRows[i][j] << " , ";
	std::string filename = vecOfMysqlRows[i][j];
	  std::vector<std::string> tokensVector = ismran::GetStringTokens(filename,delim);
	  int day = std::stoi(tokensVector[4].substr(0,2)); 
	  std::cout << "Date : " << tokensVector[4] <<" : " << day << std::endl;
	}
	std::cout << std::endl;
  } 
  std::cout << "Total number of files : "  << counter << std::endl;

  //Working Block
  /*std::vector<std::vector<std::string>> vecOfVecOfUncheckedFiles = d.GetVectorOfFiles("processed");
  std::cout << BLUE << vecOfVecOfUncheckedFiles[0].size() << RESET << std::endl;
  unsigned int numOfFiles = vecOfVecOfUncheckedFiles[0].size();

  std::cout << GREEN << "NumOfFiles : " << numOfFiles << RESET << std::endl;
  // for (unsigned int i = 0; i < vecOfVecOfUncheckedFiles[0].size(); i++) {
  for (unsigned int i = 0; i < numOfFiles; i++) {
    std::string filename = vecOfVecOfUncheckedFiles[1][i];
    // std::cout << RED << "FileName : " << vecOfVecOfUncheckedFiles[1][i] << RESET << std::endl;

    char delim                            = '_';
    std::vector<std::string> tokensVector = ismran::GetStringTokens(filename, delim);
    std::cout << filename << ": Date : " << tokensVector[4] << std::endl;
  }*/
  return 0;
}
