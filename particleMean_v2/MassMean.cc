#include "MassMean.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"

#include <cmath>

// float mass( const Event& ev );  --> cos'è?


// constructor
MassMean::MassMean( double min, double max ):
 // initializations
 mMin(min),
 mMax(max) {
  aev = 0;
  sum = 0;
  sqr = 0;
}


// destructor
MassMean::~MassMean() {
}


// add data from a new event
void MassMean::add( const Event& ev ) {

  // computing invariant mass
  double m;
  // double m = Utilities::iMass() - mMin;

  // check for mass being in range
  if (m < 0) return;
  if (m > (mMax - mMin) ) return;

  // update number of events and sums
  aev += aev;
  sum += sum + m;
  sqr += sqr + pow(m, 2);
  
}


// compute mean and rms
void MassMean::compute() {
  mm = sum/aev;
  rms = sqrt( sqr/aev - pow( mm, 2 ) );
}


// return number of selected events
int MassMean::nEvent() const {
  return aev;
}


// return mean and rms
double MassMean::mMean() const {
  double mf = mm + mMin;
  return mf;
}

double MassMean::mRMS() const {
  return rms;
}

