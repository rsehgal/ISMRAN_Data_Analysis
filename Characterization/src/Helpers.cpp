#include "Helpers.h"
#include <filesystem>
#include <regex>
#include <iostream>
#include <string>
namespace fs = std::filesystem;
std::string replaceSubstring(const std::string &original, const std::string &searchString,
                             const std::string &replacement)
{
  std::string modifiedString = original; // Copy the original string

  // Find the position of the substring to be replaced
  size_t pos = modifiedString.find(searchString);

  if (pos != std::string::npos) {
    // Replace the substring in the copied string
    modifiedString.replace(pos, searchString.length(), replacement);
  }

  return modifiedString;
}

std::vector<std::string> GetEnergyCalibrationFiles()
{
  std::vector<std::string> sourceVec; //={cs137,co60,na22};
  std::string sourceStr = R"(.*source.*Couples.*\+0cm\.root$)";
  //std::vector<std::string> sources = {"Cs137", "Co60", "Na22","AmBe"};
  std::vector<std::string> sources = {"Cs137","Na22","AmBe"};
  for (unsigned short i = 0; i < sources.size(); i++) {
    sourceVec.push_back(replaceSubstring(sourceStr, "source", sources[i]));
  }
  return sourceVec;
}

std::vector<std::string> GetPositionCalibrationFiles(){
  std::vector<std::string> fileVec;
  std::string sourceStr = R"(.*Cs137.*Couples.*\pos\.root$)";
std::vector<std::string> posVec={"-40cm","-30cm","-20cm","-10cm","+0cm","+10cm","+20cm","+30cm","+40cm"};
for (unsigned short i = 0; i < posVec.size(); i++) {
    fileVec.push_back(replaceSubstring(sourceStr, "pos", posVec[i]));
  }
  return fileVec;

}

std::string GetDelTOffsetFile(){
  std::string delTOffsetFile = R"(.*Cs137.*Couples.*\+0cm\.root$)";
  return delTOffsetFile;
}

