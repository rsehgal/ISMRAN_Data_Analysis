/*
 * Calibration.h
 *
 *  Created on: 21-Aug-2020
 *      Author: rsehgal
 */

#ifndef ISMRAN_ANALYSIS_INC_CALIBRATION_H_
#define ISMRAN_ANALYSIS_INC_CALIBRATION_H_

#include <string>
#include <vector>
#include <iostream>

#include <TF1.h>
#include <TGraphErrors.h>
//#include "HelperFunctions.h"
#include "PsBar.h"

namespace ismran {

struct CalibrationData {
  TF1 *fDelTCorr_F;
  TF1 *fParameterization_F;
  TF1 *fEnergyCalibration_F;

  CalibrationData() {}

  CalibrationData(TF1 *delTCorr_F, TF1 *parameterization_F, TF1 *energyCalib_F)
  {
    fDelTCorr_F          = delTCorr_F;
    fParameterization_F  = parameterization_F;
    fEnergyCalibration_F = energyCalib_F;
  }

  double GetDelTOffset() { return fDelTCorr_F->GetParameter(1); }

  TF1 *GetDelTOffsetFormula() const { return fDelTCorr_F; }

  TF1 *GetZParamFormula() const { return fParameterization_F; }

  TF1 *GetEnergyCalibFormula() const { return fEnergyCalibration_F; }
};

class Calibration {

  std::string fFileName;
  std::vector<CalibrationData *> fVecOfCalibrationData;
  static Calibration *s_instance;

public:
  Calibration();
  static Calibration *instance();
  static Calibration *instance(std::string filename);
  Calibration(std::string fileName);
  virtual ~Calibration();

  /*
   * Function to return the std::vector of Calibration data of all
   * the Scintillator Bars
   */
  std::vector<CalibrationData *> GetCalibrationDataVector() const { return fVecOfCalibrationData; }

  unsigned int GetNumberOfBars() const { return fVecOfCalibrationData.size(); }

  /*
   * Function to return Calibration data of specific Scintillator bar
   */
  CalibrationData *GetCalibrationDataOf(int barNo);
};

} // namespace ismran
#endif /* ISMRAN_ANALYSIS_INC_CALIBRATION_H_ */
