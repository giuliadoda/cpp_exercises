#include "FakeTH1F.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

FakeTH1F::FakeTH1F( const char* name, const char* title,
                    int nbin, float xmin, float xmax ):
 hname ( name ),
 htitle( title ),
 hbin( nbin ),
 hmin( xmin ),
 hmax( xmax ) {
  int nval = nbin + 2;
  nent = new int  [nval];
  cont = new float[nval];
  erro = new float[nval];
  while ( nval-- ) cont[nval] = erro[nval] = nent[nval] = 0;
  bwid = ( hmax - hmin ) / hbin;
  ntot = 0;
}


FakeTH1F::FakeTH1F() {
}


FakeTH1F::FakeTH1F( FakeTH1F& fh ):
 hname ( fh.hname ),
 htitle( fh.htitle ),
 hbin( fh.hbin ),
 hmin( fh.hmin ),
 hmax( fh.hmax ),
 nent( fh.nent ),
 cont( fh.cont ),
 erro( fh.erro ) ,
 ntot( fh.ntot ){
  fh.nent = nullptr;
  fh.cont = nullptr;
  fh.erro = nullptr;
}


FakeTH1F::~FakeTH1F() {
  delete[] nent;
  delete[] cont;
  delete[] erro;
}


void FakeTH1F::write( std::ofstream* os ) const {
  write( hname , os );
  write( htitle, os );
  write( hbin, hmin, hmax, nent, cont, erro, os );
  return;
}


FakeTH1F* FakeTH1F::get( std::ifstream* is ) {
  string name  = read( is );
  if ( name == "" ) return nullptr;
  string title = read( is );
  int n;
  float a;
  float b;
  is->read( reinterpret_cast<char*>(      &n ),     sizeof(        n ) );
  is->read( reinterpret_cast<char*>(      &a ),     sizeof(        a ) );
  is->read( reinterpret_cast<char*>(      &b ),     sizeof(        b ) );
  FakeTH1F* h = new FakeTH1F( name.c_str(), title.c_str(), n, a, b );
  n += 2;
  is->read( reinterpret_cast<char*>( h->nent ), n * sizeof( *h->nent ) );
  is->read( reinterpret_cast<char*>( h->cont ), n * sizeof( *h->cont ) );
  is->read( reinterpret_cast<char*>( h->erro ), n * sizeof( *h->erro ) );
  return h;
}


void FakeTH1F::write( const std::string& s, std::ofstream* os ) {
  if ( os == nullptr ) {
    cout << s << endl;
    return;
  }
  int n = s.length();
  os->write( reinterpret_cast<char*>( &n ), sizeof( n ) );
  os->write( s.c_str(), n );
  return;
}


void FakeTH1F::write( int i, int n, float m, float w,
                      int s, float c, float e ) {
  if ( i == 0 ) {
    cout << "underflow";
  }
  else
  if ( i == n ) {
    cout << " overflow";
  }
  else {
    float a = m + ( ( i - 1 ) * w );
    cout << '[' << a << ',' << a + w << ']';
  }
  cout << " : " << s << ' ' << c << ' ' << sqrt( e ) << endl;
  return;
}


void FakeTH1F::write( int n, float a, float b,
                      int* s, float* c, float* e, std::ofstream* os ) {
  int i;
  if ( os == nullptr ) {
    float w = ( b - a ) / n;
    cout << n << " " << a << " " << b << endl;
    ++n;
    for ( i = 0; i <= n; ++i ) write( i, n, a, w, s[i], c[i], e[i] );
    return;
  }
  os->write( reinterpret_cast<char*>( &n ),     sizeof(  n ) );
  os->write( reinterpret_cast<char*>( &a ),     sizeof(  a ) );
  os->write( reinterpret_cast<char*>( &b ),     sizeof(  b ) );
  n += 2;
  os->write( reinterpret_cast<char*>(  s ), n * sizeof( *s ) );
  os->write( reinterpret_cast<char*>(  c ), n * sizeof( *c ) );
  os->write( reinterpret_cast<char*>(  e ), n * sizeof( *e ) );
  return;
}


string FakeTH1F::read( std::ifstream* is ) {
  int l;
  char* p;
  if ( is->read( reinterpret_cast<char*>( &l ), sizeof( l ) ) )
       p = new char[l + 1];
  else return "";
  is->read( p, l );
  p[l] = '\0';
  string s( p );
  delete p;
  return s;
}

