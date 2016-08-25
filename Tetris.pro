TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    Game.cpp \
    Block.cpp

HEADERS += \
    Common.h \
    Tetris.h
LIBS += \
    -lglut \
    -lGLU \
    -lGL

