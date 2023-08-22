/*
**	Filename : Test_SmallChunk.cpp
**	2021-10-27
**	username : rsehgal
*/
#include <iostream>
#include "ScintillatorBar_F.h"
#include "SingleMuonTrack.h"
#include "Analyzer_F.h"
#include "Plotter.h"
#include <TFile.h>
#include "HardwareNomenclature.h"
#include "Helpers.h"
int main(int argc, char *argv[])
{
  unsigned int numOfEvents = std::atoi(argv[2]);
  ismran::Analyzer_F an(argv[1], numOfEvents);
#ifdef USE_EXISTING_MUON_PEAK_FILE
  ismran::vecOfPeakPos = ismran::GetPeakPosVec_Direct(".","MuonPeak.root");
#else
  ismran::vecOfPeakPos = an.GetPeakPosVec();
#endif
  std::vector<ismran::ScintillatorBar_F*> vecOfScint = an.GetVectorOfScintillators();
  //std::vector<std::shared_ptr<ismran::ScintillatorBar_F>> vecOfScint = an.GetVectorOfScintillators();
  //std::vector<std::shared_ptr<ismran::SingleMuonTrack>> smtVec       = an.ReconstructMuonTrack();
  std::vector<ismran::SingleMuonTrack*> smtVec       = an.ReconstructMuonTrack();
  std::cout << "Size of SMTVEC : " << smtVec.size() << std::endl;
  unsigned int passingMuonCounter = 0;
  unsigned int hittingAllLayerCounter=0;
  TH1F *hist = new TH1F("Muons","Muons",20,0,20);
  for(unsigned int i = 0 ; i < smtVec.size() ; i++){
	if(smtVec[i]->IsPassingMuon()){
		//std::cout <<"Passing muon number : " << passingMuonCounter << " : TrackLength : " << smtVec[i]->size() << std::endl;
		hist->Fill(smtVec[i]->size());
		if(smtVec[i]->size()==10)
			hittingAllLayerCounter++;
		passingMuonCounter++;
			
	}
  }

  std::cout << "Total number of passing muons : " << passingMuonCounter << std::endl;
  std::cout << "Total number of passing muon that is detected by all the layers : " << hittingAllLayerCounter << std::endl;
 TFile *outfile = new TFile("PassingMuons.root","RECREATE");
  outfile->cd();
  hist->Write();
  outfile->Close();


#if (0)
  unsigned int trackCounter = 0;
  for (unsigned int i = 0; i < smtVec.size(); i++) {
    if (trackCounter < 10) {
      if (smtVec[i]->size() > 2) {
        smtVec[i]->Print();
        trackCounter++;
      }
    } else {
      break;
    }
  }
#endif
  return 0;
}
