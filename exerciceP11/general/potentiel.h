
#pragma once
#include "vecteur2d.h"
#include "montagne_gaussienne.h"


class Potentiel {
public:
    Potentiel (double x1 = 0.0, double y1 = 0.0, double x2 = 0.0, double y2 = 0.0)
            : potentiel(Vecteur2D(x1,y1)), laplacien(Vecteur2D(x2, y2))
    {}

    Vecteur2D getPotentiel() const { return potentiel; }
    Vecteur2D getLaplacien() const { return laplacien; }
    void setPotentiel(double x, double y);
    void setLaplacien(double x, double y);

protected:
    Vecteur2D potentiel;
    Vecteur2D laplacien;
};
