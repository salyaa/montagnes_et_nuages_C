#include <iostream>
#include "testaffichagep7.h"
using namespace std;


void Testaffichage()
{
    const MontagneGaussienne M(15.0,15.0,15.0,5.0,5.0);
    ChampPotentiel p(30,30,30,20.0/29.0,15.0,15.0,15.0,5.0,5.0);

//test laplacien P7
  p.initialise(20, M);
  p.calcul_laplaciens();
  p.resolution(2.2621843e-5, 1877, false);
  p.affiche();
}

