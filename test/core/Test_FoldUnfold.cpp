/*
**	Filename : Test_FoldUnfold.cpp
**	2022-02-24
**	username : rsehgal
*/
#include <iostream>
#include "Helpers.h"
int main(int argc, char *argv[])
{
  unsigned int qnear   = 1324;
  unsigned int qfar    = 2324;
  unsigned int qfolded = ismran::GetFoldedQNearQFar(qnear, qfar);
  std::cout << "Folded : " << qfolded << std::endl;
  unsigned int unfolded_qnear = ismran::GetUnFoldedQNear(qfolded);
  unsigned int unfolded_qfar  = ismran::GetUnFoldedQFar(qfolded);
  std::cout << "Actual Qnear : " << qnear << " : Unfolded Qnear : " << unfolded_qnear << std::endl;
  std::cout << "Actual Qfar : " << qfar << " : Unfolded Qfar : " << unfolded_qfar << std::endl;
  return 0;
}
