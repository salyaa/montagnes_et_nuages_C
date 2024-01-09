#pragma once

//pour éviter les dépendances circulaires:
class MontagneGaussienne;
class ChampPotentiel;
class Ciel;
class Systeme;
class Chaine_de_Montagnes;

class SupportADessin{ //classe abstraite
public:
  virtual ~SupportADessin() = default;

    //on ne copie pas les Supports...
    SupportADessin(SupportADessin const&)            = delete;
    SupportADessin& operator=(SupportADessin const&) = delete;

     //...mais on peut les déplacer
    SupportADessin(SupportADessin&&)            = default;
    SupportADessin& operator=(SupportADessin&&) = default;

    SupportADessin() = default;

    //objets à dessiner
    virtual void dessine(Systeme const&)            = 0;
    virtual void dessine(MontagneGaussienne const&) = 0;
    virtual void dessine(Ciel const&)               = 0;
    virtual void dessine(ChampPotentiel const&)     = 0;
    virtual void dessine (Chaine_de_Montagnes const&)=0;
};
