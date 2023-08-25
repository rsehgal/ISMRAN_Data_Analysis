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

  ULong64_t startTime = 0;
  ULong64_t endTime   = 0;

  unsigned int layerIndex = 9;
  bool startFlag          = false;
  TH1F *histMuonRate      = new TH1F("Muon Rate Estimation", "", 100, 0, 100);
  TH1F *histBarNum = new TH1F("BarNumHist","BarNumHist",90,0,90);
  unsigned int counterPassingMuon=0;
  unsigned int counterUpgoingMuon=0;
  for (unsigned int i = 0; i < smtVec.size(); i++) {
      std::vector<ismran::ScintillatorBar_F *> scintVec = smtVec[i]->GetMuonTrack();
    if (smtVec[i]->SingleHitInLayer(layerIndex)) {

	    if(smtVec[i]->IsPassingMuon()){
		    counterPassingMuon++;
		    if(smtVec[i]->IsUpgoingMuon() && scintVec[0]->GetLayerIndex()==0 && scintVec[scintVec.size()-1]->GetLayerIndex()==9){
			//std::cout <<"Upgoing muon found............." << std::endl;
			counterUpgoingMuon++;
		
		    }
	    }
	/*
      std::vector<ismran::ScintillatorBar_F *> scintVec = smtVec[i]->GetMuonTrack();
      for (unsigned int j = 0; j < scintVec.size(); j++) {
        if (scintVec[j]->GetLayerIndex() == layerIndex) {

	  std::string tempBarName = ismran::vecOfPsBars[scintVec[j]->GetBarIndex()];
	  //std::cout << tempBarName.substr(2,2) << std::endl;	  
	  histBarNum->Fill(std::stoi(tempBarName.substr(2,2)));

          if (!startFlag) {
            startFlag = true;
            startTime = scintVec[j]->GetTStampNear();
          } else {
            endTime       = scintVec[j]->GetTStampNear();
            Long64_t diff = endTime - startTime;
#ifdef VERBOSE
            std::cout << "Diff : " << diff << std::endl;
#endif
            startTime = endTime;
            if (diff > 0.) histMuonRate->Fill(diff / 1e+9);
          }
        }
      }
      */
    }
  }

  std::cout << "Total Number of Passing muons : " << counterPassingMuon << std::endl;
  std::cout << "Total Number of upgoing muons : " << counterUpgoingMuon << std::endl;
  std::cout << "% of upgoing muons : " << ((1.*counterUpgoingMuon)/(1.*counterPassingMuon)*100.) << std::endl;


  //  histMuonRate->Draw();
  //  TF1 *formula = new TF1("Formula", "expo", 0.2, 50.);
  TF1 *f2 = new TF1("f2", "([1]*exp(-x/[0])) + [2] ", 0.01, 250.01);
  f2->SetParName(0, "#tau");
  f2->SetParName(1, "N_{0}");
  // f2->SetParName(3,"#tau5");
  f2->SetParName(2, "C");
  f2->SetParameter(0, 50);
  f2->SetParameter(1, 10);
  f2->SetParameter(2, 10);
  // f2->SetParameter(3, 10);
  f2->SetLineStyle(2);
  f2->SetLineColor(2);

  histMuonRate->Fit("f2", "R");
  // histMuonRate->Fit(formula, "qn");

  histMuonRate->GetYaxis()->SetRangeUser(0, 10000);
  histMuonRate->Draw("p");
  histMuonRate->SetMarkerStyle(8);
  histMuonRate->SetMarkerSize(1.);
  f2->SetLineWidth(4);
  f2->Draw("same");
  // formula->SetLineWidth(4);
  // formula->Draw("same");

  TLegend *legendRate = new TLegend(0.2, 0.2, .8, .8);
  legendRate->AddEntry(histMuonRate, "Data", "p");
  legendRate->AddEntry(f2, "Fit", "l");
  legendRate->Draw("same");

  new TCanvas("BarNumHist","BarNumHist");
  histBarNum->Draw();
  fApp->Run();
  return 0;
}
