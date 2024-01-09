QT += core gui opengl widgets
QMAKE_CXXFLAGS += -std=c++11

win32:LIBS += -lopengl32


TARGET = exerciceP11_gl

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_qt_gl.cc \
    glwidget.cc \
    vue_opengl.cc

HEADERS += \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    ../general/dessinable.h \
    ../general/support_a_dessin.h \
    ../general/systeme.h \
    ../general/ciel.h \
    ../general/montagne_gaussienne.h \
    ../general/vecteur2d.h \
    ../general/constante.h \
    ../general/champ_potentiel.h

RESOURCES += \
    resource.qrc
