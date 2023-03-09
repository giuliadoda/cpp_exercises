#ifndef Singleton_H
#define Singleton_H

template <class T>
class Singleton {

 public:

  // get the object instance
  static T* instance();
  static bool verbose;

 protected:

  // the object can be created only through a derived object
  // created in its turn by the "instance()" function
  Singleton();
  virtual ~Singleton();

};

#include "Singleton.hpp"

#endif

