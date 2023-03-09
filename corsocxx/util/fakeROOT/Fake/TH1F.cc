#include "TH1F.h"
#include "TDirectory.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

TH1F::TH1F( const char* name, const char* title,
            int nbin, float xmin, float xmax ):
 FakeTH1F( name, title, nbin, xmin, xmax ) {
  existCheck( name );
  gDirectory->hmap[hname] = this;
}


TH1F::TH1F( FakeTH1F* fhp ):
 FakeTH1F( *fhp ) {
  existCheck( hname );
  gDirectory->hmap[hname] = this;
}


TH1F::~TH1F() {
  gDirectory->hmap[hname] = nullptr;
}


int TH1F::Fill( double x, double w ) {
  int i = ( x + bwid - hmin ) / bwid;
  if ( i < 1    ) i = 0;
  if ( i > hbin ) i = hbin + 1;
  nent[i] += 1;
  cont[i] += w;
  erro[i] += w * w;
  ++ntot;
  return i;
}


void TH1F::SetBinContent( int i, double x ) {
  if ( i < 1    ) i = 0;
  if ( i > hbin ) i = hbin + 1;
  nent[i] += 1;
  cont[i] = x;
  ++ntot;
  return;
}


void TH1F::SetBinError( int i, double e ) {
  if ( i < 1    ) i = 0;
  if ( i > hbin ) i = hbin + 1;
//  nent[i] = 1;
  erro[i] = e * e;
  return;
}


void TH1F::Write() const {
  if ( hname == "" ) return;
  ios* fptr = gDirectory->file();
  ofstream* file = dynamic_cast<ofstream*>( fptr );
  if ( ( fptr != nullptr ) && ( file == nullptr ) ) {
    cout << "file not open for write" << endl;
    return;
  }
  write( file );
  return;
}


const char* TH1F::GetName() const {
  return hname.c_str();
}


double TH1F::GetEntries() const {
  return ntot;
}


int TH1F::GetNbinsX() const {
  return hbin;
}


int TH1F::FindBin( float x ) const {
  if ( x < hmin ) return 0;
  if ( x > hmax ) return hbin + 1;
  return ( hbin * ( x - hmin ) / ( hmax - hmin ) ) + 1;
}


float TH1F::GetBinContent( int i ) const {
  if ( i < 0 ) return 0.0;
  if ( i > hbin + 1 ) return 0.0;
  return cont[i];
}


float TH1F::GetBinError( int i ) const {
  if ( i < 0 ) return 0.0;
  if ( i > hbin + 1 ) return 0.0;
  return sqrt( erro[i] );
}


TH1F* TH1F::Clone() const {
  if ( hname == "" ) return nullptr;
  TH1F* h = new TH1F( hname.c_str(), htitle.c_str(), hbin, hmin, hmax );
  int n = hbin + 2;
  int i;
  for ( i = 0; i < n; ++i ) {
    h->nent[i] = nent[i];
    h->cont[i] = cont[i];
    h->erro[i] = erro[i];
  }
  return h;
}


TH1F* TH1F::get( std::ifstream* is ) {
  FakeTH1F* fhp = FakeTH1F::get( is );
  if ( fhp == nullptr ) return nullptr;
  return new TH1F( fhp );
}


void TH1F::existCheck( const string& name ) {
  auto& hmap = gDirectory->hmap;
  auto it = hmap.find( name );
  auto ie = hmap.end();
  if ( it == ie ) return;
  if ( it->second != nullptr ) cout << "Warning: Replacing existing TH1: "
                            << name << " (Potential memory leak)." << endl;
  return;
}

