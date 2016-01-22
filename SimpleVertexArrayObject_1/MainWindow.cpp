#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>

class MainWindow::__ThisData {
public:
    unsigned int timerStamp=0;
    GLuint program = 0;
    GLuint vao = 0;
    GLuint buffer = 0;

    struct alignas( alignof(GLfloat)*8 ) Vertex{
        union{
            GLfloat color[4];
            struct{ GLfloat r,g,b,a; };
        };
        union{
            GLfloat position[4];
            struct{ GLfloat x,y,z,w; };
        };
        template<
            typename _0_T,typename _1_T,typename _2_T,typename _3_T ,
            typename _4_T,typename _5_T,typename _6_T,typename _7_T
        >
        constexpr Vertex(_0_T&&_r,_1_T&&_g,_2_T&&_b,_3_T&&_a,
               _4_T&&_x,_5_T&&_y,_6_T&&_z,_7_T&&_w
               ):r(_r),g(_g),b(_b),a(_a),
            x(_x),y(_y),z(_z),w(_w)
        {}
    };

    __ThisData(){
        glCreateVertexArrays(1,&vao);
        glCreateBuffers(1,&buffer);
        constexpr const static Vertex data_[]{
            {1,0,0,1,    0,0.5f,0,1,},
            {0,1,0,1,-0.5f,-.5f,0,1,},
            {0,0,1,1, 0.5f,-.5f,0,1,},
        };
        glNamedBufferData(buffer,sizeof(data_),data_,GL_STATIC_DRAW);

        /*0 color*/
        glEnableVertexArrayAttrib(vao,0);
        glVertexArrayVertexBuffer(vao,0,buffer,0,sizeof(Vertex));
        glVertexArrayAttribBinding(vao,0,0);
        glVertexArrayAttribFormat(vao,0,4,GL_FLOAT,false,offsetof(Vertex,color));

        /*1 position*/
        glEnableVertexArrayAttrib(vao,1);
        glVertexArrayVertexBuffer(vao,1,buffer,0,sizeof(Vertex));
        glVertexArrayAttribBinding(vao,1,1);
        glVertexArrayAttribFormat(vao,1,4,GL_FLOAT,false,offsetof(Vertex,position));

        program = createProgram({
            {GL_VERTEX_SHADER,readGLSLFile("glsl:SimpleVertexArrayObject_1.v.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:SimpleVertexArrayObject_1.f.frag")}
        });
    }
    ~__ThisData(){
        glDeleteProgram(program);
        glDeleteVertexArrays(1,&vao);
        glDeleteBuffers(1,&buffer);
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











