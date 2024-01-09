
#pragma once
#include "constante.h"
#include "champpotentiel.h"
#include <vector>


using namespace Physique;

//-------------------------------------------Classe Cube d'air----------------------------------------------------------

class CubedAir {
public:
    //constructeur :
    CubedAir(double tho=8e-3, std::vector<double> v_ = {0.0,0.0,0.0})
    : tho(tho), vitesse(v_)
    {}

    //méthodes:
    double enthalpie_infini() const;
    double cte_Bernouilli() const;
    double get_tho() const {return tho;}//test debugg

    void set_z(double z);         //pour accéder et modifier la hauteur z
    void set_vitesse(std::vector<double> V);

    double vitessecarre() const; //donne la norme au carré de la vitesse du vent

    //pour accéder facilemnent aux coordonnées de la vitesse
    double get_Vx() const;
    double get_Vy() const;
    double get_Vz() const;


    double enthalpie() const;     //calcul de l'enthalpie par unité de masse
    double temperature()const;         //calcul de la température en Kelvin en fonction de l'enthalpie
    double pression() const;            //calcul de la pression en Pascal
    double P_eau()const;               //calcul de la pression partielle de vapeur d'eau
    double P_rose() const;              //calcul de la pression de vapeur saturante d'eau
    bool   etat_nuage() const;          //pour tester si on a un nuage ou pas en fonction de la position

    void baisse_taux_humidite(double delta);
    void hausse_taux_humidite (double delta_prime);
    //double pluie(double pression_equilibre, double delta_pluie)const; //renvoie la quantité de pluie tombée
    bool pluie(double pression_equilibre) const;


private:
    static double p_inf;          //en Pascal Pa
    static double v_inf;          //en m/s
    static double t_inf;          //en Kelvin K
    double tho;                   //rapport de mélange de vapeur d'eau (taux d'humidité)
    std::vector<double> vitesse;  //vitesse du vent: tableau de double
    double z;                       //hauteur


};

//----------------------------------------------------------------------------------------------------------------------
//debugging
//double get_tho() const;
// double get_z() const;
