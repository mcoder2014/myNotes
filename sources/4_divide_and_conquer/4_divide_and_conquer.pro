TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        divides.cpp \
        main.cpp

DESTDIR = ../bin
OBJECTS_DIR = ./tmp

INCLUDEPATH += \
    $$PWD/../SortAlgorithms

HEADERS += \
    divides.h

