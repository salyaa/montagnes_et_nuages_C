
#pragma once

#include <iostream>

class Vecteur2D {
public:
    //constructeurs:
    Vecteur2D (double x=0.0, double y=0.0)
            : abscisse(x), ordonnee(y)
    {}

    Vecteur2D (Vecteur2D const& autre)
            : abscisse(autre.abscisse), ordonnee(autre.ordonnee)
    {}

    void set_coord(double x1, double x2);

    double get_x() const { return abscisse; }
    double get_y() const { return ordonnee; }

    std::ostream& affiche(std::ostream& sortie) const;


    double norme2() const; //calul de la norme au carré
    double norme() const ; //calcul de la norme

    //surcharge d'opérateurs:
    bool operator ==(Vecteur2D const&) const;
    bool operator !=(Vecteur2D  const&) const;

    Vecteur2D& operator+=(const Vecteur2D& );
    Vecteur2D& operator-=(const Vecteur2D&);
    Vecteur2D& operator*=(double);
    Vecteur2D operator*(double) const;
    Vecteur2D operator+(const Vecteur2D& ) const;
    Vecteur2D operator-(const Vecteur2D& ) const;
    Vecteur2D operator!() const; //oppose
    double operator*(const Vecteur2D& ) const;//produit scalaire
    Vecteur2D operator~ () const;//unitaire

private:
    //attributs:
    double abscisse;
    double ordonnee;
};

std::ostream& operator<<(std::ostream& sortie, Vecteur2D const& vect);
Vecteur2D operator*(double , const Vecteur2D&);

//---------------------------------------------------------------------------------------------------------------
//bool compare(Vecteur2D vect) const;

//Vecteur2D addition(Vecteur2D vect ,Vecteur2D& vectfinal) ;
//Vecteur2D soustraction(Vecteur2D vect ,Vecteur2D& vectfinal) ;
//Vecteur2D oppose (Vecteur2D& voppose) ;
//Vecteur2D mult (double a, Vecteur2D& vmult);
//double prod_scal(Vecteur2D v) const;
//Vecteur2D unitaire();
