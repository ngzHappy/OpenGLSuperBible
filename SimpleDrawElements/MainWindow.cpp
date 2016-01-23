#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>

class MainWindow::__ThisData {
public:
    unsigned int timerStamp=0;
    GLuint program = 0;
    GLuint vao = 0;
    GLuint vao_index=0;
    GLuint vao_buffer=0;
    __ThisData(){
        glCreateVertexArrays(1,&vao);
        program = createProgram({
            {GL_VERTEX_SHADER,readGLSLFile("glsl:SingleTriangle.v.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:SingleTriangle.f.frag")}
        });
        glCreateBuffers(1,&vao_buffer);
        glCreateBuffers(1,&vao_index);

        constexpr const static GLuint alignas(GLuint) index_[]{0,1,2};
        constexpr const static GLfloat alignas(GLfloat) data_[]{
            -0.5f,-0.5f,0,1,
             0.5f,-0.5f,0,1,
                0, 0.5f,0,1
        };



    }
    ~__ThisData(){
        glDeleteProgram(program);
        glDeleteVertexArrays(1,&vao);
        glDeleteBuffers(1,&vao_index);
        glDeleteBuffers(1,&vao_buffer);
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











