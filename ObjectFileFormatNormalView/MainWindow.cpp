﻿#include <ZGL/QGLTool.hpp>
#include "ObjectFileFormatNormalReader.hpp"
#include "MainWindow.hpp"
#include <QKeyEvent>
#include <type_traits>
#include <QDebug>
#include <QFileDialog>
#include <QTimer>
#include <cassert>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

class MainWindow::__ThisData {
public:
    unsigned int timerStamp=0;
    GLuint program=0;
    GLuint vao=0;
    GLuint vao_index=0;
    GLuint vao_buffer=0;
    GLuint elements_size=0;
    glm::mat4 mvp;
    glm::mat4 normal_mvp;

    void updateNormalMVP() {
        glm::dmat3 _nmvp( mvp[0].xyz(),mvp[1].xyz(),mvp[2].xyz() );
        _nmvp=glm::transpose( glm::inverse(_nmvp) );
        normal_mvp= glm::mat4( _nmvp ) ;
    }

    __ThisData() {
        glCreateVertexArrays(1,&vao);
        program=createProgram({
            {GL_VERTEX_SHADER,readGLSLFile("glsl:ObjectFileFormatNormalView.v.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:ObjectFileFormatNormalView.f.frag")}
        });
    }
    ~__ThisData() {
        glDeleteProgram(program);
        glDeleteBuffers(1,&vao_index);
        glDeleteBuffers(1,&vao_buffer);
        glDeleteVertexArrays(1,&vao);
    }
};

