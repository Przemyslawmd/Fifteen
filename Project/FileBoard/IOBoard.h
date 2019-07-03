
#ifndef IOBoard_H
#define IOBoard_H

#include "../Board.h"
#include "../Message.h"
#include <QDataStream>


class IOBoard
{
public:

    IOBoard();

    void saveNumericBoardInFile( Board&, const QString& fileName );
    void saveGraphicBoardInFile( Board&, const QString& fileName );
    Result readBoardFromFile( const QString& fileName, vector< uint >& );

private:

    void insertBoardValuesIntoStream( QDataStream&, Board& );
    void insertBoardPicturesIntoStream( QDataStream&, BoardSize );
    bool checkReadValues( vector< uint >& );
};

#endif

