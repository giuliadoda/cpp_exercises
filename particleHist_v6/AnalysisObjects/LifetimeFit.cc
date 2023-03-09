#include "LifetimeFit.h"
#include "ParticleReco.h"
#include "ProperTime.h"
#include "AnalysisUtilities/QuadraticFitter.h"

#include <cmath>


LifetimeFit::LifetimeFit( const double min, const double max,
                          const double tmin, const double tmax,  
                          const double smin, const double smax, 
                          const double step ):
 mMin(min),
 mMax(max),
 tMin(tmin),
 tMax(tmax),
 sMin(smin),
 sMax(smax),
 sStep(step) {
  }

LifetimeFit::~LifetimeFit() {
  }

// update sum of masses and squares 
bool LifetimeFit::add() {

  static ParticleReco* pr = ParticleReco::instance();

  static ProperTime* pt = ProperTime::instance();

  // get decay time
  double t = pt->decayTime();

  // if decay time is in range add to the container
  if ( (t >= tMin) && (t <= tMax) ) dTimes.push_back(t);

  // computing invariant mass
  double m = pr->pMass() - mMin;

  // check for mass being in range
  if ( ( m < 0 ) || ( m > (mMax-mMin) ) ) return false;
  
  return true;
  
  }


// likelihood fit to lifetime
void LifetimeFit::compute() {

  // quadratic fit
  QuadraticFitter qFit;

  // time scan
  double ts;
  for ( ts = sMin; ts < sMax; ts += sStep) {
    
      double L = 0;
      // loop over times
      for (auto t : dTimes) 
        L += ( (t/ts) + log(ts) + log( exp(-tMin/ts) - exp(-tMax/ts) ) );
      // adding point to quadratic fit
      qFit.add(ts, L);
  }

  // compunting mean and rms
  meanLT = - qFit.b() / (2*qFit.c()); 
  rmsLT = pow(2*qFit.c(), -1/2);

  return;

  }


// return number of entries in times vector
int LifetimeFit::nEvent() const {
  return dTimes.size();
  }


// lifetime mean
double LifetimeFit::lifeTime() const {
  return meanLT;
} 

// lifetime error
double LifetimeFit::lifeTimeError() const {
  return rmsLT;
}