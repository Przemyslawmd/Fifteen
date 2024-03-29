
#ifndef IO_BOARD_H
#define IO_BOARD_H

#include "../Board.h"

#include <memory>
#include <optional>


class IOBoard
{
public:

    IOBoard() = default;
    IOBoard( const IOBoard& ) = delete;
    IOBoard( IOBoard&& ) = delete;
    IOBoard& operator=( const IOBoard& ) = delete;
    IOBoard& operator=( IOBoard&& ) = delete;

    void writeBoardIntoFile( Board&, const std::string& fileName );
    std::optional< std::vector< uint >> readBoardFromFile( const std::string& fileName );

private:

    bool validate( const std::vector< uint >& ) const;
};

#endif

