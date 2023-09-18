/*
**	Filename : Test_MuonArrivalTime.cpp
**	2021-10-28
**	username : rsehgal
**
**      Description : Code to get the the Muon Arrival time distribution
*/
#include <iostream>
#include "ScintillatorBar_F.h"
#include "SingleMuonTrack.h"
#include "Analyzer_F.h"
#include "Plotter.h"
#include <TFile.h>
#include "PsBar.h"
#include "Helpers.h"
#include <TApplication.h>
#include "HardwareNomenclature.h"
int main(int argc, char *argv[])
{
  TApplication *fApp                            = new TApplication("Test", NULL, NULL);
  std::vector<ismran::SingleMuonTrack *> smtVec = ismran::GetMuonTracksVector(argv[1]);

  ismran::Analyzer_F an;
  ismran::vecOfPeakPos = an.GetPeakPosVec_Direct();

  ULong64_t startTime = 0;
  ULong64_t endTime   = 0;

  unsigned int layerIndex         = 9;
  bool startFlag                  = false;
  TH1F *histMuonRate              = new TH1F("Muon Rate Estimation", "", 100, 0, 100);
  TH1F *histBarNum                = new TH1F("BarNumHist", "BarNumHist", 90, 0, 90);
  unsigned int counterPassingMuon = 0;
  unsigned int counterUpgoingMuon = 0;
  unsigned short printCounter     = 0;
  for (unsigned int i = 0; i < smtVec.size(); i++) {
    std::vector<ismran::ScintillatorBar_F *> scintVec = smtVec[i]->GetMuonTrack();
    //if (smtVec[i]->SingleHitInLayer(layerIndex)) {
    if (smtVec[i]->SingleHitInEachLayer()) {
      // smtVec[i]->Print();
      if (smtVec[i]->IsPassingMuon()) {
        counterPassingMuon++;
        if (counterPassingMuon <= 2) smtVec[i]->Print();
        if (smtVec[i]->IsUpgoingMuon()//)
        	 && scintVec[0]->GetLayerIndex() == 0 && scintVec[scintVec.size() - 1]->GetLayerIndex() == 9)
        {
          counterUpgoingMuon++;
          if (counterUpgoingMuon <= 5) smtVec[i]->Print();
        }
      }
    }
  }

  std::cout << "Total Number of Passing muons : " << counterPassingMuon << std::endl;
  std::cout << "Total Number of upgoing muons : " << counterUpgoingMuon << std::endl;
  std::cout << "% of upgoing muons : " << ((1. * counterUpgoingMuon) / (1. * counterPassingMuon) * 100.) << std::endl;

  fApp->Run();
  return 0;
}
