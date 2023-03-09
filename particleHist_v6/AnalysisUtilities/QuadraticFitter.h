#ifndef QuadraticFitter_h
#define QuadraticFitter_h

class QuadraticFitter {

  // class to fit y = a+bx+cx^2

 public:

  // constructor
  QuadraticFitter();
  // deleted copy constructor and assignment to prevent unadvertent copy
  QuadraticFitter           ( const QuadraticFitter& x ) = delete;
  QuadraticFitter& operator=( const QuadraticFitter& x ) = delete;

  // destructor
  ~QuadraticFitter();

  // add a point
  void add( double x, double y );

  // get coefficients
  double a();
  double b();
  double c();

  // remove all points
  void clear();

 private:

  double sumx0y0;
  double sumx1y0;
  double sumx2y0;
  double sumx3y0;
  double sumx4y0;
  double sumx0y1;
  double sumx1y1;
  double sumx2y1;

  mutable bool outdated;
  mutable double ac;
  mutable double bc;
  mutable double cc;

  void reset() const;
  void update() const;

};

#endif

