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

    qDebug().noquote()<<"this project dir:"<<THIS_PROJECT_PWD;
    qDebug().noquote()<<"the computer system local codec:"<<THIS_PROJECT_LOCALCODEC;

    {
        const QStringList search_path_base{ app.applicationDirPath(),QFile::decodeName(THIS_PROJECT_PWD) };
        QDir::setSearchPaths("images",addSearchPath(search_path_base,"images"));
        QDir::setSearchPaths("glsl",addSearchPath(search_path_base,"glsl"));
    }

    {
        QFile file("images:readme.txt");
        file.open(QIODevice::ReadOnly);
        qDebug().noquote()<<file.readAll();
    }

    {
        QFile file("glsl:readme.txt");
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream stream(&file);
        qDebug().noquote()<<stream.readAll();
    }

    MainWindow window;
    window.show();

    return app.exec();
}



