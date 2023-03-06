#include "Event.h"


Event::Event( int n, float x, float y, float z ):   
 evNumber (n),
 x(x),
 y(y),
 z(z) {
  np = 0;
  // allocate a buffer for particle pointers 
  Ps = new Particle*[maxP]; // array of pointers to Particle struct
  }

Event::~Event() {
  // delete all the particle pointers
  unsigned int i;
  for (i=0; i<maxP; ++i) delete Ps[i];
  // delete the pointers array
  delete[] Ps;
  }

// add particles to event 
// --> called in read(file) function --> loop over particles
void Event::pAdd( int charge, double px, double py, double pz ) {

  // check for the number of particles
  // if maximum reached do nothing and return
  if (np > maxP) return;

  // create the new particle and fill with data
  // store the new particle pointer in the array and increase counter
  Ps[np] = new Particle;

  Ps[np]->charge = charge;
  Ps[np]->px = px;
  Ps[np]->py = py;
  Ps[np]->pz = pz;

  ++np;

  return;

  }

// get event id.
int Event::eventNumber() const {
  return evNumber;
  }

// get decay point coordinates
float Event::X() const {
  return x;
  }

float Event::Y() const {
  return y;
  }

float Event::Z() const {
  return z;
  }

// get number of particles
int Event::nParticles() const {
  return np;
  }

// get particle: returning pointer to i-particle (or nullptr)
// note i>=maxP and not i>maxP because this function is called in a loop where
// the argument passed begins with i = 0 so we have to go until (maxP-1)
const Event::Particle* Event::particle( unsigned int i ) const {
  if (i>=maxP) return nullptr;
  else return Ps[i];
  }