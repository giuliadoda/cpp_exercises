#include <cmath>

#include "Event.h"


// compute energy from momentum x,y,z components and invariant mass
double energy (double &px, double &py, double &pz, const double mass){
  double e = sqrt( pow(px, 2) + (pow(py, 2) + pow(pz, 2) + pow(mass, 2)) );
  return e;
}

// compute invariant mass from momentum x,y,z components and energy
double iMass (double &ptx, double &pty, double &ptz, double en){
  double r = pow(en, 2) - ( pow(ptx, 2) + pow(pty, 2) + pow(ptz, 2) );
  double m = ( r > 0 ? sqrt(r) : -1);
  return m;
}


// known values
const double massPion    = 0.1395706;   // GeV/c^2
const double massProton  = 0.938272;    // GeV/c^2
const double massK0      = 0.497611;    // GeV/c^2
const double massLambda0 = 1.115683;    // GeV/c^2


// functions that returns invariant mass of the decay particle

double mass(const Event& ev) {

  // retrieve particles in the event 
  typedef const Particle* part_ptr;   // declare pointers to const-Particle structs
  const part_ptr* particle = ev.Ps;  

  // variables to loop over particles
  int j;
  double px, py, pz;

  // variables for momentum sums
  double spx = 0;
  double spy = 0;
  double spz = 0;

  // positive / negative track counters
  int ptc = 0;
  int ntc = 0;

  // variables for energy sums, for K0 and Lambda0 hypoteses
  double eK0 = 0;
  double eL0 = 0;

  // loop over particles 
  for (j=0; j<ev.n; ++j) {

    px = particle[j]->px;
    py = particle[j]->py;
    pz = particle[j]->pz;
    
    // update momentum sums --> total momentum of final state
    spx += px;
    spy += py;
    spz += pz;

    // update energy sums, for K0 and Lambda0 hypotheses 
    eK0 += energy(px, py, pz, massPion);

    // update positive/negative track counters 
    if (particle[j]->charge > 0) {
        ++ptc;
        eL0 += energy(px, py, pz, massProton);
        }

    else if (particle[j]->charge < 0) {
      ++ntc;
      eL0 += energy(px, py, pz, massPion);
      }

  }

  // invariant mass of the decaying particle, for K0 and Lambda0 hypoteses
  double mfK = iMass(spx, spy, spz, eK0);
  double mfL = iMass(spx, spy, spz, eL0);

  // differences with known values
  double dK = mfK - massK0;
  double dL = mfL - massLambda0;

  // check for exactly one positive and one negative track
  // otherwise return negative (unphysical) invariant mass
  if ( (ptc == 1) && (ntc == 1) ) {
    if ( fabs(dK) < fabs(dL) ) return mfK; 
    else return mfL;
  }
  else return -1; 
  
}

