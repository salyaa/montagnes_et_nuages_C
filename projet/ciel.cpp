#include <iostream>
#include <cmath>
#include "ciel.h"
#include "montagnegaussienne.h"
using namespace std;

//---------------------------------------------------constructeur-------------------------------------------------------------------
Ciel::Ciel( ChampPotentiel const& champ, unsigned int Nx, unsigned int Ny, unsigned int Nz, double lambda)
    : Boite3D(champ.get_Nx(), champ.get_Ny(), champ.get_Nz(), champ.get_lambda()),
      //on construit le ciel à la même taille que le champ potentiel
    cube(champ.get_Nx(), std::vector<std::vector<CubedAir>>(champ.get_Ny(),std::vector<CubedAir>(champ.get_Nz())))
      {
        //on récupère les vitesses des cubes d'air pour initialiser notre cube

        for(size_t i(0); i<Nx; ++i) {
            for(size_t j(0); j<Ny; ++j) {
                for(size_t k(0); k<Nz; ++k) {
                    cube[i][j][k].set_z(k*lambda);
                    cube[i][j][k].set_vitesse(champ.vitesse(i,j,k));
                }
            }
        }
    }
//------------------------------------------------------constructeur 2------------------------------------------------------------------------
Ciel::Ciel(unsigned int Nx, unsigned int Ny, unsigned int Nz, unsigned int lambda, double x)
        : Boite3D(Nx ,Ny, Nz, lambda)
        {
            for (size_t i(0); i<Nx; ++i) {
               for (size_t j(0); j<Ny; ++j) {
                  for (size_t k(0); k<Nz; ++k) {
                     cube[i][j][k].set_vitesse({x,0.0,0.0});
                  }
               }
            }
        }

//-------------------------------------------------------------------------------------------------------------------------------
 ostream& Ciel::affiche(ostream& sortie)const
{
     sortie<<"Un ciel"<<endl;
    for(size_t i(1); i<Nx-1; ++i) {
        for( size_t j(1); j<Ny-1; ++j) {
            for(size_t k(1); k<Nz-1; ++k) {
                sortie << i << " " << j << " " << k << " "
                    << cube[i][j][k].vitessecarre() << " "
                     << cube[i][j][k].enthalpie() << " " << cube[i][j][k].temperature()
                     << " " <<cube[i][j][k].pression() << " " <<cube[i][j][k].P_eau()
                     << " " <<cube[i][j][k].P_rose() << " " <<cube[i][j][k].etat_nuage()

                     << endl;

            }
        }
    }
    return sortie;
}
//" "<<cube[i][j][k].get_tho() <<
//---------------------------------------------------------------------------------------------------------------------------------
 vector<int> Ciel:: Precedent(double dt, int i, int j, int k){

    int a = trunc(-dt * cube[i][j][k].get_Vx()/ lambda);
    int b = trunc(-dt * cube[i][j][k].get_Vy()/ lambda);
    int c = trunc(-dt * cube[i][j][k].get_Vz()/ lambda);

    if(i+a< 0 or j+b<0 or k+c<0 or i+a>= Nx or j+b>=Ny or k+c>=Nz){ //test des conditions si l'on sort de la boite
        return vector <int> (3,0);
    } else{
        return vector <int> {i+a, j+b, k+c}; //on retourne les coordonnées du cube précédent
    }
 }

 void Ciel::deplace_nuage(){
     for( size_t i(0); i<Nx; ++i){
         for( size_t j(0); j<Ny; ++j){
             for( size_t k(0); k<Nz; ++k){
                 vector<int> precede= Precedent(i*Physique::dt,i,j,k);

                 unsigned int a= precede[0];
                 unsigned int b= precede[1];
                 unsigned int c= precede[2];

                 if(a!=i or b!=j or c!=k){//différentes variations du taux d'humidité selon les conditions imposées
                     if (cube[i][j][k].etat_nuage() and not (cube[a][b][c].etat_nuage())){
                         cube[i][j][k].hausse_taux_humidite(Physique::delta_prime);

                     }
                      else if (not (cube[i][j][k].etat_nuage()) and cube[a][b][c].etat_nuage()){
                         cube[i][j][k].baisse_taux_humidite(Physique::delta) ;
                     }
                     //if ( cube[i][j][k].pluie(Physique::pression_equilibre, Physique::delta_pluie)!=0.0){
                         //cube[i][j][k].baisse_taux_humidite(Physique::delta_pluie);
                    // }
                 }


             }
         }
     }
 }

 void Ciel::recalcule_ciel(){
     for(size_t i(1); i<Nx-1; ++i) {
       for(size_t j(1); j<Ny-1; ++j) {
         for(size_t k(1); k<Nz-1; ++k) {
            // cout<<i<<j<<k<<endl;
         cube[i][j][k].etat_nuage();
         cube[i][j][k].P_rose();
         cube[i][j][k].P_eau();
         cube[i][j][k].enthalpie();
         cube[i][j][k].temperature();
         cube[i][j][k].pression();
         }
       }
     }
 }
