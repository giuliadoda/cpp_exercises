#include <fstream>

// function that returns the number of particles producted in decay

int read( std::ifstream& file,  // input file
            float& x_decay,     // decay point coordinates
            float& y_decay,
            float& z_decay,
            int* charges,       // particles charges
            float* px,          // momenta components
            float* py,
            float* pz ) {

    int n; // number of particles producted in that decay

    file >> x_decay >> y_decay >> z_decay   // reading decay point coordinates
                               >> n;        // reading number of particles producted

    // loop over particles
    unsigned int i;
    for ( i = 0; i < n; ++i ) {
        file >> charges[i];
        file >> px[i] >> py[i] >> pz[i];
        }
    
    return n;

    }