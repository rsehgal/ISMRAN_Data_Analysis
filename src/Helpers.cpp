/*
**	Filename : Helpers.cpp
**	2021-10-27
**	username : rsehgal
*/

#include "Helpers.h"
namespace ismran {

bool CompareTimestampScintillator(ScintillatorBar_F *i1, ScintillatorBar_F *i2)
{
  return (i1->GetTStampSmall() < i2->GetTStampSmall());
}

} // namespace ismran
