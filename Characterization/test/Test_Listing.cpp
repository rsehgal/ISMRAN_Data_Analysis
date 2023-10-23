#include <iostream>
#include <regex>
#ifdef EXPERIMENTAL_FILESYSTEM
#include <experimental/filesystem>
namespace fs=std::experimental::filesystem;
#else
#include <filesystem>
namespace fs=std::filesystem;
#endif
#include <string>

int main() {
    std::string directory_path = "/home/rsehgal/PS5_S2AB1006"; // Replace with the actual directory path.
    std::string file_pattern = "*.root"; // Replace with the desired file pattern.

    try {
	//std::regex pattern(file_pattern);
        for (const auto& entry : fs::directory_iterator(directory_path)) {
   	    //std::cout << entry << std::endl;

		std::string filename = entry.path().filename().string();
		//std::cout << "Filename : " << filename << std::endl;
		//std::cout << filename.find("Cs137") << std::endl;
		size_t found = filename.find("Cs137");
		/*if(found != "std::string::npos")
			std::cout <<"Cs137 files : " << filename << std::endl;*/
		//if(found > 10000){
		if(filename.find("Couples") > 10000 || filename.find("+0cm.root") > 10000 ){
		}else{
		std::cout <<filename << std::endl;
		}
	
		/*if (fs::is_regular_file(entry) && std::regex_match(entry.path().filename().string(), pattern)) 
		{
                std::cout << entry.path() << std::endl;
            	}*/
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing the directory: " << e.what() << std::endl;
    }

    return 0;
}

