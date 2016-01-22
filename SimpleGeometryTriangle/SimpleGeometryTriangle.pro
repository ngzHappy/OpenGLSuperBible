
QT += core
QT += gui
QT += widgets
QT += opengl

CONFIG += c++14
CONFIG += console

TARGET = SimpleGeometryTriangle
TEMPLATE = app


SOURCES += main.cpp
SOURCES += MainWindow.cpp

HEADERS += MainWindow.hpp

include($$PWD/../_global_config_and_source/global_config_and_source.pri)
DEFINES *= THIS_PROJECT_PWD=\\\"$$PWD\\\"
DEFINES *= THIS_PROJECT_LOCALCODEC=\\\"$$LOCAL_LANGUAGE_\\\"

DISTFILES += $$PWD/glsl/readme.txt \
    glsl/SimpleGeometryTriangle.g.geo
DISTFILES += $$PWD/glsl/SimpleGeometryTriangle.v.vert
DISTFILES += $$PWD/glsl/SimpleGeometryTriangle.t.tcs
DISTFILES += $$PWD/glsl/SimpleGeometryTriangle.t.tes
DISTFILES += $$PWD/glsl/SimpleGeometryTriangle.f.frag
DISTFILES += $$PWD/images/readme.txt




