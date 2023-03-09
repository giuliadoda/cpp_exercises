#include "ProperTime.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"
#include "ParticleReco.h"

#include <iostream>
#include <cmath>

using namespace std;


// constructor
ProperTime::ProperTime() {
  }


// destructor
ProperTime::~ProperTime() {
  }

// return particle type
ProperTime::ParticleType ProperTime::pType() {
  // check for new event and return result
  check();
  return type;
  }

// return particle energy
double ProperTime::pEnergy() {
  // check for new event and return result
  check();
  return totEnergy;
  }

// return particle mass
double ProperTime::pMass() {
  // check for new event and return result
  check();
  return invMass;
  }

// computing time
void ProperTime::update( const Event& ev ) {

  static ParticleReco* part = ParticleReco::instance();

  // computing distance
  double d = sqrt( pow(ev.X(),2) + pow(ev.Y(),2) + pow(ev.Z(),2 ) );

  // get energy and mass from particleReco
  double e = part->pEnergy();
  double m = part->pMass();

  // computing momentum
  double u = pow(e,2) - pow(m,2);
  double p = ( u > 0 ? sqrt(u) : -1 );

  // computing time
  time = d * m / (p * Constants::lightVelocity);
  
  return;

  }


// return decay time
double ProperTime::decayTime() {
  // check for new event and return result
  check();
  return time;
}