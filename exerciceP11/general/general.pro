TEMPLATE = lib

CONFIG = staticlib
QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH = ../text

SOURCES = vecteur2d.cpp \
          montagne_gaussienne.cpp \
          potentiel.cpp \
          champ_potentiel.cpp \
          cube_d_air.cpp \
          ciel.cpp \
          systeme.cc \
          chaine_de_montagnes.cpp \
    boite3d.cpp

HEADERS += \
    vecteur2d.h \
    boite3d.h \
    constante.h \
    montagne_gaussienne.h \
    supermontagne.h \
    chaine_de_montagnes.h \
    potentiel.h \
    champ_potentiel.h \
    ciel.h \
    dessinable.h \
    support_a_dessin.h \
    cube_d_air.h \
    systeme.h
