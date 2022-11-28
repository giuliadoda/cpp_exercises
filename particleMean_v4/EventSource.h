#ifndef EventSource_h
#define EventSource_h

class Event;

class EventSource {

 public:

  EventSource();
  // deleted copy constructor and assignment to prevent unadvertent copy
  EventSource           ( const EventSource& x ) = delete;
  EventSource& operator=( const EventSource& x ) = delete;

  virtual ~EventSource();

  // get an event
  virtual const Event* get() = 0;

};

#endif

