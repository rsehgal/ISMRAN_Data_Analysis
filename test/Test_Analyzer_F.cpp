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
  //ismran::Analyzer_F an(argv[1],10000000);
  ismran::Analyzer_F an(argv[1],0);

  #ifdef USE_EXISTING_MUON_PEAK_FILE
  ismran::vecOfPeakPos = ismran::GetPeakPosVec_Direct(".", "MuonPeak.root");
#else
  ismran::vecOfPeakPos = an.GetPeakPosVec();
#endif

  std::vector<ismran::ScintillatorBar_F*> vecOfScint = an.GetVectorOfScintillators();
  std::cout <<"SIZE of SCINT VECTOR : " << vecOfScint.size() << std::endl;
  ismran::InitializeHistograms();
  for (unsigned int i = 0; i < vecOfScint.size(); i++) {
    if (i < 5) {

      std::cout << "--------------------------------------" << std::endl;
      if (vecOfScint[i]->GetBarIndex() < 96) vecOfScint[i]->Print();
    }
  }
  std::vector<TH1F*> vecOfQMeanHist = ismran::GetQMeanCorrectedPlots(vecOfScint);

  TFile *fp = new TFile("hists.root", "RECREATE");
  fp->cd();
  TCanvas *can = new TCanvas("AllBars", "AllBars");

  for (unsigned int i = 0; i < vecOfQMeanHist.size(); i++) {
    can->cd();
    if (i == 0)
      vecOfQMeanHist[i]->Draw();
    else
      vecOfQMeanHist[i]->Draw("same");
    fp->cd();
    vecOfQMeanHist[i]->Write();
  }

/*  TCanvas *canNew = new TCanvas("MuonCalibBars", "MuonCalibBars");
  canNew->SetLogy();
  canNew->cd();
  for (unsigned int i = 0; i < vecOfQMeanHist.size(); i++) {
    if (i == 90){
      vecOfQMeanHist[i]->SetLineColor(1);
	vecOfQMeanHist[i]->
}
    if (i == 91)
      vecOfQMeanHist[i]->SetLineColor(2);
    if (i == 92)
      vecOfQMeanHist[i]->SetLineColor(4);
    if (i == 93)
      vecOfQMeanHist[i]->SetLineColor(6);
    if (i == 94)
      vecOfQMeanHist[i]->SetLineColor(8);




    else
      vecOfQMeanHist[i]->Draw("same");
    fp->cd();
    vecOfQMeanHist[i]->Write();
  }
*/
  fp->cd();
  can->Write();

  fp->Close();
  return 0;
}
