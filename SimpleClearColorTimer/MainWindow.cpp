#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <array>

class MainWindow::ThisData {
public:
    GLfloat timerStamp=0;
    std::array<GLfloat,4> clearColor;
    bool isUpdateByTimer=false;
    ThisData():clearColor{0,0,0,1} {}
};

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent){
    qGLWidgetInitializeGlew(this);
}

MainWindow::~MainWindow(){
    delete thisData;
}

void MainWindow::paintGL() {
    if (thisData->isUpdateByTimer) {
        thisData->isUpdateByTimer=false;
        constexpr const static GLfloat pi=3.141592654f;
        auto currentTime = thisData->timerStamp+0.055f;
        if (currentTime>pi) { currentTime-=(2*pi); }
        thisData->timerStamp=currentTime;
        new(thisData->clearColor.data()) std::array<GLfloat,4>{
            std::sin(currentTime)/2+0.5f,std::cos(currentTime)/2+0.5f,0.5f,1
        };
    }
    glClearBufferfv(GL_COLOR,0,thisData->clearColor.data());
}
void MainWindow::initializeGL() {
    if(thisData==nullptr){
        setSimpleCallbackFunction();
        const_cast<ThisData * &>(thisData)=new ThisData;
        assert(thisData);
        startTimer(25);
    }
}

void MainWindow::resizeGL(int w, int h) {glViewport(0,0,w,h);}

void MainWindow::timerEvent(QTimerEvent *e) {
    QGLWidget::timerEvent(e);
    thisData->isUpdateByTimer=true;
    updateGL();
}











