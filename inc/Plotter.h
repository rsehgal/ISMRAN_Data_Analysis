/*
**	Filename : Plotter.h
**	2021-10-06
**	username : rsehgal
*/
#ifndef Plotter_h
#define Plotter_h
#include <vector>
#include "ScintillatorBar_F.h"
class TH1F;
namespace ismran {
extern std::vector<TH1F *> vecOfQNearHist;
extern std::vector<TH1F *> vecOfQFarHist;
extern std::vector<TH1F *> vecOfQMeanHist;
extern std::vector<TH1F *> vecOfQMeanCorrectedHist;

extern std::vector<TH1F *> GetQNearPlots(std::vector<ScintillatorBar_F *> vecOfScint_F);
extern std::vector<TH1F *> GetQFarPlots(std::vector<ScintillatorBar_F *> vecOfScint_F);
extern std::vector<TH1F *> GetQMeanPlots(std::vector<ScintillatorBar_F *> vecOfScint_F);
extern std::vector<TH1F *> GetQMeanCorrectedPlots(std::vector<ScintillatorBar_F *> vecOfScint_F);
extern std::vector<TH1F *> GetQPlots(std::vector<ScintillatorBar_F *> vecOfScint_F, unsigned short opt);

extern void InitializeHistograms();
} // namespace ismran
#endif
