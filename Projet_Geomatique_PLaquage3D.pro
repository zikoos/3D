#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T09:10:51
#
#-------------------------------------------------

QT       += core gui opengl xml
LIBS += -lQGLViewer -lassimp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet_Geomatique_PLaquage3D
TEMPLATE = app


SOURCES += main.cpp\
        interface.cpp \
    fichier.cpp \
    objet.cpp \
    viewer.cpp \
    point.cpp \
    mnt.cpp \
    global.cpp \
    plaquage.cpp \
    plan.cpp

HEADERS  += interface.h \
    fichier.h \
    objet.h \
    viewer.h \
    point.h \
    mnt.h \
    global.h \
    plaquage.h \
    plan.h

FORMS    += interface.ui
