/*
 * ScintillatorBar_F.h
 *
 *  Created on: 08-Nov-2020
 *      Author: rsehgal
 */

#ifndef ISMRAN_ANALYSIS_INC_SCINTILLATORBAR_H_
#define ISMRAN_ANALYSIS_INC_SCINTILLATORBAR_H_

#include "includes.hh"

//#include "PsBar.h"
//#include "Point3D.h"
#include "Calibration.h"

#pragma once
#include <TROOT.h>
//#include "Point3D.h"
class TH1F;

namespace ismran {

class ScintillatorBar_F {

private:
  ushort fBarIndex;  // Index of Bar starting from 0
  UInt_t fQlong;     // Folded Charge first 16 bits near, next 16 bits farftr
  ULong64_t fTstamp; // DAQ timestamp
  UInt_t fTime;      // Wall clock time
  Int_t fDelt;       // Time diff between left and right PMT

  /*Only for H9 data*/
  UInt_t fQnear;
  UInt_t fQfar;

#ifdef DEB
  ushort fBrCh;
#endif


public:
  ScintillatorBar_F();
  ScintillatorBar_F(unsigned int bIndex);
  // Required copy constructor
  ScintillatorBar_F(const ScintillatorBar_F &sbar);
  ScintillatorBar_F(ushort barIndex, UInt_t qlong, ULong64_t tstamp, UInt_t wtime, Int_t deltstamp);
  ScintillatorBar_F(ushort barIndex, UInt_t qnear, UInt_t qfar, ULong64_t tstamp, UInt_t wtime, Int_t deltstamp);

  // Functions to get the Hit Position
  /*ismran::Point3D *EstimateHitPosition();
  ismran::Point3D *EstimateHitPosition_Param();
  ismran::Point3D *EstimateHitPosition_QParam();*/

  /*
   * Required Getters
   */

  // Bar related
  ushort GetBarIndex() const;
  ushort GetLayerIndex();
  ushort GetBarIndexInLayer();

  // Charge related
  UInt_t GetQNear();
  UInt_t GetQFar();
  Double_t GetQMean();
  // Function to get the corrected QMean
  Double_t GetQMeanCorrected();
  Double_t GetQMeanCorrected(unsigned int muonPeakPos);

  // Timing related function
  Long_t GetDelT() const;
  // Function to get the corrected delT
  Long_t GetDelTCorrected();
  // Function to get the delT offset
  double GetOffsetCorrection();
  Long_t GetTStampNear() const;
  Long_t GetTStampFar();
  Long_t GetTStampSmall();

  // Function to get the parameterization
  TF1 *GetZParameterization();

  // double GetLogQNearByQFar() { return log((1. * GetQLongFar()) / (1. * GetQLongNear())); }

  // Time related
  /*ULong64_t GetTSmallTimestamp() const;
  ULong64_t GetTNearCorr();
  ULong64_t GetTFarCorr();
  ULong64_t GetTNear();
  ULong64_t GetTFar();
  ULong64_t GetTAverage();
  Double_t GetQMeanCorrected();*/

  // Function to print the scintillator contents
  void Print();

  // Destructor
  virtual ~ScintillatorBar_F();

  ClassDef(ScintillatorBar_F, 1)
};
} // namespace ismran
#endif /* ISMRAN_ANALYSIS_INC_SCINTILLATORBAR_H_ */
