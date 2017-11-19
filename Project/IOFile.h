
#ifndef IOFILE_H
#define IOFILE_H

#include "Board.h"
#include "Options.h"
#include <QFile>
#include <QIODevice>
#include "GraphicBoard/ImageProvider.h"

class IOFile
{
public:
    IOFile();

    void saveNumericBoardInFile( Board* board, QString fileName );
    void saveGraphicBoardInFile( Board* board, QString fileName );
    int** readBoardFromFile( QString fileName );

private:

    QDataStream& getDataStream( QFile& file, QIODevice::OpenModeFlag mode );
    void insertBoardValuesIntoStream( QDataStream& stream, Board* board );
};

#endif // IOFILE_H
