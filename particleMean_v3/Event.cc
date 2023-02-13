#include "Event.h"

using namespace std;

// constructor
Event::Event( int n, float x, float y, float z ):
 // initializations
 evNumber (n),
 x(x),
 y(y),
 z(z) {
  Ps.reserve(10);
}

// destructor
Event::~Event() {
  Ps.clear();
}

// add particles to event 
// --> called in read(file) function --> loop over particles
void Event::add( int charge, double px, double py, double pz ) {

  // check for the number of particles
  // if maximum reached do nothing and return
  if (Ps.size() > 10) return;

  // create the new particle and fill with data
  // store the new particle pointer in the vector
  Particle p;

  p.charge = charge;
  p.px = px;
  p.py = py;
  p.pz = pz;

  Ps.push_back(p);

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
  return Ps.size();
}

// get particle: returning struct to i-particle (or nullptr)
// note i>=maxP and not i>maxP because this function is called in a loop where
// the argument passed begins with i = 0 so we have to go until (maxP-1)
const Event::Particle* Event::particle( unsigned int i ) const {
  if (i >= 10) return nullptr;
  else return &Ps[i];
}