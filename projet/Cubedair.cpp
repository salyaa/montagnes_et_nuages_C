#include <iostream>
#include <cmath>
#include "Cubedair.h"
#include "ciel.h"



using namespace std;
using namespace Physique;

//initialisation des données pour les calculs
 double CubedAir:: p_inf (101325.0);
 double CubedAir:: v_inf ( 20.0);
 double CubedAir:: t_inf ( 284.5);

//-----------------------------------------------------------------------------------------------------------------------
 //norme au carré du vecteur vitesse
 double CubedAir::vitessecarre() const
 {
     return (vitesse[0]*vitesse[0]+vitesse[1]*vitesse[1]+vitesse[2]*vitesse[2]);
 }
 //----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

double CubedAir::enthalpie_infini() const
{
    return ((3.5*(R/M_air_sec))*t_inf);
}

//----------------------------------------------------------------------------------------------------------------------

double CubedAir::cte_Bernouilli() const
{
    return ((0.5*v_inf*v_inf)+enthalpie_infini());
}

//----------------------------------------------------------------------------------------------------------------------

void CubedAir::set_z(double Z){
    z=Z;

}

//----------------------------------------------------------------------------------------------------------------------

void CubedAir::set_vitesse(vector<double> V){
    vitesse[0]=V[0];
    vitesse[1]=V[1];
    vitesse[2]=V[2];
}



bool CubedAir::etat_nuage() const{

    if (P_eau()>P_rose()){
        return true;
    }else{
        return false;
    }
}

//----------------------------------------------------------------------------------------------------------------------

double CubedAir::P_eau()const{
    double p_eau;
    p_eau=((tho))/((M_eau/M_air_sec)+tho)* pression();
    return p_eau;
}

//----------------------------------------------------------------------------------------------------------------------

double CubedAir::P_rose() const
{
    return(P_ref*exp(13.96 -(5208/temperature())));
}

//----------------------------------------------------------------------------------------------------------------------

double CubedAir::temperature()const{
    double t;
    t=((2.0* M_air_sec)/(7.0*R))*enthalpie();
    return t;
}

//----------------------------------------------------------------------------------------------------------------------

double CubedAir::pression() const{
    double P;
    P= p_inf* pow(t_inf,(-3.5))*pow(temperature(),3.5);
    return P;
}

//----------------------------------------------------------------------------------------------------------------------

double CubedAir::enthalpie()const
{
    return (cte_Bernouilli()-g*z-0.5*vitessecarre());
}

//----------------------------------------------------------------------------------------------------------------------
//on accède aux vitesses selon chaque coordonnées
double CubedAir::get_Vx() const{
    return vitesse[0];
}

double CubedAir::get_Vy() const{
    return vitesse[1];
}

double CubedAir::get_Vz() const{
    return vitesse[2];
}
//-------------------------------------------variation du taux d'humidité------------------------------------------------------------------------------------
void CubedAir:: baisse_taux_humidite( double delta){
    tho= tho - tho*delta;
}

void CubedAir:: hausse_taux_humidite(double delta_prime){
    tho= tho + tho*delta_prime;
}
//----------------------------------------------pluie-----------------------------------------------------------------------------

bool CubedAir:: pluie(double pression_equilibre) const{
    if(abs(pression_equilibre-P_eau())<20) {
        return true;
    }
    else {return false;}

}
//----------------------------------------------------------------------------------------------------------------------------------------





/* double CubedAir::get_z() const// debugging

 {
     return z;
 }
 */

/*double CubedAir:: get_tho() const{
    return tho;
}
*/
/*double CubedAir:: pluie(double pression_equilibre, double delta_pluie) const{
    double nouveau_taux(0.0);
    double eau;
    if(pression_equilibre < P_eau()) {
     nouveau_taux= tho-tho*delta_pluie;
    }
    eau= tho-nouveau_taux;

    return eau; //quantité de pluie tombée
}
*/
