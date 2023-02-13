#include <fstream>
#include <iostream>
#include "Event.h"
#include "MassMean.h"

void dump (const Event& ev);
Event* read (std::ifstream& file);

int main( int argc, char* argv[] ) {

  // open input file
  const char* name = argv[1];
  std::ifstream file (name);

  // create MassMean objects (with mass range passed to constructor)
  const double mMinK = 0.495;
  const double mMaxK = 0.500;

  const double mMinL = 1.115;
  const double mMaxL = 1.116;

  MassMean K0(mMinK, mMaxK);
  MassMean L0(mMinL, mMaxL);

  // loop over events
  const Event* ev;
  while ( ( ev = read(file) ) != nullptr ) {

    // dump(*ev);
    K0.add(*ev);
    L0.add(*ev);

    delete ev;
  }

  // compute results
  K0.compute();
  L0.compute();

  // print number of selected events and results for both particles
  std::cout << K0.nEvent() << " " << K0.mMean() << " " << K0.mRMS() << std::endl;
  std::cout << L0.nEvent() << " " << L0.mMean() << " " << L0.mRMS() << std::endl;

  return 0;

}