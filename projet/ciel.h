#pragma once
#include "Cubedair.h"
#include "dessinable.h"
#include "supportadessin.h"
#include <memory>

//-------------------------------------------Classe Ciel----------------------------------------------------------------
typedef std::vector<std::vector<std::vector<CubedAir>>> Cube;

//typedef std::vector<std::vector<std::vector<double>>> coord_vitesse;//pour pouvoir après appeler la vitesse dans le constructeur

class Ciel:  public Boite3D
            ,public Dessinable
{ //on hérite car le ciel est une boite 3D et est un dessinable

public:

    //constructeur 1
        Ciel( ChampPotentiel const& champ ,unsigned int Nx=0.0, unsigned int Ny=0.0, unsigned int Nz=0.0, double lambda=0.0);

        //destructeur
        ~Ciel()=default;

        //constructeur 2
        Ciel(unsigned int Nx=0.0, unsigned int Ny=0.0, unsigned int Nz=0.0, unsigned int lambda=0.0, double x=0.0);



 //méthodes:

     std::ostream& affiche(std::ostream& sortie)const;
     virtual void dessine_sur(SupportADessin& support) override
    { support.dessine(*this); }

     std::vector<int> Precedent(double dt, int i, int j, int k); //renvoie les coordonnées du cube précédent suivant le sens du vent
     void deplace_nuage(); //permet de faire évoluer le système
     //Cube get_cube() const {return cube;}
    void recalcule_ciel();
     std::vector<std::vector<unsigned int>> pluie_accumulee(  unsigned int i, unsigned int j);

     //attributs:

protected:

    Cube cube;

};
//------------------------------------------------------------------------------------------------------------------------------------
//   virtual void dessine() override{
//       affiche();
 //  }

/* std::unique_ptr<Dessinable> copie() const override {
     return std::unique_ptr<Dessinable>(new Ciel(*this)); }
*/
