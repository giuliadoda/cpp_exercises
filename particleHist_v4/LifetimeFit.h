#ifndef LifetimeFit_h
#define LifetimeFit_h

#include "TF1.h"

class Event;

class LifetimeFit {

 public:

  LifetimeFit( const double min, const double max ); // mass range
  ~LifetimeFit();
  

  bool add();                       // check if mass is in range
  void compute();                   // empty

  int nEvent() const;           // return number of accepted events

 private:

  double mMin; // min mass 
  double mMax; // max mass

  int aev; // number of accepted events

  };

#endif