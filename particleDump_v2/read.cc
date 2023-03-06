#include <fstream>

#include "Event.h"


// function that reads an event returning a pointer to that event 
// (or nullptr at file's end)

const Event* read( std::ifstream& file ) {

    // event pointer and identifier
    Event* ev;
    int i;

    // read input file and on success create dynamically event
    if ( file >> i ) ev = new Event;
    else return nullptr;            // on failure the function returns nullptr

    // filling Event struct with event id 
    ev->evNumber = i;

    // filling Event struct with decay point coordinates
    file >> ev->x 
         >> ev->y 
         >> ev->z;

    // number of particles producted in decay
    int m;
    file >> m;
    ev->n = m;

    // allocate array of pointers to Particle structs
    // array's dimension is equal to number of particles producted
    ev->Ps = new Particle*[m];

    // loop over particles
    unsigned int j;
    for ( j=0; j<m; ++j ) {

        // create dynamically poiter to Particle struct
        Particle* p = new Particle;

        file >> p->charge
             >> p->px
             >> p->py
             >> p->pz;

        // filling array of pointers
        ev->Ps[j] = p;

        }

    return ev; // returns the pointer to the event

    }