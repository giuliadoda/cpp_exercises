#include "MassMean.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"

#include <iostream>
#include <cmath>

// function to compute invariant mass of the decaying particle
double mass( const Event& ev );  

// constructor
MassMean::MassMean( const double min, const double max ):
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

// update sum of masses and squares 
bool MassMean::add( const Event& ev ) {

  // computing invariant mass
  double m = mass(ev) - mMin;

  // check for mass being in range
  if ( ( m < 0 ) || ( m > (mMax-mMin) ) ) return false;

  // update number of events and sums
  ++aev;
  sum += m;
  sqr += pow(m, 2);
  
  return true;
  
}

// please note: nothing changes if I don't use precision update


// compute mean and rms
void MassMean::compute() {
  mm = sum*1./aev;
  double r = sqr*1./aev - pow( mm, 2 );
  rms = (r > 0 ? sqrt(r) : 0.0);
  return;
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

