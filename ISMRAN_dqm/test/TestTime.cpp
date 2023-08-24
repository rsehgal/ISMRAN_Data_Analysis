#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Database.h"
int main() {
  std::time_t ct = std::time(0);
  char *cc = ctime(&ct);
  std::cout << cc << std::endl;

  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  std::cout << "--------------------------------------" << std::endl;
  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
  auto str = oss.str();
  std::cout << str << std::endl;
  
  std::string sourcePath = "/home/rsehgal/ISMRAN_dqm/sourceDir/" ;
  //std::string targetPath = "/home/rsehgal/ISMRAN_dqm/sourceDir/" ;
  std::ofstream outfile((sourcePath+str).c_str(),"w");
  outfile << str << std::endl;
  outfile.close();

  return 0;
}
