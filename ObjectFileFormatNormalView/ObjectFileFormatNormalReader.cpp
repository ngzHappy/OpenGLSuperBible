#include "ObjectFileFormatNormalReader.hpp"
#include <cassert>
#include <QFile>
#include <QTextStream>
#include <cstddef>
#include <algorithm>
#include <forward_list>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

ObjectFileFormatNormalReader::ObjectFileFormatNormalReader(){

}

ObjectFileFormatNormalReader::~ObjectFileFormatNormalReader(){

}

std::shared_ptr<ObjectFileNormalFormat>
ObjectFileFormatNormalReader::read( const QString & fileName ){
    std::shared_ptr<ObjectFileNormalFormat> ans ;

    QFile file( fileName );

    if ( file.open( QIODevice::ReadOnly |QIODevice::Text ) ) {
        QTextStream stream( &file );

        /*read off*/
        while ( stream.atEnd()==false ) {
            QString line_=stream.readLine();
            line_=line_.trimmed().toLower();
            if (line_.isEmpty()) { continue; }
            if (line_=="off") { break; }
            return std::move(ans);
        }

        std::size_t points_size_=0;
        std::size_t faces_size_=0;

        {
            QString line_=stream.readLine();
            QTextStream tmpstream(&line_);
            tmpstream>>points_size_;
            tmpstream>>faces_size_;
        }

        if ((stream.atEnd()==false)
            &&(faces_size_>0)
            &&(points_size_>0)) {
            ans=std::make_shared<ObjectFileNormalFormat>();
            auto * ansPointer=ans.get();
            {/*read points*/
                auto & points_=ans->points;
                points_.reserve(points_size_);
                {/*read points*/
                    GLfloat x,y,z;

                    bool xMax_set=false;bool xMin_set=false;
                    bool zMax_set=false;bool zMin_set=false;
                    bool yMax_set=false;bool yMin_set=false;

                    std::size_t current_point_=0;
                    while ((stream.atEnd()==false)&&(current_point_<points_size_)) {
                        stream>>x;
                        stream>>y;
                        stream>>z;
                        if (stream.status()==QTextStream::ReadCorruptData) {
                            return nullptr;
                        }

                        if (zMax_set) { if (z>ansPointer->zMax) { ansPointer->zMax=z; } }
                        else { ansPointer->zMax=z; zMax_set=true; }
                        if (zMin_set) { if (z<ansPointer->zMin) { ansPointer->zMin=z; } }
                        else { ansPointer->zMin=z; zMin_set=true; }
                        if (yMax_set) { if (y>ansPointer->yMax) { ansPointer->yMax=y; } }
                        else { ansPointer->yMax=y; yMax_set=true; }
                        if (yMin_set) { if (y<ansPointer->yMin) { ansPointer->yMin=y; } }
                        else { ansPointer->yMin=y; yMin_set=true; }
                        if (xMax_set) { if (x>ansPointer->xMax) { ansPointer->xMax=x; } }
                        else { ansPointer->xMax=x; xMax_set=true; }
                        if (xMin_set) { if (x<ansPointer->xMin) { ansPointer->xMin=x; } }
                        else { ansPointer->xMin=x; xMin_set=true; }

                        points_.emplace_back(x,y,z);
                        ++current_point_;
                    }
                }
            }/*read points*/

            {/*read faces*/
                auto & faces_=ans->faces;
                faces_.reserve(faces_size_);
                {/*read faces*/
                    std::vector<GLuint> line_face_;
                    std::size_t current_face_=0;
                    GLuint tmp;
                    while ((stream.atEnd()==false)&&(current_face_<faces_size_)) {
                        line_face_.clear();
                        GLuint n_points=0;
                        stream>>n_points;
                        if (stream.status()==QTextStream::ReadCorruptData) {
                            return nullptr;
                        }
                        if (n_points<3) { return nullptr; }
                        line_face_.reserve(n_points);
                        {/*read npoints*/
                            std::size_t c_point=0;
                            while ((stream.atEnd()==false)&&(c_point<n_points)) {
                                stream>>tmp;
                                if (stream.status()==QTextStream::ReadCorruptData) {
                                    return nullptr;
                                }
                                line_face_.push_back(tmp);
                                ++c_point;
                            }
                        }

                        if (n_points==3) {/*a triangle */
                            faces_.emplace_back(line_face_[0],line_face_[1],line_face_[2]);
                        }
                        else {/*a polygon */
                            const auto first_point_=line_face_.begin();
                            auto second_point_=first_point_+1;
                            auto third_point_=second_point_+1;
                            const auto end_point_=line_face_.end();
                            for (; third_point_!=end_point_; second_point_=third_point_++) {
                                faces_.emplace_back(*first_point_,*second_point_,*third_point_);
                            }

                        }

                        ++current_face_;
                    }
                }
            }/*read faces*/
        }

    }

    return __make__normal__( std::move(ans) );
}

std::shared_ptr<ObjectFileNormalFormat>
ObjectFileFormatNormalReader::__make__normal__(
    std::shared_ptr<ObjectFileNormalFormat> && data
    ) {

    typedef ObjectFileNormalFormat::Vector3D v3d_type;
    if (bool(data)==false) { return std::move(data); }
    std::vector< v3d_type > face_normal_;
    face_normal_.reserve( data->faces.size() );

    {/*make face normals*/
        const auto & face_=data->faces;
        const auto & point_=data->points;
        auto get_point_=[point_](auto index_)->const glm::vec3 {
            static_assert( sizeof(glm::vec3)==sizeof(v3d_type) ,"core error!");
            const auto & point__ =  point_[index_].point ;
            return glm::vec3( point__.x , point__.y ,point__.z);
        };
        for (const auto & f:face_) {
            const auto & p0=get_point_(f.p0);
            const auto & p1=get_point_(f.p1);
            const auto & p2=get_point_(f.p2);
            const glm::vec3 f_normal_ = glm::cross((p1-p0),(p2-p0));
            face_normal_.push_back( f_normal_ );
        }
    }

    std::vector< std::forward_list<std::size_t> > point_2_face_index_;
    {/*make point 2 face*/
        point_2_face_index_.resize( data->points.size() );
        const auto & face_=data->faces;
        std::size_t face_index_=0;
        for (const auto & f:face_) {
            point_2_face_index_[f.p2].push_front(face_index_);
            point_2_face_index_[f.p1].push_front(face_index_);
            point_2_face_index_[f.p0].push_front(face_index_);
            ++face_index_;
        }
    }

    {/*make point normal*/
        auto & point_ = data->points;
        std::size_t point_index_=0;
        for (auto & p_:point_2_face_index_) {
            std::vector< glm::vec3 > normals_;
            for ( const auto & i:p_ ) {
                const auto & tmp_ = face_normal_[i];
                normals_.emplace_back( tmp_.x,tmp_.y,tmp_.z );
            }
            p_.clear();
            auto normal_0_ = std::accumulate(normals_.begin(),normals_.end(),glm::vec3(0,0,0));
            const auto length_ = glm::length( normal_0_ );
            if (length_==0) {
                point_[point_index_].normal={0,0,0};
            }
            else {
                normal_0_/=length_;
                point_[point_index_].normal=normal_0_ ;
            }

            ++point_index_;
        }
    }

    return std::move(data);

}
