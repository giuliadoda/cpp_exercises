#include <iostream>

#include "Event.h"


// function to perform event dump on screen

void dump( const Event& ev ) {

    // print event number
    std::cout << ev.evNumber << " ";

    // print decay point coordinates
    std::cout << ev.x << " "
              << ev.y << " "
              << ev.z << " ";

    // print number of particles
    std::cout << ev.n << " ";

    // print Particle structs content
    unsigned int i;
    for ( i=0; i<ev.n; ++i ) std::cout << ev.Ps[i]->charge << " "
                                     << ev.Ps[i]->px << " "
                                     << ev.Ps[i]->py << " "
                                     << ev.Ps[i]->pz << " ";

    std::cout << std::endl;

    return;

    }