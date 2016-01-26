#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>
#include <QTimer>
// vec3, vec4, ivec4, mat4
#include <glm/glm.hpp>
// translate, rotate, scale, perspective
#include <glm/gtc/matrix_transform.hpp>
// glm::to_string
#include <glm/gtx/string_cast.hpp>
// glm::value_ptr
#include <glm/gtc/type_ptr.hpp>

class SimpleFrameBuffer {
    NOCOPY_GLTOOL(SimpleFrameBuffer);
    bool isOK=false;
    GLuint fbo_=0;
    int width_=0;
    int height_=0;
    GLuint color0_texture_=0;
    GLuint depth_texture_=0;
    void __init_frame_buffer()try {

        isOK=true;
        if (width_<=0) { throw QString("width is null"); }
        if (height_<=0) {throw QString("height is null");}

        glCreateFramebuffers(1,&fbo_);

        glCreateTextures(GL_TEXTURE_2D,1,&depth_texture_);
        glCreateTextures(GL_TEXTURE_2D,1,&color0_texture_);

        glTextureStorage2D(depth_texture_,1,GL_DEPTH_COMPONENT32,width_,height_);
        glTextureStorage2D(color0_texture_,1,GL_RGB16F,width_,height_);

        glNamedFramebufferTexture(fbo_,GL_DEPTH_ATTACHMENT,depth_texture_,0);
        glNamedFramebufferTexture(fbo_,GL_COLOR_ATTACHMENT0,color0_texture_, 0 );

#if defined(_DEBUG)
        /*check*/
        GLenum fboStatus = glCheckNamedFramebufferStatus(
            fbo_,GL_DRAW_FRAMEBUFFER);
        if (fboStatus!=GL_FRAMEBUFFER_COMPLETE){
            isOK=false;
            switch ( fboStatus )
            {
                case GL_FRAMEBUFFER_UNDEFINED: qDebug() << "GL_FRAMEBUFFER_UNDEFINED"; break;
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:qDebug() << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"; break;
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:qDebug() << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"; break;
                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:qDebug() << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"; break;
                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:qDebug() << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"; break;
                case GL_FRAMEBUFFER_UNSUPPORTED:qDebug() << "GL_FRAMEBUFFER_UNSUPPORTED"; break;
                case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:qDebug() << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"; break;
                case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:qDebug() << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"; break;
                default:
                    break;
            }
            return ;
        }

#endif

    }/*__init_frame_buffer*/
    catch (const QString & error) {
        isOK=false;
        qDebug().noquote()<<error;
    }
public:
    SimpleFrameBuffer(int w_,int h_):
        width_(w_),height_(h_) {
        __init_frame_buffer();
    }
    ~SimpleFrameBuffer() {
        glDeleteFramebuffers(1,&fbo_);
        glDeleteTextures(1,&color0_texture_);
        glDeleteTextures(1,&depth_texture_);
    }

    int getWidth() const { return width_; }
    int getHeight()const { return height_; }
    GLuint getColor0()const { return color0_texture_; }
    GLuint getFBO() const { return fbo_; }
    bool isValid() const { return isOK&&(fbo_); }
    void drawBuffer() const{
        constexpr const static GLenum draws_[]{GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1};
        glNamedFramebufferDrawBuffers(fbo_,2,draws_);
    }
};

class SimpleMultiFrameBuffer {
    NOCOPY_GLTOOL(SimpleMultiFrameBuffer);
    bool isOK=false;
    GLuint fbo_=0;
    int width_=0;
    int height_=0;
    GLuint color0_texture_=0;
    GLuint depth_texture_=0;
    void __init_frame_buffer()try {

        isOK=true;
        if (width_<=0) { throw QString("width is null"); }
        if (height_<=0) {throw QString("height is null");}

        glCreateFramebuffers(1,&fbo_);

        glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE,1,&depth_texture_);
        glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE,1,&color0_texture_);

        glTextureStorage2DMultisample(depth_texture_,8,GL_DEPTH_COMPONENT32,width_,height_,false);
        glTextureStorage2DMultisample(color0_texture_,8,GL_RGB16F,width_,height_,false);

        glNamedFramebufferTexture(fbo_,GL_DEPTH_ATTACHMENT,depth_texture_,0);
        glNamedFramebufferTexture(fbo_,GL_COLOR_ATTACHMENT0,color0_texture_, 0 );

