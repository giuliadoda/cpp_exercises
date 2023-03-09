#include <iostream>

#include "Event.h"


void dump( const Event& ev ) {

    // write event ID
    std::cout << ev.eventNumber() << " ";

    // decay point coordinates
    std::cout << ev.X() << " "
              << ev.Y() << " "
              << ev.Z() << " ";

    // number of particles
    int n = ev.nParticles();
    std::cout <<  n << " ";

    // loop for particles details
    unsigned int j;
    for ( j = 0; j < n; ++j ) std::cout << ev.particle(j)->charge << " "
                                        << ev.particle(j)->px     << " "
                                        << ev.particle(j)->py     << " "
                                        << ev.particle(j)->pz     << " ";
    
    std::cout << std::endl;

    return;

    }