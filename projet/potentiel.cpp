#include <iostream>
#include <vector>
#include "Potentiel.h"
using namespace std;

//-----------------------------------------------------------------------------------------------------------------------------------------

void Potentiel::setPotentiel(double x, double y)
{
    potentiel.set_coord(x,y);
}

//-----------------------------------------------------------------------------------------------------------------------------------------


void Potentiel::setLaplacien(double x, double y)
{
    laplacien.set_coord(x,y);
}

//-----------------------------------------------------------------------------------------------------------------------------------------
