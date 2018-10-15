
#ifndef IOBoard_H
#define IOBoard_H

#include "../Board.h"
#include <QFile>
#include <QIODevice>
#include <memory>

using std::unique_ptr;

class IOBoard
{
public:

    IOBoard();

    void saveNumericBoardInFile( Board&, const QString& fileName );
    void saveGraphicBoardInFile( Board&, const QString& fileName );
    bool readBoardFromFile( const QString& fileName, vector< int >& );

private:

    void insertBoardValuesIntoStream( QDataStream&, Board& );
    void insertBoardPicturesIntoStream( QDataStream&, BoardSize );
    bool checkReadValues( vector< int >&, int squareCount );
};

#endif // IOBoard_H

