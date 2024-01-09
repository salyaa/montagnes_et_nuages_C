#include <iostream>
#include "testnuage.h"

using namespace std;

void Testnuage()
{
    ostream& sortie(cout) ;
    const MontagneGaussienne M(15.0,15.0,15.0,5.0,5.0);
     ChampPotentiel champ(30,30,30,20.0/29.0, 15.0,15.0,15.0,5.0,5.0);
     champ.initialise(20, M);
     champ.calcul_laplaciens();
     champ.resolution(2.2621843e-5, 1877, false);
      Ciel sky(champ,30,30,30,20.0/29);

      sky.affiche(sortie);


}

