#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>
#include <QImage>
#include <type_traits>

constexpr GLint operator""_xoffset(unsigned long long  v) { return static_cast<GLint>(v); }
constexpr GLint operator""_depth(unsigned long long  v) { return static_cast<GLint>(v); }
constexpr GLint operator""_width(unsigned long long  v) { return static_cast<GLint>(v); }
constexpr GLint operator""_height(unsigned long long  v) { return static_cast<GLint>(v); }
constexpr GLint operator""_yoffset(unsigned long long  v) { return static_cast<GLint>(v); }
constexpr GLint operator""_zoffset(unsigned long long  v) { return static_cast<GLint>(v); }
constexpr GLint operator""_level(unsigned long long  v) { return static_cast<GLint>(v); }

class MainWindow::__ThisData {
public:
    enum { IMAGES_SIZE=64 };
    static const QImage (& getImages() ) [IMAGES_SIZE] {
        static const QImage images_[ ]{
            readGLSLImage("images:00.png").mirrored(false,true),
            readGLSLImage("images:01.png").mirrored(false,true),
            readGLSLImage("images:02.png").mirrored(false,true),
            readGLSLImage("images:03.png").mirrored(false,true),
            readGLSLImage("images:04.png").mirrored(false,true),
            readGLSLImage("images:05.png").mirrored(false,true),
            readGLSLImage("images:06.png").mirrored(false,true),
            readGLSLImage("images:07.png").mirrored(false,true),
            readGLSLImage("images:08.png").mirrored(false,true),
            readGLSLImage("images:09.png").mirrored(false,true),
            readGLSLImage("images:10.png").mirrored(false,true),
            readGLSLImage("images:11.png").mirrored(false,true),
            readGLSLImage("images:12.png").mirrored(false,true),
            readGLSLImage("images:13.png").mirrored(false,true),
            readGLSLImage("images:14.png").mirrored(false,true),
            readGLSLImage("images:15.png").mirrored(false,true),
            readGLSLImage("images:16.png").mirrored(false,true),
            readGLSLImage("images:17.png").mirrored(false,true),
            readGLSLImage("images:18.png").mirrored(false,true),
            readGLSLImage("images:19.png").mirrored(false,true),
            readGLSLImage("images:20.png").mirrored(false,true),
            readGLSLImage("images:21.png").mirrored(false,true),
            readGLSLImage("images:22.png").mirrored(false,true),
            readGLSLImage("images:23.png").mirrored(false,true),
            readGLSLImage("images:24.png").mirrored(false,true),
            readGLSLImage("images:25.png").mirrored(false,true),
            readGLSLImage("images:26.png").mirrored(false,true),
            readGLSLImage("images:27.png").mirrored(false,true),
            readGLSLImage("images:28.png").mirrored(false,true),
            readGLSLImage("images:29.png").mirrored(false,true),
            readGLSLImage("images:30.png").mirrored(false,true),
            readGLSLImage("images:31.png").mirrored(false,true),
            readGLSLImage("images:32.png").mirrored(false,true),
            readGLSLImage("images:33.png").mirrored(false,true),
            readGLSLImage("images:34.png").mirrored(false,true),
            readGLSLImage("images:35.png").mirrored(false,true),
            readGLSLImage("images:36.png").mirrored(false,true),
            readGLSLImage("images:37.png").mirrored(false,true),
            readGLSLImage("images:38.png").mirrored(false,true),
            readGLSLImage("images:39.png").mirrored(false,true),
            readGLSLImage("images:40.png").mirrored(false,true),
            readGLSLImage("images:41.png").mirrored(false,true),
            readGLSLImage("images:42.png").mirrored(false,true),
            readGLSLImage("images:43.png").mirrored(false,true),
            readGLSLImage("images:44.png").mirrored(false,true),
            readGLSLImage("images:45.png").mirrored(false,true),
            readGLSLImage("images:46.png").mirrored(false,true),
            readGLSLImage("images:47.png").mirrored(false,true),
            readGLSLImage("images:48.png").mirrored(false,true),
            readGLSLImage("images:49.png").mirrored(false,true),
            readGLSLImage("images:50.png").mirrored(false,true),
            readGLSLImage("images:51.png").mirrored(false,true),
            readGLSLImage("images:52.png").mirrored(false,true),
            readGLSLImage("images:53.png").mirrored(false,true),
            readGLSLImage("images:54.png").mirrored(false,true),
            readGLSLImage("images:55.png").mirrored(false,true),
            readGLSLImage("images:56.png").mirrored(false,true),
            readGLSLImage("images:57.png").mirrored(false,true),
            readGLSLImage("images:58.png").mirrored(false,true),
            readGLSLImage("images:59.png").mirrored(false,true),
            readGLSLImage("images:60.png").mirrored(false,true),
            readGLSLImage("images:61.png").mirrored(false,true),
            readGLSLImage("images:62.png").mirrored(false,true),
            readGLSLImage("images:63.png").mirrored(false,true),
        };

        static_assert( IMAGES_SIZE ==
            std::extent< std::remove_reference_t<decltype(images_)> ,0>::value
            ,"images size must equal IMAGES_SIZE!");

        return images_;
    }

