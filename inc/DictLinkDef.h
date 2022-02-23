// See: https://root.cern.ch/selecting-dictionary-entries-linkdefh
//#ifdef __CINT__
#ifdef __CLING__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedef;

#pragma link C++ namespace ismran;
#pragma link C++ defined_in namespace ismran;

//#pragma link C++ class ismran::Point3D+;
//#pragma link C++ class std::vector<ismran::Point3D*>+;
#pragma link C++ class ismran::ScintillatorBar_F+;
#pragma link C++ class std::vector<std::shared_ptr<ismran::ScintillatorBar_F>>+;
//#pragma link C++ class std::vector<ismran::ScintillatorBar_F*>+;
#pragma link C++ class ismran::SingleMuonTrack+;
#pragma link C++ class ismran::MuonPeakAnalyzer+;
#endif
