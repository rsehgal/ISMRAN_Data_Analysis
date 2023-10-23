#include "CharacterizationFileReader.h"
#include <numeric>
#include <bits/stdc++.h>

CharacterizationFileReader::CharacterizationFileReader() {}

CharacterizationFileReader::~CharacterizationFileReader()
{
  // fOut->Close();
}

CharacterizationFileReader::CharacterizationFileReader(std::string filename,bool dataFile)
{
  fFileName = filename;
  // fOut      = new TFile((GetBarName() + ".root").c_str(), "RECREATE");
  fp     = new TFile(fFileName.c_str(), "r");
  fEvent = new Event();
  ConnectTree();
  fDelTOffset = 0.;
}
CharacterizationFileReader::CharacterizationFileReader(std::string filename, int offsetCorrFactor)
{
  fFileName = filename;
  // fOut      = new TFile((GetBarName() + ".root").c_str(), "RECREATE");
  fp          = new TFile(fFileName.c_str(), "r");
  fEvent      = new Event();
  fDelTOffset = offsetCorrFactor;
  ConnectTree();
}

void CharacterizationFileReader::ResetWith(std::string filename)
{
  fFileName = filename;
  fp        = new TFile(fFileName.c_str(), "r");
  ConnectTree();
}

void CharacterizationFileReader::ConnectTree(std::string treeName)
{
  fTree = (TTree *)fp->Get("ftree");
  fTree->SetBranchAddress("fBrCh", &fEvent->sBrch);
  fTree->SetBranchAddress("fQlong", &fEvent->sQlong);
  fTree->SetBranchAddress("fTstamp", &fEvent->sTstamp);
  fTree->SetBranchAddress("fTime", &fEvent->sTime);
  fTree->SetBranchAddress("fDelt", &fEvent->sDelt);
}

TTree *CharacterizationFileReader::GetTree() const
{
  return fTree;
}

int CharacterizationFileReader::GetActualPosition()
{
  unsigned int locationOfDot            = fFileName.find(".");
  unsigned int locationOfLastUnderscore = fFileName.find_last_of("_");
  unsigned int charsToPick              = locationOfDot - locationOfLastUnderscore - 1;
  std::string locationString            = fFileName.substr(locationOfLastUnderscore + 1, charsToPick);
  return std::stoi(locationString);
}

std::string CharacterizationFileReader::GetBarName()
{
  std::string justFileName = fFileName.substr(fFileName.find_last_of("/") + 1);
  // std::cout << "JUST FILE NAME : " << justFileName << std::endl;
  unsigned int locationOfPS      = justFileName.find("PS");
  std::string source             = justFileName.substr(0, locationOfPS - 1);
  unsigned int locationOfCouples = justFileName.find("Couples");
  std::string barName            = "";
  if (source == "Cs137") barName = justFileName.substr(locationOfPS, locationOfCouples - 7);
  if (source == "Na22") barName = justFileName.substr(locationOfPS, locationOfCouples - 6);
  return barName;
}

TF1 *CharacterizationFileReader::GetDelTOffsetFormula()
{
  TH1F *hist           = new TH1F("DelTOffset", "DelTOffset", 100, -30000, 30000);
  std::string deltCorr = GetBarName() + "_ZOffset";
  TF1 *gaussianFit     = new TF1(deltCorr.c_str(), "gaus", -30000, 30000);
  gaussianFit->SetParameter(1, hist->GetMean());
  gaussianFit->SetParameter(2, hist->GetStdDev());

  for (unsigned int i = 0; i < GetTotalNumOfEvents(); i++) {
    fTree->GetEntry(i);
    hist->Fill(fEvent->GetDelT() - fDelTOffset);
  }

  hist->Fit(gaussianFit, "R");
  return gaussianFit;
}

void CharacterizationFileReader::SetDelTOffsetCorrection(int corrFactor)
{
  fDelTOffset = corrFactor;
}

int CharacterizationFileReader::GetDelTOffsetCorrection() const
{
  return fDelTOffset;
}

TF1 *CharacterizationFileReader::GetPositionCalibrationFormula()
{
  TF1 *formula = new TF1;

  return formula;
}

TH1F *CharacterizationFileReader::GetComptonEdge()
{
  std::string histname = "";
  if (fFileName.find("Cs137") != std::string::npos) histname = "Cs137";
  if (fFileName.find("Co60") != std::string::npos) histname = "Co60";
  if (fFileName.find("Na22") != std::string::npos) histname = "Na22";
  if (fFileName.find("AmBe") != std::string::npos) histname = "AmBe";

  histname += "_QMean";
  TH1F *hist;
  if (histname == "AmBe_QMean") hist = new TH1F(histname.c_str(), histname.c_str(), 300, 1500, 3000);
  if (histname == "Na22_QMean") hist = new TH1F(histname.c_str(), histname.c_str(), 80, 400, 700);
  if (histname == "Co60_QMean") hist = new TH1F(histname.c_str(), histname.c_str(), 80, 300, 700);
  if (histname == "Cs137_QMean") hist = new TH1F(histname.c_str(), histname.c_str(), 100, 0, 500);

  // else
  // hist = new TH1F(histname.c_str(), histname.c_str(), 1000, 0, 5000);

  for (unsigned int i = 0; i < GetTotalNumOfEvents(); i++) {
    fTree->GetEntry(i);
    hist->Fill(fEvent->GetQMean());
  }

  return hist;
}

TF1 *CharacterizationFileReader::GetEnergyCalibrationFormula()
{
  TF1 *formula = new TF1;

  return formula;
}

unsigned int CharacterizationFileReader::GetTotalNumOfEvents()
{
  return fTree->GetEntries();
}
