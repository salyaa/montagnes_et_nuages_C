#include <cmath>
#include "montagne_gaussienne.h"
#include <iostream>

using namespace std;


double MontagneGaussienne::altitude(double x, double y) const
{
    double alt;
    double tmpX = (x-x_0);
    double tmpY = (y-y_0);
    alt = H * exp(-(tmpX*tmpX / (2*sigma_x*sigma_x)) - (tmpY*tmpY / (2*sigma_y*sigma_y)));

    if (alt < 0.5) {
        return 0;
    } else {
        return alt;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------
//cette méthode n'est désormais plus utile, elle est réutilisée dans chaînes de montagnes
void MontagneGaussienne::affiche() const
{
    for(int i(0); i<=29; ++i) {
        for(int j(0); j<=29; ++j) {
            cout << i << " " << j << " ";
            cout<<altitude(i,j);
            cout << endl;
        }
        cout << endl;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------

ostream& MontagneGaussienne:: affiche_systeme(ostream& sortie) const
{
    sortie << "une montagne : " << endl;
    sortie << "gaussienne de paramètres : " << endl;
    sortie << "x0 = "  << x_0 << endl;
    sortie << "yo = "  << y_0 << endl;
    sortie << "h = "   << H << endl;
    sortie << "Sx0 = " << sigma_x << endl;
    sortie << "Sy0 = " << sigma_y << endl;

    return sortie;
}

//-------------------------------------------------------------------------------------------------------------------------------
