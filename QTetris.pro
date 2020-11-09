QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    mainwindow.h \
    piecefactory.h \
    tetrispiece.h

FORMS += \
    mainwindow.ui
