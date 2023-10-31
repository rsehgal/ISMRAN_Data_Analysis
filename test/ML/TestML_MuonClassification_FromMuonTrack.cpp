/*
**	Filename : Test_Analyzer_F.cpp
**	2021-10-06
**	username : rsehgal
*/
#include <iostream>
#include "Analyzer_F.h"
#include "Plotter.h"
#include <TFile.h>
#include "ScintillatorBar_F.h"
#include "HardwareNomenclature.h"
#include "Helpers.h"
#include "SingleMuonTrack.h"
int main(int argc, char *argv[])
{
  // ismran::Analyzer_F an(argv[1],10000000);
  ismran::Analyzer_F an(argv[1], 0);
#ifdef USE_EXISTING_MUON_PEAK_FILE
  ismran::vecOfPeakPos = ismran::GetPeakPosVec_Direct(".", "MuonPeak.root");
#else
  ismran::vecOfPeakPos = an.GetPeakPosVec();
#endif

  std::vector<ismran::ScintillatorBar_F *> vecOfScint = an.GetVectorOfScintillators();
  std::vector<ismran::SingleMuonTrack *> smtVec       = an.ReconstructMuonTrack();

  std::cout << "SIZE of SCINT VECTOR : " << vecOfScint.size() << std::endl;
  // TFile *fp   = new TFile(("MLData_" + std::string(argv[1])).c_str(), "RECREATE");
  TFile *fp   = new TFile("MLData_Track.root", "RECREATE");
  TTree *tree = new TTree("mltree", "Classification ML Tree");
  ushort barIndex;
  UInt_t qnear;
  UInt_t qfar;
  double qmean;
  Long64_t delT;
  ULong64_t evNo;
  // char particleId = 1;
  unsigned short particleId = 0; // Muon : 0 , Gamma : 1 default

  tree->Branch("fBarIndex", &barIndex);
  tree->Branch("fEvNo", &evNo);
  tree->Branch("fQNear", &qnear);
  tree->Branch("fQFar", &qfar);
  tree->Branch("fQMean", &qmean);
  tree->Branch("fDelT", &delT);
  tree->Branch("fParticleId", &particleId);

  for (unsigned int i = 0; i < smtVec.size(); i++) {

    if (smtVec[i]->IsPassingMuon()) {
      std::vector<ismran::ScintillatorBar_F *> vecOfScint = smtVec[i]->GetMuonTrack();

      for (unsigned int j = 0; j < vecOfScint.size(); j++) {
        //particleId = 1;
        evNo       = vecOfScint[j]->GetEvNo();
        barIndex   = vecOfScint[j]->GetBarIndex();
        qnear      = vecOfScint[j]->GetQNear();
        qfar       = vecOfScint[j]->GetQFar();
        qmean      = vecOfScint[j]->GetQMeanCorrected();
        delT       = vecOfScint[j]->GetDelT();
        /*if (vecOfScint[j]->GetQMeanCorrected() > qmeanCorrThreshold) {
          particleId = 0; // Muon : 0 , Gamma : 1 default
        }*/

        if (barIndex == 19){
		//if(qmean >=3 && qmean <= 15)
		{
			tree->Fill();
		}
	}
      }
    }
  }

  tree->Write();
  fp->Close();

  //  fp->Close();
  return 0;
}
