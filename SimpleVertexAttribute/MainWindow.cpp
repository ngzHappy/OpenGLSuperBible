#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>
#include <cmath>

class MainWindow::ThisData {
public:
    unsigned int timerStamp=0;
    GLuint program = 0;
    GLuint vao = 0;
    ThisData(){
        glCreateVertexArrays(1,&vao);
        program = createProgram({
            {GL_VERTEX_SHADER,readGLSLFile("glsl:SimpleVertexAttribute.v.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:SimpleVertexAttribute.f.frag")}
        });
    }
    ~ThisData(){
        glDeleteVertexArrays(1,&vao);
        glDeleteProgram(program);
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
    glBindVertexArray(thisData->vao);
    glClearColor(0.1f,0.6f,0.3f,1);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    auto rand_data=[]() ->GLfloat{
        GLfloat ans=std::sin((rand()%123'456)*(1/1'000.0f));
        return ((rand()&1)? ans:(-ans))*0.5f;
    };
    const GLfloat offset[]{ rand_data(),rand_data(),0,0 };
    glVertexAttrib4fv(0,offset);
    glDrawArrays(GL_TRIANGLES,0,3);
}

void MainWindow::initializeGL() {
    if(thisData==nullptr){
        setSimpleCallbackFunction();
        const_cast<ThisData * &>(thisData)=new ThisData;
        assert(thisData);
        startTimer(360);
    }
}

void MainWindow::resizeGL(int w, int h) {glViewport(0,0,w,h);}

void MainWindow::timerEvent(QTimerEvent *e) {
    QGLWidget::timerEvent(e);
    updateGL();
}











