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
extern std::vector<std::shared_ptr<TH1F>> vecOfQNearHist;
extern std::vector<std::shared_ptr<TH1F>> vecOfQFarHist;
extern std::vector<std::shared_ptr<TH1F>> vecOfQMeanHist;
extern std::vector<std::shared_ptr<TH1F>> vecOfQMeanCorrectedHist;

extern std::vector<std::shared_ptr<TH1F>> GetQNearPlots(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScint_F);
extern std::vector<std::shared_ptr<TH1F>> GetQFarPlots(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScint_F);
extern std::vector<std::shared_ptr<TH1F>> GetQMeanPlots(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScint_F);
extern std::vector<std::shared_ptr<TH1F>> GetQMeanCorrectedPlots(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScint_F);
extern std::vector<std::shared_ptr<TH1F>> GetQMeanCorrectedPlots(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScint_F,
                                           std::vector<unsigned int> vecOfPeakPos);
extern std::vector<std::shared_ptr<TH1F>> GetQPlots(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScint_F, unsigned short opt);

extern void InitializeHistograms();
} // namespace ismran
#endif
