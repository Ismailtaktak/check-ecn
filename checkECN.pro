#-------------------------------------------------
#
# Project created by QtCreator 2011-11-15T17:39:38
#
#-------------------------------------------------

QT       += core gui sql

TARGET = checkECN
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ecnitemmodel.cpp \
    itemdockwidget.cpp \
    centralwidget.cpp

HEADERS  += mainwindow.h  ecnitemmodel.cpp \
    ecnitemmodel.h \
    itemdockwidget.h \
    centralwidget.h

FORMS    += mainwindow.ui \
    itemdockwidget.ui \
    centralwidget.ui

RC_FILE = checkecn.rc

RESOURCES += \
    gfx.qrc

















