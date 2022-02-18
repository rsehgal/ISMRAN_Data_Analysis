/*
**	Filename : Helpers.h
**	2021-10-27
**	username : rsehgal
*/
#ifndef Helpers_h
#define Helpers_h
#include "ScintillatorBar_F.h"
#include "SingleMuonTrack.h"
#include <string>
namespace ismran {

extern bool CompareTimestampScintillator(ScintillatorBar_F *i1, ScintillatorBar_F *i2);
extern std::vector<ismran::SingleMuonTrack*> GetMuonTracksVector(std::string filename, std::string treeName="TracksTree", unsigned int numOfEvents=0);
extern std::vector<std::string> GetVectorOfFileNameInADirectory(std::string directoryPath);
extern std::string GetBaseName(std::string const &path);
}
#endif
