/*
**	Filename : Database.h
**	2021-10-30
**	username : rsehgal
*/
#ifndef Database_h
#define Database_h

#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>
namespace ismran {

class Database {
  // MYSQL related data members
  MYSQL *conn, mysql;
  MYSQL_RES *res;
  MYSQL_ROW row;

  int fQueryState;

  // MySql database details
  std::string fDbName;
  std::string fUsername;
  std::string fPasswd;
  std::string fQuery;
  std::string fServerIp;

  bool fVerbose;

public:
  Database();
  virtual ~Database();
  Database(std::string serverIp, std::string dbName, std::string uName, std::string passWd);
  Database(std::string dbName, std::string uName, std::string passWd);
  int Connect();

  /* Required Setters */
  void Set(char *serverIp, char *dbName, char *uName, char *passWd);
  void SetServerIp(char *serverIp);
  void SetDbName(char *dbName);
  void SetUname(char *uName);
  void SetPasswd(char *passWd);

  template <bool select = false>
  int Query(std::string query);

  int Insert(std::string query);
  int InsertFileNameAndPath(std::string filePath, std::string fileName);

  int Delete(std::string tablename);
  int Select(std::string query);
  int Count(std::string query);
  int Update(std::string query);
  int GetNumOfColumns(std::string tablename);
  int GetNumOfRows(std::string tablename);
  void PrintQueryOutput();
  std::vector<std::vector<std::string>> GetVectorOfUnCopiedFiles();
  void CalculateHashAndCopyFile(std::string sourcePath, std::string fileToCopy);
  std::vector<std::vector<std::string>> GetVectorOfFiles_ForIntegrityCheck();
  std::vector<std::vector<std::string>> GetVectorOfFiles_ForSinglePointCalibration();
  std::vector<std::vector<std::string>> GetVectorOfFiles(std::string flagName);
  std::vector<MYSQL_ROW> GetVectorOfFiles_FromQuery(std::string query);
  void DoIntegrityCheck(std::string targetPath, std::string fileToChec);
  std::vector<std::vector<std::string>> GetVectorOfDeletedFiles();
  void UpdateDbForDeletedFile();

  std::string GetShaSum(std::string filename);

  // Functions for offline processing for already existing files
  void UpdateDbForFileNames_Offline(std::string sourceDir);
  void UpdateDbForTargetFiles_Cron_Offline(std::string sourceDir);

  // Function to set the fVERBOSE flag
  void SetVerbose(bool verbose);

  // Function to get the row length
  //NOT WORKING EXPECTEDLY
  unsigned short GetMySqlRowLength(MYSQL_ROW row)
  {
    unsigned short length = 0;
    // Iterate through the row until a NULL value is encountered
    while (row[length] != NULL) {
      length++;
    }

    return length;
  }
};

  unsigned short GetRowLength_FromQuery(std::string query){
	

  }
template <bool select>
int Database::Query(std::string query)
{

  //	fQueryState = mysql_query(conn,fQuery.c_str());
  fQueryState = mysql_query(conn, query.c_str());
  if (fQueryState != 0) {
    std::cout << mysql_error(conn) << std::endl << std::endl;
    return 1;
  }
  if (select) {
    res = mysql_store_result(conn);

    // if (fVerbose)
    // PrintQueryOutput();
  }
  return fQueryState;
}

} // namespace ismran
#endif
