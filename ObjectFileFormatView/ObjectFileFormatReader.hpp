#if !defined( OBJECTFILEFORMATREADER_HPP )
#define OBJECTFILEFORMATREADER_HPP

#include <ZGL/QGLTool.hpp>
#include <memory>
#include <vector>

class ObjectFileFormat{
public:

    struct alignas(GLfloat) Point3D{
        GLfloat x;
        GLfloat y;
        GLfloat z;
        template<typename _0t,typename _1t,typename _2t>
        Point3D(_0t&&v0,_1t&&v1,_2t&&v2):x(v0),y(v1),z(v2) {}
    };

    struct alignas(GLuint) Face{
        GLuint p0;
        GLuint p1;
        GLuint p2;
        template<typename _0t,typename _1t,typename _2t>
        Face(_0t&&v0,_1t&&v1,_2t&&v2):p0(v0),p1(v1),p2(v2) {}
    };

    std::vector<Point3D> points ;
    std::vector<Face> faces;

    GLfloat xMax=0;
    GLfloat yMax=0;
    GLfloat zMax=0;
    GLfloat zMin=0;
    GLfloat yMin=0;
    GLfloat xMin=0;
};

class ObjectFileFormatReader
{
public:
    ObjectFileFormatReader();
    static std::shared_ptr<ObjectFileFormat> read( const QString & fileName );
protected:
    virtual~ObjectFileFormatReader();
};

#endif // OBJECTFILEFORMATREADER_HPP
