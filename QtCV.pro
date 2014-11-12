#-------------------------------------------------
#
# Project created by QtCreator 2014-11-09T16:06:04
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCV
TEMPLATE = app

CONFIG += opengl

SOURCES += main.cpp\
    window.cpp \
    glwidget.cpp \
    rrt.cpp \
    zgraph.c

HEADERS  += window.h \
    glwidget.h \
    rrt.h \
    zgraph.h

FORMS    += window.ui

QMAKE_CXXFLAGS += -std=c++11

unix:!macx: LIBS += -L/usr/local/lib/ -lczmq

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libczmq.a

unix:!macx: LIBS += -L/usr/local/lib/ -lzmq

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libzmq.a

LIBS += `pkg-config opencv --libs`
LIBS += -lglut

INCLUDEPATH += /usr/include/opencv
CONFIG += link_pkgconfig
PKGCONFIG += opencv

