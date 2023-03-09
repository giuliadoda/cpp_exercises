#ifndef RootRandom_H
#define RootRandom_H

#include "Random.h"
#include "TRandom.h"

class RootRandom: public Random {

 public:

  // constructor
  RootRandom();
  // deleted copy constructor and assignment to prevent unadvertent copy
  RootRandom           ( const RootRandom& x ) = delete;
  RootRandom& operator=( const RootRandom& x ) = delete;

  // destructor
  ~RootRandom() override;

 protected:

  // redeclaration of random number generation functions
  void set( unsigned int seed ) override;
  float generate( Random::probability p, float a, float b ) override;

 private:

  // actual ROOT generator
  TRandom* rand;

};

#endif

