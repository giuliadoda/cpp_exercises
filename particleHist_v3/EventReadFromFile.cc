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

    if ( *file >> i ) {
        *file >> x;
        *file >> y;
        *file >> z;
        ev = new Event(i, x, y, z);
        }
    else return nullptr;

    int k;
    *file >> k;

    int j, c;
    double px, py, pz;
    for ( j = 0; j < k; j++) {
        *file >> c;

        *file >> px;
        *file >> py;
        *file >> pz;

        ev->pAdd(c, px, py, pz);
        }
    
    return ev;

}