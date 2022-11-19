/*
Modify the "dump" functions to access event data through the "Event" class
functions.
*/

#include <iostream>
#include <fstream>
#include "Event.h"

void dump (const Event& ev) {

    // write event ID
    std::cout << ev.eventNumber() << " ";

    // decay point coordinates
    std::cout << ev.X() << " "
              << ev.Y() << " "
              << ev.Z() << " ";

    // number of particles
    std::cout << ev.nParticles() << " ";

    // particles details
    int j;
    for ( j = 0; j < ev.nParticles(); ++j) std::cout << ev.particle(j)->charge << " "
                                                     << ev.particle(j)->px << " "
                                                     << ev.particle(j)->py << " "
                                                     << ev.particle(j)->pz << " ";
    
    std::cout << std::endl;

}
