#include "OBJReader.hpp"
#include <QFileInfo>
#include <QFile>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <QDebug>
#include <list>
#include <map>
#include <QDir>
/*v,vt,vn*/

std::shared_ptr<OBJData>
OBJReader::read(const QString & fileName) {
    std::shared_ptr<OBJData> ans;

    {/*read data*/
        QString dirPath; QString textureFileName;
        std::string fileName_;
        const static std::regex r_space  (u8R"___(\s*)___");
        const static std::regex r_comment(u8R"___(\s*#[\s\S]*)___");
        const static std::regex r_vt     (u8R"___(\s*vt)___");
        const static std::regex r_vn     (u8R"___(\s*vn)___");
        const static std::regex r_v      (u8R"___(\s*v)___");
        const static std::regex r_f      (u8R"___(\s*f)___");
        const static std::regex r_face_data(u8R"___(\s*([^/]*)/([^/]*)/([^\s]*)\s*([^/]*)/([^/]*)/([^\s]*)\s*([^/]*)/([^/]*)/([^\s]*)\s*)___");

        {
            QFileInfo info(fileName);
            if (info.exists()==false) { return nullptr; }
            fileName_=info.absoluteFilePath().toLocal8Bit().toStdString();
            dirPath= QDir::cleanPath( info.absoluteDir().absolutePath() );
            textureFileName = info.completeBaseName().trimmed().toLower();
        }

        std::ifstream stream_(fileName_);
        if (stream_.is_open()==false) { return nullptr; }
        fileName_.clear();

        struct MinMaxValue final {
        private:
            GLfloat max_,min_;
            bool isMaxSet=false;
            bool isMinSet=false;
        public:
            void setValue(const GLfloat & v) {
                if (isMaxSet==false) { isMaxSet=true; max_=v; }
                else { if (v>max_) { max_=v; return; } }
                if (isMinSet==false) { isMinSet=true; min_=v; }
                else { if (v<min_) { min_=v; return; } }
            }
            const auto & getMax() const { return max_; }
            const auto & getMin() const { return min_; }
        };

        MinMaxValue mmx,mmy,mmz;

        std::vector< OBJData::Point2D > uvs;
        std::vector< OBJData::Point3D > positions;
        std::vector< OBJData::Vector3D > normals;

        enum { RESERVE__=1024 };
        uvs.reserve(RESERVE__);
        positions.reserve(RESERVE__);
        normals.reserve(RESERVE__);

        struct Face {
            GLuint p0_v,p0_t,p0_n; GLuint p0_index;
            GLuint p1_v,p1_t,p1_n; GLuint p1_index;
            GLuint p2_v,p2_t,p2_n; GLuint p2_index;
        };

        struct _Point3D {
            GLuint pv,pt,pn;
        };

        auto less_point_3d_=[](const _Point3D & l,const _Point3D &r) {
            if (l.pv<r.pv) { return true; }
            if (l.pv>r.pv) { return false; }
            if (l.pt<r.pt) { return true; }
            if (l.pt>r.pt) { return false; }
            return l.pn<r.pn;
        };

        typedef bool(*Less_point_3d_)(const _Point3D &,const _Point3D &);
        std::map< _Point3D,GLuint,Less_point_3d_> face_point_index_(less_point_3d_);

        auto insert_=[&face_point_index_](GLuint a,GLuint b,GLuint c)mutable->GLuint {
            _Point3D _p3d{ a,b,c };
            auto _i=face_point_index_.find(_p3d);
            if (_i!=face_point_index_.end()) {
                return _i->second;
            }
            auto _size=face_point_index_.size();
            face_point_index_[_p3d]=_size;
            return _size;
        };

        Face temp_face;
        std::list< Face > faces;

        {
            std::string key_word_;
            std::string line_;

            while (std::getline(stream_,line_)) try {

                if (line_.empty()) { continue; }
                if (std::regex_match(line_,r_space)) { continue; }

                std::stringstream stream(std::move(line_));
                stream.exceptions(std::ifstream::failbit|std::ifstream::badbit);
#if defined(NDEBUG)
                line_.clear();
#endif

                /*get the keyword*/
                stream>>key_word_;

                if (key_word_.empty()) { continue; }
                if (std::regex_match(key_word_,r_comment)) { continue; }
                if (std::regex_match(key_word_,r_vn)) {
                    GLfloat dx,dy,dz;
                    stream>>dx; stream>>dy; stream>>dz;
                    normals.emplace_back(dx,dy,dz);
                    continue;
                }

                if (std::regex_match(key_word_,r_vt)) {
                    GLfloat u,v;
                    stream>>u; stream>>v;
                    uvs.emplace_back(u,v);
                    continue;
                }

                if (std::regex_match(key_word_,r_v)) {
                    GLfloat x,y,z;
                    stream>>x; stream>>y; stream>>z;
                    positions.emplace_back(x,y,z);
                    mmx.setValue(x);
                    mmy.setValue(y);
                    mmz.setValue(z);
                    continue;
                }

                if (std::regex_match(key_word_,r_f)) {
                    std::getline(stream,line_);
                    std::smatch ans_;
                    if (std::regex_match(line_,ans_,r_face_data)) {

                        const std::string __ans__[]{
                            ans_[1].str(),ans_[2].str(),ans_[3].str(),
                            ans_[4].str(),ans_[5].str(),ans_[6].str(),
                            ans_[7].str(),ans_[8].str(),ans_[9].str()
                        };

                        temp_face.p0_v=std::stoi(__ans__[0],nullptr,10)-1;
                        temp_face.p0_t=std::stoi(__ans__[1],nullptr,10)-1;
                        temp_face.p0_n=std::stoi(__ans__[2],nullptr,10)-1;
                        temp_face.p0_index=insert_(temp_face.p0_v,temp_face.p0_t,temp_face.p0_n);

                        temp_face.p1_v=std::stoi(__ans__[3],nullptr,10)-1;
                        temp_face.p1_t=std::stoi(__ans__[4],nullptr,10)-1;
                        temp_face.p1_n=std::stoi(__ans__[5],nullptr,10)-1;
                        temp_face.p1_index=insert_(temp_face.p1_v,temp_face.p1_t,temp_face.p1_n);

                        temp_face.p2_v=std::stoi(__ans__[6],nullptr,10)-1;
                        temp_face.p2_t=std::stoi(__ans__[7],nullptr,10)-1;
                        temp_face.p2_n=std::stoi(__ans__[8],nullptr,10)-1;
                        temp_face.p2_index=insert_(temp_face.p2_v,temp_face.p2_t,temp_face.p2_n);

                    }
                    else { throw "???"; }
                    faces.push_back(temp_face);
                    continue;
                }
            }/*while*/
            catch (const std::ifstream::failure & e) {
                qDebug().noquote()<<e.what();
                return nullptr;
            }
            catch (...) {
                qDebug().noquote()<<"unknow error";
                return nullptr;
            }

        }

        std::vector<bool> _isPointsSet;
        ans=std::make_shared<OBJData>();
        auto & _points=ans->points;
        auto & _faces=ans->faces;

        {
            ans->zMin=mmz.getMin();
            ans->zMax=mmz.getMax();
            ans->xMin=mmx.getMin();
            ans->xMax=mmx.getMax();
            ans->yMin=mmy.getMin();
            ans->yMax=mmy.getMax();
        }

        _faces.reserve(faces.size());
        _points.resize(face_point_index_.size(),OBJData::PointNormalUV(1,1,1));
        _isPointsSet.resize(face_point_index_.size(),false);
        face_point_index_.clear();

        for (const auto & f:faces) {

            _faces.emplace_back(f.p0_index,f.p1_index,f.p2_index);

            if (_isPointsSet[f.p0_index]==false) {
                _isPointsSet[f.p0_index]=true;
                auto & __p=_points[f.p0_index];
                __p.point=positions[f.p0_v];
                __p.normal=normals[f.p0_n];
                __p.uv=uvs[f.p0_t];
            }

            if (_isPointsSet[f.p1_index]==false) {
                _isPointsSet[f.p1_index]=true;
                auto & __p=_points[f.p1_index];
                __p.point=positions[f.p1_v];
                __p.normal=normals[f.p1_n];
                __p.uv=uvs[f.p1_t];
            }

            if (_isPointsSet[f.p2_index]==false) {
                _isPointsSet[f.p2_index]=true;
                auto & __p=_points[f.p2_index];
                __p.point=positions[f.p2_v];
                __p.normal=normals[f.p2_n];
                __p.uv=uvs[f.p2_t];
            }
        }

        ans->textureFileName=textureFileName;
        ans->dirPath=std::move(dirPath);
    }/*~read data*/

    return std::move(ans);
}


