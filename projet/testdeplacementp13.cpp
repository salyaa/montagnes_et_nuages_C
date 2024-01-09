#include <iostream>
#include "testdeplacementp13.h"

using namespace std;

void Testdeplacement(){

        ostream& sortie (cout);
        unsigned int i(0);
        const MontagneGaussienne M(15.0,15.0,15.0,5.0,5.0);
         ChampPotentiel champ(30,30,30,20.0/29.0, 15.0,15.0,15.0,5.0,5.0);
         champ.initialise(20, M);
         champ.calcul_laplaciens();
         champ.resolution(2.2621843e-5, 1877, false);


         Systeme syst (champ , M);
         syst.demarre(Physique::dt,i);
         syst.affiche(sortie);

}
