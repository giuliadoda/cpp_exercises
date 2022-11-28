#include "EventReadFromFile.h"

#include "Event.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


EventReadFromFile::EventReadFromFile ( const string& name ) {
    file = new ifstream(name);
}

EventReadFromFile::~EventReadFromFile() {
  delete file;
}

// get an event
const Event* EventReadFromFile::get() {
    return readFile();
}

//read an event
const Event* EventReadFromFile::readFile() {

    Event* ev;
    int i;
    float x, y, z;

    if ( file->operator>>(i) ) {
        file->operator>>(x);
        file->operator>>(y);
        file->operator>>(z);
        ev = new Event(i, x, y, z);
        }
    else return nullptr;

    int k;
    file->operator>>(k);

    int j, c;
    double px, py, pz;
    for ( j = 0; j < k; j++) {
        file->operator>>(c);

        file->operator>>(px);
        file->operator>>(py);
        file->operator>>(pz);

        ev->add(c, px, py,pz);
        }
    
    return ev;

}