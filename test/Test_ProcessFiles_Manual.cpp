/*
**	Filename : Test_ProcessFiles.cpp
**	2023-08-23
**	username : rsehgal
*/
#include <iostream>
#include "Database.h"
#include "colors.h"
#include "Helpers_Dqm.h"
#include <string>
#include <TApplication.h>
#include <TH1F.h>
#include <TFile.h>
int main(int argc, char *argv[])
{

  TApplication *fApp = new TApplication("App",NULL,NULL);
  /*std::string year = std::string(argv[1]);
  std::vector<std::string> monthVec = {
					"Jan","Feb","Mar","Apr",
					"May","Jun","Jul","Aug",
					"Sep","Oct","Nov","Dec",
					};*/

  ismran::Database d("127.0.0.1", "ismran_db", "ismran", "ismran123");
  d.SetVerbose(true);
  d.Connect();

//  TFile *fp = new TFile("DataStats.root","RECREATE");
  //TFile *fp = new TFile(("DataStats_"+std::string(year)+".root").c_str(),"RECREATE");
 // fp->cd();
//  for(unsigned int monIndex = 0 ; monIndex < monthVec.size() ; monIndex++)
{ 
  std::cout << "-----------Files to Check ----------------" << std::endl;
  //std::string monthYear=monthVec[monIndex]+year;
  //std::string query = "select FileName from ismran_files where processed=0 and FileName like '%"+monthYear+"%'";
  std::string query = "select FileName from ismran_files where processed=0 and FileName like '%"+std::string(argv[1])+"%'";

  std::vector<MYSQL_ROW> vecOfMysqlRows = d.GetVectorOfFiles_FromQuery(query);
  unsigned short rowLen                 = 1; // d.GetMySqlRowLength(vecOfMysqlRows[0]);
  std::cout << "Length of MySQL row : " << rowLen << std::endl;
  std::cout << "FileName : " << vecOfMysqlRows[0][0] << std::endl;

  //TH1F *monthHist = new TH1F("MonthHist","MonthHist",32,0,32);
  TH1F *monthHist = new TH1F(argv[1],argv[1],32,0,32);

  unsigned int counter                  = 0;
  char delim                            = '_';
  unsigned int counterCorrectPlaceToken = 0;
  unsigned int counterWrongPlaceToken   = 0;

  for (unsigned int i = 0; i < vecOfMysqlRows.size(); i++) {
    counter++;

    for (unsigned int j = 0; j < rowLen; j++) {
      // std::cout << vecOfMysqlRows[i][j] << " , ";
      std::string filename                  = vecOfMysqlRows[i][j];
      std::vector<std::string> tokensVector = ismran::GetStringTokens(filename, delim);
      std::string dayStr                    = tokensVector[4].substr(0, 2);

      try {
        // std::string str = "abc"; // Invalid input
        int num = std::stoi(dayStr);
        //std::cout << "Converted integer: " << num << std::endl;
        monthHist->Fill(num);
      } catch (const std::invalid_argument &e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        counterWrongPlaceToken++;
	std::cout << RED << filename << RESET << std::endl;
     } catch (const std::out_of_range &e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
      }

      //std::cout << "Date : " << tokensVector[4] << " : " << dayStr << std::endl;
    }
    //std::cout << std::endl;
  }
  std::cout << "Total number of files : " << counter << std::endl;
  std::cout << "Total number of files where Date token comes at wrong place : " << counterWrongPlaceToken << std::endl;
  // Working Block
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
  
  monthHist->Draw();
  //monthHist->Write();

}
 //fp->Close();
 fApp->Run();
  return 0;
}
