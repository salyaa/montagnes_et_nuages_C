#include "chainedemontagnes.h"
#include <iostream>
using namespace std;

//constructeur
Chaine_de_Montagnes:: Chaine_de_Montagnes( vector<SuperMontagne*> const& chaine ){
for (auto const& element: chaine){
    ajouter_montagne(element);
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Chaine_de_Montagnes::ajouter_montagne( SuperMontagne* mont){
    if(mont!= nullptr){
    chaine.push_back( unique_ptr <SuperMontagne> (mont) );
        }
}
//------------------------------------------------------------------------------------------------------------------------------

double Chaine_de_Montagnes::altitude(double x, double y)const { //renvoie le maximum entre toutes les altitudes en chaque coordonnées
    double maximum(0.0);
    for(size_t i(0); i< chaine.size(); ++i){
        if (chaine[i]->altitude(x, y) > maximum){
            maximum = chaine[i]->altitude(x, y);
        }

    }
    return maximum;
}
//-----------------------------------------------------------------------------------------------------------------------------
void Chaine_de_Montagnes::affiche()const {
    for(int i(0); i<=29; ++i) {
        for(int j(0); j<=29; ++j) {
            cout << i << " " << j << " ";
            cout<<altitude(i,j);
            cout << endl;
        }
        cout << endl;
    }
}
//-----------------------------------------------------------------------------------------------------------------------------

/*void Chaine_de_Montagnes::affiche() const {
    for (size_t i(0); i< chaine.size(); ++i){
        chaine[i]->affiche();
    }

}
*/
/*void Chaine_de_Montagnes::affiche() const{
    for(int i(0); i<=29; ++i) {
        for(int j(0); j<=29; ++j) {
            cout << i << " " << j << " ";
            cout<<altitude(i,j);
            cout << endl;
        }
        cout << endl;
    }
}
*/