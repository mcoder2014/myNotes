TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin

TARGET = epoll_server

SOURCES += \
        main.cpp
