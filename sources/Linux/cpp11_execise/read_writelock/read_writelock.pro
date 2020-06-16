TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin

SOURCES += \
        main.cpp

unix {
LIBS += \
    -lpthread
}
