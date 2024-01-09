#include <iostream>
#include "boite3d.h"

using namespace std;

void Boite3D:: set_coordonnees(unsigned int Nx_, unsigned int Ny_, unsigned int Nz_, double echant) {
    Nx = Nx_;
    Ny = Ny_;
    Nz = Nz_;
    lambda = echant;
}
