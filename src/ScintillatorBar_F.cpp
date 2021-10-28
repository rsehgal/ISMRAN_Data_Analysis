#include "ScintillatorBar_F.h"
#include "Calibration.h"
#include "HardwareNomenclature.h"
#include "Mapping.h"
//#include "Point3D.h"
//#include "Analyzer.h"
#include "colors.h"
#define cm 10
ClassImp(ismran::ScintillatorBar_F);
namespace ismran {

ScintillatorBar_F::ScintillatorBar_F()
{
  // std::cout << "SCINTILLATORBAR : Default Constructor called" << std::endl;
  fBarIndex = 1234;
  fQlong    = 0;
  fTstamp   = 0;
  fTime     = 0;
  fDelt     = 0;
}

ScintillatorBar_F::ScintillatorBar_F(unsigned int bIndex) : fBarIndex(bIndex), fQlong(0), fTstamp(0), fTime(0), fDelt(0)
{
}

ScintillatorBar_F::ScintillatorBar_F(ushort barIndex, UInt_t qlong, ULong64_t tstamp, UInt_t wtime, Int_t deltstamp)
    : fBarIndex(barIndex / 2), fQlong(qlong), fTstamp(tstamp), fTime(wtime), fDelt(deltstamp)
{
}

ScintillatorBar_F::ScintillatorBar_F(const ScintillatorBar_F &sbar)
{
  fBarIndex = sbar.fBarIndex;
  fQlong    = sbar.fQlong;
  fTstamp   = sbar.fTstamp;
  fTime     = sbar.fTime;
  fDelt     = sbar.fDelt;
}

void ScintillatorBar_F::Print()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "BarIndex : " << fBarIndex << " : LayerIndex : " << GetLayerIndex()
            << " : BAR Name : " << vecOfBarsNamess[fBarIndex] << " :  Energy :  " << GetQMean() // Corrected()
            << " : DelT : " << GetDelT() << std::endl;
}

ScintillatorBar_F::~ScintillatorBar_F() {}

ushort ScintillatorBar_F::GetBarIndex() const
{
  return fBarIndex;
}
ushort ScintillatorBar_F::GetLayerIndex()
{
  //return (fBarIndex / numOfBarsInEachLayer);
  return (fBarIndex % numOfLayers);
}

ushort ScintillatorBar_F::GetBarIndexInLayer()
{
  //return (fBarIndex % numOfBarsInEachLayer);
  return (fBarIndex / numOfLayers);
}
UInt_t ScintillatorBar_F::GetQNear()
{
  return (fQlong >> 16);
}

UInt_t ScintillatorBar_F::GetQFar()
{
  unsigned short int maxU_16bits = USHRT_MAX;
  UInt_t maskingVal              = maxU_16bits;
  return (fQlong & maskingVal);
}

Double_t ScintillatorBar_F::GetQMean()
{
  return sqrt(GetQNear() * GetQFar());
}
/*Double_t ScintillatorBar_F::GetQMeanCorrected()
{
  //  return GetQMean();
  return (20. / (1. * GetPeakPos(vecOfBarsNamess[fBarIndex]))) * GetQMean();
}*/
Long_t ScintillatorBar_F::GetDelT() const
{
  return fDelt;
}

Long_t ScintillatorBar_F::GetTStampNear() const
{
  return fTstamp;
}

Long_t ScintillatorBar_F::GetTStampFar()
{
  return (fTstamp - fDelt);
}

Long_t ScintillatorBar_F::GetTStampSmall()
{
  if (fDelt < 0)
    return GetTStampNear();
  else
    return GetTStampFar();
}

Long_t ScintillatorBar_F::GetDelTCorrected()
{
  return (fDelt - GetOffsetCorrection());
}

double ScintillatorBar_F::GetOffsetCorrection()
{
  std::string barName             = vecOfPsBars[fBarIndex];
  unsigned int sequentialBarIndex = GetIndexFromBarName(barName);
  return Calibration::instance()->GetCalibrationDataOf(sequentialBarIndex)->GetDelTOffset() * 1000;
  // return 0;
}

TF1 *ScintillatorBar_F::GetZParameterization()
{
  std::string barName             = vecOfPsBars[fBarIndex];
  unsigned int sequentialBarIndex = GetIndexFromBarName(barName);
  return Calibration::instance()->GetCalibrationDataOf(sequentialBarIndex)->GetZParamFormula();
}


Double_t ScintillatorBar_F::GetQMeanCorrected()
{
  {
    Double_t ener = 0.;
std::string barName             = vecOfPsBars[fBarIndex];
  unsigned int sequentialBarIndex = GetIndexFromBarName(barName);

#ifndef SINGLE_POINT_CALIBRATION
    TF1 *enercalibFormula = Calibration::instance()->GetCalibrationDataOf(sequentialBarIndex)->GetEnergyCalibFormula();
    ener                  = (enercalibFormula->Eval(GetQMean()));
    // std::cout << "Predicted Energy : " << ener << std::endl;
#else
    // Using single point calibration, and using equation of straight line to get y correspoinding to a x
    ener = (20. / (1. * GetPeakPos(vecOfBarsNamess[sequentialBarIndex]))) * GetQMean();
#endif
    return ener;
  }
}
} // namespace ismran
