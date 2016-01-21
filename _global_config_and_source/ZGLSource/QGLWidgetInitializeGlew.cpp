#include <QGLWidget>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QDebug>

namespace  {
enum{
    MajorVersion=4,
    MinorVersion=5
};
static void __initialization( QGLWidget * glWidget ){
    if(0==glWidget){return;}
    QOpenGLContext * ch = glWidget->context()->contextHandle() ;
    {
        QGLFormat format_=glWidget->format();
        if (format_.majorVersion()<MajorVersion) { qDebug().noquote()<<"error opengl MajorVersion"; return; };
        if (format_.minorVersion()<MinorVersion) { qDebug().noquote()<<"error opengl MinorVersion";return; }
    }
    if(ch){
        QSurfaceFormat format =ch->format() ;
        format.setVersion(MajorVersion,MinorVersion);
        format.setProfile( QSurfaceFormat::CoreProfile );
        format.setOption( QSurfaceFormat::DebugContext );
        format.setSamples(0);
        format.setDepthBufferSize(24);
        format.setStencilBufferSize(8);
        ch->setFormat(format);
        if(ch->create()){return;}
        else{qDebug()<<"error create opengl";}
    }else{qDebug()<<"error init opengl";}
}

}


extern void _i_qInitializeQGLWidget(QGLWidget *glWidget){
    __initialization(glWidget);
}

