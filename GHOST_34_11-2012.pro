#-------------------------------------------------
#
# Project created by QtCreator 2016-11-24T19:18:30
#
#-------------------------------------------------

QT += core gui

CONFIG += c++1z strict_c++


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GHOST_34_11-2012
TEMPLATE = app


gcc:QMAKE_CXXFLAGS += -pedantic-errors
gcc:QMAKE_CXXFLAGS_DEBUG += -fsanitize=address,undefined
gcc:QMAKE_LFLAGS_DEBUG += -fsanitize=address,undefined

SOURCES += main.cpp\
        mainwindow.cpp \
    hash.cpp

HEADERS  += mainwindow.hpp \
    hash.hpp

FORMS    += mainwindow.ui


LIBS += -lgcrypt -lgpg-error
