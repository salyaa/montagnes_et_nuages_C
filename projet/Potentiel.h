#pragma once
#include "vecteur2d.h"
#include "montagnegaussienne.h"

//-----------------------------------------------------------------------------------------------------------------------------

class Potentiel {

public:
    //constructeurs:
    Potentiel (double x1 = 0.0, double y1 = 0.0, double x2 = 0.0, double y2 = 0.0)
            : potentiel(Vecteur2D(x1,y1)), laplacien(Vecteur2D(x2, y2))
    {}

    //méthodes
    Vecteur2D getPotentiel() const { return potentiel; }
    Vecteur2D getLaplacien() const { return laplacien; }
    void setPotentiel(double x, double y);
    void setLaplacien(double x, double y);

private:
    //attributs
    Vecteur2D potentiel;
    Vecteur2D laplacien;
};

