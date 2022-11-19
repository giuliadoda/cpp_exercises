#include <iostream>
#include <fstream>

#include "Event.h"

Event* read (std::ifstream& file) {

    // event pointer and identifier
    Event* ev;
    int i;
    float x, y, z;

    // read input file and on success create event
    // passing event number and decay point coordinates to Event constructor
    if (file >> i) {
        file >> x >> y >> z;
        ev = new Event(i, x, y, z);
        }
    else return nullptr;

    // number of particles
    int k;
    file >> k;
    

    // loop over particles
    int j;
    int c;
    double px, py, pz;
    for ( j = 0; j < k; ++j) {
        file >> c >> px >> py >> pz;
        ev->add(c, px, py, pz); // filling particle object with data
    }

    return ev;
    
}