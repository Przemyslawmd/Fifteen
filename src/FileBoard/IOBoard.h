
#ifndef IO_BOARD_H
#define IO_BOARD_H

#include <QString>

#include <memory>
#include "../Board.h"


class IOBoard
{
public:

    IOBoard() = default;
    IOBoard( const IOBoard& ) = delete;
    IOBoard operator=( const IOBoard& ) = delete;

    void writeBoardIntoFile( Board&, const QString& fileName );
    std::unique_ptr< std::vector< uint >> readBoardFromFile( const QString& fileName );

private:

    bool validate( const std::vector< uint >& );
};

#endif