//---------------------------------------------------------------------------------------------------------------------------------
 vector<vector<unsigned int>> Ciel:: pluie_accumulee(  unsigned int i, unsigned int j){
     vector<vector<unsigned int>> cube_pluvieux({0});
     for(unsigned int i(1); i<Nx-1; ++i) {
       for(unsigned int  j(1); j<Ny-1; ++j) {
         for(unsigned int  k(1); k<Nz-1; ++k) {
          if (cube[i][j][k].etat_nuage()and cube[i][j][k].pluie(Physique:: pression_equilibre) ){
                cube_pluvieux[i][j]+= 1;
          }
         }
       }

     }
        return cube_pluvieux; //renvoie le nombre de cube de pluie au dessus de la coordonnée[i][j]
 }
 //----------------------------------------------------------------------------------------------------------------------------------------

 //-----------------------------------------------------------------------------------------------------------------------------
 /*void Ciel::deplace_nuage(){//testdebugg
     for( size_t i(16); i<17; ++i){
         for( size_t j(26); j<27; ++j){
             for( size_t k(1); k<3; ++k){
                 vector<int> precede= Precedent(Physique::dt,i,j,k);

                 unsigned int a= precede[0];
                 unsigned int b= precede[1];
                 unsigned int c= precede[2];

  cout<< a <<" "<< b <<" "<<c<< " "<<endl;
  cout<<i<<" "<<j<<" "<<" "<<k<<endl;

                 if(a!=i or b!=j or c!=k){
                     if (cube[i][j][k].etat_nuage() and not (cube[a][b][c].etat_nuage())){
                         cube[i][j][k].baisse_taux_humidite(Physique::delta);

                     }
                      else if (not (cube[i][j][k].etat_nuage()) and cube[a][b][c].etat_nuage()){
                         cube[i][j][k].hausse_taux_humidite(Physique::delta_prime) ;
                     }
                 }


             }
         }
     }
 }
*/


/* void Ciel::affiche() //test debugg
{
    for(size_t i(1); i<Nx-1; ++i) {
        for( size_t j(1); j<Ny-1; ++j) {
            for(size_t k(1); k<Nz-1; ++k) {
                cout  << i << " " << j << " " << k << " "
                     << cube[i][j][k].get_v() << " ";
                    cout<< cube[i][j][k].set_z(k*lambda)<<endl;
                     cout << cube[i][j][k].enthalpie() <<endl;
                cout<< cube[i][j][k].cte_Bernouilli() <<endl;
                //cout<< cube[i][j][k].get_z()<<endl;
            }
         }

      }
 }
*/
//----------------------------------------------------------------------------------------------------------------------

/* void Ciel:: dessine(){
     this->affiche();
 }
*/
