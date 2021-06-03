#-------------------------------------------------
#
# Project created by QtCreator 2021-05-27T08:06:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtictactoe
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
        src/main.cpp \
        src/mainwindow.cpp \
        src/brick.cpp \
        src/boardbase.cpp \
        src/gamescene.cpp \
        src/game.cpp \
        src/playeractor.cpp \
        src/botactor.cpp \
        src/endview.cpp \
        src/actor.cpp \
        src/newseriesdialog.cpp \
        src/actornote.cpp

HEADERS += \
        src/mainwindow.h \
        src/brick.h \
        src/boardbase.h \
        src/gamescene.h \
        src/game.h \
        src/playeractor.h \
        src/botactor.h \
        src/endview.h \
        src/actor.h \
        src/newseriesdialog.h \
        src/actornote.h
