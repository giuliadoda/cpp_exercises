#ifndef Event_h
#define Event_h

struct Particle {
    int charge; // particle charge
    float px;
    float py;
    float pz;   // particle momentum
};

struct Event {
    int evNumber;   // event number identifier
    float x;
    float y; 
    float z;        // decay point coordinates
    int n;          // number of particles
    Particle** Ps;  // array of pointers to Particle structs
};

#endif