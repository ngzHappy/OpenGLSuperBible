﻿#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>

class MainWindow::__ThisData {
public:
    unsigned int timerStamp=0;
    GLuint program = 0;
    GLuint vao = 0;
    GLuint buffer = 0;
    __ThisData(){
        glCreateVertexArrays(1,&vao);
        glCreateBuffers(1,&buffer);
        alignas(GLfloat) constexpr const static GLfloat data_[]{
                0,0.5f,0,1,
            -0.5f,-.5f,0,1,
             0.5f,-.5f,0,1,
        };
        glNamedBufferData(buffer,sizeof(data_),data_,GL_STATIC_DRAW);
        glEnableVertexArrayAttrib(vao,0);
        glVertexArrayVertexBuffer(vao,0,buffer,0,sizeof(data_)/3);
        glVertexArrayAttribBinding(vao,0,0);
        glVertexArrayAttribFormat(vao,0,4,GL_FLOAT,false,0);
        program = createProgram({
            {GL_VERTEX_SHADER,readGLSLFile("glsl:SimpleVertexArrayObject.v.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:SimpleVertexArrayObject.f.frag")}
        });
    }
    ~__ThisData(){
        glDeleteProgram(program);
        glDeleteVertexArrays(1,&vao);
        glDeleteBuffers(1,&buffer);
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent){
    qGLWidgetInitializeGlew(this);
}

MainWindow::~MainWindow(){
    delete thisData;
}

void MainWindow::paintGL() {
    glUseProgram(thisData->program);
    glClearColor(0.1f,0.6f,0.3f,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(thisData->vao);
    glDrawArrays(GL_TRIANGLES,0,3);
}

void MainWindow::initializeGL() {
    if(thisData==nullptr){
        setSimpleCallbackFunction();
        const_cast<__ThisData * &>(thisData)=new __ThisData;
        assert(thisData);
    }
}

void MainWindow::resizeGL(int w, int h) {glViewport(0,0,w,h);}

void MainWindow::timerEvent(QTimerEvent *e) {
    QGLWidget::timerEvent(e);
    updateGL();
}











