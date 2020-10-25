
#ifndef IOBoard_H
#define IOBoard_H

#include "../Board.h"
#include <memory>

using std::unique_ptr;

class IOBoard
{
public:

    IOBoard() = default;
    IOBoard( const IOBoard& ) = delete;
    IOBoard operator=( const IOBoard& ) = delete;

    void writeBoardIntoFile( Board&, BoardMode, const QString& fileName );
    unique_ptr< vector< uint >> readBoardFromFile( const QString& fileName );
};

#endif

