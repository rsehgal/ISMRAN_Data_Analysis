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
int main()
{
  TApplication *fApp                            = new TApplication("Test", NULL, NULL);
  std::vector<ismran::SingleMuonTrack *> smtVec = ismran::GetMuonTracksVector("MuonTracks.root");

  ULong64_t startTime = 0;
  ULong64_t endTime   = 0;

  unsigned int layerIndex = 9;
  bool startFlag          = false;
  TH1F *histMuonRate      = new TH1F("Muon Rate Estimation", "", 70, 30, 100);

  for (unsigned int i = 0; i < smtVec.size(); i++) {
    if (smtVec[i]->SingleHitInLayer(layerIndex)) {
      std::vector<ismran::ScintillatorBar_F *> scintVec = smtVec[i]->GetMuonTrack();
      for (unsigned int j = 0; j < scintVec.size(); j++) {
        if (scintVec[j]->GetLayerIndex() == layerIndex) {
          if (!startFlag) {
            startFlag = true;
            startTime = scintVec[j]->GetTStampNear();
          } else {
            endTime       = scintVec[j]->GetTStampNear();
            Long64_t diff = endTime - startTime;
            std::cout << "Diff : " << diff << std::endl;
            startTime = endTime;
            histMuonRate->Fill(diff / 1e+9);
          }
        }
      }
    }
  }

  histMuonRate->Draw();
  fApp->Run();
  return 0;
}
