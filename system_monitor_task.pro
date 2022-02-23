TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += sql

SOURCES += \
        dbmanager.cpp \
        main.cpp \
        systemmonitor.cpp

HEADERS += \
    dbmanager.h \
    systemmonitor.h
