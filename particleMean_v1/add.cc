#include "Event.h"

double mass(const Event& ev);

bool add (const Event& ev, double mMin, double mMax, double& sum,  // sum of invariant masses
                                                     double& sqr){ // sum of the squares

    // computing invariant mass of the decay particle
    double m = mass(ev) - mMin;

    if ( m > (mMax -mMin) ) return false;
    else if ( m < 0 ) return false;
    else {
        // std::cout << ev.evNumber << "    " << m << std::endl;
        sum += m;
        sqr += m*m;
        return true;
    } 

}