/*
Add to the class:
- a constructor taking the min and max invariant mass as parameters,
- a destructor,
- a function "add" taking as argument a reference to const-Event,
  to update the sum of masses and squares
- a function "compute" to compute mean and rms,
- a function "nEvents" returning the number of selected events,
- two functions "mMean" and "mRMS" returning the mean and rms.

Initialize all the variables in the costructor.

In the function "add" compute the invariant mass calling the "mass" function, 
check if the result is in the required range, if yes increase the event
counter and the sums, otherwise do nothing.
Declare "const" the functions returning results (number of selected events,
mean and rms ).
If you chose to subtract the min. mass event by event, use the same
parameter used to select events inside the mass range.
*/

#ifndef MassMean_h
#define MassMean_h

class Event;

class MassMean {

 public:

  // constructor
  MassMean( double min, double max ); // mass range

  // destructor
  ~MassMean();

  void add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  int nEvent() const;           // return number of accepted events
  double mMean() const;         // return mean mass
  double mRMS() const;          // return rms  mass

 private:

  double mMin; // min mass 
  double mMax; // max mass

  int aev; // number of accepted events
  double sum; // sum of masses
  double sqr; // sum of masses square

  double mm; // mean mass
  double rms; // rms  mass

};

#endif

