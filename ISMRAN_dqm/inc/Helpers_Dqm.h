/*
**	Filename : Helpers.h
**	2021-11-16
**	username : rsehgal
*/
#ifndef Helpers_Dqm_h
#define Helpers_Dqm_h

#include <string>
#include <vector>
namespace ismran {
extern std::vector<std::string> GetStringTokens(std::string pathString,char delim='/');
extern std::string GetStringToken_WithIndex(std::string pathString,char delim='/', unsigned short tokenIndex=0);
extern std::string GetPath_StartingFromMountPoint(std::string pathString);
extern std::string GetPath_StartingFrom_DelimiterWithIndex(std::string pathString,char delim='_',unsigned short delimIndex=1);
extern std::string GetCopyPath_UptoMonth(std::string pathString);
extern std::string GetAmbarMountPoint_ParentDir();
extern std::string GetRemoteDataDirectory_OnDAQMachine();
extern bool FileExists (const std::string& name);
extern std::string GetFileNameWithoutExtension(std::string filename);
} // namespace ismran

#endif
