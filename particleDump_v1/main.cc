#include <iostream>
#include <fstream>

int read( std::ifstream& file,
            float& x_decay,
            float& y_decay,
            float& z_decay,
            int* charges,
            float* px,
            float* py,
            float* pz);

void dump( int ev_id,
           int n_particles,
           float x_decay,
           float y_decay,
           float z_decay,
           int* charges,
           float* px,
           float* py,
           float* pz);


int main( int a, char* w[] ) {

    const char* name_f = w[1];

    std::ifstream file ( name_f );

    // event variables
    int ev_id;
    float x_decay, y_decay, z_decay;
    int n_particles;
    int charges[10];
    float px[10];
    float py[10];
    float pz[10];

    while ( file >> ev_id) {

        n_particles = read( file, 
                            x_decay, y_decay, z_decay, 
                            charges, 
                            px, py, pz);
        
        dump( ev_id,
              n_particles,
              x_decay, y_decay, z_decay,
              charges, 
              px, py, pz);
    }

}