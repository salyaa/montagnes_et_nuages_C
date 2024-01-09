
#include <iostream>
#include "systeme.h"
using namespace std;

//-----------------------------------------------------------------------------------------------

ostream& operator<<(ostream& sortie, Systeme & systeme)
{
    return systeme.affiche(sortie);
}


//-----------------------------------------------------------------------------------------------

ostream& Systeme::affiche2(ostream& sortie) const
{
    sortie << "Le système est constitué de : " << endl;
    mont-> affiche_systeme(sortie);
    sortie << endl;
    champ-> affiche_systeme(sortie);

    return sortie;
}

//-----------------------------------------------------------------------------------------------

ostream& Systeme:: affiche(ostream& sortie) const
{
     sortie<< "Un Ciel : " <<endl;
     ciel_bleu.affiche(sortie);

     return sortie;
}

 //-----------------------------------------------------------------------------------------------

void Systeme::evolue(double dt)
{
     cout<<"Evolue"<<endl;
     ciel_bleu.deplace_nuage();
     ciel_bleu.recalcule_ciel();

}

//-----------------------------------------------------------------------------------------------

void Systeme::demarre(double dt, unsigned int i)
{
     champ->resolution(2.2621843e-5, 1877, false);
     for (unsigned int i(1); i<300; ++i){
     evolue(i*dt);
     }
}

//-----------------------------------------------------------------------------------------------
