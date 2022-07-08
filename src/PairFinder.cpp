#include "PairFinder.h"
#include "includes.hh"
#include "TreeEntry.h"
#include "Helpers.h"
#include "colors.h"
namespace ismran {

unsigned int PairFinder::numOfShots = 0;
unsigned int PairFinder::shotNo     = 0;

PairFinder::PairFinder() {}

PairFinder::PairFinder(std::string datafilename) : fDatafileName(datafilename)
{
  if (0) {
    LoadDataAndSort();
    CheckPairs();
    ValidatePairs();
  } else {
    FindPair();
  }
}

PairFinder::~PairFinder() {}
void PairFinder::FindPair()
{
  TFile *fp = new TFile(fDatafileName.c_str(), "r");
  UShort_t brch;    //! board #  and channel number ( its packed in as follows )	//! board*16 + chno.
  UInt_t qlong;     //! integrated charge in long gate 88 nsec
  ULong64_t tstamp; //! time stamp in pico sec.
  UInt_t time;      //! real computer time in sec

  TTree *tr = (TTree *)fp->Get("ftree");
  tr->SetBranchAddress("fBrCh", &brch);
  tr->SetBranchAddress("fQlong", &qlong);
  tr->SetBranchAddress("fTstamp", &tstamp);
  tr->SetBranchAddress("fTime", &time);

  std::string transFileName = ("New_Transformed_" + ismran::GetBaseName(fDatafileName));
  std::cout << RED << "Transformed file Name : " << transFileName << RESET << std::endl;
  TFile *fpT  = new TFile(transFileName.c_str(), "RECREATE");
  TTree *tree = new TTree("ftree", "ftree");
  UShort_t FBrCh;
  ULong64_t FTstamp;
  UInt_t FTime;
  UInt_t FQlong;
  Int_t FDelt;

  tree->Branch("fBrCh", &FBrCh, "FBrCh/s");
  tree->Branch("fTstamp", &FTstamp, "FTstamp/l");
  tree->Branch("fTime", &FTime, "FTime/i");
  tree->Branch("fQlong", &FQlong, "FQlong/i");
  tree->Branch("fDelt", &FDelt, "FDelt/I");

  TTimeStamp *times = new TTimeStamp();
  //Long64_t nEntries = 1000000; // tr->GetEntries();
  Long64_t nEntries =  tr->GetEntries();
  std::cout << "Total number of Entries : " << nEntries << std::endl;

  Long64_t nb = 0;

  if (numOfShots == 0) {
    numOfShots = 1;
    shotNo     = 1;
  }
  unsigned long int numOfEventsInOneShot = nEntries / numOfShots;
  // if(numOfShots==1)
  // numOfEventsInOneShot = 10000;
  unsigned int start = (shotNo - 1) * numOfEventsInOneShot;
  // tr->GetEntry(start);
  TreeEntry *near = new TreeEntry;
  TreeEntry *far  = new TreeEntry;
  bool pairFound  = true;

  unsigned int rightPairs = 0, wrongPairs = 0;
  // for (Long64_t iev = 0; iev < nEntries; iev++) {
  // for (Long64_t iev = (shotNo - 1) * numOfEventsInOneShot; iev < shotNo * numOfEventsInOneShot; iev++) {
  // for (Long64_t iev = start ; iev < shotNo * numOfEventsInOneShot; iev++) {
  for (Long64_t iev = start; iev < shotNo * numOfEventsInOneShot;) {

    // for (Long64_t iev = (start + 1); iev < 10000000; iev++) {
    //    std::cout << RED << "Pair Found : " << pairFound << RESET << std::endl;
    if (pairFound) {
      nb += tr->GetEntry(iev);
      near->Set(brch, qlong, tstamp, time);
      iev++;

      nb += tr->GetEntry(iev);
      far->Set(brch, qlong, tstamp, time);
      iev++;
    } else {
      near->Set(far->brch, far->qlong, far->tstamp, far->time);
      nb += tr->GetEntry(iev);
      far->Set(brch, qlong, tstamp, time);
      iev++;
    }

    //    nb += tr->GetEntry(iev);
    if (0) std::cout << brch << " , " << qlong << " , " << tstamp << " , " << time << std::endl;

    // fVecOfTreeEntry.push_back(new TreeEntry(brch, qlong, tstamp, time));

    if (iev % 1000000 == 0) {
      times->Set(time, kTRUE, offset, kFALSE);
      std::cout << " Processing event : " << iev << "\t" << times->GetTimeSpec() << std::endl;
    }

    pairFound = ValidatePair(near, far);
    if (pairFound)
      rightPairs++;
    else
      wrongPairs++;
    // std::cout << BLUE << pairFound << std::endl;
    if (pairFound) {
      FBrCh   = near->brch;
      FTstamp = near->tstamp;
      FTime   = near->time;
      FQlong  = ismran::GetFoldedQNearQFar(near->qlong, far->qlong);
      FDelt   = near->tstamp - far->tstamp;
      tree->Fill();
      // std::cout << RED << FBrCh << ", " << FTstamp << ", " << FTime << ", " << FQlong << ", " << FDelt << RESET
      //<< std::endl;
    }

  } //! event loop

  fp->Close();
  fpT->cd();
  tree->Write();
  fpT->Close();

  std::cout << "Size of TreeEntry vector : " << fVecOfTreeEntry.size() << std::endl;
  std::cout << BLUE << "RightPairs : " << rightPairs << " : WrongPairs : " << wrongPairs << RESET << std::endl;
  return;
}
void PairFinder::LoadDataAndSort()
{
  TFile *fp = new TFile(fDatafileName.c_str(), "r");
  UShort_t brch;    //! board #  and channel number ( its packed in as follows )	//! board*16 + chno.
  UInt_t qlong;     //! integrated charge in long gate 88 nsec
  ULong64_t tstamp; //! time stamp in pico sec.
  UInt_t time;      //! real computer time in sec

  TTree *tr = (TTree *)fp->Get("ftree");
  tr->SetBranchAddress("fBrCh", &brch);
  tr->SetBranchAddress("fQlong", &qlong);
  tr->SetBranchAddress("fTstamp", &tstamp);
  tr->SetBranchAddress("fTime", &time);

  TTimeStamp *times = new TTimeStamp();
  Long64_t nEntries = tr->GetEntries();
  std::cout << "Total number of Entries : " << nEntries << std::endl;

  Long64_t nb = 0;

  if (numOfShots == 0) {
    numOfShots = 1;
    shotNo     = 1;
  }
  unsigned long int numOfEventsInOneShot = nEntries / numOfShots;
  // if(numOfShots==1)
  // numOfEventsInOneShot = 10000;

  // for (Long64_t iev = 0; iev < nEntries; iev++) {
  for (Long64_t iev = (shotNo - 1) * numOfEventsInOneShot; iev < shotNo * numOfEventsInOneShot; iev++) {
    nb += tr->GetEntry(iev);
    if (0) std::cout << brch << " , " << qlong << " , " << tstamp << " , " << time << std::endl;

    fVecOfTreeEntry.push_back(new TreeEntry(brch, qlong, tstamp, time));

    if (iev % 1000000 == 0) {
      times->Set(time, kTRUE, offset, kFALSE);
      std::cout << " Processing event : " << iev << "\t" << times->GetTimeSpec() << std::endl;
    }

  } //! event loop

  fp->Close();

  std::cout << "Size of TreeEntry vector : " << fVecOfTreeEntry.size() << std::endl;
  // std::sort(fVecOfTreeEntry.begin(), fVecOfTreeEntry.end(), CompareTimestamp);
  // std::cout << "TreeEntryVector Sorting done..... " << std::endl;
  return;
}

void PairFinder::CheckPairs()
{
  std::cout << "=============== Checking Pairs ==================" << std::endl;

  for (unsigned int i = 0; i < fVecOfTreeEntry.size() - 1;) {

    if (abs(fVecOfTreeEntry[i]->brch - fVecOfTreeEntry[i + 1]->brch) == 1) {
      fVecOfPairedTreeEntry.push_back(fVecOfTreeEntry[i]);
      fVecOfPairedTreeEntry.push_back(fVecOfTreeEntry[i + 1]);
      i = i + 2;
    } else {
      i++;
    }
  }
  std::cout << "Length of Paired Entries Vector : " << fVecOfPairedTreeEntry.size() << std::endl;
  std::cout << "Percentage of Unpaired Entries : "
            << (1. * (fVecOfTreeEntry.size() - fVecOfPairedTreeEntry.size()) / fVecOfTreeEntry.size()) * 100 << " %"
            << std::endl;
  fVecOfTreeEntry.clear();
}
bool PairFinder::ValidatePair(TreeEntry *near, TreeEntry *far)
{

  //IdentifyNearFar(near, far);
  unsigned int smallChannelNum = (near->brch < far->brch) ? near->brch : far->brch;
  int diff                     = near->tstamp - far->tstamp;
  if ((abs(near->brch - far->brch) != 1) || (abs(diff) > 25000) || (smallChannelNum % 2) ||
      smallChannelNum == far->brch) {
    std::cout << GREEN << "Invalid Pair Found...." << RESET << std::endl;
    return false;
  } else {
    return true;
  }
}

void PairFinder::IdentifyNearFar(TreeEntry *near, TreeEntry *far)
{
  if (near->brch > far->brch) {
    std::cout << "================================================" << std::endl;
    std::cout << RED;
    near->Print();
    far->Print();
    std::cout << RESET;
    TreeEntry *temp = new TreeEntry;
    temp->Set(near->brch, near->qlong, near->tstamp, near->time);
    near->Set(far->brch, far->qlong, far->tstamp, far->time);
    far->Set(temp->brch, temp->qlong, temp->tstamp, temp->time);
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << BLUE;
    near->Print();
    far->Print();
    std::cout << RESET;
    delete temp;
  }
}
void PairFinder::ValidatePairs()
{
  std::string transFileName = ("Transformed_" + ismran::GetBaseName(fDatafileName));
  std::cout << RED << "Transformed file Name : " << transFileName << RESET << std::endl;
  TFile *fp   = new TFile(transFileName.c_str(), "RECREATE");
  TTree *tree = new TTree("ftree", "ftree");
  UShort_t fBrCh;
  ULong64_t fTstamp;
  UInt_t fTime;
  UInt_t fQlong;
  Int_t fDelt;

  tree->Branch("fBrCh", &fBrCh, "fBrCh/s");
  tree->Branch("fTstamp", &fTstamp, "fTstamp/l");
  tree->Branch("fTime", &fTime, "fTime/i");
  tree->Branch("fQlong", &fQlong, "fQlong/i");
  tree->Branch("fDelt", &fDelt, "fDelt/I");

  std::cout << "=============== Validating Pairs ==================" << std::endl;
  std::cout << "Size of vector to be validated : " << fVecOfPairedTreeEntry.size() << std::endl;
  unsigned int counter         = 0;
  unsigned int counterDelT     = 0;
  unsigned int counterOddSmall = 0;
  unsigned int notAPairCounter = 0;
  std::vector<TreeEntry *> vecOfValidatedPairedTreeEntry;
  for (unsigned long int i = 0; i < fVecOfPairedTreeEntry.size();) {

    unsigned int smallChannelNum = (fVecOfPairedTreeEntry[i]->brch < fVecOfPairedTreeEntry[i + 1]->brch)
                                       ? fVecOfPairedTreeEntry[i]->brch
                                       : fVecOfPairedTreeEntry[i + 1]->brch;
    if (smallChannelNum % 2) {
      counterOddSmall++;
      // std::cout << "I : " << fVecOfPairedTreeEntry[i]->brch << " : I+1 : " << fVecOfPairedTreeEntry[i+1]->brch <<
      // std::endl;
    }

    int diff = fVecOfPairedTreeEntry[i]->tstamp - fVecOfPairedTreeEntry[i + 1]->tstamp;
    if (abs(diff) > 25000) {
      // std::cout << "Abs DelT : " << abs(diff) << std::endl;
      counterDelT++;
    }

    if (abs(fVecOfPairedTreeEntry[i]->brch - fVecOfPairedTreeEntry[i + 1]->brch) != 1) {
      notAPairCounter++;
    }

    if ((abs(fVecOfPairedTreeEntry[i]->brch - fVecOfPairedTreeEntry[i + 1]->brch) != 1) || (abs(diff) > 25000) ||
        (smallChannelNum % 2)) {

      counter++;
      // fVecOfPairedTreeEntry[i]->Print();
      // fVecOfPairedTreeEntry[i+1]->Print();
      /*std::cout << "Invalid pair found : " << fVecOfPairedTreeEntry[i]->brch <<" : "
            << fVecOfPairedTreeEntry[i+1]->brch
            << " : DelT : " << (fVecOfPairedTreeEntry[i]->tstamp-fVecOfPairedTreeEntry[i+1]->tstamp) << std::endl;*/
    } else {
      // Lets push it to new vector which later replace the old one and get itself cleared
      vecOfValidatedPairedTreeEntry.push_back(fVecOfPairedTreeEntry[i]);
      vecOfValidatedPairedTreeEntry.push_back(fVecOfPairedTreeEntry[i + 1]);
      fBrCh   = fVecOfPairedTreeEntry[i]->brch;
      fTstamp = fVecOfPairedTreeEntry[i]->tstamp;
      fTime   = fVecOfPairedTreeEntry[i]->time;
      fQlong  = ismran::GetFoldedQNearQFar(fVecOfPairedTreeEntry[i]->qlong, fVecOfPairedTreeEntry[i + 1]->qlong);
      fDelt   = fVecOfPairedTreeEntry[i]->tstamp - fVecOfPairedTreeEntry[i + 1]->tstamp;
      tree->Fill();
    }

    i += 2;
  }

  fp->cd();
  tree->Write();
  fp->Close();
  fVecOfPairedTreeEntry.clear();
  for (unsigned long int i = 0; i < vecOfValidatedPairedTreeEntry.size(); i++) {
    fVecOfPairedTreeEntry.push_back(vecOfValidatedPairedTreeEntry[i]);
  }
  vecOfValidatedPairedTreeEntry.clear();

  std::cout << "=======================================================" << std::endl;
  std::cout << "@@@@@@@@@@@@@ Overall Validation Summary @@@@@@@@@@@@@@" << std::endl;
  std::cout << "Invalid ChannelNum counter : " << counterOddSmall << std::endl;
  std::cout << "Invalid DelT counter : " << counterDelT << std::endl;
  std::cout << "Not A Pair counter : " << notAPairCounter << std::endl;
  std::cout << "Globally there are " << counter << " invalid pairs" << std::endl;
  // sleep(10);
}

std::vector<TreeEntry *> PairFinder::GetVectorOfPairedTreeEntries() const
{
  return fVecOfPairedTreeEntry;
}

} // namespace ismran
