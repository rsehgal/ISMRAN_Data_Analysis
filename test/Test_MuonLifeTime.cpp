/*
**	Filename : Test_MuonLifeTime.cpp
**	2022-03-09
**	username : rsehgal
*/
#include <iostream>
#include "ScintillatorBar_F.h"
#include "SingleMuonTrack.h"
#include "Analyzer_F.h"
#include "Plotter.h"
#include <TFile.h>
#include "colors.h"
#include <TH1F.h>
#include <TApplication.h>
#include "Helpers.h"
#include "HardwareNomenclature.h"
int main(int argc, char *argv[])
{
  TApplication *fApp       = new TApplication("TEST", NULL, NULL);
  unsigned int numOfEvents = std::atoi(argv[2]);
  ismran::Analyzer_F an(argv[1], numOfEvents);
  ismran::vecOfPeakPos = an.GetPeakPosVec();

  TFile *fp = new TFile(("MuonLifeTime_" + ismran::GetBaseName(argv[1])).c_str(), "RECREATE");
  std::vector<std::shared_ptr<ismran::ScintillatorBar_F>> vecOfScint = an.GetVectorOfScintillators();
  // std::vector<std::shared_ptr<ismran::SingleMuonTrack>> smtVec       = an.ReconstructMuonTrack();
  // std::vector<ismran::SingleMuonTrack*> smtVec       = an.ReconstructMuonTrack();

  std::vector<unsigned int> vecOfPeakPos = an.GetPeakPosVec();

  bool start          = false;
  ULong64_t startTime = 0.;
  ULong64_t endTime   = 0.;

  TH1F *hist = new TH1F("MuonLifeTime", "MuonLifetime", 150, 0, 15.);
  for (unsigned int i = 0; i < vecOfScint.size(); i++) {
    //double qmeanCorr = vecOfScint[i]->GetQMeanCorrected(vecOfPeakPos[vecOfScint[i]->GetBarIndex()]);
    double qmeanCorr = vecOfScint[i]->GetQMeanCorrected();//vecOfPeakPos[vecOfScint[i]->GetBarIndex()]);

    // For muon start signal
    if ((qmeanCorr > 10) && (qmeanCorr < 25) && (vecOfScint[i]->GetLayerIndex() == 9)) {
      startTime = vecOfScint[i]->GetTStampNear();
    }

    // For electron delay signal
    if ((qmeanCorr > 3) && (qmeanCorr < 30)) {
      endTime       = vecOfScint[i]->GetTStampNear();
      Long64_t delT = endTime - startTime;
      if (delT > 1000000 && delT < 15000000) {
        // std::cout << GREEN << (delT/1e+6) << " us....." <<RESET << std::endl;
        hist->Fill(((1. * delT) / 1e+6));
      }
    }

    /*if (qmeanCorr > qmeanCorrThreshold) } && vecOfScint[i]->GetLayerIndex() == 9) {
      if (!start) {
        start     = true;
        startTime = vecOfScint[i]->GetTStampSmall();
        //startTime = vecOfScint[i]->GetTStampNear();
        //std::cout << BLUE << vecOfScint[i]->GetTStampNear() << RESET << std::endl;
      } else {
        endTime       = vecOfScint[i]->GetTStampSmall();
        //endTime       = vecOfScint[i]->GetTStampNear();
        Long64_t diff = endTime - startTime;
        if (std::fabs(diff) > 30000)//} && std::fabs(diff) < 25000000) {
        //if ((diff) > 30000)
  {//} && std::fabs(diff) < 25000000) {
          // std::cout << RED << startTime << " : " << endTime << " :: " << diff << RESET << std::endl;
          if (std::fabs(diff) < 15000000) {
          //if ((diff) < 15000000) {
            hist->Fill(std::fabs(diff) / 1e+6);
          } else {
            start = false;
          }
        }
        // startTime = endTime;
      }
    }*/
  }
  std::cout << "Size of vecOfScint : " << vecOfScint.size() << std::endl;
  hist->Draw();
  fp->cd();
  hist->Write();
  fp->Close();
  // fApp->Run();
  return 0;
}
