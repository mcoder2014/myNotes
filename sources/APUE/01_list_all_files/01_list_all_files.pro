TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

INCLUDEPATH +=\
    $$PWD/../3rd_part/apue_3e/include
LIBS +=\
    -L$$PWD/../3rd_part/apue_3e/lib -lapue

message("apue:$$PWD")
