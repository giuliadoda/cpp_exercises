#include <iostream>

#include "Event.h"

// function performs event dump on screen

void dump (const Event& ev){

    // write event number
    std::cout << ev.evNumber << " ";

    // write decay point coordinates
    std::cout << ev.x << " "
              << ev.y << " "
              << ev.z << " ";

    // write number of particles
    std::cout << ev.n << " ";

    // write Particle structs content (loop over particles)
    int i;
    for (i=0; i<ev.n; ++i) std::cout << ev.Ps[i]->charge << " "
                                     << ev.Ps[i]->px << " "
                                     << ev.Ps[i]->py << " "
                                     << ev.Ps[i]->pz << " ";

    std::cout << std::endl;

}