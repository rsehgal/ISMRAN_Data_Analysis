/*
**	Filename : HardWareNomenclature.h
**	2021-09-25
**	username : rsehgal
*/
#ifndef HardWareNomenclature_h
#define HardWareNomenclature_h
#include <vector>
#include <string>
namespace ismran {
extern std::vector<std::string> vecOfBarsNamess;
extern std::vector<std::string> sequentialBarNames;
extern std::vector<unsigned int> vecOfPeakPos;
extern std::vector<std::string> vecOfPsBars;

extern unsigned int GetIndexFromBarName(std::string barName);
extern unsigned int GetIndexFromBarName(std::vector<std::string> vecofbarnames, std::string barName);
extern unsigned int GetPeakPos(std::string barName);
} // namespace ismran
#endif
