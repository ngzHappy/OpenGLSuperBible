#include "ObjectFileFormatReader.hpp"
#include <cassert>
#include <QFile>
#include <QTextStream>
#include <cstddef>

ObjectFileFormatReader::ObjectFileFormatReader(){

}

ObjectFileFormatReader::~ObjectFileFormatReader(){

}

std::shared_ptr<ObjectFileFormat>
ObjectFileFormatReader::read( const QString & fileName ){
    std::shared_ptr<ObjectFileFormat> ans ;

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
            ans=std::make_shared<ObjectFileFormat>();
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

    return std::move(ans);
}

