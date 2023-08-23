/*
**	Filename : Test_MuonTrackAnalysis.cpp
**	2023-08-23
**	username : rsehgal
**
**	Code to do Analysis on reconstructed muon tracks.
**	Need MuonTrack file as command line input.
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
#include "colors.h"
int main(int argc, char *argv[])
{
  TApplication *fApp                            = new TApplication("Test", NULL, NULL);
  std::vector<ismran::SingleMuonTrack *> smtVec = ismran::GetMuonTracksVector(argv[1]);

  ULong64_t startTime = 0;
  ULong64_t endTime   = 0;

  unsigned int counter = 0;

  TH1F *hitMultiplicity           = new TH1F("HitMultiplicity", "HitMultiplicity", 10, 0, 10);
  unsigned int layerIndex         = 3;
  unsigned int passingMuonCounter = 0;
  unsigned int missedCounter = 0;
  unsigned int detectedTriggerCounter=0;
  for (unsigned int i = 0; i < smtVec.size(); i++) {
    if (smtVec[i]->IsPassingMuon()) {
      passingMuonCounter++;
      std::vector<ismran::ScintillatorBar_F *> scintVec = smtVec[i]->GetMuonTrack();
      unsigned short multiplicityCounter                = 0;
      for (unsigned int j = 0; j < scintVec.size(); j++) {
        if (scintVec[j]->GetLayerIndex() == layerIndex) multiplicityCounter++;
      }
      if(multiplicityCounter==0){
		missedCounter++;
		//std::cout << RED << "No hits for for Track number : " << i << std::endl;
	}
      if (multiplicityCounter > 0) {
	hitMultiplicity->Fill(multiplicityCounter);
	detectedTriggerCounter++;
	}

      if (smtVec[i]->SingleHitInLayer(layerIndex)) {
        counter++;
      }
    }
  }

  std::cout << GREEN << "Missed Counter : " << missedCounter << RESET << std::endl;

  std::cout << RED << "Passing Muon Counter : " << passingMuonCounter << std::endl;
  std::cout << "Single hit counter : " << counter << std::endl;
  std::cout << "Single hit triggering efficiency : " << ((1. * counter) / (1. * passingMuonCounter) * 100.)
            << std::endl;
  std::cout << BLUE << "Multiple hit counter : " << detectedTriggerCounter << std::endl;
  std::cout << "Multiple hit triggering efficiency : " << ((1.*detectedTriggerCounter)/(1.*passingMuonCounter)*100.) << std::endl;

  hitMultiplicity->Draw();
  fApp->Run();
}
