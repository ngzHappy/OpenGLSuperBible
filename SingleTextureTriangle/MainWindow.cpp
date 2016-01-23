#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>

class MainWindow::__ThisData {
public:
    unsigned int timerStamp=0;
    GLuint program = 0;
    GLuint vao = 0;
    GLuint texture=0;
    __ThisData(){
        glCreateVertexArrays(1,&vao);
        program = createProgram({
            {GL_VERTEX_SHADER,readGLSLFile("glsl:SingleTextureTriangle.v.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:SingleTextureTriangle.f.frag")}
        });
        glCreateTextures(GL_TEXTURE_2D,1,&texture);

        {
            QImage image_=readGLSLImage( "images:simpletest.jpg" );
            image_=image_.mirrored(false,true);
            glTextureStorage2D(texture,1,GL_RGBA16F,image_.width(),image_.height());
            glTextureSubImage2D(texture,0,0,0,image_.width(),image_.height(),
                GL_RGBA,GL_UNSIGNED_BYTE,image_.constBits()
                );
        }

    }
    ~__ThisData(){
        glDeleteProgram(program);
        glDeleteVertexArrays(1,&vao);
        glDeleteTextures(1,&texture);
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
    glBindTextureUnit(0,thisData->texture);
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











