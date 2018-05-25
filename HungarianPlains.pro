#-------------------------------------------------
#
# Project created by QtCreator 2017-12-17T10:41:24
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HungarianPlains
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    myscene.cpp \
    myelement.cpp \
    mypixmapvector.cpp \
    manualdialog.cpp \
    controlpanel.cpp \
    controlcar.cpp

HEADERS  += mainwindow.h \
    myscene.h \
    myelement.h \
    mypixmapvector.h \
    manualdialog.h \
    controlpanel.h \
    controlcar.h

FORMS    += mainwindow.ui \
    manualdialog.ui

RESOURCES += \
    icons.qrc

DISTFILES +=

