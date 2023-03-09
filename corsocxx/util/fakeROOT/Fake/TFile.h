#ifndef TFile_h
#define TFile_h

#include "TDirectory.h"
#include <iostream>
#include <string>

class TH1F;

class TFile: public TDirectory {

 public:

  // constructor
  TFile( const char* name, const char* mode = "READ" );
  // deleted copy constructor and assignment to prevent unadvertent copy
  TFile           ( const TFile& x ) = delete;
  TFile& operator=( const TFile& x ) = delete;

  // destructor
  ~TFile() override;

  void Close();

 private:

  static std::ios* open( const char* name, const std::string& mode );
  static bool check    ( const char* name, const std::string& mode );
  void update() override;

};

#endif

