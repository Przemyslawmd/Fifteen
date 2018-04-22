
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

    void saveNumericBoardInFile( Board&, QString fileName );
    void saveGraphicBoardInFile( Board&, QString fileName );
    unique_ptr< vector< int >> readBoardFromFile( QString fileName );

private:

    unique_ptr< QDataStream > getDataStream( QFile&, QIODevice::OpenModeFlag );
    unique_ptr< QDataStream > insertBoardValuesIntoStream( unique_ptr< QDataStream >, Board& );
    bool checkReadValues( vector< int >&, BoardSize );
};

#endif // IOFILE_H

