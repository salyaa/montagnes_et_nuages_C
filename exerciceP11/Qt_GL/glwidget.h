#pragma once

#include <QOpenGLWidget>    // Classe pour faire une fenêtre OpenGL
#include <QTime>            // Classe pour gérer le temps
#include "vue_opengl.h"
#include "systeme.h"

class GLWidget : public QOpenGLWidget
/* La fenêtre hérite de QOpenGLWidget ;
 * les événements (clavier, souris, temps) sont des méthodes virtuelles à redéfinir.
 */
{
public:
  GLWidget(MontagneGaussienne M, ChampPotentiel champ, QWidget* parent = nullptr)
   : QOpenGLWidget(parent), systeme(champ, M)
   {}

  virtual ~GLWidget() = default;

private:
  // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  // Méthodes de gestion d'évènements
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void timerEvent(QTimerEvent* event)  override;

  // Méthodes de gestion interne
  void pause();

  // Vue : ce qu'il faut donner au système pour qu'il puisse se dessiner sur la vue
  VueOpenGL vue;

  // Timer
  int timerId;
  // pour faire évoluer les objets avec le bon "dt"
  QTime chronometre;
  // objets à dessiner, faire évoluer
  Systeme systeme;
};
