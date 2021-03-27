
#ifndef IO_BOARD_H
#define IO_BOARD_H

#include "../Board.h"
#include <memory>


class IOBoard
{
public:

    IOBoard() = default;
    IOBoard( const IOBoard& ) = delete;
    IOBoard operator=( const IOBoard& ) = delete;

    void writeBoardIntoFile( Board&, BoardMode, const QString& fileName );
    std::unique_ptr< vector< uint >> readBoardFromFile( const QString& fileName );
};

#endif

