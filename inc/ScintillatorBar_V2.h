/*
 * ScintillatorBar.h
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

class ScintillatorBar {

private:
  //! board #  and channel number ( its packed in as follows ) //! board*16 + chno.
  ushort fBarIndex;
  //! integrated charge in long gate 88 nsec
  UInt_t fQlongNear;
  //! integrated charge in long gate 88 nsec
  Double_t fQlongMean;
  //! time stamp in pico sec.
  ULong64_t fTSmallTimeStamp;
  //! time stamp in pico sec.
  Long_t fDelTstamp;

public:
  ScintillatorBar();
  ScintillatorBar(unsigned int bIndex);
  //Required copy constructor
  ScintillatorBar(const ScintillatorBar &sbar);
  ScintillatorBar(ushort barIndex, ushort qlongNear, ushort qlongMean, ULong64_t tstampSmall, Long_t delTStamp);

  //Functions to get the Hit Position
  /*ismran::Point3D *EstimateHitPosition();
  ismran::Point3D *EstimateHitPosition_Param();
  ismran::Point3D *EstimateHitPosition_QParam();*/

  /*
   * Required Getters
   */

  //Bar related
  ushort GetBarIndex() const;
  ushort GetLayerIndex();
  ushort GetBarIndexInLayer();

  //Charge related
  UInt_t GetQLongNear() const;
  UInt_t GetQLongFar();
  double GetLogQNearByQFar() { return log((1. * GetQLongFar()) / (1. * GetQLongNear())); }
  Double_t GetQLongMean() const;

  //Time related
  ULong64_t GetTSmallTimestamp() const;
  ULong64_t GetTNearCorr();
  ULong64_t GetTFarCorr();
  ULong64_t GetTNear();
  ULong64_t GetTFar();
  double GetOffsetCorrection();
  ULong64_t GetTAverage();
  Long_t GetDelT() const;
  Long_t GetDelTCorrected();
  Double_t GetQMeanCorrected();

  //Function to print the scintillator contents
  void Print();

  //Destructor
  virtual ~ScintillatorBar();

//  ClassDef(ScintillatorBar, 1)
};
} // namespace ismran
#endif /* ISMRAN_ANALYSIS_INC_SCINTILLATORBAR_H_ */
