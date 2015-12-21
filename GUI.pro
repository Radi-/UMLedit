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
    source/Connector.cpp \
    source/CommentObject.cpp \
    source/ClassObject.cpp

HEADERS += \
    header/MainWindow.h \
    header/Element.h \
    header/Connector.h \
    header/CommentObject.h \
    header/ClassObject.h

RESOURCES += \
    resource/images.qrc
