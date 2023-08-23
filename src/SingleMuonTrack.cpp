/*
**	Filename : SingleMuonTrack.cpp
**	2021-10-27
**	username : rsehgal
*/

#include "SingleMuonTrack.h"
#include "ScintillatorBar_F.h"
#include <iterator>
#include "PsBar.h"
//#include "Point3D.h"
#include "HardwareNomenclature.h"
//#include <TVector3.h>
#include "Plotter.h"
#include <algorithm>
//#include <TF1.h>
//#include "HelperFunctions.h"
#include "colors.h"

ClassImp(ismran::SingleMuonTrack)

    namespace ismran
{

  SingleMuonTrack::SingleMuonTrack() {}

  SingleMuonTrack::~SingleMuonTrack() {}

  // SingleMuonTrack::SingleMuonTrack(std::vector<std::shared_ptr<ScintillatorBar_F>> vecOfScintBars)
  SingleMuonTrack::SingleMuonTrack(std::vector<ScintillatorBar_F *> vecOfScintBars)
  {
    fVecOfScintillators = vecOfScintBars;
  }

  SingleMuonTrack::SingleMuonTrack(const SingleMuonTrack &smt)
  {
    for (unsigned int i = 0; i < smt.GetMuonTrack().size(); i++) {
      fVecOfScintillators.push_back(new ScintillatorBar_F(*(smt.GetMuonTrack()[i])));
      // fVecOfScintillators.push_back(std::shared_ptr<ScintillatorBar_F>(new
      // ScintillatorBar_F(*(smt.GetMuonTrack()[i]))));
    }
  }

  // std::vector<std::shared_ptr<ScintillatorBar_F>> SingleMuonTrack::GetMuonTrack() const { return fVecOfScintillators;
  // }
  std::vector<ScintillatorBar_F *> SingleMuonTrack::GetMuonTrack() const { return fVecOfScintillators; }

  // bool SingleMuonTrack::CompareBarIndexInScintillator(std::shared_ptr<ScintillatorBar_F> i1,
  // std::shared_ptr<ScintillatorBar_F> i2)
  bool SingleMuonTrack::CompareBarIndexInScintillator(ScintillatorBar_F * i1, ScintillatorBar_F * i2)
  {
    return (i1->GetBarIndex() > i2->GetBarIndex());
  }

  void SingleMuonTrack::Sort()
  {
    std::sort(fVecOfScintillators.begin(), fVecOfScintillators.end(), CompareBarIndexInScintillator);
  }

  void SingleMuonTrack::clear()
  {

    for (unsigned int i = 0; i < size(); i++) {
      delete fVecOfScintillators[i];
    }
    fVecOfScintillators.clear();
  }

  unsigned long int SingleMuonTrack::size() { return fVecOfScintillators.size(); }

  // void SingleMuonTrack::push_back(ScintillatorBar_F * scint) {
  // fVecOfScintillators.push_back(std::shared_ptr<ScintillatorBar_F>(scint)); }
  void SingleMuonTrack::push_back(ScintillatorBar_F * scint) { fVecOfScintillators.push_back(scint); }

  unsigned int SingleMuonTrack::NumOfHitsInLayer(unsigned int layerNum)
  {
    unsigned int noOfHits = 0;
    for (unsigned int i = 0; i < size(); i++) {
      if (fVecOfScintillators[i]->GetLayerIndex() == layerNum) {
        noOfHits++;
      }
    }
    return noOfHits;
  }

  bool SingleMuonTrack::SingleHitInLayer(unsigned int layerIndex)
  {
    std::vector<unsigned int> vecOfNumOfHits;
    for (unsigned int i = 0; i < numOfLayers; i++) {
      vecOfNumOfHits.push_back(NumOfHitsInLayer(i));
    }

    /*
     * If number of hits in each layer is 0 or 1
     * then return true else false
     */
    bool singleHit = true;
    /*for(unsigned int i = 0 ; i < numOfLayers ; i++){
      singleHit &= (vecOfNumOfHits[i]==1);
    }*/

    singleHit &= (vecOfNumOfHits[layerIndex] == 1);
    return singleHit;
  }

  bool SingleMuonTrack::SingleHitInEachLayer()
  {
    std::vector<unsigned int> vecOfNumOfHits;
    for (unsigned int i = 0; i < numOfLayers; i++) {
      vecOfNumOfHits.push_back(NumOfHitsInLayer(i));
    }

    /*
     * If number of hits in each layer is 0 or 1
     * then return true else false
     */
    bool singleHit = true;
    for (unsigned int i = 0; i < numOfLayers; i++) {
      singleHit &= (vecOfNumOfHits[i] <= 1);
    }
    return singleHit;
  }

  void SingleMuonTrack::Print()
  {
    std::cout << RED << "******************** Size : " << size() << "***************************************" << RESET <<  std::endl;
    // std::vector<std::shared_ptr<ScintillatorBar_F>> scintBarVec = GetMuonTrack();
    std::vector<ScintillatorBar_F *> scintBarVec = GetMuonTrack();
    for (unsigned int i = 0; i < scintBarVec.size(); i++) {
      scintBarVec[i]->Print();
    }
    std::cout << std::endl;
  }

  bool SingleMuonTrack::IsPassingMuon(){
	unsigned int numOfHist_layer0 = NumOfHitsInLayer(0);
	unsigned int numOfHist_layer9 = NumOfHitsInLayer(9);
	return ((numOfHist_layer0 > 0) && (numOfHist_layer9 > 0));
  }
} // namespace ismran
