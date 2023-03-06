#ifndef Event_h
#define Event_h

struct Particle {
    int charge; // particle charge
    float px;   // momenta coordinates
    float py;
    float pz;   
    };

struct Event {
    int evNumber;   // event number identifier
    float x;        // decay point coordinates
    float y; 
    float z;        
    int n;          // number of particles
    Particle** Ps;  // array of pointers to Particle structs
    };

#endif