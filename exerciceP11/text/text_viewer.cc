
#include <iostream>
#include "text_viewer.h"
#include "systeme.h"


//---------------------------------------------------------------------------------------------------------------------------------------------------------

void TextViewer::dessine(MontagneGaussienne const& a_dessiner)
{
    flot << "La montagne se présente de la manière suivante : " << std::endl;
    a_dessiner.affiche();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

void TextViewer::dessine(Ciel const& a_dessiner)
{
    flot << "Le ciel se présente de la manière suivante : " << std::endl;
    a_dessiner.affiche(flot);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

void TextViewer::dessine(Systeme const&  a_dessiner)
{
    flot << "Le système se présente de la manière suivante : " << std::endl;
    a_dessiner.affiche(flot);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
