#ifndef Utilities_h
#define Utilities_h

class Utilities {

    public:
        Utilities();
        ~Utilities();

        // function to compute energy from momentum components and invariant mass 
        static double energy(double &px, double &py, double &pz, const double mass);

        // function to compute invariant mass from momentum components and energy 
        static double iMass (double &ptx, double &pty, double &ptz, double en);

    };

#endif