/*
**	Filename : Test_GenerateCalibrationFile.cpp
**	2023-10-19
**	username : rsehgal
*/
#include <string>
#include <iostream>
#include <filesystem>
#include <regex>
#include "Helpers.h"
#include "CharacterizationFileReader.h"
#include <TApplication.h>
#include <algorithm>
namespace fs = std::filesystem;

int main()
{
  TApplication *fApp           = new TApplication("Tapp", NULL, NULL);
  TFile *fout                  = new TFile("calibration.root", "RECREATE");
  fs::path directoryPath       = "/home/rsehgal/PS5_S2AB1006";
  int correctionFactor         = 0;
  short counter                = 0;
  TCanvas *can                 = new TCanvas("Calibration", "Calibraion");
  TSpectrum *spectrum          = new TSpectrum(1);
  std::vector<float> energyVec = {477., 1000., 3700};
  std::vector<float> peakPosVec;
  std::vector<std::string> sourceVec = GetEnergyCalibrationFiles();
  std::string barName                = directoryPath.string();
  barName                            = barName.substr(barName.rfind('/') + 1);

  std::cout << "BarName : " << barName << std::endl;

  // return 0;

  {
    for (unsigned short i = 0; i < sourceVec.size(); i++) {
      // for (unsigned short i = 0; i < 1; i++) {

      std::regex b(sourceVec[i]);

      // Iterate through the directory entries
      // TFile *fw = new TFile("output.root","w");
      for (const auto &entry : fs::directory_iterator(directoryPath)) {
        // Convert the directory entry to a string
        std::string entryString = entry.path().string();

        if (regex_match(entryString, b)) {
          counter++;
          std::cout << "FOUND : " << entryString << std::endl;

          // TFile *fp = new TFile(entryString.c_str(),"r");
          CharacterizationFileReader *cf = new CharacterizationFileReader(entryString);
          // barName = cf->GetBarName();
          TH1F *qmeanHist = cf->GetComptonEdge();
          if (entryString.find("Cs137") != std::string::npos) qmeanHist->SetTitle("Cs137");
          if (entryString.find("Co60") != std::string::npos) qmeanHist->SetTitle("Co60");
          if (entryString.find("Na22") != std::string::npos) qmeanHist->SetTitle("Na22");
          if (entryString.find("AmBe") != std::string::npos) qmeanHist->SetTitle("AmBe");

          spectrum->Search(qmeanHist, 2);
          Double_t *xpeaks = spectrum->GetPositionX();
          peakPosVec.push_back(xpeaks[0]);
          // new TCanvas;
          qmeanHist->SetLineColor(counter);
          fout->cd();
          qmeanHist->Write();

          /*if(counter==1)
          qmeanHist->Draw();
          else
          qmeanHist->Draw("same");

          gPad->SetLogy();*/
        }
      }
    }
  }
  // can->BuildLegend();
  // fApp->Run();

  for (unsigned int i = 0; i < peakPosVec.size(); i++) {
    std::cout << peakPosVec[i] << " : ";
  }

  TGraph *grE = new TGraph(peakPosVec.size(), &peakPosVec[0], &energyVec[0]);
  grE->SetMarkerStyle(8);
  // std::string barName= "PS5";//""cf->GetBarName();
  TF1 *comptonFit = new TF1((barName + "_ECalib").c_str(), "pol1", 250, 2250);
  grE->Fit(comptonFit, "q");
  comptonFit->Write();
  // grE->Write();
  // fout->Close();
  std::cout << std::endl;
  // return 0;

  {
    std::string delTOffsetFile = GetDelTOffsetFile();

    std::regex b(delTOffsetFile);

    // Iterate through the directory entries
    // TFile *fw = new TFile("output.root","w");
    for (const auto &entry : fs::directory_iterator(directoryPath)) {
      // Convert the directory entry to a string
      std::string entryString = entry.path().string();

      if (regex_match(entryString, b)) {
        std::cout << "================== DELT OFFSET FILE ====================" << std::endl;
        std::cout << "FOUND : " << entryString << std::endl;
        CharacterizationFileReader *cf = new CharacterizationFileReader(entryString);
        std::cout << "BarName : " << cf->GetBarName() << std::endl;
        std::cout << "Source Pos : " << cf->GetActualPosition() << std::endl;
        std::cout << "Total Num of Events : " << cf->GetTotalNumOfEvents() << std::endl;

        TF1 *delTOffsetFormula = cf->GetDelTOffsetFormula();
        // delTOffsetFormula->Draw();
        // cf->GetOutputFile()->cd();
        fout->cd();
        delTOffsetFormula->Write();
        correctionFactor = delTOffsetFormula->GetParameter(1);
        delete cf;

        // TFile *fp = new TFile(entryString.c_str(),"r");
      }
    }
  }

  std::cout << "======================== STARTING PARAMETERIZATIOn ==========================" << std::endl;
  std::vector<float> posVec;
  std::vector<float> meanVec;
  {
    std::vector<std::string> sourceVec = GetPositionCalibrationFiles();

    for (unsigned short i = 0; i < sourceVec.size(); i++) {
      // for (unsigned short i = 4; i < 5; i++) {

      std::regex b(sourceVec[i]);

      // Iterate through the directory entries
      // TFile *fw = new TFile("output.root","w");
      for (const auto &entry : fs::directory_iterator(directoryPath)) {
        // Convert the directory entry to a string
        std::string entryString = entry.path().string();

        if (regex_match(entryString, b)) {
          std::cout << "===============================================" << std::endl;
          std::cout << "FOUND : " << entryString << std::endl;
          CharacterizationFileReader *cf = new CharacterizationFileReader(entryString, correctionFactor);
          std::cout << "Delt Offset factor : " << cf->GetDelTOffsetCorrection() << std::endl;
          // std::cout << "BarName : " << cf->GetBarName() << std::endl;
          // std::cout << "Source Pos : " << cf->GetActualPosition() << std::endl;
          // std::cout << "Total Num of Events : " << cf->GetTotalNumOfEvents() << std::endl;
          TF1 *delTOffsetFormula = cf->GetDelTOffsetFormula();
          std::cout << "Mean after offset correction : " << delTOffsetFormula->GetParameter(1) << std::endl;
          posVec.push_back(cf->GetActualPosition());
          meanVec.push_back(delTOffsetFormula->GetParameter(1));
          delete cf;

          // TFile *fp = new TFile(entryString.c_str(),"r");
        }
      }
    }
  }

  TGraph *gr = new TGraph(posVec.size(), &meanVec[0], &posVec[0]);
  gr->SetTitle((barName + "_z").c_str());
  gr->SetName((barName + "_z").c_str());
  gr->SetMarkerStyle(8);
  
  auto grmin = *(std::min_element(meanVec.begin(), meanVec.end()));
  auto grmax = *(std::max_element(meanVec.begin(), meanVec.end()));

  
  TF1 *zdelt = new TF1((barName + "_ZCalib").c_str(), "pol2", grmin,grmax);
  gr->Fit(zdelt, "r");
  // gr->Draw("ap");
  fout->cd();
  gr->Write();
  zdelt->Write();

  fout->Close();
  // fApp->Run();

  return 0;
}
