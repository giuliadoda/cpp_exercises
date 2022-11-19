#include <iostream>

// this function dumps data on screen

/*
    FUNCTION ARGUMENTS
    int ev_id --> event number
    int n_particles --> particle numbers
    float x_decay --> decay point coordinates
    float y_decay
    float z_decay
    int* charges --> array of integers containing electric charges
    float* px --> 3 array of float containing momenta components
    float* py
    float* pz
*/

void dump ( int ev_id,
            int n_particles,
            float x_decay,
            float y_decay,
            float z_decay,
            int* charges,
            float* px,
            float* py,
            float* pz) {

    std::cout << ev_id << ' ' 
              << x_decay << ' '
              << y_decay << ' '
              << z_decay << ' '
              << n_particles << ' ';

    int i;
    for ( i = 0; i < n_particles; ++i)
        std::cout << charges[i] << ' ' 
                  << px[i] << ' ' 
                  << py[i] << ' ' 
                  << pz[i] << ' ';

    std::cout << std::endl;

    return;

}