#if defined(_DEBUG)
        /*check*/
        GLenum fboStatus = glCheckNamedFramebufferStatus(
            fbo_,GL_DRAW_FRAMEBUFFER);
        if (fboStatus!=GL_FRAMEBUFFER_COMPLETE){
            isOK=false;
            switch ( fboStatus )
            {
                case GL_FRAMEBUFFER_UNDEFINED: qDebug() << "GL_FRAMEBUFFER_UNDEFINED"; break;
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:qDebug() << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"; break;
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:qDebug() << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"; break;
                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:qDebug() << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"; break;
                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:qDebug() << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"; break;
                case GL_FRAMEBUFFER_UNSUPPORTED:qDebug() << "GL_FRAMEBUFFER_UNSUPPORTED"; break;
                case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:qDebug() << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"; break;
                case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:qDebug() << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"; break;
                default:
                    break;
            }
            return ;
        }

#endif

    }/*__init_frame_buffer*/
    catch (const QString & error) {
        isOK=false;
        qDebug().noquote()<<error;
    }
public:
    SimpleMultiFrameBuffer(int w_,int h_):
        width_(w_),height_(h_) {
        __init_frame_buffer();
    }
    ~SimpleMultiFrameBuffer() {
        glDeleteFramebuffers(1,&fbo_);
        glDeleteTextures(1,&color0_texture_);
        glDeleteTextures(1,&depth_texture_);
    }

    int getWidth() const { return width_; }
    int getHeight()const { return height_; }
    GLuint getFBO() const { return fbo_; }
    bool isValid() const { return isOK&&(fbo_); }
    void drawBuffer() const{
        constexpr const static GLenum draws_[]{GL_COLOR_ATTACHMENT0};
        glNamedFramebufferDrawBuffers(fbo_,1,draws_);
    }
    std::shared_ptr<SimpleFrameBuffer> downSample()const {
        auto down_fbo = std::make_shared<SimpleFrameBuffer>(width_,height_);
        if (down_fbo) {

            glNamedFramebufferReadBuffer(fbo_,GL_COLOR_ATTACHMENT0);
            glNamedFramebufferDrawBuffer(down_fbo->getFBO(),GL_COLOR_ATTACHMENT0);
            glBlitNamedFramebuffer(fbo_,down_fbo->getFBO(),
                0,0,width_,height_,
                0,0,width_,height_,
                GL_COLOR_BUFFER_BIT,
                GL_LINEAR
                );

            glBlitNamedFramebuffer(fbo_,down_fbo->getFBO(),
                0,0,width_,height_,
                0,0,width_,height_,
                GL_DEPTH_BUFFER_BIT,
                GL_NEAREST
                );

        }
        return std::move(down_fbo);
    }
};

class MainWindow::__ThisData {
public:
    unsigned int timerStamp=0;
    bool isResize=false;
    GLuint vao = 0;
    GLuint vao_cube_data_buffer=0;
    GLuint frame_program=0;/*gen a texture*/
    GLuint cube_program=0;/*draw texture to cube*/
    glm::mat4 mvp_matrix;

    std::shared_ptr<SimpleMultiFrameBuffer> fbo;

