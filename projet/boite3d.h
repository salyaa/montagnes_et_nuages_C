#pragma once

//------------------------------------------Classe Boite3D----------------------------------------------------------------------------
class Boite3D{//permet de regrouper les coordonnées dans une seule super classe ce qui est plus facile à gérer au niveau de la conception
public:
    //constructeur:
    Boite3D( unsigned int Nx = 0.0, unsigned int Ny = 0.0, unsigned int Nz = 0.0, double echant = 0.0)
            :Nx(Nx), Ny(Ny), Nz(Nz), lambda(echant)
            {}

    //méthodes:
    void set_coordonnees(unsigned int Nx_, unsigned int Ny_, unsigned int Nz_, double echant);


    //getters pour la classe Ciel
    unsigned int get_Nx()     const { return Nx; }
    unsigned int get_Ny()     const { return Ny; }
    unsigned int get_Nz()     const { return Nz; }
    double       get_lambda() const { return lambda; }

protected:
    unsigned int Nx, Ny, Nz; //nombre de cubes contenus dans la direction x, y et z
    double       lambda;     //pas d'échantillonage, c-à-d la taille des cubes
};
