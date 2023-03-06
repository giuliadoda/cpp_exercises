#ifndef SourceFactory_h
#define SourceFactory_h

#include <string>
#include <map>

class EventSource;
class AnalysisInfo;

class SourceFactory {

 public:

  SourceFactory();
  // deleted copy constructor and assignment to prevent unadvertent copy
  SourceFactory           ( const SourceFactory& x ) = delete;
  SourceFactory& operator=( const SourceFactory& x ) = delete;

  virtual ~SourceFactory();

  // create event source
  static EventSource* create( const AnalysisInfo* info ); // static --> non è necessario creare l'oggetto

};

#endif

