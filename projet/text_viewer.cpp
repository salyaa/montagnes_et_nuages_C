#include "text_viewer.h"
#include "systeme.h"

using namespace std;

//---------------------------------------------------------------------------------------------------------------------------------------------------------

void TextViewer::dessine(ChampPotentiel const& a_dessiner)
{
    flot << "Le champ de potentiels de présente de la manière suivante : " << endl;
    a_dessiner.affiche_systeme(flot);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

void TextViewer::dessine(MontagneGaussienne const& a_dessiner)
{
    flot << "La montagne se présente de la manière suivante : " << endl;
    a_dessiner.affiche_systeme(flot);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

void TextViewer::dessine( Ciel const& a_dessiner)
{
    flot << "Le ciel se présente de la manière suivante : " << endl;
    a_dessiner.affiche(flot);
}

void TextViewer::dessine( Chaine_de_Montagnes const& a_dessiner)
{
    flot << "La chaine de montagnes se présente de la manière suivante : " << endl;
    a_dessiner.affiche();
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------

void TextViewer::dessine(Systeme const&  a_dessiner)
{
    flot << "Le système se présente de la manière suivante : " << endl;
    a_dessiner.affiche2(flot);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------
