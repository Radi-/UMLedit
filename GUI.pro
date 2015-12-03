
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UMLEdit
TEMPLATE = app

SOURCES += \
    source/main.cpp \
    source/MainWindow.cpp \
    source/MenuBar.cpp

HEADERS += \
    header/MainWindow.h \
    header/MenuBar.h
