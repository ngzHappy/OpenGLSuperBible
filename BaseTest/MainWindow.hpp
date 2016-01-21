#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QGLWidget>

class MainWindow : public QGLWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_HPP
