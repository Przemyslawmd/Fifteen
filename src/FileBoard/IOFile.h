
#ifndef IOFILE_H
#define IOFILE_H

#include <fstream>
#include <memory>
#include <QDataStream>
#include <QFile>


class IOFile
{
private:

    friend class IOBoard;

    IOFile( const QString& filePath, QIODevice::OpenModeFlag );
    IOFile( const IOFile& ) = delete;
    IOFile operator=( const IOFile& ) = delete;
    ~IOFile();

    QDataStream& getDataStream();

    QFile file;
    std::unique_ptr< QDataStream > stream;
};

#endif

