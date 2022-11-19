#include "Event.h"

// constructor
Event::Event( int n, float x, float y, float z ):
 // initializations
 evNumber (n) {
  maxP = 10; // max number of particles
  np = 0;
  // allocate a buffer for particle pointers 
  Ps = new Particle*[maxP]; // array of pointers to Particle struct
}


// destructor
Event::~Event() {
  // delete all the particle pointers
  int i;
  for (i=0; i<maxP; ++i) delete Ps[i];
  // delete the pointers array
  delete[] Ps;
}

// add particles to event --> called in read(file) function --> loop over particles
void Event::add( int charge, double px, double py, double pz ) {

  // check for the number of particles
  // if maximum reached do nothing and return
  if (np > maxP) return;

  // create the new particle and fill with data
  // store the new particle pointer in the array and increase counter
  int i;
  for ( i = 0; i < np; ++i) {
    Ps[i] = new Particle;
    Ps[i]->charge = charge;
    Ps[i]->px = px;
    Ps[i]->py = py;
    Ps[i]->pz = pz;
  }

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


// get particle
const Event::Particle* Event::particle( unsigned int i ) const {
  // restituisce il puntatore alla particella i esima --> se non esiste deve restituire puntatore nullo
  if (i>maxP) return nullptr;
  else return Ps[i];
}

