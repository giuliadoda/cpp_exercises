#include <iostream>
#include <fstream>

#include "Event.h"

const Event* read (std::ifstream& file);
void dump (const Event& ev);
void clear (const Event* ev);

int main (int argc, char* argv[]) {

    const char* name = argv[1];
    std::ifstream file (name);

    const Event* ev;
    while ( (ev = read(file) ) != nullptr ) {
        dump(*ev);
        clear(ev);
    }

    return 0;

}