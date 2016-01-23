#include <memory>
#include <QApplication>
#include <QImage>
#include <QDir>
#include <QDebug>
#include <QTextCodec>
#include <QFile>
#include <QTextStream>
#include "MainWindow.hpp"

namespace {
inline QStringList addSearchPath(QStringList base,QString path) {
    base.detach();
    for (auto & i:base) {
        QDir tmp( i );
        i=QDir::cleanPath( tmp.absoluteFilePath(path) );
    }
    return std::move(base);
}
}

int main(int argc, char *argv[]){

    QTextCodec::setCodecForLocale( QTextCodec::codecForName(THIS_PROJECT_LOCALCODEC) );

    QApplication app(argc, argv);

    { delete (new QImage("..null.png")); }

    {
        const QStringList search_path_base{ app.applicationDirPath(),QFile::decodeName(THIS_PROJECT_PWD) };
        QDir::setSearchPaths("images",addSearchPath(search_path_base,"images"));
        QDir::setSearchPaths("glsl",addSearchPath(search_path_base,"glsl"));
        QDir::setSearchPaths("obj3d",addSearchPath(search_path_base,"obj3d"));
    }

    MainWindow window;
    window.resize(512,512);
    window.show();

    return app.exec();
}





