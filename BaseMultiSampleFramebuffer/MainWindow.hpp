﻿#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QGLWidget>

class MainWindow : public QGLWidget
{
    Q_OBJECT
    class __ThisData;
    __ThisData * const thisData=nullptr;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void timerEvent(QTimerEvent *) override;
};

#endif // MAINWINDOW_HPP
