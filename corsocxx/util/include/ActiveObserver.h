#ifndef ActiveObserver_H
#define ActiveObserver_H

template <class T>
class ActiveObserver {

 public:

  // constructor
  ActiveObserver();
  // deleted copy constructor and assignment to prevent unadvertent copy
  ActiveObserver           ( const ActiveObserver& x ) = delete;
  ActiveObserver& operator=( const ActiveObserver& x ) = delete;

  // destructor
  virtual ~ActiveObserver();

  virtual void update( const T& x ) = 0;

};

#include "ActiveObserver.hpp"

#endif

