#-------------------------------------------------
#
# Project created by QtCreator 2018-09-02T10:49:30
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Colonization
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainmenuwindow.cpp \
    uunit.cpp \
    uanimal.cpp \
    uarmy.cpp \
    uenemy.cpp \
    countryselectionwindow.cpp \
    gamemainclass.cpp \
    ufood.cpp \
    ubonus.cpp \
    gamewindow.cpp \
    resources.cpp \
    gamecentralcontrol.cpp \
    uanimalgrass.cpp \
    globalfunctions.cpp \
    uanimalmeat.cpp \
    uanimalmother.cpp \
    uanimalmaterial.cpp \
    uanimalmaterialmother.cpp \
    uanimalking.cpp \
    uenemybarbarian.cpp \
    uenemybarbarian.cpp \
    uenemyeater.cpp \
    uammo.cpp \
    uarmykinds.cpp \
    uenemynative.cpp \
    usteward.cpp \
    pausedialog.cpp \
    loadmenu.cpp \
    savemenu.cpp \
    loadingwindow.cpp \
    victorywindow.cpp \
    losewindow.cpp

HEADERS += \
        mainmenuwindow.h \
    uunit.h \
    uenemy.h \
    uarmy.h \
    uanimal.h \
    gamemainclass.h \
    constant.hpp \
    ufood.h \
    ubonus.h \
    gamewindow.h \
    resources.h \
    countryselectionwindow.h \
    countryselectionbuttonmanager.hpp \
    gamecentralcontrol.h \
    uanimalgrass.h \
    globalfunctions.h \
    uanimalmeat.h \
    uanimalmother.h \
    uanimalmaterial.h \
    uanimalmaterialmother.h \
    uanimalking.h \
    uenemybarbarian.h \
    uenemyeater.h \
    uammo.h \
    uarmykinds.h \
    uenemynative.h \
    usteward.h \
    pausedialog.h \
    loadmenu.h \
    savemenu.h \
    loadingwindow.h \
    victorywindow.h \
    losewindow.h

FORMS += \
        mainmenuwindow.ui \
    countryselectionwindow.ui \
    gamewindow.ui \
    pausedialog.ui \
    loadmenu.ui \
    savemenu.ui \
    loadingwindow.ui \
    victorywindow.ui \
    losewindow.ui

RESOURCES += \
    res.qrc \
    audio.qrc
