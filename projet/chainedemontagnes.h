#pragma once
#include"supermontagne.h"
#include"montagnegaussienne.h"
#include <vector>
#include <memory>

typedef std:: vector<std:: unique_ptr<SuperMontagne>> collectionmontagne; //on utilise les unique_ptr pour éviter d'avoir à s'occuper des delete

class Chaine_de_Montagnes: public SuperMontagne
                           ,public Dessinable
{
  public:

    //constructeur:
    Chaine_de_Montagnes( std::vector <SuperMontagne*> const& chaine );
    Chaine_de_Montagnes()=default;

    //destructeur:
     ~Chaine_de_Montagnes()=default;

    //méthodes:

    void ajouter_montagne(SuperMontagne* mont);
    double altitude(double x, double y)const override;
    void affiche() const override;
    virtual void dessine_sur(SupportADessin& support) override
         { support.dessine(*this); }

    //attribut:
 private:
    collectionmontagne chaine;

    
};


