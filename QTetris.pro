QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    board.cpp \
    main.cpp \
    mainwindow.cpp \
    tetrispiece.cpp

HEADERS += \
    board.h \
    mainwindow.h \
    tetrispiece.h

FORMS += \
    mainwindow.ui
