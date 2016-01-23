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
            {GL_VERTEX_SHADER,readGLSLFile("glsl:SimpleDrawElements.v.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:SimpleDrawElements.f.frag")}
        });
        glCreateBuffers(1,&vao_buffer);
        glCreateBuffers(1,&vao_index);

        alignas(GLuint) constexpr const static GLuint index_[]{0,1,2};
        alignas(GLfloat) constexpr const static GLfloat data_[]{
            -0.5f,-0.5f,0,1,
             0.5f,-0.5f,0,1,
                0, 0.5f,0,1
        };

        glNamedBufferData(vao_buffer,sizeof(data_),data_,GL_STATIC_DRAW);
        glNamedBufferData(vao_index,sizeof(index_),index_,GL_STATIC_DRAW);

        glEnableVertexArrayAttrib(vao,0);
        glVertexArrayVertexBuffer(vao,0,vao_buffer,0,sizeof(GLfloat[4]));
        glVertexArrayAttribFormat(vao,0,4,GL_FLOAT,false,0);
        glVertexArrayAttribBinding(vao,0,0);
            
        glVertexArrayElementBuffer(vao,vao_index);
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
    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,nullptr);
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











