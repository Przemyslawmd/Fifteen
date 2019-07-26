
#ifndef IOBoard_H
#define IOBoard_H

#include "IODataModel.h"
#include "../Board.h"
#include "../Message.h"
#include <QDataStream>


class IOBoard
{
public:

    IOBoard();

    void writeBoardIntoFile( Board&, BoardMode, const QString& fileName );
    vector< uint >* readBoardFromFile( const QString& fileName );
};

#endif

