#include <string>
#include <iostream>
#include <filesystem>
#include <regex>
extern std::string replaceSubstring(const std::string &original, const std::string &searchString,
                                    const std::string &replacement);
extern std::vector<std::string> GetEnergyCalibrationFiles();
extern std::vector<std::string> GetPositionCalibrationFiles();
extern std::string GetDelTOffsetFile();
