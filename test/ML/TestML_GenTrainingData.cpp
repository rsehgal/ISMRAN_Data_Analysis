/*
**	Filename : TestML_GenTrainingData.cpp
**	2023-09-11
**	username : rsehgal
*/

#include <TFile.h>
#include <TTree.h>
#include <vector>
#include <iostream>

std::vector<ULong64_t> muonEventVec;

void FillMuonEventVector()
{

  TFile *inputFile = new TFile("MLData_Track.root", "READ");
  TTree *inputTree = (TTree *)inputFile->Get("mltree");
  ULong64_t fEvNo;

  // Set branch addresses.
  inputTree->SetBranchAddress("fEvNo", &fEvNo);

  Long64_t nEntries = inputTree->GetEntries();
  for (Long64_t iEntry = 0; iEntry < nEntries; iEntry++) {
    // Read data from the original tree
    inputTree->GetEntry(iEntry);
    muonEventVec.push_back(fEvNo);
    // std::cout << muonEventVec[iEntry] << " : " << (int)fParticleId<< std::endl;
  }

  inputFile->Close();
}
void ModifyData()
{
  // Open the original ROOT file with the TTree
  TFile *inputFile = new TFile("MLData.root", "READ");
  TTree *inputTree = (TTree *)inputFile->Get("mltree");

  // Define variables to hold data from the original tree
  UShort_t fBarIndex;
  ULong64_t fEvNo;
  UInt_t fQNear;
  UInt_t fQFar;
  Double_t fQMean;
  Long64_t fDelT;
  unsigned short fParticleId;

  // Set branch addresses.
  inputTree->SetBranchAddress("fBarIndex", &fBarIndex);
  inputTree->SetBranchAddress("fEvNo", &fEvNo);
  inputTree->SetBranchAddress("fQNear", &fQNear);
  inputTree->SetBranchAddress("fQFar", &fQFar);
  inputTree->SetBranchAddress("fQMean", &fQMean);
  inputTree->SetBranchAddress("fDelT", &fDelT);
  inputTree->SetBranchAddress("fParticleId", &fParticleId);

  // Create a new ROOT file for writing the modified data
  TFile *outputFile = new TFile("MLData_training.root", "RECREATE");
  TTree *outputTree = new TTree("mltree", "Training Tree");

  // Create branches in the output tree with the modified data
  // ...
  UShort_t mBarIndex;
  ULong64_t mEvNo;
  UInt_t mQNear;
  UInt_t mQFar;
  Double_t mQMean;
  Long64_t mDelT;
  unsigned short mParticleId;

  // Set branch addresses.
  outputTree->Branch("fBarIndex", &mBarIndex);
  outputTree->Branch("fEvNo", &mEvNo);
  outputTree->Branch("fQNear", &mQNear);
  outputTree->Branch("fQFar", &mQFar);
  outputTree->Branch("fQMean", &mQMean);
  outputTree->Branch("fDelT", &mDelT);
  outputTree->Branch("fParticleId", &mParticleId);

  // Loop through entries in the original tree
  Long64_t nEntries  = inputTree->GetEntries();
  unsigned int count = 0;
  for (Long64_t iEntry = 0; iEntry < nEntries; iEntry++) {
    // Read data from the original tree
    inputTree->GetEntry(iEntry);

    mBarIndex   = fBarIndex;
    mEvNo       = fEvNo;
    mQNear      = fQNear;
    mQFar       = fQFar;
    mQMean      = fQMean;
    mDelT       = fDelT;
    mParticleId = fParticleId;

    // std::cout << "Particle Id : " << fParticleId << std::endl;
    if (std::find(muonEventVec.begin(), muonEventVec.end(), fEvNo) != muonEventVec.end()) {
      count++;
      mParticleId = 0;
    }
    // Modify the data as needed
    // ...

    // Fill the modified data into the output tree
    outputTree->Fill();
  }

  std::cout << "Value of Count : " << count << std::endl;

  // Write the output tree to the new ROOT file
  outputTree->Write();

  // Clean up
  outputFile->Close();
  inputFile->Close();
}

int main(int argc, char *argv[])
{
  FillMuonEventVector();
  /*for(unsigned int i = 0 ; i < muonEventVec.size() ; i++){
  std::cout << "Event no. : " << muonEventVec[i] << std::endl;
  }*/
  std::cout << "Size of MuonVec : " << muonEventVec.size() << std::endl;
  ModifyData();
}
