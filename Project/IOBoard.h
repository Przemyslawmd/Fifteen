
#ifndef IOBoard_H
#define IOBoard_H

#include "Board.h"
#include <QFile>
#include <QIODevice>
#include <memory>

using std::unique_ptr;

class IOBoard
{
public:
    IOBoard();

    void saveNumericBoardInFile( Board&, QString fileName );
    void saveGraphicBoardInFile( Board&, QString fileName );
    bool readBoardFromFile( QString fileName, vector< int >& );

private:

    unique_ptr< QDataStream > getDataStream( QFile&, QIODevice::OpenModeFlag );
    unique_ptr< QDataStream > insertBoardValuesIntoStream( unique_ptr< QDataStream >, Board& );
    bool checkReadValues( vector< int >&, BoardSize );
};

#endif // IOBoard_H

