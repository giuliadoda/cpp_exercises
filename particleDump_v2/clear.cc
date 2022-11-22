#include "Event.h"

// function that delete Event struct and its content

void clear (const Event* ev) {

    int i;
    for (i=0; i<ev->n; ++i) {
        delete ev->Ps[i]; // delete Particle structs 
                          // (Ps[i] is a pointer to Particle)
    }

    delete[] ev->Ps; // delete array of pointers

    delete ev; // delete event

    return;

}