#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent){
    qGLWidgetInitializeGlew(this);
}

MainWindow::~MainWindow(){

}












