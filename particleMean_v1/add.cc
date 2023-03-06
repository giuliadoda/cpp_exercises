#include "Event.h"


double mass( const Event& ev );


// function to check if the invariant mass is in the range
// if true update mass sum and sum of squares

bool add( const Event& ev, double mMin, double mMax, double& sum, double& sqr ) { 

    // computing invariant mass of the decay particle
    // subtracting min to increase precision
    if (mass(ev) != -1) {

        double m = mass(ev) - mMin;

        // check for mass being in range
        if ( (m < 0) || m > (mMax - mMin) ) return false;
        else {
            sum += m;
            sqr += m*m;
            return true;
            } 
        }
    
    else return false;

    }