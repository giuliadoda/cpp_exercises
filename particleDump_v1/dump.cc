#include <iostream>

// function that dumps data on screen

void dump ( int ev_id,          // event number
            int n_particles,    // number of particles producted
            float x_decay,      // decay point coordinates
            float y_decay,
            float z_decay,
            int* charges,       // particles charges
            float* px,          // momenta components
            float* py,
            float* pz) {

    std::cout << ev_id << ' ' 
              << x_decay << ' '
              << y_decay << ' '
              << z_decay << ' '
              << n_particles << ' ';

    // loop over particles
    int i;
    for ( i = 0; i < n_particles; ++i)
        std::cout << charges[i] << ' ' 
                  << px[i] << ' ' 
                  << py[i] << ' ' 
                  << pz[i] << ' ';

    std::cout << std::endl;

    return;

}