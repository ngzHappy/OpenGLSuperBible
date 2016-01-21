#include <ZGL/QGLTool.hpp>
#include <QGLWidget>
#include <QDebug>
#include <QList>
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <QMessageBox>


extern void _i_qInitializeQGLWidget(QGLWidget *glWidget);

namespace{
static inline bool __QGLWidgetInitializeGlew(
    QGLWidget * const ptr
    )
{
    _i_qInitializeQGLWidget(ptr);
    ptr->makeCurrent();
    glewExperimental = GL_TRUE;
    int glewErr = glewInit();
    if( glewErr != GLEW_OK )
    {
        QMessageBox box;
        box.setText("opengl/glew init error!");
        box.exec();
        return false;
    }//
    return true;
}
}

bool qGLWidgetInitializeGlew(QGLWidget * const ptr){
    return __QGLWidgetInitializeGlew(ptr);
}

extern QImage readGLSLImage(const QString & fileName ) {
    QImage ans( fileName );
    return ans.convertToFormat(QImage::Format_RGBA8888);
}

extern QString readGLSLFile( const QString & fileName  ){
    QFile file( fileName );
    if( file.open(QIODevice::ReadOnly|QIODevice::Text ) ){
        QTextStream stream(&file);
        return stream.readAll() ;
    }
    return QString();
}

GLuint createProgram( const std::initializer_list<GLSLFile> & glslFiles )try{
    const auto shaderSize=glslFiles.size();
    if( shaderSize<1 ){return 0;}

    class Shader{
    public:
        GLuint value;
        Shader(GLuint v):value(v){ if(v==0){throw v;} }
        Shader(Shader && o):value(o.value){o.value=0;}
        Shader(const Shader &)=delete;
        Shader&operator=(const Shader &)=delete;
        Shader&operator=(Shader &&)=delete;
        ~Shader() { glDeleteShader(value); }
    };

    std::vector< Shader > shaders;
    shaders.reserve( shaderSize );

    for (const auto & i :glslFiles) {/*create shaders*/
        shaders.emplace_back( glCreateShader(i.type) );
    }

    {/*set shader source*/
        auto fp=glslFiles.begin(); const auto fe=glslFiles.end();
        auto sp=shaders.begin();
        for (;fp!=fe;++fp,++sp) {
            const QByteArray shader_data_=fp->data.toUtf8();
            if (shader_data_.isEmpty()) { throw "shader data empty"; }
            const char * shader_data[]{ shader_data_.constData()};
            glShaderSource(sp->value,1,shader_data,nullptr);
        }
    }

    {/*build shader source*/
        for (const auto &shader:shaders) {glCompileShader(shader.value);}
    }

    class Program {
        Program&operator=(const Program &)=delete;
        Program&operator=(Program &&)=delete;
        Program(const Program &)=delete;
        Program(Program &&)=delete;
    public:
        GLuint value;
        Program(GLuint v):value(v) {if (0==value) { throw "null program"; }}
        ~Program() { glDeleteProgram(value); }
    };

    Program program{ glCreateProgram() };

    {/*attch shader*/
        for (const auto &shader:shaders) {glAttachShader(program.value,shader.value);}
    }

    /*link program*/
    glLinkProgram(program.value);

    {
        const auto ans=program.value;
        program.value=0;
        return ans;
    }
}catch( ... ){
return 0;
}

namespace  {

namespace _private__debug__callback {
inline QString source2string(GLenum source) {
    switch (source) {
        case GL_DEBUG_SOURCE_APPLICATION:return"GL_DEBUG_SOURCE_APPLICATION";
        case GL_DEBUG_SOURCE_THIRD_PARTY:return"GL_DEBUG_SOURCE_THIRD_PARTY";
    }
    return "unknow source:0x"+QString::number(source,16);
}

inline QString type2string(GLenum type){
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:return"GL_DEBUG_TYPE_ERROR";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:return"GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
        case GL_DEBUG_TYPE_PORTABILITY:return "GL_DEBUG_TYPE_PORTABILITY"; 
        case GL_DEBUG_TYPE_PERFORMANCE:return "GL_DEBUG_TYPE_PERFORMANCE";
        case GL_DEBUG_TYPE_MARKER:return"GL_DEBUG_TYPE_MARKER"; 
        case GL_DEBUG_TYPE_PUSH_GROUP:return"GL_DEBUG_TYPE_PUSH_GROUP";
        case GL_DEBUG_TYPE_POP_GROUP:return"GL_DEBUG_TYPE_POP_GROUP"; 
        case GL_DEBUG_TYPE_OTHER:return"GL_DEBUG_TYPE_OTHER";
    }
    return"unknow type:0x"+QString::number(type,16);
}

inline QString serverity2string(GLenum severity) {
    switch (severity) {
        case GL_DEBUG_SEVERITY_LOW:return"GL_DEBUG_SEVERITY_LOW";
        case GL_DEBUG_SEVERITY_MEDIUM:return"GL_DEBUG_SEVERITY_MEDIUM";
        case GL_DEBUG_SEVERITY_HIGH:return"GL_DEBUG_SEVERITY_HIGH";
        case GL_DEBUG_SEVERITY_NOTIFICATION:return"GL_DEBUG_SEVERITY_NOTIFICATION";
    }
    return "unknow serverity:0x"+QString::number(severity,16);
}

}

static void GLAPIENTRY __debug__callback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* /*userParam*/
        )
{
    using namespace _private__debug__callback;
    QString message_;
    message_+="source:"+QString::number( source )+"::"+source2string(source)+"\n";
    message_+="type:"+QString::number( type )+"::"+type2string(type)+"\n";
    message_+="id:"+QString::number( id )+"::"+QString::number(id,16)+"\n";
    message_+="severity:"+QString::number( severity )+"::"+serverity2string(severity)+"\n";
    message_+=QString::fromUtf8( message,length );
    qDebug().noquote()<<"message: "<<message_ ;
}

}

void setSimpleCallbackFunction(bool e )
{
    if(e==false){return;}

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageControl(GL_DONT_CARE,
                          GL_DONT_CARE,
                          GL_DONT_CARE,
                          0,
                          0,
                          true);
    glDebugMessageCallback(
                &__debug__callback,
                0);

    GLint v = 0x01;
    glGetIntegerv( GL_CONTEXT_FLAGS, &v );
    if(GL_CONTEXT_FLAG_DEBUG_BIT&v){
        qDebug()<<"simple debug function set!" ;
    }
    else{
        qDebug()<<"debug function set failed!";
    }
}


