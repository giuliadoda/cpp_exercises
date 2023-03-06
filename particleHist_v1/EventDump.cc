#include "EventDump.h"

#include "Event.h"
#include <iostream>

using namespace std;

EventDump::EventDump() {
  }

EventDump::~EventDump() {
  }

// function to be called at execution start
void EventDump::beginJob() {
  return;
  }

// function to be called at execution end
void EventDump::endJob() {
  return;
  }

void EventDump::process( const Event& ev ) {

    cout << ev.eventNumber() << " ";

    cout << ev.X() << " "
         << ev.Y() << " "
         << ev.Z() << " ";

    int n = ev.nParticles();
    cout << n << " ";

    unsigned int j;
    for (j = 0; j < n; ++j) {
      cout << ev.particle(j)->charge << " "
           << ev.particle(j)->px << " "
           << ev.particle(j)->py << " "
           << ev.particle(j)->pz << " ";
      }
    
    cout << endl;
    
    }