/*
 * ScintillatorBar_V2.h
 *
 *  Created on: 08-Nov-2020
 *      Author: rsehgal
 */

#ifndef ISMRAN_ANALYSIS_V2_INC_PAIRFINDER_H_
#define ISMRAN_ANALYSIS_V2_INC_PAIRFINDER_H_

#include <string>
#include "TreeEntry.h"
#include <vector>

namespace ismran {
class PairFinder {
  std::string fDatafileName;
  std::vector<TreeEntry *> fVecOfTreeEntry;
  std::vector<TreeEntry *> fVecOfPairedTreeEntry;

public:
  PairFinder();
  PairFinder(std::string datafilename);
  void FindPair();
  void IdentifyNearFar(TreeEntry *near, TreeEntry *far);
  void LoadDataAndSort();
  void CheckPairs();
  void ValidatePairs();
  bool ValidatePair(TreeEntry *near, TreeEntry *far);
  std::vector<TreeEntry *> GetVectorOfPairedTreeEntries() const;
  virtual ~PairFinder();

  /*
   * Variable for Shots mechanism,
   * May be useful during batch job submission.
   */
  static unsigned int numOfShots;
  static unsigned int shotNo;
};
} // namespace ismran

#endif
