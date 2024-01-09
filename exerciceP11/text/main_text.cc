#include <iostream>
#include "text_viewer.h"
#include "systeme.h"

using namespace std;

int main()
{
  const MontagneGaussienne M(15.,15.,15.,5.,5.);
  ChampPotentiel champ(30,30,30,20./29.,15.,15.,15.,5.,5.);
  TextViewer ecran(cout);
  Systeme systeme(champ, M);

  cout << "Au départ :" << endl;
  systeme.dessine_sur(ecran);

  systeme.evolue(0.1);
  cout << "Après un pas de calcul :" << endl;
  systeme.dessine_sur(ecran);

  systeme.evolue(0.1);
  cout << "Après deux pas de calcul :" << endl;
  systeme.dessine_sur(ecran);

  return 0;
}
