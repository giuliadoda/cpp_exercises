#include "LifetimeFit.h"
#include "ParticleReco.h"

#include <cmath>


LifetimeFit::LifetimeFit( const double min, const double max ):
 mMin(min),
 mMax(max) {
  aev = 0;
  }

LifetimeFit::~LifetimeFit() {
  }

// update sum of masses and squares 
bool LifetimeFit::add() {

  static ParticleReco* pr = ParticleReco::instance();

  // computing invariant mass
  double m = pr->pMass() - mMin;

  // check for mass being in range
  if ( ( m < 0 ) || ( m > (mMax-mMin) ) ) return false;

  // update number of events and sums
  ++aev;
  
  return true;
  
  }

// compute mean and rms
void LifetimeFit::compute() {
  }


// return number of selected events
int LifetimeFit::nEvent() const {
  return aev;
  }