/*
**	Filename : MuonPeakAnalyzer.cpp
**	2022-02-17
**	username : rsehgal
*/

#include <iostream>
#include "MuonPeakAnalyzer.h"
#include "Plotter.h"
#include <TFile.h>
#include "ScintillatorBar_F.h"
#include "Analyzer_F.h"
#include <TSpectrum.h>
#include "colors.h"
#include "Helpers.h"
ClassImp(ismran::MuonPeakAnalyzer);

namespace ismran {

MuonPeakAnalyzer::MuonPeakAnalyzer() {}

MuonPeakAnalyzer::~MuonPeakAnalyzer() {}

MuonPeakAnalyzer::MuonPeakAnalyzer(std::string filename) : fFileName(filename)
{
  fVecOfPeakPos.clear();
  FillMuonPeakPosVector();
}
void MuonPeakAnalyzer::SetFileName(std::string filename)
{
  fFileName = filename;
  FillMuonPeakPosVector();
}
void MuonPeakAnalyzer::UpdateFileName()
{
  fFileName = GetBaseName(fFileName);
}

std::string MuonPeakAnalyzer::GetFileName() const
{
  return fFileName;
}

std::vector<unsigned int> MuonPeakAnalyzer::GetVectorOfPeakPositions() const
{
  return fVecOfPeakPos;
}

unsigned int MuonPeakAnalyzer::GetRunNumber() {}

void MuonPeakAnalyzer::FillMuonPeakPosVector()
{
  ismran::Analyzer_F an(fFileName);
  std::vector<ismran::ScintillatorBar_F *> vecOfScint = an.GetVectorOfScintillators();
  ismran::InitializeHistograms();
  std::vector<TH1F *> vecOfQMeanHist = ismran::GetQMeanPlots(vecOfScint);

  for (unsigned int i = 0; i < vecOfQMeanHist.size(); i++) {
    fVecOfPeakPos.push_back(FindMuonPeakPos(vecOfQMeanHist[i]));
  }
}

unsigned int MuonPeakAnalyzer::FindMuonPeakPos(TH1F *hist)
{
  Int_t npeaks = 10;
  hist->Rebin(8);
  hist->GetXaxis()->SetRangeUser(2000, 25000);
  // npeaks = TMath::Abs(npeaks);
  TSpectrum *s = new TSpectrum(2 * npeaks);
  Int_t nfound = s->Search(hist, 2, "", 0.40);
  if (nfound > 1) {
    std::cout << RED << hist->GetName() << " : Found : " << nfound << " Peaks" << RESET << std::endl;
  }
  //  std::cout << "Found : " << nfound << " : candidate peaks to fit" << std::endl;
  Double_t *xpeaks;
  xpeaks = s->GetPositionX();
  for (unsigned short p = 0; p < nfound; p++) {
    Double_t xp = xpeaks[p];
    // std::cout << "Peak Location : " << xp << std::endl;
  }

  return (int)xpeaks[nfound - 1];
}
} // namespace ismran