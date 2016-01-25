
QT += core
QT += gui
QT += widgets
QT += opengl

CONFIG += c++14
CONFIG += console

TARGET = OBJView
TEMPLATE = app


SOURCES += main.cpp
SOURCES += OBJReader.cpp
SOURCES += MainWindow.cpp

HEADERS += MainWindow.hpp
HEADERS += OBJReader.hpp

include($$PWD/../_global_config_and_source/global_config_and_source.pri)
DEFINES *= THIS_PROJECT_PWD=\\\"$$PWD\\\"
DEFINES *= THIS_PROJECT_LOCALCODEC=\\\"$$LOCAL_LANGUAGE_\\\"

DISTFILES += $$PWD/glsl/readme.txt
DISTFILES += $$PWD/obj3d/test.obj
DISTFILES += $$PWD/obj3d/test.png
DISTFILES += $$PWD/glsl/OBJView.v.vert
DISTFILES += $$PWD/glsl/OBJView.f.frag
DISTFILES += $$PWD/images/readme.txt




