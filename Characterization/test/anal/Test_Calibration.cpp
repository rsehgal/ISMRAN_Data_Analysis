/*
**	Filename : Test_Calibration.cpp
**	2023-10-23
**	username : rsehgal
*/
#include<iostream>
#include "CharacterizationFileReader.h"
#include "TFile.h"
#include "TH1F.h"
int main(int argc, char *argv[]){

TFile *fr = new TFile("calibration.root","r");
TF1 *eCalib = (TF1*)fr->Get("PS5_S2AB1006_ECalib");
fr->Close();

TFile *fd = new TFile(argv[1],"r");



}
