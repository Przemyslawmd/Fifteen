
#ifndef IOFILE_H
#define IOFILE_H

#include <QDataStream>
#include <QFile>


class IOFile
{

friend class IOBoard;

private:

    IOFile( const QString& filePath, QIODevice::OpenModeFlag );
    IOFile( const IOFile& ) = delete;
    ~IOFile();

    QDataStream& getDataStream();

    QFile file;
    QDataStream* stream;
};

#endif

