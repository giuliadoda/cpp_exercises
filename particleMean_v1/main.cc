#include <iostream>
#include <fstream>
#include <cmath>

#include "Event.h"

const Event* read (std::ifstream& file);
void dump (const Event& ev);
double mass (const Event& ev);
bool add (const Event& ev, double mMin, double mMax, double& sum, double& sqr);
void clear (const Event* ev);

int main (int argc, char* argv[]) {

    const char* name = argv[1];
    std::ifstream file (name);

    int aev = 0; // accepted events
    double sum = 0; // sum of invariant masses
    double sqr = 0; // sum of squares of invariant masses

    double mm;  // mean invariant mass
    double rms = 0; // rms invariant mass

    double mMin = 0.490; // selecting only K0 events
    double mMax = 0.505;

    // loop over events
    const Event* ev;
    while ( (ev = read(file) ) != nullptr ) {
        // dump(*ev);
        if (add(*ev, mMin, mMax, sum, sqr)) ++aev;
        clear(ev);
    }

    // computing mass mean and rms
    mm = sum*1./aev;
    double r = sqr*1./aev - pow( mm, 2 );
    rms = (r > 0 ? sqrt(r) : 0.0);

    std::cout << (mm+mMin) << "   " << rms << std::endl;

    return 0;

}

