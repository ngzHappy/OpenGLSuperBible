﻿#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>

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

void MainWindow::paintGL() {}
void MainWindow::initializeGL() {
    if(thisData==nullptr){
        const_cast<ThisData *>(thisData)=new ThisData;
        assert(thisData);
        startTimer(1000);
    }
}

void MainWindow::resizeGL(int w, int h) {glViewport(0,0,w,h);}

void MainWindow::timerEvent(QTimerEvent *e) {
    QGLWidget::timerEvent(e);
    qDebug()
        <<"opengl version:"
        <<format().majorVersion()
        <<format().minorVersion()
        <<(thisData->timerStamp++);
}











