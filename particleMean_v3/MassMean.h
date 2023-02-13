#ifndef MassMean_h
#define MassMean_h

class Event;

class MassMean {

 public:

  // constructor
  MassMean( const double min, const double max ); // mass range

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