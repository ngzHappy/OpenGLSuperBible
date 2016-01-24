#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>

class MainWindow::__ThisData {
public:
    unsigned int timerStamp=0;
    GLuint program = 0;
    GLuint vao = 0;
    __ThisData(){
        glCreateVertexArrays(1,&vao);
        program = createProgram({
            {GL_VERTEX_SHADER,readGLSLFile("glsl:SimpleBlendTest.v.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:SimpleBlendTest.f.frag")}
        });
    }
    ~__ThisData(){
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
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
    glClearColor(0.1f,0.6f,0.3f,1);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(thisData->vao);
    glDrawArrays(GL_TRIANGLES,0,6);
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











