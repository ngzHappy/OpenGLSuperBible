#if !defined( __OBJREADER__HPP__ )
#define __OBJREADER__HPP__

#include <ZGL/QGLTool.hpp>
#include <vector>
#include <memory>
#include <QString>

class OBJData{
public:

    struct alignas(GLfloat) Point3D{
        GLfloat x;
        GLfloat y;
        GLfloat z;
        template<typename _0t,typename _1t,typename _2t>
        Point3D(_0t&&v0,_1t&&v1,_2t&&v2):x(v0),y(v1),z(v2) {}
    };

    struct alignas(GLfloat) Vector3D{
        GLfloat x;
        GLfloat y;
        GLfloat z;
        template<typename _0t,typename _1t,typename _2t>
        Vector3D(_0t&&v0,_1t&&v1,_2t&&v2):
            x(static_cast<GLfloat>(v0)),
            y(static_cast<GLfloat>(v1)),
            z(static_cast<GLfloat>(v2)) {}
        template<typename _0t >
        Vector3D(_0t&&v0 ):Vector3D(v0[0],v0[1],v0[2]) {}
    };

    struct alignas(GLfloat) Point2D {
        GLfloat u;
        GLfloat v;
        template<typename __U,typename __V>
        Point2D(__U&&_u,__V&&_v):u(_u),v(_v) {}
    };

    struct alignas(GLuint) Face{
        GLuint p0;
        GLuint p1;
        GLuint p2;
        template<typename _0t,typename _1t,typename _2t>
        Face(_0t&&v0,_1t&&v1,_2t&&v2):p0(v0),p1(v1),p2(v2) {}
        template<typename _0t >
        Face(_0t&&v0 ):Face(v0[0],v0[1],v0[2]) {}
    };

    struct alignas(GLfloat) PointNormalUV{
        Point3D point ;
        Vector3D normal ;
        Point2D uv;
        template<typename _0t,typename _1t,typename _2t>
        PointNormalUV(_0t&&v0,_1t&&v1,_2t&&v2):point(v0,v1,v2),normal(1,1,1),uv(1,1) {}
        template<typename _0t,typename _1t,typename _2t,
            typename __0t,typename __1t,typename __2t>
        PointNormalUV(_0t&&v0,_1t&&v1,_2t&&v2,
            __0t&&v_0,__1t&&v_1,__2t&&v_2
            ):point(v0,v1,v2),normal(v_0,v_1,v_2),uv(1,1) {}
        template<typename _0t,typename _1t,typename _2t,
            typename __0t,typename __1t,typename __2t,
            typename ___0t,typename ___1t >
            PointNormalUV(_0t&&v0,_1t&&v1,_2t&&v2,
                __0t&&v_0,__1t&&v_1,__2t&&v_2,
                ___0t&&_u,___1t&&_v
                ):point(v0,v1,v2),normal(v_0,v_1,v_2),uv(_u,_v) {}
    };

    std::vector<PointNormalUV> points ;
    std::vector<Face> faces;

    GLfloat xMax=0;
    GLfloat yMax=0;
    GLfloat zMax=0;
    GLfloat zMin=0;
    GLfloat yMin=0;
    GLfloat xMin=0;

    QString dirPath;
    /* if the file named AbcDef.xYz.obj then
    textureFileName = abcdef.xyz
    the textureFile should be a picture likc jpg,png,bmp ... which qt an read 
    */
    QString textureFileName;
};

class OBJReader{
public:
    static std::shared_ptr<OBJData> read( const QString & );
};

#endif
