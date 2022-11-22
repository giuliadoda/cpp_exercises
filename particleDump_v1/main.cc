#include <fstream>

// functions that returns number of particles producted in decay
int read( std::ifstream& file,
            float& x,
            float& y,
            float& z,
            int* charges,
            float* px,
            float* py,
            float* pz);

// function to print a dump on screen
void dump( int ev_id,
           int n_particles,
           float x,
           float y,
           float z,
           int* charges,
           float* px,
           float* py,
           float* pz);


int main( int argc, char* argv[] ) {

    const char* name = argv[1];

    std::ifstream file ( name );

    // max number of particles producted in each event
    const int maxP = 10;

    // event variables
    int ev_id;
    float x, y, z;
    int n_particles;
    int charges[maxP];
    float px[maxP];
    float py[maxP];
    float pz[maxP];

    // loop over events
    while ( file >> ev_id) {

        // number of particles producted in decay
        n_particles = read( file, 
                            x, y, z, 
                            charges, 
                            px, py, pz);
        
        dump( ev_id,
              n_particles,
              x, y, z,
              charges, 
              px, py, pz);
    }

}