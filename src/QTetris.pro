TEMPLATE = app
TARGET = Mattoncini
ICON = icon/ttr_round.icns

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    I.cpp \
    J.cpp \
    L.cpp \
    O.cpp \
    S.cpp \
    T.cpp \
    Z.cpp \
    board.cpp \
    datamanager.cpp \
    game.cpp \
    gamecontrols.cpp \
    main.cpp \
    mainwindow.cpp \
    piecefactory.cpp \
    tetrispiece.cpp

HEADERS += \
    I.h \
    J.h \
    L.h \
    O.h \
    S.h \
    T.h \
    Z.h \
    board.h \
    datamanager.h \
    defines.h \
    game.h \
    gamecontrols.h \
    mainwindow.h \
    piecefactory.h \
    tetrispiece.h

FORMS += \
    gamecontrols.ui \
    mainwindow.ui

RESOURCES += \
    sounds.qrc
