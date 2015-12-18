include(qtpropertybrowser/qtpropertybrowser.pri)

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = UMLEdit
TEMPLATE = app

SOURCES += \
    source/main.cpp \
    source/MainWindow.cpp \
    source/Element.cpp \
    source/Object.cpp \
    source/Connector.cpp

HEADERS += \
    header/MainWindow.h \
    header/Element.h \
    header/Object.h \
    header/Connector.h
