#-------------------------------------------------
#
# Project created by QtCreator 2016-08-12T22:12:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = generator
TEMPLATE = app


SOURCES += main.cpp\
	mainwindow.cpp\
	appcore.cpp \
    settingshandler.cpp \
    mydialog.cpp

HEADERS  += mainwindow.h\
	    appcore.h \
    settingshandler.h \
    mydialog.h

FORMS    += mainwindow.ui \
    mydialog.ui

CONFIG += c++11

RESOURCES += \
    AppIcon.qrc
