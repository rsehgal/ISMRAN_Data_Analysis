#include <iostream>
#include <vector>
#include <string>
#include "Helpers_Dqm.h"
//#include "colors.h"
using std::cout; using std::cin;
using std::endl; using std::vector;
#ifdef EXPERIMENTAL_FILESYSTEM
#include <experimental/filesystem>
namespace FS=std::experimental::filesystem;
#else
#include <filesystem>
namespace FS=std::filesystem;
#endif
using std::string;
using namespace ismran;
int main() {
/*    vector<string> files_to_check = {"/home/rsehgal/ISMRAN_Code/ISMRAN_dqm/sourceDir/test1.txt"};

    for (const auto &file : files_to_check) {
        FS::exists(file) ? cout << "Exists\n" : cout << "Doesn't exist\n";
    }
*/

//	/home/neutrino/IsmranDataA/Dhruva//March2022//ISMRAN_digiROOT_RON_11hrs46mins17secs_01Mar2022_Run2671.root
    std::string fullImageSourceFilePrefix="/home/neutrino/IsmranDataA/Dhruva/March2022//images/";
    std::string fileToCopy = "ISMRAN_digiROOT_RON_11hrs46mins17secs_01Mar2022_Run2671.root";

    std::cout << "FileToCopy : " << fileToCopy << std::endl;
    std::string imageFileSuffix = GetPath_StartingFrom_DelimiterWithIndex(fileToCopy,'_',1);
    std::cout <<"Image suffix : " << imageFileSuffix << std::endl;

  imageFileSuffix = GetStringToken_WithIndex(imageFileSuffix,'.',0);
  imageFileSuffix += ".png";
  std::string imageName = "NearRate"+imageFileSuffix;
  std::string fullImageSourceFilePath = fullImageSourceFilePrefix+imageName;
  std::cout << "FullImageFile : " << fullImageSourceFilePath << std::endl;
  std::cout << "File Exists : " << ismran::FileExists(fullImageSourceFilePath) << std::endl;

    return EXIT_SUCCESS;
}

