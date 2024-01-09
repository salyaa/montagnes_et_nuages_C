#pragma once

#include "dessinable.h"
#include "supportadessin.h"


class TextViewer : public SupportADessin
{
public:
    TextViewer(std::ostream& flot_)
        : flot(flot_)
        {}
     virtual ~TextViewer() = default;

    //On ne copie pas les Supports...
    TextViewer(TextViewer const&)            = delete;
    TextViewer& operator=(TextViewer const&) = delete;

     //...mais on peut les déplacer!
    TextViewer(TextViewer&&)            = default;
    TextViewer& operator=(TextViewer&&) = default;

    void dessine (ChampPotentiel const& a_dessiner)     override;
    void dessine (MontagneGaussienne const& a_dessiner) override;
    void dessine ( Chaine_de_Montagnes const& a_dessiner)override;
    void dessine (Ciel const& a_dessiner) override;
    void dessine (Systeme const& a_dessiner) override;

private:
   std::ostream& flot;
};
