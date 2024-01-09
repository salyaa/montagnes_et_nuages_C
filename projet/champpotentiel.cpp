#include <iostream>
#include <vector>
#include "champpotentiel.h"
#include <iomanip>
using namespace std;


//---------------------------------------------------Constructeur----------------------------------------------------------------------------

ChampPotentiel::ChampPotentiel(unsigned int Nx, unsigned int Ny, unsigned int Nz,  double echant, double x_, double y_,
                                double h_, double sigma1, double sigma2)
        :Boite3D(Nx, Ny, Nz,echant),
         collection3D (Nx,vector < vector < Potentiel > > (Ny, vector < Potentiel > (Nz))),
         M(MontagneGaussienne(x_,y_,h_,sigma1,sigma2))
        {}

//-------------------------------------------------------------------------------------------------------------------------------------------

void ChampPotentiel::initialise(double const& v_inf, MontagneGaussienne const& montagne)
{
    for(size_t i(0); i<Nx; ++i) {
        for(size_t j(0); j<Ny; ++j) {
            for(size_t k(0); k<Nz; ++k) {
                //initialisation de (A2/ijk, A3/ijk)
                collection3D[i][j][k].setPotentiel((-v_inf*k*lambda)*0.5,(v_inf*(lambda*(j-(Ny-1)*0.5))*0.5));
                collection3D[i][j][k].setLaplacien(0.0, 0.0);
                //mettre à (0,0) sous la montagne
                if (k<montagne.altitude(i,j)) {
                    collection3D[i][j][k].setPotentiel(0.0, 0.0);
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void ChampPotentiel::calcul_laplaciens() {
    for (size_t i(1); i<Nx-1; ++i) {
        for (size_t j(1); j<Ny-1; ++j) {
            for (size_t k(1); k<Nz-1; ++k) {
                if (k< M.altitude (i,j)){ //condition des laplaciens sous la montagne
                    collection3D[i][j][k].setLaplacien(0.0, 0.0);
                } else {
                    collection3D[i][j][k].setLaplacien(
                            (collection3D[i-1][j][k].getPotentiel()).get_x() + (collection3D[i][j-1][k].getPotentiel()).get_x()
                             + (collection3D[i][j][k-1].getPotentiel()).get_x() - 6*(collection3D[i][j][k].getPotentiel()).get_x()
                             + (collection3D[i+1][j][k].getPotentiel()).get_x() + (collection3D[i][j+1][k].getPotentiel()).get_x()
                             + (collection3D[i][j][k+1].getPotentiel()).get_x(),
                            (collection3D[i-1][j][k].getPotentiel()).get_y() + (collection3D[i][j-1][k].getPotentiel()).get_y()
                             + (collection3D[i][j][k-1].getPotentiel()).get_y() - 6*(collection3D[i][j][k].getPotentiel()).get_y()
                             + (collection3D[i+1][j][k].getPotentiel()).get_y() + (collection3D[i][j+1][k].getPotentiel()).get_y()
                             + (collection3D[i][j][k+1].getPotentiel()).get_y());
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void ChampPotentiel::affichePot() const
{
    for(size_t i(0); i < Nx; ++i) {
        for(size_t j(0); j < Ny; ++j) {
            for (size_t k(0); k < Nz; ++k) {
                cout << i << " " << j << " " << k << " " <<std::setprecision(14)<< collection3D[i][j][k].getPotentiel() << endl;
            }
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------------------------------

void ChampPotentiel::afficheLap() const
{
    for(size_t i(1); i < Nx-1; ++i) {
        for(size_t j(1); j < Ny-1; ++j) {
            for (size_t k(1); k < Nz-1; ++k) {
                cout << i << " " << j << " " << k << " " <<std::setprecision(14)<< collection3D[i][j][k].getLaplacien() << endl;
            }
        }
    }
}


//-------------------------------------------------------------------------------------------------------------------------------------------

double ChampPotentiel::erreur()
{
    double erreur(0.0);
    for(size_t i(0); i<Nx; ++i) {
        for(size_t j(0); j<Ny; ++j) {
            for(size_t k(0); k<Nz; ++k) {
                erreur += (collection3D[i][j][k].getLaplacien()).norme2();
            }
        }
    }
    return erreur;
}

//-------------------------------------------------------------------------------------------------------------------------------------------

void ChampPotentiel::iteration()
{
    for(size_t i(0); i<Nx; ++i) {
        for(size_t j(0); j<Ny; ++j) {
            for(size_t k(0); k<Nz; ++k) {
                collection3D[i][j][k].setPotentiel (collection3D[i][j][k].getPotentiel().get_x() + eps*collection3D[i][j][k].getLaplacien().get_x(),
                                                    collection3D[i][j][k].getPotentiel().get_y() + eps*collection3D[i][j][k].getLaplacien().get_y());
            }
        }
    }
    //on doit recalculer les laplaciens car on modifie les potentiels et les laplaciens sont exprimés en fonction d'eux
    calcul_laplaciens();
}

//-------------------------------------------------------------------------------------------------------------------------------------------
//DECOMMENTER DANS CETTE MÉTHODE SI L'ON VEUT FAIRE AFFICHER L'ERREUR ET LA CONVERGENCE
void ChampPotentiel::resolution(double const& seuil, unsigned int const& nb_ite, bool verbeuse)
{
    unsigned int r(0);

    while((erreur()>=seuil) and (r<=nb_ite)){
        iteration();
        if(verbeuse)
        {
            for(size_t i(0); i<Nx; ++i) {
                for(size_t j(0); j<Ny; ++j) {
                    for(size_t k(0); k<Nz; ++k) {
                        cout << collection3D[i][j][k].getPotentiel() << " "
                             << collection3D[i][j][k].getLaplacien() << endl;
                    }
                }
            }
        }
        r+=1;
       //DECOMMENTER ICI POUR LE TEST ERREUR:

       //cout << r << " " << erreur() << endl;
    }
}


//-------------------------------------------------------------------------------------------------------------------------------------------

vector<double> ChampPotentiel:: vitesse(unsigned int const& i, unsigned int const& j, unsigned int const& k) const
{
    vector<double> retour(3,0);
    if(i==0 or j==0 or k==0 or i==Nx-1 or j==Ny-1 or k==Nz-1) {
        retour = {v_,0.0,0.0};
    } else {
        double x = collection3D[i][j+1][k].getPotentiel().get_y() - collection3D[i][j-1][k].getPotentiel().get_y()
                   -collection3D[i][j][k+1].getPotentiel().get_x() + collection3D[i][j][k-1].getPotentiel().get_x();
        double y = -collection3D[i+1][j][k].getPotentiel().get_y() + collection3D[i-1][j][k].getPotentiel().get_y();
        double z = collection3D[i+1][j][k].getPotentiel().get_x() - collection3D[i-1][j][k].getPotentiel().get_x();

        x = x/(2*lambda);
        y = y/(2*lambda);
        z = z/(2*lambda);

        retour = {x,y,z};
    }
    return retour;
}

//-------------------------------------------------------------------------------------------------------------------------------------------

double ChampPotentiel::norme3D_2(vector<double> test) const { // calcul de la norme au carré
    double t;
    t = test[0]*test[0]+test[1]*test[1]+test[2]*test[2];
    return t;
}

//------------------------------------------------------------------------------------------------------------------------------------
void ChampPotentiel::affiche()const
{
    for (size_t i(0); i < Nx; ++i) {
        for (size_t j(0); j < Ny; ++j) {
            for (size_t k(0); k < Nz; ++k) {
                cout << i << " " << j << " " << k << " " <<std::setprecision(14)<< collection3D[i][j][k].getPotentiel()
                     << " " << vitesse(i,j,k)[0] << " " << vitesse(i,j,k)[1] << " "
                     << vitesse(i,j,k)[2] << " " << norme3D_2(vitesse(i,j,k)) << endl;
            }
            cout << endl;
        }
        cout << endl;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
ostream& ChampPotentiel:: affiche_systeme(ostream& sortie)const{
    sortie << "un champ de potentiels : " << endl;
    sortie << "Nx="  << Nx << " Ny" << Ny
           << " Nz=" << Nz << endl;
    //sortie << "Lx="  << Lx << " Ly=" << Ly
           //<< " Lz=" << Lz << endl;
    sortie << "lambda = " << lambda << endl;
    sortie << "valeurs:" << endl;
    sortie << "### comme testPotentiel2.dat de l'exercice P6 : " << endl;
    affichePot();

    return sortie;
}
//------------------------------------------------------------------------------------------------------------------------------
/*void ChampPotentiel::affiche()//test debugg
{
    for (size_t i(1); i < 3; ++i) {
        for (size_t j(1); j < 3; ++j) {
            for (size_t k(1); k < 3; ++k) {
                cout<< i <<" "<< j <<" "<< k <<" "<<(1/(2*lambda))<<"*"<<std::setprecision(14)<<-(collection3D[i+1][j][k].getPotentiel()).get_y()<<endl;
                cout<< "+"<<(collection3D[i-1][j][k].getPotentiel()).get_y() <<endl;
                cout<<collection3D[i][j][k].getPotentiel() <<endl;
                 cout<< vitesse(i,j,k)[0] << endl;
                 cout <<vitesse(i,j,k)[1]<< endl;
                 cout<<vitesse(i,j,k)[2]<<endl;

                cout<<norme3D_2(vitesse(i,j,k)) <<endl;
            }
        }
    }
}
*/
//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

/*vector<double> ChampPotentiel::vitesse(unsigned int const& i, unsigned int const& j, unsigned int const& k)
{
    vector<double> v(3, 0.0);
    //coordonnées de la vitesse du vent en (x_i, y_j, z_k):
    if((i==0) or (j==0) or (k==0)){
        v[0]=0.0;
        v[1]=0.0;
        v[2]=0.0;
    } else {
        v[0] = (1/(2*lambda))*((collection3D[i][j+1][k].getPotentiel()).get_y()-(collection3D[i][j-1][k].getPotentiel()).get_y()
                                -(collection3D[i][j][k+1].getPotentiel()).get_x()+(collection3D[i][j][k-1].getPotentiel()).get_x());
        v[1] = (1/(2*lambda))*(-(collection3D[i+1][j][k].getPotentiel()).get_y()+(collection3D[i-1][j][k].getPotentiel()).get_y());
        v[2] = (1/(2*lambda))*((collection3D[i+1][j][k].getPotentiel()).get_x()-(collection3D[i-1][j][k].getPotentiel()).get_x());
    }
    return v;
}*/
//------------------------------------------------------------------------------
/*void ChampPotentiel::affichePot()// test debugg
{
    for(size_t i(2); i < 3; ++i) {
        for(size_t j(14); j < 15; ++j) {
            for (size_t k(0); k < 1; ++k) {
                cout << i << " " << j << " " << k << " " <<std::setprecision(14)<< collection3D[i][j][k].getPotentiel() << endl;
            }
        }
    }
}
*/
//-----------------------------------------------------------------------------------------------------------------------
/*void ChampPotentiel::afficheLap() //test debugging
{
    for(size_t i(2); i < 3; ++i) {
        for(size_t j(14); j < 15; ++j) {
            for (size_t k(1); k < 2; ++k) {
                cout << i << " " << j << " " << k << "en x " <<std::setprecision(14)<<(collection3D[i-1][j][k].getPotentiel()).get_x()<<endl;
                cout <<"+"<< (collection3D[i][j-1][k].getPotentiel()).get_x() <<endl;
                cout<< "+"<< (collection3D[i][j][k-1].getPotentiel()).get_x()<<endl;
                cout<< "-"<< - (6*(collection3D[i][j][k].getPotentiel()).get_x())<<endl;
                cout<< "+"<< (collection3D[i+1][j][k].getPotentiel()).get_x()<< endl;
                cout<<"+" << (collection3D[i][j+1][k].getPotentiel()).get_x()<<endl;
                cout<<"+" << (collection3D[i][j][k+1].getPotentiel()).get_x()<<endl;
                cout<< "en y"<<(collection3D[i-1][j][k].getPotentiel()).get_y()<<endl;
                cout<<"+" << (collection3D[i][j-1][k].getPotentiel()).get_y()<<endl;

                cout<<"+" <<(collection3D[i][j][k-1].getPotentiel()).get_y()<<endl;

                cout<<"-"<<- (6*(collection3D[i][j][k].getPotentiel()).get_y())<<endl;
                cout<<"+"<<(collection3D[i+1][j][k].getPotentiel()).get_y()<<endl;
                cout<<"+"<< (collection3D[i][j+1][k].getPotentiel()).get_y()<<endl;
                cout<<"+"<< (collection3D[i][j][k+1].getPotentiel()).get_y()<<endl;
                cout<<"le laplacien"<< collection3D[i][j][k].getLaplacien() << endl;
            }
        }
    }
}
*/
