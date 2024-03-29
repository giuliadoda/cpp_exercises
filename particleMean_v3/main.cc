#include "Event.h"
#include "MassMean.h"

#include <fstream>
#include <iostream>
#include <string>


using namespace std;

void dump( const Event& ev );
const Event* read( ifstream& file );

int main( int argc, char* argv[] ) {

  // open input file
  string name = argv[1];
  ifstream file (name);

  // create MassMean objects 
  const double mMinK = 0.495;
  const double mMaxK = 0.500;

  const double mMinL = 1.115;
  const double mMaxL = 1.116;

  MassMean K0(mMinK, mMaxK);
  MassMean L0(mMinL, mMaxL);

  // loop over events
  const Event* ev;
  while ( ( ev = read(file) ) != nullptr) {

    // dump(*ev);
    K0.add(*ev);
    L0.add(*ev);

    delete ev;
    }

  // compute results
  K0.compute();
  L0.compute();

  // print number of selected events and results for both particles
  cout << K0.nEvent() << " " << K0.mMean() << " " << K0.mRMS() << endl;
  cout << L0.nEvent() << " " << L0.mMean() << " " << L0.mRMS() << endl;

  return 0;

  }