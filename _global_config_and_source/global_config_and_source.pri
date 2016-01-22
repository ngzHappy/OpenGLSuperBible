##you must set the local language codec
win32{
LOCAL_LANGUAGE_ = GBK
}else{
LOCAL_LANGUAGE_ = UTF-8
}

CONFIG(debug,debug|release){
CONFIG *= _DEBUG
}else{
CONFIG *= NDEBUG
}

##GLM
DEFINES *= GLM_FORCE_CXX14
DEFINES *= GLM_SWIZZLE

##GLEW
DEFINES *= GLEW_STATIC
SOURCES += $$PWD/ZGLSource/glew.c###glew
SOURCES += $$PWD/ZGLSource/QGLWidgetInitializeGlew.cpp###init glew
SOURCES += $$PWD/ZGLSource/QOpenGLTool.cpp##init qglwidget

HEADERS += $$PWD/ZGL/QGLTool.hpp

INCLUDEPATH += $$PWD

win32-msvc*{
LIBS += -lopengl32 -lgdi32 -luser32 -lkernel32
}

win32-g++{
LIBS += -lopengl32 -lgdi32 -luser32 -lkernel32
}

linux:{
###libglu1-mesa-dev
###libgl1-mesa-dev
LIBS+=-lXmu -lXi -lGL -lXext -lX11
}

##codelf
##http://unbug.github.io/codelf/

##glm
##https://github.com/g-truc/glm

##reference:
##https://github.com/openglsuperbible/sb7code
##http://www.openglsuperbible.com
##http://www.glfw.org/download.html
##http://openglsuperbible.com/files/superbible7-media.zip

##highlight
##http://renderingpipeline.com/2013/12/glsl-syntax-highlighting-for-opengl-4-4/
##http://www.lighthouse3d.com/2013/01/notepad-glsl-4-3-syntax-highlight/
