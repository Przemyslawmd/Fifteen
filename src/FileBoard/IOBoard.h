
#ifndef IO_BOARD_H
#define IO_BOARD_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "../Board.h"


class IOBoard
{
public:

    IOBoard() = default;
    IOBoard( const IOBoard& ) = delete;
    IOBoard( IOBoard&& ) = delete;
    IOBoard& operator=( const IOBoard& ) = delete;
    IOBoard& operator=( IOBoard&& ) = delete;

    void writeBoardIntoFile( Board&, const std::string& fileName );
    std::optional<std::vector<size_t>> readBoardFromFile( const std::string& fileName );

private:

    bool validate( const std::vector<size_t>& ) const;
};

#endif

