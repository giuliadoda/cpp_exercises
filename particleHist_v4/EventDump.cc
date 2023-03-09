#include "EventDump.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"
#include "Event.h"

#include <iostream>

using namespace std;


// concrete factory to create EventDump
class EventDumpFactory: public AnalysisFactory::AbsFactory {

  public:
    // assign "dump" as name for this analyzer and factory
    EventDumpFactory(): AnalysisFactory::AbsFactory( "dump" ) {}
    // create an EventDump when builder is run
    AnalysisSteering* create( const AnalysisInfo* info ) override {
      return new EventDump( info );
      }

};

// create a global EventDumpFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an EventDumpFactory will be available with name "dump".
static EventDumpFactory ed;

EventDump::EventDump( const AnalysisInfo* info ):
 AnalysisSteering( info ) {
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

void EventDump::update( const Event& ev ) {

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