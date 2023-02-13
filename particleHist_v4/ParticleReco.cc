#include "ParticleReco.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"
#include <iostream>
#include <cmath>

using namespace std;


// constructor
ParticleReco::ParticleReco() {
}


// destructor
ParticleReco::~ParticleReco() {
}


// recompute tag informations for new event
void ParticleReco::update( const Event& ev ) {

  // set default quantities
  type   = unknown;
  energy = -1.0;
  mass   = -1.0;

  // code to compute total energy and invariant mass for the two
  // mass hypotheses for the decay products
  ...

  // compare invariant masses with known values and set final values
  // ( type, energy and mass )
  ...

  return;

}


// return particle type
...() {
  // check for new event and return result
  ...
}


// return particle energy
...() {
  // check for new event and return result
  ...
}


// return particle mass
...() {
  // check for new event and return result
  ...
}

