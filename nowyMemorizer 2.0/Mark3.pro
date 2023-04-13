QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dodajkurs.cpp \
    listaprzedmiotow.cpp \
    main.cpp \
    mainwindow.cpp \
    powtorka.cpp \
    sesja.cpp
    powtorka.cpp

HEADERS += \
    dodajkurs.h \
    listaprzedmiotow.h \
    mainwindow.h \
    powtorka.h \
    sesja.h
    powtorka.h

FORMS += \
    dodajkurs.ui \
    listaprzedmiotow.ui \
    mainwindow.ui \
    powtorka.ui \
    sesja.ui
    powtorka.ui

RESOURCES += \
    moje_obrazy.qrc




