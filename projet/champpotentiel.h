#pragma once
#include <vector>
#include "Potentiel.h"
#include "boite3d.h"

//-------------------------------------------Classe ChampPotentiel---------------------------------------------------------------------------------------------------------

class ChampPotentiel: public Boite3D{
public:
    //constructeur (plus de deux lignes donc il est dans le cpp)
    ChampPotentiel (unsigned int Nx, unsigned int Ny, unsigned int Nz,  double echant, double x_=0.0, double y_=0.0, double h_=0.0, double sigma1=0.0, double sigma2=0.0);

    //initalisation de collection3D et calcule des laplaciens aux bords
    void initialise(double const& v_inf, MontagneGaussienne const& montagne);
    void calcul_laplaciens();

    //méthodes d'affichages des potentiels et des laplaciens dans collection3D en fonction de i, j et k
    void affichePot()const;
    void afficheLap() const;

    //P7: résolution des équations de Laplace
    void resolution (double const& seuil, unsigned int const& nb_ite, bool verbeuse);
    std::vector<double> vitesse (unsigned int const& i,unsigned int const& j,unsigned int const& k) const;
    double norme3D_2 (std::vector<double> v) const; //permet de calculer la norme au carré d'un vecteur de 3 coordonnées, i.e la vitesse
    void affiche() const;
   std::ostream& affiche_systeme(std::ostream& sortie)const;

protected:
    //champ de vecteurs A, i.e le potentiel vecteur
    std::vector < std::vector < std::vector < Potentiel> > > collection3D;

    //on a besoin d'une montagne en attribut pour pouvoir appliquer les conditions sous la montagne et l'utiliser dans calcul_laplacien(), etc...
    const MontagneGaussienne M;

    //P7: résolution des équations de Laplace
    constexpr static double eps = 0.1;

private:
    //elles sont privates car seulement utilisées dans des méthodes de la classe
    double erreur();
    void iteration();
    constexpr static double v_ = 20.0;
};
//--------------------------------------------------------------------------------------------------------------------------------
/*
//on met une montagne en attribut pcq il faut que le laplacien soit nul sous la montagne
ChampPotentiel()
:collection3D (0,std::vector < std::vector < Potentiel > > (0, std::vector < Potentiel > (0))), Nx(0),
 Ny(0), Nz(0), lambda(0.0), M(0,0,0,0,0)
{}

ChampPotentiel (unsigned int Nx, unsigned int Ny, unsigned int Nz, double echant, Montagne M1)
: Nx(Nx), Ny(Ny), Nz(Nz), lambda(echant), M(M1)
{} */
