#pragma once

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "support_a_dessin.h"


class VueOpenGL : public SupportADessin {
public:
  // méthodes de dessin héritées de SupportADessin
  virtual void dessine(Systeme const& a_dessiner)              override;
  virtual void dessine(MontagneGaussienne const& a_dessiner)   override;
  virtual void dessine(Ciel const& a_dessiner)                 override;

  // méthodes de (ré-)initialisation
  void init();
  void initializePosition();

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);
  
  // méthodes utilitaire offerte pour simplifier
  // (on a besoin de deux méthodes dessineCube pour pouvoir faire 2 couleurs différentes)
  void dessineCube_Montagne(QMatrix4x4 const& point_de_vue = QMatrix4x4());
  void dessineCube_Nuage(QMatrix4x4 const& point_de_vue = QMatrix4x4());
  void dessineCube_Pluie(QMatrix4x4 const& point_de_vue = QMatrix4x4());


private:
  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;
  // Caméra
  QMatrix4x4 matrice_vue;
};