void MainWindow::setObjectFileFormat(const QString & fileName) {
    auto off_=ObjectFileFormatNormalReader::read(fileName);
    if (off_) {
        glDeleteBuffers(1,&(thisData->vao_index));
        glDeleteBuffers(1,&(thisData->vao_buffer));
        glDeleteVertexArrays(1,&(thisData->vao));

        glCreateBuffers(1,&(thisData->vao_index));
        glCreateBuffers(1,&(thisData->vao_buffer));
        glCreateVertexArrays(1,&(thisData->vao));

        glNamedBufferData(
            thisData->vao_buffer,
            off_->points.size()*sizeof(off_->points[0]),
            off_->points.data(),
            GL_STATIC_DRAW
            );

        glNamedBufferData(
            thisData->vao_index,
            off_->faces.size()*sizeof(off_->faces[0]),
            off_->faces.data(),
            GL_STATIC_DRAW
            );

        typedef std::remove_reference_t<decltype(off_->points[0])> AttribType;
        /*0 position*/
        glEnableVertexArrayAttrib(thisData->vao,0);
        glVertexArrayVertexBuffer(thisData->vao,0,thisData->vao_buffer,0,sizeof(AttribType) );
        glVertexArrayAttribBinding(thisData->vao,0,0);
        glVertexArrayAttribFormat(thisData->vao,0,3,GL_FLOAT,false, offsetof(AttribType,point));

        /*1 normal*/
        glEnableVertexArrayAttrib(thisData->vao,1);
        glVertexArrayVertexBuffer(thisData->vao,1,thisData->vao_buffer,0,sizeof(AttribType) );
        glVertexArrayAttribBinding(thisData->vao,1,1);
        glVertexArrayAttribFormat(thisData->vao,1,3,GL_FLOAT,false, offsetof(AttribType,normal) );

        /*set the index buffer*/
        glVertexArrayElementBuffer(thisData->vao,thisData->vao_index);
        thisData->elements_size=off_->faces.size()*3;

        /*reset mvp*/
        const auto left_right=off_->xMax-off_->xMin;
        const auto up_down=off_->yMax-off_->yMin;
        const auto near_far=off_->zMax-off_->zMin;
        auto max_outer_=std::max({ left_right,up_down,near_far });

        max_outer_=1.65f/max_outer_;

        const auto scale_ =glm::scale(glm::mat4(),
            glm::vec3(max_outer_,max_outer_,max_outer_)
            );

        const auto translate_=glm::translate(glm::mat4(),
            glm::vec3(
            -(off_->xMax+off_->xMin)/2,
            -(off_->yMax+off_->yMin)/2,
            -(off_->zMax+off_->zMin)/2)
            );

        thisData->mvp= scale_ * translate_ ;
        thisData->normal_mvp= glm::transpose( glm::inverse( scale_ ) )  ;

        /*redraw*/
        updateGL();
    }
    else {
        qDebug().noquote()<<("read"+fileName+"object file format error!");
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent) {
    qGLWidgetInitializeGlew(this);
}

MainWindow::~MainWindow() {
    delete thisData;
}

void MainWindow::paintGL() {
    glClearColor(0.1f,0.6f,0.3f,1);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    if (thisData->elements_size) {
        //thisData->updateNormalMVP();
        glEnable(GL_DEPTH_TEST);
        glUseProgram(thisData->program);
        glBindVertexArray(thisData->vao);
        glProgramUniformMatrix4fv(thisData->program,1,1,false,glm::value_ptr(thisData->mvp));
        glProgramUniformMatrix4fv(thisData->program,2,1,false,glm::value_ptr(thisData->normal_mvp) );
        glDrawElements(GL_TRIANGLES,thisData->elements_size,GL_UNSIGNED_INT,nullptr);
        glDisable(GL_DEPTH_TEST);
    }
}

void MainWindow::keyPressEvent(QKeyEvent * e) {

    const static auto left_right_axis=glm::vec3(0,1,0);
    const static auto up_down_axis=glm::vec3(1,0,0);
    const static auto page_up_down_axis=glm::vec3(0,0,1);
    const static auto rotate_step=0.3f;

    switch (e->key()) {
        case Qt::Key_O:
        case Qt::Key_F: {
            QString fileName=QFileDialog::getOpenFileName(
                this,
                "Open File",
                "",
                "ObjectFileFormat (*.off)"
                );
            if (fileName.isEmpty()) { return; }
            this->setObjectFileFormat(fileName);
        } break;
        case Qt::Key_Left: {
            const static auto rotate_=glm::rotate(glm::mat4(),rotate_step,left_right_axis);
            thisData->mvp=rotate_*thisData->mvp; updateGL(); 
        } break;
        case Qt::Key_Right: {
            const static auto rotate_=glm::rotate(glm::mat4(),-rotate_step,left_right_axis);
            thisData->mvp=rotate_*thisData->mvp; updateGL(); 
        }break;
        case Qt::Key_Up: {
            const static auto rotate_=glm::rotate(glm::mat4(),rotate_step,up_down_axis);
            thisData->mvp=rotate_*thisData->mvp; updateGL(); 
        }break;
        case Qt::Key_Down: {
            const static auto rotate_=glm::rotate(glm::mat4(),-rotate_step,up_down_axis);
            thisData->mvp=rotate_*thisData->mvp; updateGL(); 
        }break;
        case Qt::Key_PageDown: {
            const static auto rotate_=glm::rotate(glm::mat4(),rotate_step,page_up_down_axis);
            thisData->mvp=rotate_*thisData->mvp; updateGL(); 
        }break;
        case Qt::Key_PageUp: {
            const static auto rotate_=glm::rotate(glm::mat4(),-rotate_step,page_up_down_axis);
            thisData->mvp=rotate_*thisData->mvp; updateGL();
        }break;
        default:break;
    }
}

void MainWindow::initializeGL() {
    if (thisData==nullptr) {
        setSimpleCallbackFunction();
        const_cast<__ThisData * &>(thisData)=new __ThisData;
        assert(thisData);
        QTimer::singleShot(87,this,[this]() {setObjectFileFormat("obj3d:161.off"); });
    }
}

void MainWindow::resizeGL(int w,int h) { glViewport(0,0,w,h); }

void MainWindow::timerEvent(QTimerEvent *e) {
    QGLWidget::timerEvent(e);
    updateGL();
}











