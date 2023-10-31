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
  std::cout << "SIZE of SCINT VECTOR : " << vecOfScint.size() << std::endl;
  // TFile *fp   = new TFile(("MLData_" + std::string(argv[1])).c_str(), "RECREATE");
  TFile *fp   = new TFile("MLData.root", "RECREATE");
  TTree *tree = new TTree("mltree", "Classification ML Tree");
  ushort barIndex;
  UInt_t qnear;
  UInt_t qfar;
  double qmean;
  unsigned short particleId = 1;
  ULong64_t evNo;
  Long64_t delT;

  tree->Branch("fBarIndex", &barIndex);
  tree->Branch("fEvNo", &evNo);
  tree->Branch("fQNear", &qnear);
  tree->Branch("fQFar", &qfar);
  tree->Branch("fQMean", &qmean);
  tree->Branch("fDelT", &delT);
  tree->Branch("fParticleId", &particleId);

  

  for (unsigned int i = 0; i < vecOfScint.size(); i++) {

    /*std::cout << vecOfScint[i]->GetQNear() << " : " << vecOfScint[i]->GetQFar() << std::endl;
    if(i > 100)
      break;*/

    particleId = 1;
    evNo	= vecOfScint[i]->GetEvNo();
    barIndex   = vecOfScint[i]->GetBarIndex();
    qnear      = vecOfScint[i]->GetQNear();
    qfar       = vecOfScint[i]->GetQFar();
    qmean      = vecOfScint[i]->GetQMeanCorrected();
    delT      = vecOfScint[i]->GetDelT();
    /*if (vecOfScint[i]->GetQMeanCorrected() > qmeanCorrThreshold) {
      particleId = 0; // Muon : 0 , Gamma : 1 default
    }*/

    if (barIndex == 19) tree->Fill();
  }

  tree->Write();
  fp->Close();

  //  fp->Close();
  return 0;
}
