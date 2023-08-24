/*
**	Filename : TestFileName.cpp
**	2022-03-07
**	username : rsehgal
*/
#include "Helpers_Dqm.h"
#include <iostream>
int main(int argc, char *argv[]) {

  std::cout << "Just file Name : " << ismran::GetFileNameWithoutExtension("Hello_Raman_Sehgal.root") << std::endl;
}
