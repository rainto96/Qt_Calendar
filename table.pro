#-------------------------------------------------
#
# Project created by QtCreator 2014-07-03T19:14:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = table
TEMPLATE = app


SOURCES += main.cpp\
    datetime.cpp \
    daytime.cpp \
    dialog_save.cpp \
    FileIO.cpp \
    date.cpp \
    ShowNowTime.cpp \
    character.cpp \
    dialog_loop.cpp \
    dialog_edit.cpp \
    remind.cpp \
    search.cpp \
    weekdialog.cpp \
    daydialog.cpp \
    mainwindow.cpp \
    loop.cpp \
    dialog_search.cpp

HEADERS  += \
    datetime.h \
    daytime.h \
    dialog_save.h \
    FileIO.h \
    date.h \
    ShowNowTime.h \
    character.h \
    dialog_loop.h \
    dialog_edit.h \
    remind.h \
    search.h \
    weekdialog.h \
    daydialog.h \
    mainwindow.h \
    loop.h \
    dialog_search.h

FORMS    += \
    dialog_save.ui \
    dialog_loop.ui \
    dialog_edit.ui \
    weekdialog.ui \
    daydialog.ui \
    mainwindow.ui \
    dialog_search.ui

RESOURCES += \
    new.qrc

OTHER_FILES +=
