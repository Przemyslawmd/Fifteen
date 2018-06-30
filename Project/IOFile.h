
#ifndef IOFILE_H
#define IOFILE_H

#include <QDataStream>
#include <QFile>

class IOFile
{

friend class IOBoard;

private:

    IOFile( QString& filePath, QIODevice::OpenModeFlag );
    ~IOFile();

    QDataStream& getDataStream();

    QFile file;
    QDataStream* stream;
};

#endif // IOFILE_H

