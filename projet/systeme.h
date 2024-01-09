#pragma once

#include "champpotentiel.h"
#include "ciel.h"
#include "dessinable.h"
#include "chainedemontagnes.h"
#include "supportadessin.h"
#include "montagnegaussienne.h"
#include "text_viewer.h"


class Systeme : public Dessinable { //le systeme est une dessinable
public:

    //constructeur
    Systeme(ChampPotentiel const& champ , MontagneGaussienne const& mont)
        : champ(new ChampPotentiel(champ)),mont(new MontagneGaussienne(mont)),
          ciel_bleu(champ, champ.get_Nx(), champ.get_Ny(), champ.get_Nz(), champ.get_lambda())
        {}

    //constructeur de copie par defaut n'a pas besoin d'etre modifié car on utilise des unique_ptr

    //destructeur
    ~Systeme() = default;

    //méthodes
    virtual void dessine_sur(SupportADessin& support) override
    { support.dessine(*this); }

    std::ostream& affiche2(std::ostream& sortie) const;// affichage les données comme dans l'exemple montrant de quoi est constitué un système
    std::ostream& affiche( std::ostream& sortie) const; //affichage juste les données du ciel comme voulu pour vérifier l'évolution du système

    void evolue(double dt);
    void demarre(double dt, unsigned int i);

    //attributs:
private:

    std::unique_ptr<ChampPotentiel> champ;
    std::unique_ptr <MontagneGaussienne> mont;
    Ciel ciel_bleu;
};

//surcharge de l'opérateur <<
std::ostream& operator<<(std::ostream& sortie, Systeme const& systm);

//-------------------------------------------------------------------------------------------------------------------------------
//void ajouter_dessinable(std::unique_ptr<Dessinable> nouveau);
//objets_a_dessiner chef_doeuvre;
//void affiche()const;
