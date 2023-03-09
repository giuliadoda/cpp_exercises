#ifndef LazyObserver_H
#define LazyObserver_H

template <class T>
class LazyObserver {

 public:

  // constructor
  LazyObserver();
  // deleted copy constructor and assignment to prevent unadvertent copy
  LazyObserver           ( const LazyObserver& x ) = delete;
  LazyObserver& operator=( const LazyObserver& x ) = delete;

  // destructor
  virtual ~LazyObserver();

  virtual void lazyUpdate( const T& x );

 protected:

  virtual void update( const T& x ) = 0;
  virtual void check();

 private:

  bool upToDate;
  bool updating;
  const T* last;

};

#include "LazyObserver.hpp"

#endif

