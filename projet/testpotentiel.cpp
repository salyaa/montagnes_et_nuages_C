#include <iostream>
#include "testpotentiel.h"
using namespace std;


void Testpotentiel()
{
    const MontagneGaussienne M(15.0,15.0,15.0,5.0,5.0);
    ChampPotentiel p(30,30,30,20.0/29.0,15.0,15.0,15.0,5.0,5.0);

    //test potentiel P6
    p.initialise(20, M);
    p.affichePot();





}
