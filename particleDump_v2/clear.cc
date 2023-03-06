#include "Event.h"


// function that deletes Event struct and its content

void clear( const Event* ev ) {

    // loop over particles
    unsigned int i;
    for ( i=0; i<ev->n; ++i ) {
        delete ev->Ps[i]; // delete Particle structs 
                          // (Ps[i] is a pointer to Particle)
        }

    delete[] ev->Ps; // delete array of pointers to Particle

    delete ev; // delete event

    return;

    }