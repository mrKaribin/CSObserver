#-------------------------------------------------
#
# Project created by QtCreator 2019-04-24T15:06:58
#
#-------------------------------------------------

QT       += core gui sql network webengine webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CSAnalisis
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        delphinosyncro.cpp \
        instruments.cpp \
        main.cpp \
        mainwindow.cpp \
        matches.cpp \
        matchinfo.cpp \
        teaminfo.cpp \
        teams.cpp \
        tournaments.cpp \
        winbody.cpp

HEADERS += \
        delphinosyncro.h \
        instruments.h \
        mainwindow.h \
        matches.h \
        matchinfo.h \
        teaminfo.h \
        teams.h \
        tournaments.h \
        winbody.h


