/*
**	Filename : smart.cpp
**	2022-02-22
**	username : rsehgal
**
**	Demonstration of using std::shared_ptr to automatically clean memory
**	on object delete, which otherwise needs to be one manually
*/
#include <iostream>
#include <TH1F.h>
#include <vector>
#include "colors.h"
#include <TFile.h>
using namespace std;
int main()
{
  TFile *fp = new TFile("test.root", "RECREATE");
  fp->cd();
  /*TH1F h("h", "h", 100, 0., 10.);
  auto h_clone = static_cast<TH1F *>(h.Clone("h_clone"));
  std::shared_ptr<TH1F> clone_ptr(h_clone);
*/
  std::vector<TH1F *> vecOfHist_ord;
  for (unsigned int i = 0; i < 5; i++) {
    vecOfHist_ord.clear();
    std::cout << RED << "Cleared Ordinary Raw pointer vector......" << RESET << std::endl;
    vecOfHist_ord.push_back((new TH1F("TestHist0_ord", "TestHist0_ord", 100, 0, 100)));
    vecOfHist_ord.push_back((new TH1F("TestHist1_ord", "TestHist1_ord", 100, 0, 100)));
    vecOfHist_ord.push_back((new TH1F("TestHist2_ord", "TestHist2_ord", 100, 0, 100)));
    vecOfHist_ord.push_back((new TH1F("TestHist3_ord", "TestHist3_ord", 100, 0, 100)));

    // std::vector<std::shared_ptr<TH1F>> vecOfHist_copy;
    // vecOfHist_copy = vecOfHist;
   for (unsigned int j = 0; j < 4; j++) {
    vecOfHist_ord[j]->SetDirectory(0);
  }

  }


  for (unsigned int i = 0; i < 4; i++) {
    vecOfHist_ord[i]->Write();
  }

  std::cout << MAGENTA << "Going to create smart pointers..........." << RESET << std::endl;
  std::vector<std::shared_ptr<TH1F>> vecOfHist;
  for (unsigned int i = 0; i < 5; i++) {
    vecOfHist.clear();
    std::cout << BLUE << "Cleared Smart pointer vector......" << RESET << std::endl;
    vecOfHist.push_back(std::shared_ptr<TH1F>(new TH1F("TestHist0_smart", "TestHist0_smart", 100, 0, 100)));
    vecOfHist.push_back(std::shared_ptr<TH1F>(new TH1F("TestHist1_smart", "TestHist1_smart", 100, 0, 100)));
    vecOfHist.push_back(std::shared_ptr<TH1F>(new TH1F("TestHist2_smart", "TestHist2_smart", 100, 0, 100)));
    vecOfHist.push_back(std::shared_ptr<TH1F>(new TH1F("TestHist3_smart", "TestHist3_smart", 100, 0, 100)));

    // std::vector<std::shared_ptr<TH1F>> vecOfHist_copy;
    // vecOfHist_copy = vecOfHist;
  }
  for (unsigned int i = 0; i < vecOfHist.size(); i++) {
    vecOfHist[i]->SetDirectory(0);
  }
for (unsigned int i = 0; i < vecOfHist.size(); i++) {
    vecOfHist[i]->Write();
  }

  fp->Close();
  return 0;
}
