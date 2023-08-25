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
#include <TString.h>
#include "Database.h"
int main(int argc, char *argv[])
{
  unsigned int numOfEvents = 0; // std::atoi(argv[2]);
  std::string filePath     = std::string(argv[1]);
  std::string justfilename = std::string(argv[2]);
  TString compFileName     = (filePath + "/" + justfilename).c_str();
  TString oldSubStr        = "neutrino";
  TString newSubStr        = "ismran";//"rsehgal";
  compFileName.ReplaceAll(oldSubStr, newSubStr);
  const char *updatedFileName = compFileName.Data();
  // std::cout << "Updated File Name : " << updatedFileName << std::endl;

  unsigned int passingMuonCounter = 0;
  /*{
    ismran::Database d("127.0.0.1", "ismran_db", "ismran", "ismran123");
    d.SetVerbose(true);
    d.Connect();

    d.Update(std::string("update ismran_files set passingmuons=") + std::to_string(passingMuonCounter) +
             std::string(" where fileName='") + justfilename + std::string("'"));
  }

  return 0;
  */
  // return 0;
  // ismran::Analyzer_F an(argv[1], numOfEvents);
  ismran::Analyzer_F an(updatedFileName, numOfEvents);
#ifdef USE_EXISTING_MUON_PEAK_FILE
  ismran::vecOfPeakPos = ismran::GetPeakPosVec_Direct(".", "MuonPeak.root");
#else
  ismran::vecOfPeakPos = an.GetPeakPosVec();
#endif
  std::vector<ismran::ScintillatorBar_F *> vecOfScint = an.GetVectorOfScintillators();
  // std::vector<std::shared_ptr<ismran::ScintillatorBar_F>> vecOfScint = an.GetVectorOfScintillators();
  // std::vector<std::shared_ptr<ismran::SingleMuonTrack>> smtVec       = an.ReconstructMuonTrack();
  std::vector<ismran::SingleMuonTrack *> smtVec = an.ReconstructMuonTrack();
  std::cout << "Size of SMTVEC : " << smtVec.size() << std::endl;
  unsigned int hittingAllLayerCounter = 0;
  unsigned int printCounter           = 0;
  TH1F *hist                          = new TH1F("Muons", "Muons", 20, 0, 20);
  for (unsigned int i = 0; i < smtVec.size(); i++) {
    if (smtVec[i]->IsPassingMuon()) {
      if (printCounter < 5) {
        printCounter++;
        // smtVec[i]->Print();
      }
      // std::cout <<"Passing muon number : " << passingMuonCounter << " : TrackLength : " << smtVec[i]->size() <<
      // std::endl;
      hist->Fill(smtVec[i]->size());
      if (smtVec[i]->size() >= 10) hittingAllLayerCounter++;

      passingMuonCounter++;
    }
  }

  std::cout << "Total number of passing muons : " << passingMuonCounter << std::endl;
  std::cout << "Total number of passing muon that is detected by all the layers : " << hittingAllLayerCounter
            << std::endl;

  std::cout << "Tracking efficiency  : " << ((1. * hittingAllLayerCounter) / (1. * passingMuonCounter) * 100.)
            << std::endl;
  /* TFile *outfile = new TFile("PassingMuons.root","RECREATE");
    outfile->cd();
    hist->Write();
    outfile->Close();
  */

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

  ismran::Database d("127.0.0.1", "ismran_db", "ismran", "ismran123");
  d.SetVerbose(true);
    d.Connect();

    d.Update(std::string("update ismran_files set passingmuons=") + std::to_string(passingMuonCounter) +
             std::string(" where fileName='") + justfilename + std::string("'"));

  return passingMuonCounter;
  // return 0;
}
