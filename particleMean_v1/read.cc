#include <fstream>

#include "Event.h"

// function that reads an event returning a pointer to that event

Event* read (std::ifstream& file) {

    // event pointer and identifier
    Event* ev;
    int i;

    // read input file and on success create event
    if (file >> i) ev = new Event;
    else return nullptr; // on failure the function returns nullptr

    ev->evNumber = i;

    file >> ev->x 
         >> ev->y 
         >> ev->z;

    int m;
    file >> m;
    ev->n = m;

    // allocate array of pointers to Particle structs
    ev->Ps = new Particle*[m];

    // loop over particles
    int j;
    for (j=0; j<m; ++j) {
        Particle* p = new Particle;
        file >> p->charge
             >> p->px
             >> p->py
             >> p->pz;
        ev->Ps[j] = p;
    }

    return ev; 

}