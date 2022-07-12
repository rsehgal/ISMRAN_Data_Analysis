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

extern bool CompareTimestampScintillator(std::shared_ptr<ScintillatorBar_F> i1, std::shared_ptr<ScintillatorBar_F> i2);
extern std::vector<ismran::SingleMuonTrack*> GetMuonTracksVector(std::string filename, std::string treeName="TracksTree", unsigned int numOfEvents=0);
extern std::vector<std::string> GetVectorOfFileNameInADirectory(std::string directoryPath);
extern std::string GetBaseName(std::string const &path);

//Helper functions to use the peak position file for the current file under processing
extern std::vector<unsigned int> GetPeakPosVec(std::string filename);
extern std::vector<unsigned int> GetPeakPosVec(std::string dirpath,std::string filename);
extern std::vector<unsigned int> GetPeakPosVec_Direct(std::string dirpath,std::string filename);
extern unsigned int GetPeakPos(std::string filename, std::vector<std::string> vecofbarnames, std::string barName);

extern unsigned int GetFoldedQNearQFar(unsigned int qnear, unsigned int qfar);
extern unsigned int GetUnFoldedQNear(unsigned int qlong);
extern unsigned int GetUnFoldedQFar(unsigned int qlong);
}
#endif
