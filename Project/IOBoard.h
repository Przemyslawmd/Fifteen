
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

    void insertBoardValuesIntoStream( QDataStream&, Board& );
    bool checkReadValues( vector< int >&, BoardSize );
};

#endif // IOBoard_H

