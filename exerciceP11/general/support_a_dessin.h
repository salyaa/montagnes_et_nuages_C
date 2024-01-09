#pragma once

class MontagneGaussienne;
class ChampPotentiel;
class Ciel;
class Systeme;

class SupportADessin
{
 public:
  virtual ~SupportADessin() = default;
  // on ne copie pas les Supports
  SupportADessin(SupportADessin const&)            = delete; 
  SupportADessin& operator=(SupportADessin const&) = delete;
   // mais on peut les déplacer
  SupportADessin(SupportADessin&&)            = default; 
  SupportADessin& operator=(SupportADessin&&) = default;
  
  SupportADessin() = default; 

  /* Mettre ici toutes les méthodes nécessaires pour dessiner tous les
   * objets que l'on veut dessiner. Par exemple :
   *    virtual void dessine(Nounours const& a_dessiner) = 0;
   *    virtual void dessine(Voiture  const& a_dessiner) = 0;
   */

  virtual void dessine (Systeme const&)            = 0;
  virtual void dessine (MontagneGaussienne const&) = 0;
  virtual void dessine (Ciel const&)               = 0;

  //on a supprimé la méthode dessine(ChampPotentiel const&) car pour le graphisme, on n'a pas besoin de dessiner un champ de
  //potentiels mais uniquement une montagne et les nuages/le ciel.
};
