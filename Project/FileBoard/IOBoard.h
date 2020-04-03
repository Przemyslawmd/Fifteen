
#ifndef IOBoard_H
#define IOBoard_H

#include "IODataModel.h"
#include "../Board.h"
#include "../Message.h"
#include <QDataStream>

using std::unique_ptr;
using std::move;

class IOBoard
{
public:

    IOBoard();

    void writeBoardIntoFile( Board&, BoardMode, const QString& fileName );
    unique_ptr< vector< uint >> readBoardFromFile( const QString& fileName );
};

#endif

