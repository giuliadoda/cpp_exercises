// namespace: to do

#ifndef Utilities_h
#define Utilities_h

class Utilities {

    public:
    
    // create Utilities
    Utilities();

    // deleted copy constructor and assignment operator to prevent unadvertent copy
    Utilities (const Utilities& x) = delete;
    Utilities& operator=(const Utilities& x) = delete;

    ~Utilities();


    // function to compute energy from momentum components and invariant mass
    static double energy(double &px, double &py, double &pz, const double mass);

    // function to compute invariant mass from momentum components and energy
    static double iMass (double &ptx, double &pty, double &ptz, double en);

};

#endif