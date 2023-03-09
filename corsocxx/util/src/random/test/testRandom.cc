#include "Random.h"

#include <iostream>
#include <string>

using namespace std;

int main( int argc, char* argv[] ) {

  Random::verbosity = 3;

  const string strn = argv[1];
  const string prob = argv[2];
  const string str1 = argv[3];
  const string str2 = argv[4];

  // number of generations
  int n = stoi( strn );
  // lower bound / mean
  float par1 = stof( str1 );
  // upper bound / rms
  float par2 = stof( str2 );

  switch ( *prob.c_str() ) {
  case 'f':
    while ( n-- ) cout << Random::flat ( par1, par2 ) << endl;
    break;
  case 'g':
    while ( n-- ) cout << Random::gauss( par1, par2 ) << endl;
    break;
  }

  return 0;

}

