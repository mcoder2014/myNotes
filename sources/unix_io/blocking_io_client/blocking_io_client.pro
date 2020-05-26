TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin
TARGET = blocking_io_client

SOURCES += \
        main.cpp

LIBS += \ 
        -lpthread