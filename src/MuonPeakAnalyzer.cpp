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

MuonPeakAnalyzer::MuonPeakAnalyzer(std::string filename, unsigned int barIndex) : fFileName(filename)
{
  fVecOfPeakPos.clear();
  FillMuonPeakPosVector(barIndex);
}

MuonPeakAnalyzer::MuonPeakAnalyzer(MuonPeakAnalyzer &obj)
{
  fFileName     = obj.GetFileName();
  fVecOfPeakPos = obj.GetVectorOfPeakPositions();
  fFileTime     = obj.GetFileTime();
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

void MuonPeakAnalyzer::FillMuonPeakPosVector(unsigned int barIndex)
{
  std::cout << RED << "Started the work of filling peak position vector ...." << RESET << std::endl;
  ismran::Analyzer_F an(fFileName,1000000);
  fFileTime = an.GetFileTime();
  std::cout << "FileTime : " << fFileTime << std::endl;
  std::vector<std::shared_ptr<ismran::ScintillatorBar_F>> vecOfScint = an.GetVectorOfScintillators();
  std::cout << RED << "Vector of scintillator filled........" << RESET << std::endl;
  ismran::InitializeHistograms();
  std::vector<std::shared_ptr<TH1F>> vecOfQMeanHist = ismran::GetQMeanPlots(vecOfScint);
  std::cout << BLUE << "QMean histograms received......." << RESET << std::endl;

  vecOfScint.clear();
  std::cout << MAGENTA << "Scint vector cleared........" << RESET << std::endl;

  if (barIndex == 500) {
    for (unsigned int i = 0; i < vecOfQMeanHist.size(); i++) {
      fVecOfPeakPos.push_back(FindMuonPeakPos(vecOfQMeanHist[i].get()));
    }
  } else {
    fVecOfPeakPos.push_back(FindMuonPeakPos(vecOfQMeanHist[barIndex].get()));
  }
  vecOfQMeanHist.clear();
}

unsigned int MuonPeakAnalyzer::FindMuonPeakPos(TH1F *hist)
{
  Int_t npeaks = 10;
  hist->Rebin(16);
  hist->GetXaxis()->SetRangeUser(2000, 25000);
  // npeaks = TMath::Abs(npeaks);
  TSpectrum *s = new TSpectrum(2 * npeaks);
  Int_t nfound = s->Search(hist, 2, "", 0.60);
  if (nfound > 1) {
    std::cout << RED << hist->GetName() << " : Found : " << nfound << " Peaks" << RESET << std::endl;
  }
  //  std::cout << "Found : " << nfound << " : candidate peaks to fit" << std::endl;
  Double_t *xpeaks;
  xpeaks = s->GetPositionX();
  double sum = 0;  
for (unsigned short p = 0; p < nfound; p++) {
    Double_t xp = xpeaks[p];
    std::cout << BLUE << hist->GetName() <<  " : Peak Location : " << xp << RESET <<  std::endl;
    sum += xp;
  }

  //return (int)xpeaks[nfound - 1];
  sum /= nfound;
  std::cout << MAGENTA <<  "FINAL RETURN VaLUE : " << sum << RESET << std::endl;
  return sum;
}

unsigned int MuonPeakAnalyzer::GetFileTime() const
{
  return fFileTime;
}

bool PeakAnalyzerComparator(const MuonPeakAnalyzer *lhs, const MuonPeakAnalyzer *rhs)
{
  return lhs->GetFileTime() < rhs->GetFileTime();
}

} // namespace ismran
