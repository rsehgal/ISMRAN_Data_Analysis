/*
**	Filename : CharacterizationFileReader.h
**	2023-10-13
**	username : rsehgal
*/
#ifndef CharacterizationFileReader_h
#define CharacterizationFileReader_h

#include "includes.h"
#include <string>
#include <climits>

#ifdef EXPERIMENTAL_FILESYSTEM
#include <experimental/filesystem>
namespace FS = std::experimental::filesystem;
#else
#include <filesystem>
namespace FS = std::filesystem;
#endif

#include "Event.h"

class CharacterizationFileReader {
private:
  TFile *fp;
  TFile *fOut;
  TTree *fTree;
  int fDelTOffset;

  std::string fFileName;
  Event *fEvent;

  TF1 *fDeltOffsetFormula;
  TF1 *fPosCalibFormula;
  TF1 *fEnerCalibFormula;

public:
  CharacterizationFileReader();
  ~CharacterizationFileReader();
  CharacterizationFileReader(std::string filename,bool dataFile=false);
  CharacterizationFileReader(std::string filename,int offsetCorrFactor);
  void ConnectTree(std::string treeName = "ftree");
  void ResetWith(std::string filename);
  /*Required Getters*/
  TTree *GetTree() const;

  int GetActualPosition();
  std::string GetBarName();
  unsigned int GetTotalNumOfEvents();

  TF1 *GetDelTOffsetFormula();
  TF1 *GetPositionCalibrationFormula();
  TF1 *GetEnergyCalibrationFormula();

  TH1F* GetComptonEdge();

  TFile *GetOutputFile() const { return fOut; }

  void SetDelTOffsetCorrection(int corrFactor);
  int GetDelTOffsetCorrection()const;
};

#endif
