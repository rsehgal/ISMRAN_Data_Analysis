/*
**	Filename : Database.cpp
**	2021-10-30
**	username : rsehgal
*/

#include "Database.h"
#include "Helpers_Dqm.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#ifdef EXPERIMENTAL_FILESYSTEM
#include <experimental/filesystem>
namespace FS = std::experimental::filesystem;
#else
#include <filesystem>
namespace FS = std::filesystem;
#endif

namespace ismran {

Database::Database() {
  // TODO Auto-generated constructor stub
  fUsername = "barcq";
  fPasswd = "barcq";
  fDbName = "barcq";
  fQueryState = 0;

  fVerbose = true; // false;
  fServerIp = "127.0.0.1";
  mysql_init(&mysql);
}

Database::Database(std::string dbName, std::string uName, std::string passWd)
    : fUsername(uName), fPasswd(passWd), fDbName(dbName), fQueryState(0), fVerbose(false), fServerIp("127.0.0.1") {
  mysql_init(&mysql);
}
Database::Database(std::string serverIp, std::string dbName, std::string uName, std::string passWd)
    : fUsername(uName), fPasswd(passWd), fDbName(dbName), fQueryState(0), fVerbose(false), fServerIp(serverIp) {
  mysql_init(&mysql);
}

Database::~Database() {
  // TODO Auto-generated destructor stub
  // mysql_free_result(res);
  // mysql_close(conn);
}

int Database::Connect() {
  conn = mysql_real_connect(&mysql, fServerIp.c_str(), fUsername.c_str(), fPasswd.c_str(), fDbName.c_str(), 0, 0, 0);
  if (conn == NULL) {
    std::cout << mysql_error(&mysql) << std::endl << std::endl;
    return 1;
  } else {
    return 0;
  }
}

void Database::Set(char *serverIp, char *dbName, char *uName, char *passWd) {
  fDbName = std::string(dbName);
  fServerIp = std::string(serverIp);
  fUsername = std::string(uName);
  fPasswd = std::string(passWd);
}

void Database::SetServerIp(char *serverIp) { fServerIp = std::string(serverIp); }
void Database::SetDbName(char *dbName) { fDbName = std::string(dbName); }
void Database::SetUname(char *uName) { fUsername = std::string(uName); }
void Database::SetPasswd(char *passWd) { fPasswd = std::string(passWd); }

int Database::Delete(std::string tablename) {
  std::string query = "DELETE FROM " + tablename;
  return Query(query);
}

int Database::Update(std::string query) { return Query(query); }

int Database::Insert(std::string query) { return Query(query); }

int Database::InsertFileNameAndPath(std::string filePath, std::string fileName) {
  std::string query = "INSERT into ismran_files (filePath,fileName) values('" + filePath + "','" + fileName + "')";
  std::cout << "QUERY : " << query << std::endl;
  return Query(query);
}

int Database::Select(std::string query) { return Query<true>(query); }

int Database::GetNumOfRows(std::string tablename) {
  std::string query = "SELECT count(*) FROM " + tablename;
  return Count(query);
}

int Database::GetNumOfColumns(std::string tablename) {
  std::string query = "SELECT count(*) FROM INFORMATION_SCHEMA.Columns where TABLE_NAME = '" + tablename + "'";
  return Count(query);
}

int Database::Count(std::string query) {
  int queryReturnCode = Query<true>(query);
  row = mysql_fetch_row(res);
  return atoi(row[0]);
}

void Database::PrintQueryOutput() {
  std::cout << "MySQL Tables in mysql database." << std::endl << std::endl;
  while ((row = mysql_fetch_row(res)) != NULL) {
    // std::cout << left;
    std::cout << std::setw(18) << row[0] << std::setw(18)
              << row[1]
              //<< std::setw(18) << row[2]
              //<< std::setw(18) << row[3]
              << std::endl;
  }
}
std::vector<std::vector<std::string>> Database::GetVectorOfDeletedFiles() {
  std::vector<std::vector<std::string>> vecOfVecOfFileNames;
  Select("select * from ismran_files");
  std::vector<std::string> vecOfFilePaths;
  std::vector<std::string> vecOfFileNames;
  while ((row = mysql_fetch_row(res)) != NULL) {
    std::string fullFileName = std::string(row[0]) + "/" + std::string(row[1]);
    if (!FS::exists(fullFileName.c_str())) {
      vecOfFilePaths.push_back(std::string(row[0]));
      vecOfFileNames.push_back(std::string(row[1]));
    }
  }
  vecOfVecOfFileNames.push_back(vecOfFilePaths);
  vecOfVecOfFileNames.push_back(vecOfFileNames);
  return vecOfVecOfFileNames;
}

void Database::UpdateDbForDeletedFile() {
  std::vector<std::vector<std::string>> vecOfVecOfDeletedFileNames = GetVectorOfDeletedFiles();

  std::string concatenatedFileName = "";
  for (unsigned int i = 0; i < vecOfVecOfDeletedFileNames[1].size(); i++) {
    if (i == vecOfVecOfDeletedFileNames[1].size() - 1)
      concatenatedFileName += "'" + vecOfVecOfDeletedFileNames[1][i] + "'";
    else
      concatenatedFileName += "'" + vecOfVecOfDeletedFileNames[1][i] + "',";
  }
  std::cout << concatenatedFileName << std::endl;
  std::string query = "update ismran_files set fileExistInSourceDir=0 where fileName IN (" + concatenatedFileName + ")";
  Update(query);
}

std::vector<std::vector<std::string>> Database::GetVectorOfUnCopiedFiles() {
  std::vector<std::vector<std::string>> vecOfVecOfFileNames;
  Select("select * from ismran_files where copied=0 and currenFile=0");
  std::vector<std::string> vecOfFilePaths;
  std::vector<std::string> vecOfFileNames;

  while ((row = mysql_fetch_row(res)) != NULL) {
    vecOfFilePaths.push_back(std::string(row[0]));
    vecOfFileNames.push_back(std::string(row[1]));

    // vecOfFileNames.push_back(std::string(row[0]) + "/" + std::string(row[1]));
  }
  vecOfVecOfFileNames.push_back(vecOfFilePaths);
  vecOfVecOfFileNames.push_back(vecOfFileNames);
  return vecOfVecOfFileNames;
}

void Database::CalculateHashAndCopyFile(std::string sourcePath, std::string fileToCopy) {
  std::string fullFilePath = sourcePath + "/" + fileToCopy;
  /*std::ifstream infile("../files/copyPath.txt");
  std::string copyPath;
  infile >> copyPath;
  infile.close();*/
  std::string copyPath = GetRemoteDataDirectory_OnDAQMachine();
  system(("sha256sum " + fullFilePath + " > sha.txt").c_str());
  std::ifstream inHashFile("sha.txt");
  std::string hashCode;
  inHashFile >> hashCode;
  inHashFile.close();
  system(("cp " + fullFilePath + " " + copyPath).c_str());

  std::string fullImageTargetFilePath = GetCopyPath_UptoMonth(copyPath)+"/images";
  std::string fullImageSourceFilePrefix=sourcePath+"/images/";
  std::string imageFileSuffix = GetPath_StartingFrom_DelimiterWithIndex(fileToCopy,'_',1);
  imageFileSuffix = GetStringToken_WithIndex(imageFileSuffix,'.',0); 
  imageFileSuffix += ".png";
  std::string imageName = "NearRate"+imageFileSuffix;
  std::string fullImageSourceFilePath = fullImageSourceFilePrefix+imageName;

  if(FileExists(fullImageSourceFilePath))  
    system(("cp "+fullImageSourceFilePath+" "+fullImageTargetFilePath).c_str());

  imageName = "FarRate"+imageFileSuffix;
  fullImageSourceFilePath = fullImageSourceFilePrefix+imageName;
  if(FileExists(fullImageSourceFilePath))  
    system(("cp "+fullImageSourceFilePath+" "+fullImageTargetFilePath).c_str());

  imageName = "CoincRate"+imageFileSuffix;
  fullImageSourceFilePath = fullImageSourceFilePrefix+imageName;
  if(FileExists(fullImageSourceFilePath))  
    system(("cp "+fullImageSourceFilePath+" "+fullImageTargetFilePath).c_str());

  std::string query = "update ismran_files set copied=1 where fileName='" + fileToCopy + "'";
  Update(query);
  query = "update ismran_files set hashCode='" + hashCode + "' where fileName='" + fileToCopy + "'";
  Update(query);

  query = "update ismran_files set remoteFilePath='" + copyPath + "' where fileName='" + fileToCopy + "'";
  Update(query);
}

std::vector<std::vector<std::string>> Database::GetVectorOfFiles_ForIntegrityCheck() {
  std::vector<std::vector<std::string>> vecOfVecOfFileNames;
  Select("select * from ismran_files where integrityCheck=0 and copied=1");
  std::vector<std::string> vecOfFilePaths;
  std::vector<std::string> vecOfFileNames;

  while ((row = mysql_fetch_row(res)) != NULL) {
    vecOfFilePaths.push_back(std::string(row[6]));
    vecOfFileNames.push_back(std::string(row[1]));

    // vecOfFileNames.push_back(std::string(row[0]) + "/" + std::string(row[1]));
  }
  vecOfVecOfFileNames.push_back(vecOfFilePaths);
  vecOfVecOfFileNames.push_back(vecOfFileNames);
  return vecOfVecOfFileNames;
}

std::vector<std::vector<std::string>> Database::GetVectorOfFiles_ForSinglePointCalibration() {
  std::vector<std::vector<std::string>> vecOfVecOfFileNames;
  Select("select remoteFilePath,fileName from ismran_files where integrityCheck=1 and copied=1 and singlePointCalib=0");
  // Select("select remoteFilePath,fileName from ismran_files where integrityCheck=1 and copied=1 and singlePointCalib=0
  // and fileName like '%02Feb%' ");
  std::vector<std::string> vecOfFilePaths;
  std::vector<std::string> vecOfFileNames;

  while ((row = mysql_fetch_row(res)) != NULL) {
    vecOfFilePaths.push_back(std::string(row[0]));
    vecOfFileNames.push_back(std::string(row[1]));

    // vecOfFileNames.push_back(std::string(row[0]) + "/" + std::string(row[1]));
  }
  vecOfVecOfFileNames.push_back(vecOfFilePaths);
  vecOfVecOfFileNames.push_back(vecOfFileNames);
  return vecOfVecOfFileNames;
}

std::vector<MYSQL_ROW> Database::GetVectorOfFiles_FromQuery(std::string query) {
  std::cout <<  query << std::endl;
  Select(query);
  std::vector<MYSQL_ROW> vecOfMysqlRows;
  while ((row = mysql_fetch_row(res)) != NULL) {
	vecOfMysqlRows.push_back(row);
  }
  return vecOfMysqlRows;
}

std::vector<std::vector<std::string>> Database::GetVectorOfFiles(std::string flagName) {
  std::vector<std::vector<std::string>> vecOfVecOfFileNames;
  std::string query = "select remoteFilePath,fileName from ismran_files where "+flagName+"=0";
  std::cout <<  query << std::endl;
//  Select("select remoteFilePath,fileName from ismran_files where integrityCheck=1 and copied=1 and singlePointCalib=0");
  Select(query);
  // Select("select remoteFilePath,fileName from ismran_files where integrityCheck=1 and copied=1 and singlePointCalib=0
  // and fileName like '%02Feb%' ");
  std::vector<std::string> vecOfFilePaths;
  std::vector<std::string> vecOfFileNames;

  while ((row = mysql_fetch_row(res)) != NULL) {
    vecOfFilePaths.push_back(std::string(row[0]));
    vecOfFileNames.push_back(std::string(row[1]));

    // vecOfFileNames.push_back(std::string(row[0]) + "/" + std::string(row[1]));
  }
  vecOfVecOfFileNames.push_back(vecOfFilePaths);
  vecOfVecOfFileNames.push_back(vecOfFileNames);
  return vecOfVecOfFileNames;
}
void Database::DoIntegrityCheck(std::string targetPath, std::string fileToCheck) {
  // std::string fullFilePath = targetPath + "/" + fileToCheck;
  std::string fullFilePath =
      GetAmbarMountPoint_ParentDir() + GetPath_StartingFromMountPoint(targetPath) + "/" + fileToCheck;
  // std::cout << "File for Integrity check : " << fullFilePath << std::endl;
  system(("sha256sum " + fullFilePath + " > sha.txt").c_str());
  std::ifstream inHashFile("sha.txt");
  std::string hashCode;
  inHashFile >> hashCode;
  inHashFile.close();
  std::string query = "select hashCode from ismran_files where fileName='" + fileToCheck + "'";
  Select(query);

  std::cout << "======================================" << std::endl;
  while ((row = mysql_fetch_row(res)) != NULL) {
    // std::cout << "Updating integrity check for : " << fileToCheck << std::endl;
    // std::cout << "Target Hash Code : " << hashCode << std::endl;
    std::cout << "Hash Code from DB : " << std::string(row[0]) << std::endl;
    if (hashCode == std::string(row[0]) && hashCode != "") {
      query = "update ismran_files set integrityCheck=1 where fileName='" + fileToCheck + "'";
      Update(query);
    }
  }
}

void Database::UpdateDbForFileNames_Offline(std::string sourceDir) {
  for (const auto &file : FS::directory_iterator(sourceDir)) {
    // To get the filename with full path
    // std::cout << file.path() << std::endl;

    // To get just the filename
    // std::cout << FS::path(file.path()).filename() << std::endl;
    InsertFileNameAndPath(sourceDir, FS::path(file.path()).filename());
  }
}

std::string Database::GetShaSum(std::string fullFilePath) {
  system(("sha256sum " + fullFilePath + " > sha.txt").c_str());
  std::ifstream inHashFile("sha.txt");
  std::string hashCode;
  inHashFile >> hashCode;
  inHashFile.close();
  return hashCode;
}

void Database::UpdateDbForTargetFiles_Cron_Offline(std::string targetDir) {
  for (const auto &file : FS::directory_iterator(targetDir)) {

    std::string filename = FS::path(file.path()).filename();
    std::string query = "select * from ismran_files where fileName='" + filename + "' and copied=0";
    Select(query);
    while ((row = mysql_fetch_row(res)) != NULL) {
      std::string hashCode = GetShaSum(std::string(row[0]) + "/" + std::string(row[1]));
      query = "UPDATE ismran_files SET hashCode='" + hashCode + "', copied=1, remoteFilePath='" + targetDir +
              "' where fileName='" + filename + "'";
      Update(query);
    }
  }
}

void Database::SetVerbose(bool verbose) { fVerbose = verbose; }

} // namespace ismran
