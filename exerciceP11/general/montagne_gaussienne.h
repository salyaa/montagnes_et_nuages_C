
#pragma once

//#include "support_a_dessin.h"
#include "supermontagne.h"
#include <memory>

class MontagneGaussienne: public SuperMontagne
{
public:
    //constructeur
    MontagneGaussienne (double x_=0.0, double y_=0.0, double h_=0.0, double sigma1=0.0, double sigma2=0.0)
    : x_0(x_), y_0(y_), H(h_), sigma_x(sigma1), sigma_y(sigma2)
    {}
    //destructeur
     ~MontagneGaussienne()=default;

    //méthodes
     double altitude(double x, double y) const override;
     //on en a besoin pour l'affichage dans système
     double get_x0()      const { return x_0; }
     double get_y0()      const { return y_0; }
     double get_H()       const { return H; }
     double get_sigma_x() const { return sigma_x; }
     double get_sigma_y() const { return sigma_y; }

     //Pour afficher une montagne, cette méthode n'est plus utile car nous avons maintenant une
     //chaine de montagnes qui peut elle même afficher qu'une seule montagne Gaussienne
     void affiche()const override;

     std::ostream& affiche_systeme(std::ostream& sortie)const;

private:
    double x_0;     //coordonnée du "centre" de la montagne (axe de symétrie)
    double y_0;     //coordonnée du "centre" de la montagne (axe de symétrie)
    double H;       //hauteur
    double sigma_x; //étalement en x
    double sigma_y; //étalement en y
};

//---------------------------------------------------------------------------------------------------------------------------
/*std::unique_ptr<Dessinable> copie() const override {
    return std::unique_ptr<Dessinable>(new Montagne(*this)); }
*/
//   virtual void dessine() override;
