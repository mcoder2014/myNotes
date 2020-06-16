TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin

SOURCES += \
        main.cpp \
    singleinstance.cpp \
    singleinstanceii.cpp \
    singleinstanceiii.cpp \
    singleinstanceiv.cpp

HEADERS += \
    singleinstance.h \
    singleinstanceii.h \
    singleinstanceiii.h \
    singleinstanceiv.h

unix {
LIBS += \
    -lpthread
}
