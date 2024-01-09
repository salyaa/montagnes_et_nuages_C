#pragma once
#include "dessinable.h"
#include "supportadessin.h"
#include "supermontagne.h"
#include <memory>

class MontagneGaussienne: public SuperMontagne
                         ,public Dessinable
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
  void affiche()const override; //Pour afficher une montagne, cette méthode n'est plus utile car nous avons maintenant une chaine de montagnes qui peut elle même afficher qu'une seule montagne Gaussienne
     std:: ostream& affiche_systeme(std::ostream& sortie) const; //permet de faire l'affichage similaire à celui de l'exemple pour l'affichage totale de la classe système
  virtual void dessine_sur(SupportADessin& support) override
       { support.dessine(*this); }


     //attributs:

private:

  double x_0; //coordonnée du "centre" de la montagne (axe de symétrie)
  double y_0; //coordonnée du "centre" de la montagne (axe de symétrie)
  double H; //hauteur
  double sigma_x; //étalement en x
  double sigma_y; //étalement en y
};
//---------------------------------------------------------------------------------------------------------------------------
/*std::unique_ptr<Dessinable> copie() const override {
    return std::unique_ptr<Dessinable>(new Montagne(*this)); }
*/
//   virtual void dessine() override;
