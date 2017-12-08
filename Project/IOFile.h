
#ifndef IOFILE_H
#define IOFILE_H

#include "Board.h"
#include <QFile>
#include <QIODevice>
#include <memory>

using std::unique_ptr;

class IOFile
{
public:
    IOFile();

    void saveNumericBoardInFile( Board* board, QString fileName );
    void saveGraphicBoardInFile( Board* board, QString fileName );
    int** readBoardFromFile( QString fileName );

private:

    unique_ptr< QDataStream > getDataStream( QFile& file, QIODevice::OpenModeFlag mode );
    unique_ptr< QDataStream > insertBoardValuesIntoStream( unique_ptr< QDataStream > stream, Board* board );
};

#endif // IOFILE_H