    __ThisData(){
     
        glCreateBuffers(1,&vao_cube_data_buffer);
        glCreateVertexArrays(1,&vao);
        frame_program = createProgram({
            {GL_VERTEX_SHADER,readGLSLFile("glsl:BaseMultiSampleFramebuffer.frame.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:BaseMultiSampleFramebuffer.frame.frag")}
        });
        cube_program = createProgram({
            {GL_VERTEX_SHADER,readGLSLFile("glsl:BaseMultiSampleFramebuffer.cube.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:BaseMultiSampleFramebuffer.cube.frag")}
        });
              

        /* cube data */
        constexpr static const GLfloat vertex_data[] =
        {
            // Position                 Tex Coord
            -0.25f, -0.25f,  0.25f,      0.0f, 1.0f,
            -0.25f, -0.25f, -0.25f,      0.0f, 0.0f,
             0.25f, -0.25f, -0.25f,      1.0f, 0.0f,

             0.25f, -0.25f, -0.25f,      1.0f, 0.0f,
             0.25f, -0.25f,  0.25f,      1.0f, 1.0f,
            -0.25f, -0.25f,  0.25f,      0.0f, 1.0f,

            0.25f, -0.25f, -0.25f,      0.0f, 0.0f,
            0.25f,  0.25f, -0.25f,      1.0f, 0.0f,
            0.25f, -0.25f,  0.25f,      0.0f, 1.0f,

            0.25f,  0.25f, -0.25f,      1.0f, 0.0f,
            0.25f,  0.25f,  0.25f,      1.0f, 1.0f,
            0.25f, -0.25f,  0.25f,      0.0f, 1.0f,

             0.25f,  0.25f, -0.25f,      1.0f, 0.0f,
            -0.25f,  0.25f, -0.25f,      0.0f, 0.0f,
             0.25f,  0.25f,  0.25f,      1.0f, 1.0f,

            -0.25f,  0.25f, -0.25f,      0.0f, 0.0f,
            -0.25f,  0.25f,  0.25f,      0.0f, 1.0f,
             0.25f,  0.25f,  0.25f,      1.0f, 1.0f,

            -0.25f,  0.25f, -0.25f,      1.0f, 0.0f,
            -0.25f, -0.25f, -0.25f,      0.0f, 0.0f,
            -0.25f,  0.25f,  0.25f,      1.0f, 1.0f,

            -0.25f, -0.25f, -0.25f,      0.0f, 0.0f,
            -0.25f, -0.25f,  0.25f,      0.0f, 1.0f,
            -0.25f,  0.25f,  0.25f,      1.0f, 1.0f,

            -0.25f,  0.25f, -0.25f,      0.0f, 1.0f,
             0.25f,  0.25f, -0.25f,      1.0f, 1.0f,
             0.25f, -0.25f, -0.25f,      1.0f, 0.0f,

             0.25f, -0.25f, -0.25f,      1.0f, 0.0f,
            -0.25f, -0.25f, -0.25f,      0.0f, 0.0f,
            -0.25f,  0.25f, -0.25f,      0.0f, 1.0f,

            -0.25f, -0.25f,  0.25f,      0.0f, 0.0f,
             0.25f, -0.25f,  0.25f,      1.0f, 0.0f,
             0.25f,  0.25f,  0.25f,      1.0f, 1.0f,

             0.25f,  0.25f,  0.25f,      1.0f, 1.0f,
            -0.25f,  0.25f,  0.25f,      0.0f, 1.0f,
            -0.25f, -0.25f,  0.25f,      0.0f, 0.0f,
        };

        glNamedBufferData(vao_cube_data_buffer,sizeof(vertex_data),vertex_data,GL_STATIC_DRAW);

        glEnableVertexArrayAttrib(vao,0);
        glVertexArrayVertexBuffer(vao,0,vao_cube_data_buffer,0,sizeof(GLfloat[5]));
        glVertexArrayAttribFormat(vao,0,3,GL_FLOAT,false,0);
        glVertexArrayAttribBinding(vao,0,0);

        glEnableVertexArrayAttrib(vao,1);
        glVertexArrayAttribFormat(vao,1,2,GL_FLOAT,false,sizeof(GLfloat[3]) );
        glVertexArrayAttribBinding(vao,1,0);

        mvp_matrix[0][0]=2;
        mvp_matrix[1][1]=2;
        mvp_matrix[2][2]=2;
    }
    ~__ThisData(){
        glDeleteBuffers(1,&vao_cube_data_buffer);
        glDeleteProgram(cube_program);
        glDeleteProgram(frame_program);
        glDeleteVertexArrays(1,&vao);
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

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    auto clear_view=[]() {
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glClearColor(0.1f,0.6f,0.3f,1);
        glClearDepth(1);
        glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT );
    };

