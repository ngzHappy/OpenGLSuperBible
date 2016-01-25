
QT += core
QT += gui
QT += widgets
QT += opengl

CONFIG += c++14
CONFIG += console

TARGET = SimpleTextureArray
TEMPLATE = app


SOURCES += main.cpp
SOURCES += MainWindow.cpp

HEADERS += MainWindow.hpp

include($$PWD/../_global_config_and_source/global_config_and_source.pri)
DEFINES *= THIS_PROJECT_PWD=\\\"$$PWD\\\"
DEFINES *= THIS_PROJECT_LOCALCODEC=\\\"$$LOCAL_LANGUAGE_\\\"

DISTFILES += $$PWD/glsl/readme.txt
DISTFILES += $$PWD/glsl/SimpleTextureArray.v.vert
DISTFILES += $$PWD/glsl/SimpleTextureArray.f.frag
DISTFILES += $$PWD/images/readme.txt

DISTFILES += $$PWD/images/00.png
DISTFILES += $$PWD/images/01.png
DISTFILES += $$PWD/images/02.png
DISTFILES += $$PWD/images/03.png
DISTFILES += $$PWD/images/04.png
DISTFILES += $$PWD/images/05.png
DISTFILES += $$PWD/images/06.png
DISTFILES += $$PWD/images/07.png
DISTFILES += $$PWD/images/08.png
DISTFILES += $$PWD/images/09.png
DISTFILES += $$PWD/images/10.png
DISTFILES += $$PWD/images/11.png
DISTFILES += $$PWD/images/12.png
DISTFILES += $$PWD/images/13.png
DISTFILES += $$PWD/images/14.png
DISTFILES += $$PWD/images/15.png
DISTFILES += $$PWD/images/16.png
DISTFILES += $$PWD/images/17.png
DISTFILES += $$PWD/images/18.png
DISTFILES += $$PWD/images/19.png
DISTFILES += $$PWD/images/20.png
DISTFILES += $$PWD/images/21.png
DISTFILES += $$PWD/images/22.png
DISTFILES += $$PWD/images/23.png
DISTFILES += $$PWD/images/24.png
DISTFILES += $$PWD/images/25.png
DISTFILES += $$PWD/images/26.png
DISTFILES += $$PWD/images/27.png
DISTFILES += $$PWD/images/28.png
DISTFILES += $$PWD/images/29.png
DISTFILES += $$PWD/images/30.png
DISTFILES += $$PWD/images/31.png
DISTFILES += $$PWD/images/32.png
DISTFILES += $$PWD/images/33.png
DISTFILES += $$PWD/images/34.png
DISTFILES += $$PWD/images/35.png
DISTFILES += $$PWD/images/36.png
DISTFILES += $$PWD/images/37.png
DISTFILES += $$PWD/images/38.png
DISTFILES += $$PWD/images/39.png
DISTFILES += $$PWD/images/40.png
DISTFILES += $$PWD/images/41.png
DISTFILES += $$PWD/images/42.png
DISTFILES += $$PWD/images/43.png
DISTFILES += $$PWD/images/44.png
DISTFILES += $$PWD/images/45.png
DISTFILES += $$PWD/images/46.png
DISTFILES += $$PWD/images/47.png
DISTFILES += $$PWD/images/48.png
DISTFILES += $$PWD/images/49.png
DISTFILES += $$PWD/images/50.png
DISTFILES += $$PWD/images/51.png
DISTFILES += $$PWD/images/52.png
DISTFILES += $$PWD/images/53.png
DISTFILES += $$PWD/images/54.png
DISTFILES += $$PWD/images/55.png
DISTFILES += $$PWD/images/56.png
DISTFILES += $$PWD/images/57.png
DISTFILES += $$PWD/images/58.png
DISTFILES += $$PWD/images/59.png
DISTFILES += $$PWD/images/60.png
DISTFILES += $$PWD/images/61.png
DISTFILES += $$PWD/images/62.png
DISTFILES += $$PWD/images/63.png



