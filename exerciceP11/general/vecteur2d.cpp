#include <iostream>
#include <cmath>
#include "vecteur2d.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------------

void Vecteur2D::set_coord(double x1, double x2)
{
    abscisse=x1;
    ordonnee=x2;
}

//----------------------------------------------------------------------------------------------------------------------

ostream& Vecteur2D::affiche(ostream& sortie) const
{
    sortie <<  abscisse << " " << ordonnee;
    return sortie;
}

//----------------------------------------------------------------------------------------------------------------------

bool Vecteur2D::operator==(Vecteur2D const& vect) const
{
    //nouveau compare avec surcharge
    return (abscisse==vect.abscisse) and (ordonnee==vect.ordonnee);
}

//----------------------------------------------------------------------------------------------------------------------

bool Vecteur2D:: operator!=(Vecteur2D const& vect) const
{
    return (abscisse!= vect.abscisse) and (ordonnee!=vect.ordonnee);
}

//----------------------------------------------------------------------------------------------------------------------

Vecteur2D& Vecteur2D::operator+=(const Vecteur2D& vect)
{
    abscisse += vect.abscisse;
    ordonnee += vect.ordonnee;
    return *this;
}

//----------------------------------------------------------------------------------------------------------------------

Vecteur2D Vecteur2D::operator+(const Vecteur2D& vect) const
{
    return Vecteur2D(*this)+= vect;
}

//----------------------------------------------------------------------------------------------------------------------

Vecteur2D& Vecteur2D::operator-=(const Vecteur2D& vect)
{
    abscisse -= vect.abscisse;
    ordonnee -= vect.ordonnee;
    return *this;
}

//----------------------------------------------------------------------------------------------------------------------

Vecteur2D Vecteur2D::operator-(const Vecteur2D& vect) const
{
    return Vecteur2D(*this)-= vect;
}

//----------------------------------------------------------------------------------------------------------------------

Vecteur2D Vecteur2D:: operator!() const
{
    //surcharge de l'oppposé
    Vecteur2D v;
    return (v - *this);
}

//----------------------------------------------------------------------------------------------------------------------

Vecteur2D& Vecteur2D::operator*=(double a)
{
    (*this).abscisse *= a;
    (*this).ordonnee *= a;
    return *this;
}

//----------------------------------------------------------------------------------------------------------------------

Vecteur2D Vecteur2D::operator*(double a) const
{
    return Vecteur2D(*this) *= a;
}

//----------------------------------------------------------------------------------------------------------------------

double Vecteur2D::operator*(const Vecteur2D& vect) const
{
    //opérateur produit scalaire
    return double ((abscisse * vect.abscisse) + (ordonnee * vect.ordonnee));
}

//----------------------------------------------------------------------------------------------------------------------

double Vecteur2D::norme2() const
{
    double n;
    n = abscisse*abscisse+ordonnee*ordonnee;
    return n;
}

//----------------------------------------------------------------------------------------------------------------------

double Vecteur2D::norme() const
{
    double n;
    n = sqrt(abscisse*abscisse+ordonnee*ordonnee);
    return n;
}

//----------------------------------------------------------------------------------------------------------------------

Vecteur2D Vecteur2D::operator~() const
{
    //unitaire surcharge
    return (1/norme())*(*this);
}

//----------------------------------------------------------------------------------------------------------------------

ostream& operator<<(ostream& sortie, Vecteur2D const& vect)
{
    return vect.affiche(sortie);
}

//----------------------------------------------------------------------------------------------------------------------

Vecteur2D operator*(double a,  const Vecteur2D& vect)
{
    return vect*a ;
}

//----------------------------------------------------------------------------------------------------------------------

