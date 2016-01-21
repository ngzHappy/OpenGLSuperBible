﻿#if !defined(__HPP__QGLTOOL__HPP__)
#define __HPP__QGLTOOL__HPP__

#include "glew.h"
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <memory>
#include <QImage>
#include <QString>
#include <QList>
#include <initializer_list>

class QGLWidget;

enum GLSLShaderType : GLuint{
    VERTEX_SHADER=GL_VERTEX_SHADER,
    TESS_EVALUATION_SHADER=GL_TESS_EVALUATION_SHADER,
    TESS_CONTROL_SHADER=GL_TESS_CONTROL_SHADER,
    GEOMETRY_SHADER=GL_GEOMETRY_SHADER,
    FRAGMENT_SHADER=GL_FRAGMENT_SHADER,
    COMPUTE_SHADER=GL_COMPUTE_SHADER,
};

class GLSLFile{
public:
    GLSLShaderType type;
    QString data ;
    GLSLFile(GLSLShaderType t,QString d):type(t),data(std::move(d)) {}
    GLSLFile(GLuint t,QString d):type(static_cast<GLSLShaderType>(t)),data(std::move(d)) {}
};

extern bool qGLWidgetInitializeGlew(QGLWidget * const ptr);
extern QString readGLSLFile( const QString & fileName  );
extern GLuint createProgram( const std::initializer_list<GLSLFile> & );
extern void setSimpleCallbackFunction(bool e=true);
extern QImage readGLSLImage(const QString & fileName );

#endif


