#ifndef TH1F_h
#define TH1F_h

#include "FakeTH1F.h"
#include <iostream>
#include <fstream>
#include <string>

class TH1F: public FakeTH1F {

 public:

  // constructor
  TH1F( const char* name, const char* title,
        int nbin, float xmin, float xmax );
  // deleted copy constructor and assignment to prevent unadvertent copy
  TH1F           ( const TH1F& x ) = delete;
  TH1F& operator=( const TH1F& x ) = delete;

  // destructor
  ~TH1F() override;

  virtual int Fill( double x, double w = 1.0 );
  virtual void SetBinContent( int i, double x );
  virtual void SetBinError  ( int i, double e );
  virtual void Write() const;

  virtual const char* GetName() const;
  virtual double GetEntries() const;
  virtual int GetNbinsX() const;
  virtual int FindBin( float x ) const;
  virtual float GetBinContent( int i ) const;
  virtual float GetBinError( int i ) const;
  TH1F* Clone() const;

  static TH1F* get( std::ifstream* is );

 private:

  void existCheck( const std::string& name );
  TH1F( FakeTH1F* fhp );

};

#endif

