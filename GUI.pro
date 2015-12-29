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
    source/ClassObject.cpp \
    source/GraphicsView.cpp \
    source/Object.cpp \
    source/GraphicsScene.cpp

HEADERS += \
    header/MainWindow.h \
    header/Element.h \
    header/Connector.h \
    header/CommentObject.h \
    header/ClassObject.h \
    header/GraphicsView.h \
    header/Object.h \
    header/GraphicsScene.h

RESOURCES += \
    resource/images.qrc
