#ifndef FakeTH1F_h
#define FakeTH1F_h

#include <iostream>
#include <fstream>
#include <string>

class FakeTH1F {

  friend class TH1F;

 public:

  // constructor
  FakeTH1F( const char* name, const char* title,
        int nbin, float xmin, float xmax );
  // deleted copy constructor and assignment to prevent unadvertent copy
  FakeTH1F           ( const FakeTH1F& x ) = delete;
  FakeTH1F& operator=( const FakeTH1F& x ) = delete;

  // destructor
  virtual ~FakeTH1F();

  static FakeTH1F* get( std::ifstream* is );

 protected:

  std::string hname;
  std::string htitle;

  int   hbin;
  float hmin;
  float hmax;
  float bwid;
  int  * nent;
  float* cont;
  float* erro;
  int ntot;

  void write( std::ofstream* os ) const;

  FakeTH1F();
  FakeTH1F( FakeTH1F& fh );

 private:

  static void write( int i, int n, float m, float w, int s, float c, float e );
  static void write( const std::string& s, std::ofstream* os );
  static void write( int n, float a, float b,
                     int* s, float* c, float* e, std::ofstream* os );
  static std::string read( std::ifstream* is );

};

#endif

