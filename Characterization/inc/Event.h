/*
**	Filename : Event.h
**	2023-10-19
**	username : rsehgal
*/
#ifndef Event_h
#define Event_h

#include "includes.h"
#include <string>
#include <climits>

#ifdef EXPERIMENTAL_FILESYSTEM
#include <experimental/filesystem>
namespace FS=std::experimental::filesystem;
#else
#include <filesystem>
namespace FS=std::filesystem;
#endif


struct Event {
  UShort_t sBrch;    //! board #  and channel number ( its packed in as follows )     //! board*16 + chno.
  UInt_t sQlong;     //! integrated charge in long gate 88 nsec
  ULong64_t sTstamp; //! time stamp in pico sec.
  UInt_t sTime;      //! real computer time in sec
  int sDelt;

  Event(){}

  void Set(UShort_t brch, UInt_t qlong, ULong64_t tstamp, UInt_t tme, int delt)
  {
    sBrch            = brch;
    sQlong           = qlong;
    sTstamp          = tstamp;
    sTime            = tme;
    sDelt            = delt;
  }

  Event(UShort_t brch, UInt_t qlong, ULong64_t tstamp, UInt_t tme, int delt)
  {
    sBrch            = brch;
    sQlong           = qlong;
    sTstamp          = tstamp;
    sTime            = tme;
    sDelt            = delt;
  }
  int GetDelT() const { return sDelt; }

  UInt_t GetQNear() { return (sQlong >> 16); }

  UInt_t GetQFar()
  {
    unsigned short int maxU_16bits = USHRT_MAX;
    UInt_t maskingVal              = maxU_16bits;
    return (sQlong & maskingVal);
  }

  float GetQMean() { return sqrt(GetQNear() * GetQFar()); }

  ULong64_t GetTNear() const { return sTstamp; }

  ULong64_t GetTFar() { return (sTstamp - sDelt); }

  void Print()
  {
    std::cout << "Branch : " << sBrch << std::endl
              << "QNear : " << GetQNear() << std::endl
              << "QFar : " << GetQFar() << std::endl
              << "QLong : " << sQlong << std::endl
              << "TNear : " << GetTNear() << std::endl
              << "TFar : " << GetTFar() << std::endl
              << "DelT : " << GetDelT() << std::endl
              << std::endl;
  }

};

#endif
