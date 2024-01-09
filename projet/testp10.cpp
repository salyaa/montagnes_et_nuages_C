#include <iostream>
#include "testp10.h"

using namespace std;

void Testsysteme_p10() //plus utile maintenant qu'on a le test deplacement
{
//cout<<'c'<<endl;
    ostream& sortie (cout);
    unsigned int i(0);
    const MontagneGaussienne M(15.0,15.0,15.0,5.0,5.0);
     ChampPotentiel champ(30,30,30,20.0/29.0, 15.0,15.0,15.0,5.0,5.0);
     champ.initialise(20, M);
     champ.calcul_laplaciens();
     //cout<<"F"<<endl;
     champ.resolution(2.2621843e-5, 1877, false);

//cout<< 'D'<<endl;
     Systeme syst (champ , M);
     //cout<<'a'<<endl;
     syst.demarre(Physique::dt,i);
    // cout<<'b'<<endl;
     syst.affiche(sortie);


}
