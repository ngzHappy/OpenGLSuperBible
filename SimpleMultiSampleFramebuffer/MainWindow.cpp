#include <ZGL/QGLTool.hpp>
#include "MainWindow.hpp"
#include <QDebug>
#include <cassert>
#include <QTimer>
 
class SimpleFrameBuffer {
    NOCOPY_GLTOOL(SimpleFrameBuffer);
    bool isOK=false;
    GLuint fbo_=0;
    int width_=0;
    int height_=0;
    GLuint color0_texture_=0;
    GLuint color1_texture_=0;
    GLuint depth_texture_=0;
    void __init_frame_buffer()try {

        isOK=true;
        if (width_<=0) { throw QString("width is null"); }
        if (height_<=0) {throw QString("height is null");}

        glCreateFramebuffers(1,&fbo_);

        glCreateTextures(GL_TEXTURE_2D,1,&depth_texture_);
        glCreateTextures(GL_TEXTURE_2D,1,&color1_texture_);
        glCreateTextures(GL_TEXTURE_2D,1,&color0_texture_);

        glTextureStorage2D(depth_texture_,1,GL_DEPTH_COMPONENT32,width_,height_);
        glTextureStorage2D(color1_texture_,1,GL_RGB16F,width_,height_);
        glTextureStorage2D(color0_texture_,1,GL_RGB16F,width_,height_);

        glNamedFramebufferTexture(fbo_,GL_DEPTH_ATTACHMENT,depth_texture_,0);
        glNamedFramebufferTexture(fbo_,GL_COLOR_ATTACHMENT0,color0_texture_, 0 );
        glNamedFramebufferTexture(fbo_,GL_COLOR_ATTACHMENT1,color1_texture_, 0 );

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
        glDeleteTextures(1,&color1_texture_);
        glDeleteTextures(1,&depth_texture_);
    }

    int getWidth() const { return width_; }
    int getHeight()const { return height_; }
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
    GLuint color1_texture_=0;
    GLuint depth_texture_=0;
    void __init_frame_buffer()try {

        isOK=true;
        if (width_<=0) { throw QString("width is null"); }
        if (height_<=0) {throw QString("height is null");}

        glCreateFramebuffers(1,&fbo_);

        glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE,1,&depth_texture_);
        glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE,1,&color1_texture_);
        glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE,1,&color0_texture_);

        glTextureStorage2DMultisample(depth_texture_,8,GL_DEPTH_COMPONENT32,width_,height_,false);
        glTextureStorage2DMultisample(color1_texture_,8,GL_RGB16F,width_,height_,false);
        glTextureStorage2DMultisample(color0_texture_,8,GL_RGB16F,width_,height_,false);

        glNamedFramebufferTexture(fbo_,GL_DEPTH_ATTACHMENT,depth_texture_,0);
        glNamedFramebufferTexture(fbo_,GL_COLOR_ATTACHMENT0,color0_texture_, 0 );
        glNamedFramebufferTexture(fbo_,GL_COLOR_ATTACHMENT1,color1_texture_, 0 );

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
        glDeleteTextures(1,&color1_texture_);
        glDeleteTextures(1,&depth_texture_);
    }

    int getWidth() const { return width_; }
    int getHeight()const { return height_; }
    GLuint getFBO() const { return fbo_; }
    bool isValid() const { return isOK&&(fbo_); }
    void drawBuffer() const{
        constexpr const static GLenum draws_[]{GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1};
        glNamedFramebufferDrawBuffers(fbo_,2,draws_);
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

            glNamedFramebufferReadBuffer(fbo_,GL_COLOR_ATTACHMENT1);
            glNamedFramebufferDrawBuffer(down_fbo->getFBO(),GL_COLOR_ATTACHMENT1);
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
    GLuint program = 0;
    GLuint vao = 0;

    std::shared_ptr<SimpleMultiFrameBuffer> fbo;

    __ThisData(){
        glCreateVertexArrays(1,&vao);
        program = createProgram({
            {GL_VERTEX_SHADER,readGLSLFile("glsl:SimpleMultiSampleFramebuffer.v.vert") },
            {GL_FRAGMENT_SHADER,readGLSLFile("glsl:SimpleMultiSampleFramebuffer.f.frag")}
        });
    }
    ~__ThisData(){
        glDeleteProgram(program);
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
    /*defined the function to copy */
    auto copy_function=[this](auto * fbo_) {
        auto fbo=fbo_->downSample();
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glClearColor(0.1f,0.6f,0.3f,1);
        glClearDepth(1);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
        glBindFramebuffer(GL_READ_FRAMEBUFFER,fbo->getFBO());
        glReadBuffer(GL_COLOR_ATTACHMENT0);
        glBlitFramebuffer(0,0,fbo->getWidth(),fbo->getHeight(),
            0,height()/2,width()/2,height(),GL_COLOR_BUFFER_BIT ,GL_NEAREST);
        glReadBuffer(GL_COLOR_ATTACHMENT1);
        glBlitFramebuffer(0,0,fbo->getWidth(),fbo->getHeight(),
            width()/2,0,width(),height()/2,GL_COLOR_BUFFER_BIT ,GL_NEAREST);
    };

    const auto _fbo=thisData->fbo;
    if ( thisData->isResize ) {
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glClearColor(0.1f,0.6f,0.3f,1);
        glClear(GL_COLOR_BUFFER_BIT);
        if ( thisData->fbo ) {copy_function(thisData->fbo.get()); }
        return;
    }

    if ((bool(thisData->fbo)==false)||
        (thisData->fbo->getHeight()!=this->height())||
        (thisData->fbo->getWidth()!=this->width())
        ) {
        thisData->fbo=
            std::make_shared<SimpleMultiFrameBuffer>(this->width(),this->height());
    }

    auto * fbo=thisData->fbo.get();
    if ((fbo==nullptr)||(fbo->isValid()==false)) { return;/*???*/ }

    glBindFramebuffer(GL_FRAMEBUFFER,fbo->getFBO());
    fbo->drawBuffer();
    glClearColor(0.1f,0.6f,0.8f,1);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glUseProgram(thisData->program);
    glBindVertexArray(thisData->vao);
    glDrawArrays(GL_TRIANGLES,0,3);
    copy_function(fbo);
    glDisable(GL_MULTISAMPLE);
}

void MainWindow::initializeGL() {
    if(thisData==nullptr){
        setSimpleCallbackFunction();
        const_cast<__ThisData * &>(thisData)=new __ThisData;
        assert(thisData);
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
    updateGL();
}











