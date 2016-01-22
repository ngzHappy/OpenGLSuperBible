#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>

class MainWindow::ThisData {
public:
    unsigned int timerStamp=0;
    GLuint program = 0;
    GLuint vao = 0;
    ThisData(){
        glCreateVertexArrays(1,&vao);
        program = createProgram({
            {GL_VERTEX_SHADER,readGLSLFile("glsl:SimpleTessellationTriangle.v.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:SimpleTessellationTriangle.f.frag")},
            {GL_TESS_CONTROL_SHADER,readGLSLFile("glsl:SimpleTessellationTriangle.t.tcs")},
            {GL_TESS_EVALUATION_SHADER,readGLSLFile("glsl:SimpleTessellationTriangle.t.tes")}
        });
    }
    ~ThisData(){
        glDeleteProgram(program);
        glDeleteVertexArrays(1,&vao);
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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0.1f,0.6f,0.3f,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(thisData->vao);
    glPatchParameteri(GL_PATCH_VERTICES,3);
    glDrawArrays(GL_PATCHES,0,3);
}

void MainWindow::initializeGL() {
    if(thisData==nullptr){
        setSimpleCallbackFunction();
        const_cast<ThisData * &>(thisData)=new ThisData;
        assert(thisData);
    }
}

void MainWindow::resizeGL(int w, int h) {glViewport(0,0,w,h);}

void MainWindow::timerEvent(QTimerEvent *e) {
    QGLWidget::timerEvent(e);
    updateGL();
}











