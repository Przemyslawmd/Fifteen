
#ifndef IO_BOARD_H
#define IO_BOARD_H

#include <memory>
#include "../Board.h"

class IOBoard
{
public:

    IOBoard() = default;
    IOBoard( const IOBoard& ) = delete;
    IOBoard operator=( const IOBoard& ) = delete;

    void writeBoardIntoFile( Board&, BoardMode, const QString& fileName );
    std::unique_ptr< std::vector< uint >> readBoardFromFile( const QString& fileName );
};

#endif

