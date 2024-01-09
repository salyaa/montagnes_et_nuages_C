#include <iostream>
#include "testchainedemontagnes.h"
using namespace std;

void testChaine_de_Montagnes(){


Chaine_de_Montagnes chaine_de_reve({new MontagneGaussienne (15.0,15.0,18.0,5.0,10.0),
                                        new Chaine_de_Montagnes({
                                            new MontagneGaussienne (2.0, 22.0, 12.0, 12.0, 3.0),
                                            new MontagneGaussienne (20.0, 2.0, 15.0, 8.0, 4.0)})
                    });


       chaine_de_reve.affiche();

}
// petite_chaine.ajouter_montagne(Mont2);
 //petite_chaine.ajouter_montagne(Mont3);
 //grosse_chaine.ajouter_montagne({Mont1, Mont2, Mont3});
// grosse_chaine.ajouter_montagne(petite_chaine);
