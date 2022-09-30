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
#include "fstream"
int main(int argc, char *argv[])
{
  std::ofstream fpT("histData.txt");
  std::ofstream binContent("histData_XY.txt");
  TApplication *fApp       = new TApplication("TEST", NULL, NULL);
  unsigned int numOfEvents = std::atoi(argv[2]);
  ismran::Analyzer_F an(argv[1], numOfEvents);
#ifdef USE_EXISTING_MUON_PEAK_FILE
  ismran::vecOfPeakPos = an.GetPeakPosVec_Direct();
#ifdef VERBOSE
  std::cout << BLUE << "Going to if..." << RESET << std::endl;
#endif
#else
#ifdef VERBOSE
  std::cout << RED << "Going to else..." << RESET << std::endl;
#endif
  ismran::vecOfPeakPos = an.GetPeakPosVec();
#endif

  TFile *fp = new TFile(("MuonLifeTime_" + ismran::GetBaseName(argv[1])).c_str(), "RECREATE");
  std::vector<std::shared_ptr<ismran::ScintillatorBar_F>> vecOfScint = an.GetVectorOfScintillators();
  // std::vector<std::shared_ptr<ismran::SingleMuonTrack>> smtVec       = an.ReconstructMuonTrack();
  // std::vector<ismran::SingleMuonTrack*> smtVec       = an.ReconstructMuonTrack();

  // std::vector<unsigned int> vecOfPeakPos = an.GetPeakPosVec();

  bool start          = false;
  ULong64_t startTime = 0.;
  ULong64_t endTime   = 0.;

  TH1F *hist = new TH1F("MuonLifeTime", "MuonLifetime", 150, 0, 15.);
  for (unsigned int i = 0; i < vecOfScint.size(); i++) {
    // double qmeanCorr = vecOfScint[i]->GetQMeanCorrected(vecOfPeakPos[vecOfScint[i]->GetBarIndex()]);
    double qmeanCorr = vecOfScint[i]->GetQMeanCorrected(); // vecOfPeakPos[vecOfScint[i]->GetBarIndex()]);

    // For muon start signal
    if ((qmeanCorr > 10) && (qmeanCorr < 25)
#ifdef FOLDED_DATA
        && (vecOfScint[i]->GetLayerIndex() == 9)
#else
        && (vecOfScint[i]->GetLayerIndex() == 4)
#endif
    ) {
      // startTime = vecOfScint[i]->GetTStampNear();
      startTime = vecOfScint[i]->GetTStampSmall();
    }

    // For electron delay signal
    if ((qmeanCorr > 3) && (qmeanCorr < 30)) {
      // endTime       = vecOfScint[i]->GetTStampNear();
      endTime       = vecOfScint[i]->GetTStampSmall();
      Long64_t delT = endTime - startTime;
      if (delT > 1000000 && delT < 15000000) {
        // std::cout << GREEN << (delT/1e+6) << " us....." <<RESET << std::endl;
        hist->Fill(((1. * delT) / 1e+6));
 	fpT << ((1. * delT) / 1e+6) << std::endl;
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
  fpT.close();
  //hist->Draw();

  hist->Rebin(2);
  TF1 *fitFunc = new TF1("fitFunc", "([1]*exp(-x/[0])) + [2] ",1.8,15);
  fitFunc->SetParameters(2.2,10,10);
  fitFunc->SetParNames("#tau","N","C");
  hist->Fit(fitFunc,"R");
  fp->cd();

  
  for(unsigned int i = 1 ; i < hist->GetNbinsX()-1 ; i++){
	binContent << i<<","<<hist->GetBinContent(i)<<std::endl;
  } 
  binContent.close();
  hist->Write();
  hist->Draw("ap");
  fp->Close();
  // fApp->Run();  
  return 0;
}
