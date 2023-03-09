#include "TFile.h"
#include "TH1.h"
#include "FakeTH1F.cc"

#include <cmath>
#include <iostream>

using namespace std;

class H1FRecover: public FakeTH1F {

 public:

  H1FRecover( FakeTH1F* fhp );
  TH1F* recover() const;

 private:

};

H1FRecover::H1FRecover( FakeTH1F* fhp ):
 FakeTH1F( *fhp ) {
}

TH1F* H1FRecover::recover() const {
  cout << "recover " << hname << endl;
  TH1F* h = new TH1F( hname.c_str(), htitle.c_str(), hbin, hmin, hmax );
  int n = hbin + 2;
  int i;
  float wbin = ( hmax - hmin ) / hbin;
  float xmin = hmin - ( wbin * 3.0 / 2.0 );
  for ( i = 0; i < n; ++i ) {
    xmin += wbin;
    int   s = nent[i];
    float c = cont[i];
    float e = erro[i];
    if ( !s ) continue;
    float w = c / s;
    float r = ( e / s ) - ( w * w );
    cout << i << ' ' << s << ' ' << c << ' ' << e << ' ' << w << ' ' << r << endl;
    if ( r >= 0.0 ) {
      r = sqrt( r );
      int t = s / 2;
      s -= t;
      float x = ( r * sqrt( t * 1.0 / s ) );
      float y = w - ( t ? s * x / t : 0.0 );
      x += w;
      while ( s-- ) h->Fill( xmin, x );
      while ( t-- ) h->Fill( xmin, y );
    }
    else {
      while ( --s ) h->Fill( xmin, 0 );
      h->SetBinContent( i, c );
      h->SetBinError  ( i, sqrt( e ) );
    }
  }
  return h;
}


//int main( int argc, char* argv[] ) {
void recoverHisto( const char* i_name, const char* o_name ) {

  ifstream* i_file = new ifstream( i_name, ios::binary );

  TDirectory* currentDir = gDirectory;
  TFile* o_file = new TFile ( o_name, "RECREATE" );

  FakeTH1F* h;
  while (( h = FakeTH1F::get( i_file ) )) {
    H1FRecover r( h );
    r.recover()->Write();
  }

  currentDir->cd();
  o_file->Close();
  delete o_file;
  delete i_file;

  return;

}