    auto draw_window=[this,clear_view]( 
        std::shared_ptr<SimpleMultiFrameBuffer> & fbo_ 
        ) {
        clear_view();
        auto fbo=fbo_->downSample();
        if ( fbo ) {
            glBindFramebuffer(GL_READ_FRAMEBUFFER,fbo->getFBO());
            glReadBuffer(GL_COLOR_ATTACHMENT0);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
            glBlitFramebuffer(0,0,fbo->getWidth(),fbo->getHeight(),0,0,
                width(),height(),GL_COLOR_BUFFER_BIT,GL_LINEAR);
        }
    };

    const auto _fbo=thisData->fbo;
    if ( thisData->isResize ) {
        if (thisData->fbo) { return draw_window(thisData->fbo); }
        return clear_view();
    }

    if ((bool(thisData->fbo)==false)||
        (thisData->fbo->getHeight()!=this->height())||
        (thisData->fbo->getWidth()!=this->width())
        ) {
        thisData->fbo=
            std::make_shared<SimpleMultiFrameBuffer>(this->width(),this->height());
    }

    auto * fbo=thisData->fbo.get();
    if ((fbo==nullptr)||(fbo->isValid()==false)) { return clear_view();/*???*/ }

    glBindFramebuffer(GL_FRAMEBUFFER,fbo->getFBO());
    fbo->drawBuffer();
    glClearColor(0.1f,0.6f,0.8f,1);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    /* draw frame */
    glUseProgram( thisData->frame_program );
    glBindVertexArray( thisData->vao );
    glDrawArrays( GL_TRIANGLES, 0 , 3);

    /*get texture*/
    auto fbo_texture_=fbo->downSample();

    /* draw cube */
    glClearColor(0.1f,0.6f,0.3f,1);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glUseProgram( thisData->cube_program );
    glBindVertexArray( thisData->vao );
    glBindTextureUnit( 0 ,fbo_texture_->getColor0() );
    glDrawArrays(GL_TRIANGLES,0,36);
    glDisable(GL_CULL_FACE);

    /*free texture*/
    fbo_texture_.reset();

    return  draw_window(thisData->fbo);
}

void MainWindow::initializeGL() {
    if(thisData==nullptr){
        setSimpleCallbackFunction();
        const_cast<__ThisData * &>(thisData)=new __ThisData;
        assert(thisData);
        startTimer(333);
    }
}

void MainWindow::resizeGL(int w, int h) {
    auto timer_stamp=++(thisData->timerStamp);
    thisData->isResize=true;
    QTimer::singleShot(100,this,[this,timer_stamp]() {
        if ( thisData->timerStamp==timer_stamp ) {
            thisData->isResize=false;
            updateGL();
        }
    });
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(0,0,w,h);
}

void MainWindow::timerEvent(QTimerEvent *e) {
    QGLWidget::timerEvent(e);

    auto rand_function=[]() ->GLfloat { return (rand()%1000)/2223.5f; };
    auto r_x=glm::rotate( glm::mat4(),rand_function(),glm::vec3(1,0,0));
    auto r_y=glm::rotate( glm::mat4(),rand_function(),glm::vec3(0,1,0));
    auto r_z=glm::rotate( glm::mat4(),rand_function(),glm::vec3(0,0,1));
    
    thisData->mvp_matrix*=r_z;
    thisData->mvp_matrix*=r_x;
    thisData->mvp_matrix*=r_y;
    
    glProgramUniformMatrix4fv(thisData->cube_program,0,1,false,
        glm::value_ptr( thisData->mvp_matrix )
        );

    updateGL();
}











