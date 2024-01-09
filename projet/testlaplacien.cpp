#include <iostream>
#include "testlaplacien.h"
using namespace std;


void Testlaplacien()
{
    const MontagneGaussienne M(15.0,15.0,15.0,5.0,5.0);
    ChampPotentiel p(30,30,30,20.0/29.0,15.0,15.0,15.0,5.0,5.0);

    //Test Laplacien P6
    p.initialise(20, M);
    p.calcul_laplaciens();
    p.afficheLap();
}
