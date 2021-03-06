
QT += core
QT += gui
QT += widgets
QT += opengl

CONFIG += c++14
CONFIG += console

TARGET = SimpleFramebufferDepth
TEMPLATE = app


SOURCES += main.cpp
SOURCES += MainWindow.cpp

HEADERS += MainWindow.hpp

include($$PWD/../_global_config_and_source/global_config_and_source.pri)
DEFINES *= THIS_PROJECT_PWD=\\\"$$PWD\\\"
DEFINES *= THIS_PROJECT_LOCALCODEC=\\\"$$LOCAL_LANGUAGE_\\\"

DISTFILES += $$PWD/glsl/readme.txt
DISTFILES += $$PWD/glsl/SimpleFramebufferDepth.v.vert
DISTFILES += $$PWD/glsl/SimpleFramebufferDepth.f.frag
DISTFILES += $$PWD/images/readme.txt




