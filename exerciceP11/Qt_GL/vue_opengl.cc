#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "systeme.h"
#include "champ_potentiel.h"
#include "montagne_gaussienne.h"
#include "ciel.h"


// ======================================================================
void VueOpenGL::dessine(Systeme const& a_dessiner)
{
    dessine(a_dessiner.get_montagne());
    dessine(a_dessiner.get_ciel());
    //nos mouvement de nuages (ni de pluie) ne sont pas bons
}

// ======================================================================
void VueOpenGL::dessine(MontagneGaussienne const& a_dessiner)
{
    QMatrix4x4 matrice;

    for (size_t i(0); i<30; ++i) {
        for (size_t j(0); j<30; ++j) {
            for (size_t k(0); k<30; ++k) {
                if( k <= a_dessiner.altitude(i, j) ) { //on met "<=", et pas "<", pour avoir le sol sous la montagne
                    matrice.setToIdentity();
                    matrice.translate(i, j, k);
                    matrice.scale(20./29.);
                    //on peut laisser scale a 1.0 : dans ce cas là mettre un facteur 2 devant i, j, k dans matrice.translate
                    //pour que les boites se positionnent bien les unes en fonction des autres
                    dessineCube_Montagne(matrice);
                }
            }
        }
    }
}

// ======================================================================
void VueOpenGL::dessine(Ciel const& a_dessiner)
{
    QMatrix4x4 matrice;

    for (size_t i(0); i<30; ++i) {
        for (size_t j(0); j<30; ++j) {
            for (size_t k(0); k<30; ++k) {
                if(a_dessiner.nuage(i, j, k)){
                    matrice.setToIdentity();
                    matrice.translate(i, j, k+3); //on met k+3 pour que les nuages soient au-dessus du sommet de la montagne
                    matrice.scale(20./29.);
                    dessineCube_Nuage(matrice);
                    if(a_dessiner.pluie(i,j,k)){
                        matrice.setToIdentity();
                        matrice.translate(i, j, k);
                        matrice.scale(0.2); //on fait de plus petits cubes pour la pluie
                        dessineCube_Pluie(matrice);
                  }
               }
            }
        }
    }
}

// ======================================================================
void VueOpenGL::init()
{
  /* Initialise notre vue OpenGL.
   * Dans cet exemple, nous créons et activons notre shader.
   *
   * En raison du contenu des fichiers *.glsl, le shader de cet exemple
   * NE permet QUE de dessiner des primitives colorées
   * (pas de textures, brouillard, reflets de la lumière ou autres).
   *
   * Il est séparé en deux parties VERTEX et FRAGMENT.
   * Le VERTEX :
   * - récupère pour chaque sommet des primitives de couleur (dans
   *     l'attribut couleur) et de position (dans l'attribut sommet)
   * - multiplie l'attribut sommet par les matrices 'vue_modele' et
   *     'projection' et donne le résultat à OpenGL
   *   - passe la couleur au shader FRAGMENT.
   *
   * Le FRAGMENT :
   *   - applique la couleur qu'on lui donne
   */

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  /* Identifie les deux attributs du shader de cet exemple
   * (voir vertex_shader.glsl).
   *
   * L'attribut identifié par 0 est particulier, il permet d'envoyer un
   * nouveau "point" à OpenGL
   *
   * C'est pourquoi il devra obligatoirement être spécifié et en dernier
   * (après la couleur dans cet exemple, voir plus bas).
   */

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);

  // Activation du shader
  prog.bind();

  /* Activation du "Test de profondeur" et du "Back-face culling"
   * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
   * partielement caché par d'autres objets.
   *
   * Le Back-face culling consiste à ne dessiner que les face avec ordre
   * de déclaration dans le sens trigonométrique.
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition()
{
  //on a changé la position initiale pour qu'on voit mieux la montagne, les nuages et la pluie dès le début
  matrice_vue.setToIdentity();
  matrice_vue.translate(-15.0, -15.0, -25.0);
  matrice_vue.rotate(90.0, -1.0, 0.0, 0.0);
  //matrice_vue.rotate(45.0, 0.0, 0.0, -1.0);
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::dessineCube_Montagne (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(CouleurId, 0.37, 0.18, 0.0);//marron
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(CouleurId, 0.33, 0.14, 0.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  // face coté Y = +1
  prog.setAttributeValue(CouleurId, 0.37, 0.18, 0.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  // face coté Y = -1
  prog.setAttributeValue(CouleurId, 0.33, 0.14, 0.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  // face coté Z = +1
  prog.setAttributeValue(CouleurId, 0.33, 0.14, 0.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  // face coté Z = -1
  prog.setAttributeValue(CouleurId, 0.38, 0.18, 0.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  //on a mis différentes teintes de marron pour que la montagne soit plus visible
  //et qu'on voit mieux les différents cubes
  glEnd();
}

// ======================================================================
void VueOpenGL::dessineCube_Nuage(QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // blanc
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  // face coté Y = +1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  // face coté Y = -1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  // face coté Z = +1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  // face coté Z = -1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  glEnd();
}

void VueOpenGL::dessineCube_Pluie (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  // face coté Y = +1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  // face coté Y = -1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  // face coté Z = +1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  // face coté Z = -1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  //on a mis différentes teintes de marron pour que la montagne soit plus visible
  //et qu'on voit mieux les différents cubes
  glEnd();
}

