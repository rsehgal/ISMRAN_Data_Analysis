#include "ScintillatorBar_V2.h"
#include "Calibration.h"
#include "HardwareNomenclature.h"
//#include "Point3D.h"
//#include "Analyzer.h"
#include "colors.h"
#define cm 10
//ClassImp(ismran::ScintillatorBar);
namespace ismran {

ScintillatorBar::ScintillatorBar()
{
  // std::cout << "SCINTILLATORBAR : Default Constructor called" << std::endl;
  fBarIndex        = 1234;
  fQlongNear       = 0;
  fQlongMean       = 0;
  fTSmallTimeStamp = 0;
  fDelTstamp       = 0;
}

ScintillatorBar::ScintillatorBar(unsigned int bIndex)
    : fBarIndex(bIndex), fQlongNear(0), fQlongMean(0), fTSmallTimeStamp(0), fDelTstamp(0)
{
}

ScintillatorBar::ScintillatorBar(ushort barIndex, ushort qlongNear, ushort qlongMean, ULong64_t tstampSmall,
                                 Long_t delTStamp)
    : fBarIndex(barIndex), fQlongNear(qlongNear), fQlongMean(qlongMean), fTSmallTimeStamp(tstampSmall),
      fDelTstamp(delTStamp)
{
}

ScintillatorBar::ScintillatorBar(const ScintillatorBar &sbar)
{
  fBarIndex        = sbar.fBarIndex;
  fQlongNear       = sbar.fQlongNear;
  fQlongMean       = sbar.fQlongMean;
  fTSmallTimeStamp = sbar.fTSmallTimeStamp;
  fDelTstamp       = sbar.fDelTstamp;
}

void ScintillatorBar::Print()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "BarIndex : " << fBarIndex << " : LayerIndex : " << GetLayerIndex()
            << " : BAR Name : " << vecOfBarsNamess[fBarIndex] << " :  Energy :  " << GetQMeanCorrected()
            << " : DelT : " << GetDelT() << " : "; // std::endl;
}

ScintillatorBar::~ScintillatorBar() {}

ushort ScintillatorBar::GetBarIndex() const
{
  return fBarIndex;
}
ushort ScintillatorBar::GetLayerIndex()
{
  return (fBarIndex / numOfBarsInEachLayer);
}

ushort ScintillatorBar::GetBarIndexInLayer()
{
  return (fBarIndex % numOfBarsInEachLayer);
}

UInt_t ScintillatorBar::GetQLongNear() const
{
  return fQlongNear;
}
UInt_t ScintillatorBar::GetQLongFar()
{
  return (fQlongMean * fQlongMean) / fQlongNear;
}
Double_t ScintillatorBar::GetQLongMean() const
{
  return fQlongMean;
}
ULong64_t ScintillatorBar::GetTSmallTimestamp() const
{
  return fTSmallTimeStamp;
}

ULong64_t ScintillatorBar::GetTAverage()
{
  return (GetTNearCorr() / 2. + GetTFarCorr() / 2.);
}

ULong64_t ScintillatorBar::GetTNearCorr()
{
  return GetTNear() - GetOffsetCorrection() / 2.;
}

ULong64_t ScintillatorBar::GetTFarCorr()
{
  return GetTFar() + GetOffsetCorrection() / 2.;
}

ULong64_t ScintillatorBar::GetTNear()
{
  if (fDelTstamp < 0.)
    return fTSmallTimeStamp;
  else
    return (fDelTstamp + fTSmallTimeStamp);
}

ULong64_t ScintillatorBar::GetTFar()
{
  if (fDelTstamp > 0.)
    return fTSmallTimeStamp;
  else
    return (fTSmallTimeStamp - fDelTstamp);
}

Long_t ScintillatorBar::GetDelT() const
{
  return fDelTstamp;
}

double ScintillatorBar::GetOffsetCorrection()
{
  return Calibration::instance()->GetCalibrationDataOf(fBarIndex)->GetDelTOffset() * 1000;
}

Long_t ScintillatorBar::GetDelTCorrected()
{
  return (fDelTstamp - GetOffsetCorrection());
}
Double_t ScintillatorBar::GetQMeanCorrected()
{
  {
    Double_t ener = 0.;
#ifndef SINGLE_POINT_CALIBRATION
    TF1 *enercalibFormula = Calibration::instance()->GetCalibrationDataOf(fBarIndex)->fEnergyCalibration_F;
    ener                  = (enercalibFormula->Eval(fQlongMean));
    // std::cout << "Predicted Energy : " << ener << std::endl;
#else
    // Using single point calibration, and using equation of straight line to get y correspoinding to a x
    ener = (20. / (1. * GetPeakPos(vecOfBarsNamess[fBarIndex]))) * fQlongMean;
#endif
    return ener;
  }
}
} // namespace ismran
