/*
**	Filename : Helpers_Dqm.cpp
**	2021-11-16
**	username : rsehgal
*/
#include "Helpers_Dqm.h"
#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace ismran {

std::vector<std::string> GetStringTokens(std::string pathString, char delim) {
  std::vector<std::string> tokensVector;
  std::stringstream ss(pathString);
  std::string token;
  while (getline(ss, token, delim)) {
    tokensVector.push_back(token);
  }
  return tokensVector;
}

std::string GetStringToken_WithIndex(std::string pathString, char delim, unsigned short tokenIndex ) {
  std::vector<std::string> tokensVector;
  std::stringstream ss(pathString);
  std::string token;
  while (getline(ss, token, delim)) {
    tokensVector.push_back(token);
  }
  return tokensVector[0];
}

std::string GetPath_StartingFrom_DelimiterWithIndex(std::string pathString, char delim, unsigned short delimIndex){
  std::vector<std::string> tokensVector = GetStringTokens(pathString,delim);
  std::string reqPath = "";
  std::string s(1,delim);
  std::cout << "Delimiter Converted to String : " << s << std::endl;
  for (unsigned int i = delimIndex+1; i < tokensVector.size(); i++) {
    reqPath += s+tokensVector[i];
  }
  std::cout << "returning string  : " << reqPath << std::endl;
  return reqPath;
}


std::string GetPath_StartingFromMountPoint(std::string pathString) {
  std::vector<std::string> tokensVector = GetStringTokens(pathString);
  std::string reqPath = "";
  for (unsigned int i = 3; i < tokensVector.size(); i++) {
    reqPath += "/"+tokensVector[i];
  }
  return reqPath;
}

std::string GetCopyPath_UptoMonth(std::string pathString) {
  std::vector<std::string> tokensVector = GetStringTokens(pathString);
  std::string reqPath = "";
  for (unsigned int i = 0; i < tokensVector.size()-1; i++) {
    reqPath += "/"+tokensVector[i];
  }
  return reqPath;
}

std::string GetAmbarMountPoint_ParentDir() { return "/var/www/html/web"; }

std::string GetRemoteDataDirectory_OnDAQMachine() {
  std::ifstream infile("/home/neutrino/ISMRAN_dqm/files/copyPath.txt");
  std::string copyPath;
  infile >> copyPath;
  infile.close();
  return copyPath;
}

bool FileExists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

std::string GetFileNameWithoutExtension(std::string filename){
	//std::string basename=GetBaseName(filename);
   	return GetStringToken_WithIndex(filename,'.');	
}
} // namespace ismran
