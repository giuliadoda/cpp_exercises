#include "Utilities.h"
#include <cmath>

double Utilities::energy(double &px, double &py, double &pz, const double mass) {
    double e = sqrt( pow(px, 2) + pow(py, 2) + pow(pz, 2) + pow(mass, 2) );
    return e;
}

double Utilities::iMass(double &ptx, double &pty, double &ptz, double en) {
    double r = pow(en, 2) - ( pow(ptx, 2) + pow(pty, 2) + pow(ptz, 2) );
    if (r>0) {
        double m = sqrt( r );
        return m;
        }
    else return -1;
}