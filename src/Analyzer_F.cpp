/*
**	Filename : Analyzer_F.cpp
**	2021-10-06
**	username : rsehgal
*/
#include <iostream>
#include "Analyzer_F.h"
#include "ScintillatorBar_F.h"

namespace ismran {
Analyzer_F::Analyzer_F() {}
Analyzer_F::Analyzer_F(std::string datafilename)
{
  fDatafileName = datafilename;
  LoadData();
}
Analyzer_F::~Analyzer_F() {}

/*Function to load the data and in the vector of Scintillator_F*/
void Analyzer_F::LoadData()
{
  TFile *fp = new TFile(fDatafileName.c_str(), "r");

  UShort_t fBrCh;
  ULong64_t fTstamp;
  UInt_t fTime;
  UInt_t fQlong;
  Int_t fDelt;

  TTree *tr = (TTree *)fp->Get("ftree");

  tr->SetBranchAddress("fBrCh", &fBrCh);
  tr->SetBranchAddress("fQlong", &fQlong);
  tr->SetBranchAddress("fTstamp", &fTstamp);
  tr->SetBranchAddress("fTime", &fTime);
  tr->SetBranchAddress("fDelt", &fDelt);

  TTimeStamp *times = new TTimeStamp();
  Long64_t nEntries = tr->GetEntries();
  std::cout << "Total number of Entries : " << nEntries << std::endl;
  Long64_t nb = 0;
  for (Long64_t iev = 0; iev < nEntries; iev++) {
    // for (Long64_t iev = (shotNo - 1) * numOfEventsInOneShot; iev < shotNo * numOfEventsInOneShot; iev++) {
    nb += tr->GetEntry(iev);
    if (0) std::cout << fBrCh << " , " << fQlong << " , " << fTstamp << " , " << fTime << " , " << fDelt << std::endl;

    fVecOfScint_F.push_back(new ScintillatorBar_F(fBrCh, fQlong, fTstamp, fTime, fDelt));

    if (iev % 1000000 == 0) {
      //times->Set(time, kTRUE, offset, kFALSE);
      std::cout << " Processing event : " << iev << "\t" << times->GetTimeSpec() << std::endl;
    }

  } //! event loop

  fp->Close();
}

std::vector<ScintillatorBar_F *> Analyzer_F::GetVectorOfScintillators(){
return fVecOfScint_F;
}
} // namespace ismran
