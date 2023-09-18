/*
**	Filename : Test_Calib_DelT.cpp
**	2021-10-29
**	username : rsehgal
*/
#include <iostream>
#include "Calibration.h"
#include <TApplication.h>
#include <TCanvas.h>
#include <TH1F.h>
#include "Analyzer_F.h"
#include "ScintillatorBar_F.h"
#include "SingleMuonTrack.h"
#include "HardwareNomenclature.h"
int main(int argc, char *argv[])
{
  TApplication *fApp         = new TApplication("Test", NULL, NULL);
  ismran::Calibration *calib = ismran::Calibration::instance("completeCalib2.root");
  TCanvas *can               = new TCanvas("DelT", "DelT");
  can->Divide(2, 2);
  unsigned int barIndex = 6;
  std::string barName = ismran::vecOfPsBars[barIndex];
  TH1F *delT            = new TH1F(("DelT_"+barName).c_str(), ("DelT_"+barName).c_str(), 100, -25, 25);
  TH1F *delTCorr        = new TH1F(("DelTCorr_"+barName).c_str(), ("DelTCorr_"+barName).c_str(), 100, -25, 25);
  TH1F *qmean           = new TH1F(("Qmean_"+barName).c_str(), ("Qmean_"+barName).c_str(), 1000, 0, 32000);
  TH1F *qmeanCorr       = new TH1F(("QmeanCorr_"+barName).c_str(), ("QmeanCorr_"+barName).c_str(), 100, 0, 50);
  //ismran::Analyzer_F an(argv[1],10000000);
  ismran::Analyzer_F an(argv[1]);
  ismran::vecOfPeakPos = an.GetPeakPosVec();
  std::vector<ismran::ScintillatorBar_F*> vecOfScint = an.GetVectorOfScintillators();
  for (unsigned int i = 0; i < vecOfScint.size(); i++) {
    if (vecOfScint[i]->GetBarIndex() == barIndex) {
      delT->Fill(vecOfScint[i]->GetDelT() / 1000.);
      delTCorr->Fill(vecOfScint[i]->GetDelTCorrected() / 1000.);
      qmean->Fill(vecOfScint[i]->GetQMean());
      qmeanCorr->Fill(vecOfScint[i]->GetQMeanCorrected());
    }
  }

  TLegend leg;
  leg.AddEntry(delT,"Before DelT correction");
  leg.AddEntry(delTCorr,"After DelT correction");
  can->cd(1);
  delT->Draw();
  delTCorr->SetLineColor(2);
  delTCorr->Draw("same");
  leg.Draw("same");

  can->cd(2);
  qmean->Draw();
  qmeanCorr->SetLineColor(2);
  //  qmeanCorr->Draw("same");

  TH1F *delT_muon                               = new TH1F(("DelT_muon_"+barName).c_str(), ("DelT_muon_"+barName).c_str(), 100, -25, 25);
  TH1F *delTCorr_muon                           = new TH1F(("DelTCorr_muon_"+barName).c_str(), ("DelTCorr_muon_"+barName).c_str(), 100, -25, 25);

 /* std::vector<ismran::SingleMuonTrack *> smtVec = an.ReconstructMuonTrack();

  for (unsigned int i = 0; i < smtVec.size(); i++) {
    std::vector<ismran::ScintillatorBar_F *> scintVec = smtVec[i]->GetMuonTrack();
    for (unsigned int j = 0; j < smtVec[i]->size(); j++) {
      if (scintVec[j]->GetBarIndex() == barIndex) {
        delT_muon->Fill(scintVec[j]->GetDelT() / 1000.);
        delTCorr_muon->Fill(scintVec[j]->GetDelTCorrected() / 1000.);
      }
    }
  }
*/
  can->cd(3);
  delT_muon->Draw();
  delTCorr_muon->SetLineColor(2);
  delTCorr_muon->Draw("same");
  can->cd(4);
  qmeanCorr->Draw();
  fApp->Run();
  return 0;
}
