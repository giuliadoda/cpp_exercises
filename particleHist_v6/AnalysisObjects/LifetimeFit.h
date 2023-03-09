#ifndef LifetimeFit_h
#define LifetimeFit_h

#include <vector>

using namespace std;

class Event;

class LifetimeFit {

 public:

  LifetimeFit( const double min, const double max,    // mass range
               const double tmin, const double tmax,  // time range
               const double smin, const double smax,  // scan range
               const double step                      // scan step
               ); 

  ~LifetimeFit();
  

  bool add();                       // check if mass is in range
  void compute();                   // empty

  int nEvent() const;           // return number of entries in times vector

  double lifeTime() const;                // returns lifetime mean
  double lifeTimeError() const;           // returns lifetime error

 private:

  // mass range
  double mMin;  
  double mMax; 

  // time range
  double tMin;
  double tMax;

  // scan range
  double sMin;
  double sMax;

  // scan step
  double sStep;

  // decay times
  vector<double> dTimes;

  // mean lifetime
  double meanLT;

  // lifetime error
  double rmsLT;

  };

#endif