#include <iostream>
#include <fstream>

// the function returns the number of particles producted in decay

/* 
  FILE STRUCTURE
  int --> event identifier
  3 floats --> decay point coordinates
  int --> number of particles producted in the decay
  for each particles: 
    int --> electric charge
    3 floats --> momenta components
*/

/*
  FUNCTION ARGUMENTS
  std::ifstream& file --> is a reference to a input file stream tipe --> the function takes a file as argument
  float& x_decay --> references to decay point coordinates
  float& y_decay
  float& z_decay
  int* charges --> charges array
  float* px --> momenta components array
  float* py
  float* pz
*/


int read( std::ifstream& file,
            float& x_decay,
            float& y_decay,
            float& z_decay,
            int* charges,
            float* px,
            float* py,
            float* pz) {

    int n; // number of particles producted in that decay

    file >> x_decay >> y_decay >> z_decay; // reading decay coordinates

    file >> n; // reading number of particles producted

    int i;
    for (i = 0; i < n; ++i) {
        file >> charges[i];
        file >> px[i] >> py[i] >> pz[i];
    }
    
    return n;

}