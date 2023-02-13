#ifndef EventDump_h
#define EventDump_h

#include "AnalysisSteering.h"

class Event;

class EventDump: public AnalysisSteering {

 public:

  EventDump();
  // deleted copy constructor and assignment to prevent unadvertent copy
  EventDump           ( const EventDump& x ) = delete;
  EventDump& operator=( const EventDump& x ) = delete;

  ~EventDump() override;

  // function to be called at execution start
  void beginJob() override;
  // function to be called at execution end
  void   endJob() override;
  // function to be called for each event
  void process( const Event& ev ) override;

};

#endif

