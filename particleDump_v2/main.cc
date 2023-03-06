#include <fstream>

#include "Event.h"


const Event* read( std::ifstream& file );    // function to read file    
void dump( const Event& ev );                // function to dump data on screen
void clear( const Event* ev );               // function to clear memory


int main( int argc, char* argv[] ) {

    // input file from command line
    const char* name = argv[1];
    std::ifstream file( name );

    const Event* ev;

    // loop over events
    while ( ( ev = read(file) ) != nullptr ) {
        dump(*ev);
        clear(ev);
        }

    return 0;

    }