    struct AInstanceData{
        float rotate=0;
        float dx=0;
        float dy=0;
        float unuse=1;
    };

    AInstanceData instanceData[IMAGES_SIZE];

    unsigned int timerStamp=0;
    GLuint program=0;
    GLuint vao=0;
    GLuint texture=0;
    GLuint instance_buffer=0;

    __ThisData() {
        glCreateVertexArrays(1,&vao);
        glCreateBuffers(1,&instance_buffer);
        program=createProgram({
            {GL_VERTEX_SHADER,readGLSLFile("glsl:SimpleTextureArray.v.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:SimpleTextureArray.f.frag")}
        });

        const auto height_ = getImages()[0].height();
        const auto width_ = getImages()[0].width();
        glCreateTextures(GL_TEXTURE_2D_ARRAY,1,&texture);
        glTextureStorage3D(texture,1,GL_RGBA16F,width_,height_,IMAGES_SIZE);

        {
            int z_=0;
            for (const auto & i:getImages()) {
                glTextureSubImage3D(
                    texture,
                    0_level,
                    0_xoffset,0_yoffset,z_++,
                    width_,height_,1_depth,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    i.constBits()
                    );
            }
        }

        glNamedBufferData(instance_buffer,sizeof(instanceData),instanceData,GL_STATIC_DRAW);
        glEnableVertexArrayAttrib(vao,0);
        glVertexArrayVertexBuffer(vao,0,instance_buffer,0,sizeof(AInstanceData));
        glVertexArrayAttribFormat(vao,0,4,GL_FLOAT,false,0);
        glVertexArrayAttribBinding(vao,0,0);

        for (int i=0; i<IMAGES_SIZE;++i  ) {
            auto u=i%8 + 1;
            auto v=i/8 + 1;

            instanceData[i].rotate = (rand()%1000)/300.0f;
            instanceData[i].dx = u * (1.80f/8);
            instanceData[i].dy = v * (1.80f/8);

        }

    }
    ~__ThisData() {
        glDeleteTextures(1,&texture);
        glDeleteProgram(program);
        glDeleteVertexArrays(1,&vao);
        glDeleteBuffers(1,&instance_buffer);
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent) {
    qGLWidgetInitializeGlew(this);
}

MainWindow::~MainWindow() {
    delete thisData;
}

void MainWindow::paintGL() {
    glUseProgram(thisData->program);
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
    glClearColor(0.1f,0.6f,0.3f,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(thisData->vao);
    glBindTextureUnit(0,thisData->texture);
    glVertexAttribDivisor( 0,1 );
    glNamedBufferSubData(thisData->instance_buffer,0,sizeof(thisData->instanceData),thisData->instanceData );
    glDrawArraysInstanced(GL_TRIANGLE_STRIP,0,4,__ThisData::IMAGES_SIZE);
}

void MainWindow::initializeGL() {
    if (thisData==nullptr) {
        setSimpleCallbackFunction();
        const_cast<__ThisData * &>(thisData)=new __ThisData;
        assert(thisData);
    }
}

void MainWindow::resizeGL(int w,int h) { glViewport(0,0,w,h); }

void MainWindow::timerEvent(QTimerEvent *e) {
    QGLWidget::timerEvent(e);
    updateGL();
}











