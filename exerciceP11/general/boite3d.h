
#pragma once

//------------------------------------------Classe Boite3D----------------------------------------------------------------------------

class Boite3D {
public:
    //constructeur
    Boite3D (unsigned int Nx=0, unsigned int Ny=0, unsigned int Nz=0, double echant=0.0)
            :Nx(Nx), Ny(Ny), Nz(Nz), lambda(echant)
            {}

    //méthode pour que l'on puisse initialiser Nx, Ny, Nz et lambda
    void set_coordonnees(unsigned int Nx_, unsigned int Ny_, unsigned int Nz_, double echant);

    //getters pour la classe Ciel et pour l'affichage dans système
    unsigned int get_Nx()     const { return Nx; }
    unsigned int get_Ny()     const { return Ny; }
    unsigned int get_Nz()     const { return Nz; }
    double       get_lambda() const { return lambda; }
    //on en a besoin pour l'affichage dans système
    //double       get_Lx()     const { return (lambda*(Nx-1)); }
    //double       get_Ly()     const { return (lambda*(Ny-1)); }
    //double       get_Lz()     const { return (lambda*(Nz-1)); }

protected:
    unsigned int Nx, Ny, Nz; //nombre de cubes contenus dans la direction x, y et z
    double       lambda;     //pas d'échantillonage, c-à-d la taille des cubes
};

