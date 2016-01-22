#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <cassert>
#include <QDebug>

class MainWindow::__ThisData{
public:
    GLuint buffer = 0;
    __ThisData(){
        glCreateBuffers(1,&buffer);
        constexpr const static GLfloat data[]{0,2,3,4};
        glNamedBufferData(buffer,sizeof(data),data,GL_STATIC_DRAW);
    }
    ~__ThisData(){glDeleteBuffers(1,&buffer);}
};

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent){
    qGLWidgetInitializeGlew(this);
}

MainWindow::~MainWindow(){
    delete thisData;
}

void MainWindow::initializeGL(){
    if(nullptr==thisData){
        setSimpleCallbackFunction();
        const_cast<__ThisData * &>( thisData )=new __ThisData;
        assert(thisData);
        startTimer(1000);
    }
}

void MainWindow::paintGL(){
    GLuint buffer = thisData->buffer ;

    {
        auto * data_ = reinterpret_cast<GLfloat *>( glMapNamedBuffer(buffer,GL_READ_WRITE) );
        data_[0]+=1;
        glUnmapNamedBuffer(buffer);
    }

    {
        auto * data_ = reinterpret_cast<GLfloat *>( glMapNamedBuffer(buffer,GL_READ_ONLY) );
        qDebug()<<data_[0]<<data_[1]<<data_[2]<<data_[3];
        glUnmapNamedBuffer(buffer);
    }

}
void MainWindow::resizeGL(int w, int h){glViewport(0,0,w,h);}
void MainWindow::timerEvent(QTimerEvent *){
    updateGL();
}









