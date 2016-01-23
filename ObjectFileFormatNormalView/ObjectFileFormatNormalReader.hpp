#if !defined( OBJECTFILEFORMATREADER_HPP )
#define OBJECTFILEFORMATREADER_HPP

#include <ZGL/QGLTool.hpp>
#include <memory>
#include <vector>

class ObjectFileNormalFormat{
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
        Vector3D(_0t&&v0,_1t&&v1,_2t&&v2):x(v0),y(v1),z(v2) {}
    };

    struct alignas(GLuint) Face{
        GLuint p0;
        GLuint p1;
        GLuint p2;
        template<typename _0t,typename _1t,typename _2t>
        Face(_0t&&v0,_1t&&v1,_2t&&v2):p0(v0),p1(v1),p2(v2) {}
    };

    struct alignas(GLfloat) PointNormal{
        Point3D point ;
        Vector3D normal ;
        template<typename _0t,typename _1t,typename _2t>
        PointNormal(_0t&&v0,_1t&&v1,_2t&&v2):point(v0,v1,v2),normal(1,1,1) {}
        template<typename _0t,typename _1t,typename _2t,
            typename __0t,typename __1t,typename __2t>
        PointNormal(_0t&&v0,_1t&&v1,_2t&&v2,
            __0t&&v_0,__1t&&v_1,__2t&&v_2
            ):point(v0,v1,v2),normal(v_0,v_1,v_2) {}
    };

    std::vector<PointNormal> points ;
    std::vector<Face> faces;

    GLfloat xMax=0;
    GLfloat yMax=0;
    GLfloat zMax=0;
    GLfloat zMin=0;
    GLfloat yMin=0;
    GLfloat xMin=0;
};

class ObjectFileFormatNormalReader
{
public:
    ObjectFileFormatNormalReader();
    static std::shared_ptr<ObjectFileNormalFormat> read( const QString & off_fileName );
protected:
    static std::shared_ptr<ObjectFileNormalFormat> __make__normal__(std::shared_ptr<ObjectFileNormalFormat> &&);
    virtual~ObjectFileFormatNormalReader();
};

#endif // OBJECTFILEFORMATREADER_HPP
