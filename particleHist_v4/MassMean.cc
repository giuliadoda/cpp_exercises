#include "MassMean.h"
#include "ParticleReco.h"

#include <cmath>


MassMean::MassMean( const double min, const double max ):
 mMin(min),
 mMax(max) {
  aev = 0;
  sum = 0;
  sqr = 0;
  }

MassMean::~MassMean() {
  }

// update sum of masses and squares 
bool MassMean::add() {

  static ParticleReco* pr = ParticleReco::instance();

  // computing invariant mass
  double m = pr->pMass() - mMin;

  // check for mass being in range
  if ( ( m < 0 ) || ( m > (mMax-mMin) ) ) return false;

  // update number of events and sums
  ++aev;
  sum += m;
  sqr += pow(m, 2);
  
  return true;
  
  }

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