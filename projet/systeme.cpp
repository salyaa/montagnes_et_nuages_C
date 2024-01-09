#include <iostream>
#include "systeme.h"
using namespace std;

//-----------------------------------------------------------------------------------------------

ostream& operator<<(ostream& sortie, Systeme & systeme)
{
    return systeme.affiche(sortie);
}


//-----------------------------------------------------------------------------------------------

 ostream& Systeme::affiche2(ostream& sortie) const //affiche ici de quoi se compose un sytème simple de base
 {
     sortie << "Le système est constitué de : " << endl;
     mont-> affiche_systeme(sortie);
        sortie << endl;
    champ-> affiche_systeme(sortie);

    ciel_bleu.affiche(sortie);

    return sortie;
}

 ostream& Systeme:: affiche(ostream& sortie) const{ //l'affichage que l'on teste dans les tests P10 et de déplacement pour vérifier l'évolution du système
     sortie<<"Un Ciel:"<<endl;

     ciel_bleu.affiche(sortie);

     return sortie;

 }
 //-----------------------------------------------------------------------------------------------

 void Systeme::evolue(double dt)
 {
     cout<<"Evolue"<<endl;

     //TextViewer ecran(cout);

    ciel_bleu.recalcule_ciel();
     cout<<"fini"<<endl;
     ciel_bleu.deplace_nuage();

     //dessine_sur(ecran);
 }

 //-----------------------------------------------------------------------------------------------

 void Systeme::demarre(double dt, unsigned int i)
 {
     //TextViewer ecran(cout);
     champ->resolution(2.2621843e-5, 1877, false);
 for (unsigned int i(1); i<10; ++i){//modifier ici le nombre d'itérations voulues
     evolue(i*dt);

    // dessine_sur(ecran);
 }
 }

 //-----------------------------------------------------------------------------------------------

 //-----------------------------------------------------------------------------------------------

 /*void Systeme::ajouter_dessinable(std::unique_ptr<Dessinable> nouveau)
 {
     if(nouveau!=nullptr){
         //chef_doeuvre.push_back(std::move(nouveau));
     }
 }
 */
