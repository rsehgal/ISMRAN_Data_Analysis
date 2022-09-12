#include "ScintillatorBar_F.h"
#include "Calibration.h"
#include "HardwareNomenclature.h"
//#include "Mapping.h"
//#include "Point3D.h"
//#include "Analyzer.h"
#include "colors.h"
#define cm 10
#ifndef USHRT_MAX
#define USHRT_MAX 65535
#endif
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
  fQnear    = 0;
  fQfar     = 0;
#ifdef DEB
  fBrCh = 0;
#endif
}

ScintillatorBar_F::ScintillatorBar_F(unsigned int bIndex)
    : fBarIndex(bIndex), fQlong(0), fTstamp(0), fTime(0), fDelt(0), fQnear(0), fQfar(0)
{
}

ScintillatorBar_F::ScintillatorBar_F(ushort barIndex, UInt_t qlong, ULong64_t tstamp, UInt_t wtime, Int_t deltstamp)
    : fBarIndex(barIndex / 2), fQlong(qlong), fTstamp(tstamp), fTime(wtime), fDelt(deltstamp)
{
  unsigned short int maxU_16bits = USHRT_MAX;
  UInt_t maskingVal              = maxU_16bits;
  fQfar                          = (fQlong & maskingVal);
  fQnear                         = (fQlong >> 16);
#ifdef DEB
  fBrCh = barIndex;
#endif
}
ScintillatorBar_F::ScintillatorBar_F(ushort barIndex, UInt_t qnear, UInt_t qfar, ULong64_t tstamp, UInt_t wtime,
                                     Int_t deltstamp)
    : fBarIndex(barIndex / 2), fQnear(qnear), fQfar(qfar), fTstamp(tstamp), fTime(wtime), fDelt(deltstamp)
{
#ifdef DEB
  fBrCh = barIndex;
#endif
}

ScintillatorBar_F::ScintillatorBar_F(const ScintillatorBar_F &sbar)
{
  fBarIndex = sbar.fBarIndex;
  fQlong    = sbar.fQlong;
  fTstamp   = sbar.fTstamp;
  fTime     = sbar.fTime;
  fDelt     = sbar.fDelt;
  fQnear    = sbar.fQnear;
  fQfar     = sbar.fQfar;
}

void ScintillatorBar_F::Print()
{
  std::cout << "-----------------------------------------------" << std::endl;
#ifdef DEB
  std::cout << "fBrCh : " << fBrCh << " : ";
#endif
  std::cout << "BarIndex : " << fBarIndex << " : LayerIndex : " << GetLayerIndex()
            << " : BAR Name : " << vecOfPsBars[fBarIndex] << " :  Energy :  " << GetQMean()
            << ": Corrected Energy : " << GetQMeanCorrected() << " : DelT : " << GetDelT()
            << " : TNear : " << GetTStampNear() << " : TFar : " << GetTStampFar() << " : TSmall : " << GetTStampSmall()
            << std::endl;
}

ScintillatorBar_F::~ScintillatorBar_F() {}

ushort ScintillatorBar_F::GetBarIndex() const
{
  return fBarIndex;
}
ushort ScintillatorBar_F::GetLayerIndex()
{
  // return (fBarIndex / numOfBarsInEachLayer);
  // return (fBarIndex % numOfLayers);
  short layerIndex = -1;
#ifndef VERTICAL_ARRANGEMENT
  layerIndex = fBarIndex / numOfBarsInEachLayer;
#else
  layerIndex      = fBarIndex % numOfLayers;
#endif
  return layerIndex;
}

ushort ScintillatorBar_F::GetBarIndexInLayer()
{
  // return (fBarIndex % numOfBarsInEachLayer);
  // return (fBarIndex / numOfLayers);
  short barIndexInLayer = -1;
#ifndef VERTICAL_ARRANGEMENT
  barIndexInLayer = fBarIndex % numOfBarsInEachLayer;
#else
  barIndexInLayer = (fBarIndex - GetLayerIndex()) / numOfBarsInEachLayer;

#endif
  return barIndexInLayer;
}
UInt_t ScintillatorBar_F::GetQNear()
{
  return fQnear;
  // return (fQlong >> 16);
}

UInt_t ScintillatorBar_F::GetQFar()
{
  return fQfar;
  /*unsigned short int maxU_16bits = USHRT_MAX;
  UInt_t maskingVal              = maxU_16bits;
  return (fQlong & maskingVal);*/
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
  /*std::string barName             = vecOfPsBars[fBarIndex];
  //unsigned int sequentialBarIndex = GetIndexFromBarName(barName);
  unsigned int sequentialBarIndex = GetIndexFromBarName(sequentialBarNames,barName);
  std::cout << RED << "BARName : " << barName << std::endl;
  std::cout << RED << "Sequential Bar Index : " << sequentialBarIndex << RESET << std::endl;
  return Calibration::instance()->GetCalibrationDataOf(sequentialBarIndex)->GetDelTOffset() * 1000;
  */

  return Calibration::instance()->GetCalibrationDataOf(fBarIndex)->GetDelTOffset() * 1000;
  // return 0;
}

TF1 *ScintillatorBar_F::GetZParameterization()
{
  std::string barName             = vecOfPsBars[fBarIndex];
  unsigned int sequentialBarIndex = GetIndexFromBarName(barName);
  return Calibration::instance()->GetCalibrationDataOf(sequentialBarIndex)->GetZParamFormula();
}

Double_t ScintillatorBar_F::GetQMeanCorrected(unsigned int muonPeakPos)
{
  Double_t ener                   = 0.;
  std::string barName             = vecOfPsBars[fBarIndex];
  unsigned int sequentialBarIndex = GetIndexFromBarName(barName);

#ifndef SINGLE_POINT_CALIBRATION
  TF1 *enercalibFormula = Calibration::instance()->GetCalibrationDataOf(sequentialBarIndex)->GetEnergyCalibFormula();
  ener                  = (enercalibFormula->Eval(GetQMean()));
  // std::cout << "Predicted Energy : " << ener << std::endl;
#else
  // Using single point calibration, and using equation of straight line to get y correspoinding to a x
  ener = (20. / (1. * muonPeakPos)) * GetQMean();
#endif
  return ener;
}
/*Double_t ScintillatorBar_F::GetQMeanCorrected()
{
  {
    Double_t ener                   = 0.;
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
}*/

Double_t ScintillatorBar_F::GetQMeanCorrected()
{
  {
    Double_t ener       = 0.;
    std::string barName = vecOfPsBars[fBarIndex];
    //   unsigned int sequentialBarIndex = GetIndexFromBarName(barName);

#ifndef SINGLE_POINT_CALIBRATION
    TF1 *enercalibFormula = Calibration::instance()->GetCalibrationDataOf(sequentialBarIndex)->GetEnergyCalibFormula();
    ener                  = (enercalibFormula->Eval(GetQMean()));
    // std::cout << "Predicted Energy : " << ener << std::endl;
#else
    // Using single point calibration, and using equation of straight line to get y correspoinding to a x
    // ener = (20. / (1. * GetPeakPos(vecOfBarsNamess[sequentialBarIndex]))) * GetQMean();
    // std::cout << RED << "BarIndex : " << fBarIndex << " : Peak Pos : " << vecOfPeakPos[fBarIndex] << " : " <<
    // GetQMean() <<std::endl;
    if (vecOfPeakPos[fBarIndex] > 0)
      ener = (20. / (1. * vecOfPeakPos[fBarIndex])) * GetQMean();
    else
      ener = GetQMean();
#endif
    return ener;
  }
}
} // namespace ismran
