#pragma once


class SuperMontagne// on crée une classe abstraite, mieux que si chaine de montagnes hérite de montagne Gaussienne, celle ci possédant plein d'attributs inutiles pour la classe chaines de montagnes
{

public:
 //méthodes

     virtual double altitude(double x, double y) const =0;
     virtual void affiche()const=0;

//destructeur
  virtual ~SuperMontagne()=default;

};
