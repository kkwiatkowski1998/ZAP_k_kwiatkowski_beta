TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += warn_off

SOURCES += main.cpp \
    mech.cpp \
    menu.cpp \
    plansza.cpp

HEADERS += \
    mech.h \
    menu.h \
    plansza.h
