#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>
#include <cstdlib>

class MainWindow::ThisData {
public:
    unsigned int timerStamp=0;
};

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent){
    qGLWidgetInitializeGlew(this);
}

MainWindow::~MainWindow(){
    delete thisData;
}

void MainWindow::paintGL() {
    auto getRandColor=[]()->GLfloat{return (rand()%1000)/1000.0f;};
    glClearColor(getRandColor(),getRandColor(),getRandColor(),1);
    glClear(GL_COLOR_BUFFER_BIT);
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
}











