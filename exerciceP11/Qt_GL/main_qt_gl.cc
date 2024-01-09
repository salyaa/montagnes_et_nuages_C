#include <QApplication>
#include "glwidget.h"
#include <iostream>
#include "chaine_de_montagnes.h"
#include <cmath>
using namespace std;
int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  const MontagneGaussienne Himalaya(15.,15.,15.,5.,5.);

  double lambda(20./29.); //pas d'échantillonage (champ de potentiels) --> taille des cubes
  ChampPotentiel champ(30, 30, 30, lambda, 15., 15., 15., 5., 5.);
  //Les 3 premiers arguments correspondent à la taille de l'univers
  // --> à ne pas dépasser ( aller de 0 à 29 )

  champ.initialise(20., Himalaya); //initialisation des potentiels + laplaciens(0.,0.)
  champ.calcul_laplaciens();
  champ.resolution(pow(lambda,4)*1e-4, 1900, false);

  GLWidget w(Himalaya, champ);
  w.show();

  return a.exec();
}
