#include <iostream>
#include "dessinable.h"
#include "testmontagne.h"
#include "testpotentiel.h"
#include "testerreurp7.h"
#include "testlaplacien.h"
#include "testaffichagep7.h"
#include "testnuage.h"
#include "systeme.h"
#include "testchainedemontagnes.h"
#include "testmontagne.h"
#include "testvecteur2d.h"
#include "testp10.h"
#include "testdeplacementp13.h"
using namespace std;

int main(){

//PARTIE D'AFFICHAGE TEXTE, ELLE PEUT ÊTRE ENTIÈREMENT COMMENTEE POUR EXÉCUTER LES FICHIERS TESTS VOULU
    /* Nous voulons un support à dessin :                          *
       * ici un TextViewer qui écrit sur cout                        */
    TextViewer ecran (cout);
     ChampPotentiel champ  (30,30,30,20.0/29.0,15.0,15.0,15.0,5.0,5.0);
     MontagneGaussienne Mont(15.0,15.0,15.0,5.0,5.0);
     champ.initialise(20, Mont);
     champ.calcul_laplaciens();
     champ.resolution(2.2621843e-5, 1877, false);

      // Nous voulons un contenu à dessiner
      Systeme a_dessiner(champ, Mont);

      // Nous dessinons notre contenu  sur notre support à dessin précédent
      a_dessiner.dessine_sur(ecran);


//ENTREZ ICI LE TEST SOUHAITÉ TOUS LES INCLUDES SONT DÉJÀ MIS:
    //testvecteur2D();
    //Testmontagne();
    //Testpotentiel();
    //Testlaplacien();
    //Testaffichage();
    //Testnuage();
    //Testerreur();//decommenter dans champpotentiel.cpp dans la méthode resolution comme indiqué dans celle-ci
    //testChaine_de_Montagnes();
    //Testsysteme_p10(); //ne sert plus, nous retrouvions exactement les mêmes valeurs que pour le ciel
    //Testdeplacement(); //sélectionner le nombre d'itérations voulues dans système.cpp méthode demarre


    return 0;

}


