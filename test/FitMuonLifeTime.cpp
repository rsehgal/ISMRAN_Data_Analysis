#include <TH1F.h>
#include <TF1.h>
#include <iostream>
#include <TFile.h>
int main(int argc, char *argv[]){

  TFile *fp = new TFile(argv[1],"r");
  TH1F *hist = (TH1F*)fp->Get("MuonLifeTime");
  hist->Rebin(2);
  hist->Draw("ap");
  TF1 *fitFunc = new TF1("fitFunc", "([1]*exp(-x/[0])) + [2] ",1.8,15);
  fitFunc->SetParameters(2.2,10,10);
  fitFunc->SetParNames("#tau","N","C");
  hist->Fit(fitFunc,"R");
  return 0;
}
