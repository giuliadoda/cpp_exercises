#include <cmath>
#include "Event.h"
#include "MassMean.h"
#include "Utilities.h"
#include "Constants.h"

double mass(const Event& ev) {

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

    // variables for energy sums, for K0 and Lambda0
    double eK0 = 0;
    double eL0 = 0;

    int k = ev.nParticles();

    // loop over particles
    for ( j = 0; j < k; ++j)
    {
        // pointer to j-particle
        const Event::Particle* particle = ev.particle(j);

        px = particle->px;
        py = particle->py;
        pz = particle->pz;

        // update momentum sums --> total momentum of final state
        spx += px;
        spy += py;
        spz += pz;

        // update energy sums, for K0 and Lambda0 hypotheses 
        eK0 += Utilities::energy(px, py, pz, Constants::massPion);

        // update positive/negative track counters
        // update energy sums
        if (particle->charge > 0) {
            ++ptc;
            eL0 += Utilities::energy(px, py, pz, Constants::massProton);
            }
        else if (particle->charge < 0) {
            ++ntc;
            eL0 += Utilities::energy(px, py, pz, Constants::massPion);
            }
    
    }

    // check for exactly one positive and one negative track
    // otherwise return negative (unphysical) invariant mass

    if ( (ptc == 1) && (ntc == 1) ) {

        // invariant mass of the decaying particle 
        double mfK = Utilities::iMass(spx, spy, spz, eK0);
        double mfL = Utilities::iMass(spx, spy, spz, eL0);

        // differences with known values
        double dK;
        double dL;

        // check if iMass returns physical value
        if ( (mfK != -1) && (mfL != -1)) {
            dK = mfK - Constants::massK0;
            dL = mfL - Constants::massLambda0;
            }
        else return -1;

        // returning invariant mass of the particle
        if ( fabs(dK) < fabs(dL) ) {
          return mfK;
          } 
        else return mfL;

        }
    else return -1; 

}