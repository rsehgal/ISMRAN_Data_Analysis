/*
**	Filename : Plotter.cpp
**	2021-10-06
**	username : rsehgal
*/
#include <vector>
#include "ScintillatorBar_F.h"
#include <TH1F.h>
#include "HardwareNomenclature.h"
//#include "Mapping.h"
#include "Plotter.h"
namespace ismran {
std::vector<std::shared_ptr<TH1F>> vecOfQNearHist;
std::vector<std::shared_ptr<TH1F>> vecOfQFarHist;
std::vector<std::shared_ptr<TH1F>> vecOfQMeanHist;
std::vector<std::shared_ptr<TH1F>> vecOfQMeanCorrectedHist;

void InitializeHistograms()
{
  /*Clearing all the vector, and triggering automatic memory deallocation done in previously
  for the histograms*/
  vecOfQNearHist.clear();
  vecOfQFarHist.clear();
  vecOfQMeanHist.clear();
  vecOfQMeanCorrectedHist.clear();
  for (unsigned int i = 0; i < vecOfPsBars.size(); i++) {
    // std::cout << "Index val : " << i << std::endl;
    std::string name = vecOfPsBars[i];

    vecOfQNearHist.push_back(
        std::shared_ptr<TH1F>(new TH1F((name + "_QNear").c_str(), (name + "_QNear").c_str(), 1000, 0, 32000)));
    vecOfQFarHist.push_back(
        std::shared_ptr<TH1F>(new TH1F((name + "_QFar").c_str(), (name + "_QFar").c_str(), 1000, 0, 32000)));
    vecOfQMeanHist.push_back(
        std::shared_ptr<TH1F>(new TH1F((name + "_QMean").c_str(), (name + "_QMean").c_str(), 1000, 0, 32000)));
    vecOfQMeanCorrectedHist.push_back(std::shared_ptr<TH1F>(
        new TH1F((name + "_QMeanCorrected").c_str(), (name + "_QMeanCorrected").c_str(), 300, 0, 60)));
  }
}

std::vector<std::shared_ptr<TH1F>> GetQNearPlots(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScint_F)
{
  return GetQPlots(vecOfScint_F, 1);
}

std::vector<std::shared_ptr<TH1F>> GetQFarPlots(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScint_F)
{
  return GetQPlots(vecOfScint_F, 2);
}

std::vector<std::shared_ptr<TH1F>> GetQMeanPlots(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScint_F)
{
  return GetQPlots(vecOfScint_F, 3);
}
std::vector<std::shared_ptr<TH1F>> GetQMeanCorrectedPlots(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScint_F)
{
  return GetQPlots(vecOfScint_F, 4);
}
std::vector<std::shared_ptr<TH1F>> GetQMeanCorrectedPlots(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScint_F,
                                                          std::vector<unsigned int> vecOfPeakPos)
{
  for (unsigned int i = 0; i < vecOfScint_F.size(); i++) {
    if (vecOfScint_F[i]->GetBarIndex() < 96) {
      vecOfQMeanCorrectedHist[vecOfScint_F[i]->GetBarIndex()]->Fill(
          vecOfScint_F[i]->GetQMeanCorrected(vecOfPeakPos[vecOfScint_F[i]->GetBarIndex()]));
    }
  }
  return vecOfQMeanCorrectedHist;
}

// std::vector<TH1F *> GetQPlots(std::vector<ScintillatorBar_F *> vecOfScint_F, unsigned short opt)
std::vector<std::shared_ptr<TH1F>> GetQPlots(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScint_F, unsigned short opt)
{
  std::vector<std::shared_ptr<TH1F>> vecOfHist;
  if (opt == 1) vecOfHist = vecOfQNearHist;
  if (opt == 2) vecOfHist = vecOfQFarHist;
  if (opt == 3) vecOfHist = vecOfQMeanHist;
  if (opt == 4) vecOfHist = vecOfQMeanCorrectedHist;

  for (unsigned int i = 0; i < vecOfScint_F.size(); i++) {

    if (vecOfScint_F[i]->GetBarIndex() < 96) {

      if (opt == 1) vecOfHist[vecOfScint_F[i]->GetBarIndex()]->Fill(vecOfScint_F[i]->GetQNear());
      if (opt == 2) vecOfHist[vecOfScint_F[i]->GetBarIndex()]->Fill(vecOfScint_F[i]->GetQFar());
      if (opt == 3) vecOfHist[vecOfScint_F[i]->GetBarIndex()]->Fill(vecOfScint_F[i]->GetQMean());
      if (opt == 4) vecOfHist[vecOfScint_F[i]->GetBarIndex()]->Fill(vecOfScint_F[i]->GetQMeanCorrected());
    }
  }
  return vecOfHist;
} // namespace ismran

} // namespace ismran
