#include "EventSource.h"
#include "util/include/Dispatcher.h"


EventSource::EventSource() {
    }


EventSource::~EventSource() {
    }


void EventSource::run() {
    const Event* ev;
    while ( ( ev = get() ) != nullptr ) {
        Dispatcher<Event>::notify( *ev );
        }

  return;
}