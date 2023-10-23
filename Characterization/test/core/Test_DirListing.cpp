#include <string>

/*int main()
{
    std::string path = "/home/rsehgal/PS5_S2AB1006";
    for (const auto & entry : fs::directory_iterator(path))
        //std::cout << entry.path() << std::endl;
  std::string filenamee = entry.path().string();
  std::cout << filenamee << std::endl;
}*/

#include <iostream>
#include <filesystem>
#include <regex>
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
  std::vector<std::string> sources = {"Cs137", "Co60", "Na22"};
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

int main()
{

  fs::path directoryPath = "/home/rsehgal/PS5_S2AB1006";

  // std::string cs137 = R"(.*Cs137.*Couples.*\+0cm\.root$)";
  // std::string co60 = R"(.*Co60.*Couples.*\+0cm\.root$)";
  // std::string na22 = R"(.*Na22.*Couples.*\+0cm\.root$)";

  /*std::vector<std::string> sourceVec; //={cs137,co60,na22};

  std::vector<std::string> sources = {"Cs137", "Co60", "Na22"};
  for (unsigned short i = 0; i < sources.size(); i++) {
    sourceVec.push_back(replaceSubstring(sourceStr, "source", sources[i]));
  }*/

  std::vector<std::string> sourceVec = GetEnergyCalibrationFiles();

  for (unsigned short i = 0; i < sourceVec.size(); i++) {

    std::regex b(sourceVec[i]);

    // Iterate through the directory entries
    // TFile *fw = new TFile("output.root","w");
    for (const auto &entry : fs::directory_iterator(directoryPath)) {
      // Convert the directory entry to a string
      std::string entryString = entry.path().string();

      if (regex_match(entryString, b)) {
        std::cout << "FOUND : " << entryString << std::endl;
        // TFile *fp = new TFile(entryString.c_str(),"r");
      }
    }
  }
std::cout <<"======================================================="<<std::endl;
{
std::vector<std::string> sourceVec = GetPositionCalibrationFiles();

  for (unsigned short i = 0; i < sourceVec.size(); i++) {

    std::regex b(sourceVec[i]);

    // Iterate through the directory entries
    // TFile *fw = new TFile("output.root","w");
    for (const auto &entry : fs::directory_iterator(directoryPath)) {
      // Convert the directory entry to a string
      std::string entryString = entry.path().string();

      if (regex_match(entryString, b)) {
        std::cout << "FOUND : " << entryString << std::endl;
        // TFile *fp = new TFile(entryString.c_str(),"r");
      }
    }
  }
}
  return 0;
}
