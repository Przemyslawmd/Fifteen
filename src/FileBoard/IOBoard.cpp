
#include "IOBoard.h"

#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

#include "../MappedValues.h"
#include "../Message.h"


void IOBoard::writeBoardIntoFile( const Board& board, const std::string& fileName )
{
    std::ofstream ofs( fileName );
    if ( !ofs )
    {
        return;
    }

    const auto& values = board.getBoardValues();
    for ( uint value : values )
    {
        ofs << value << ',';
    }
    ofs << board.getSizeInt() << '\n';
    ofs.close();
}

/*********************************************************************************/
/*********************************************************************************/

std::optional<std::vector<size_t>> IOBoard::readBoardFromFile( const std::string& fileName )
{
    std::ifstream ifs( fileName );
    if ( !ifs )
    {
        Message::putMessage( Result::READ_BOARD_ERROR );
        return std::nullopt;
    }

    std::stringstream sstr;
    sstr << ifs.rdbuf();
    ifs.close();

    std::vector<size_t> values;
    std::string value_as_string;
    uint boardValue;
    while( std::getline( sstr, value_as_string, ',' ))
    {
        try
        {
            boardValue = std::stoi( value_as_string );
        }
        catch (...)
        {
            Message::putMessage( Result::FILE_ERROR_VALUE_NOT_NUMBER );
            return std::nullopt;
        }
        values.push_back( boardValue );
    }

    if ( validate( values ) == false )
    {
        return std::nullopt;
    }
    return values;
}

/*********************************************************************************/
/*********************************************************************************/

bool IOBoard::validate( const std::vector<size_t>& values ) const
{
    uint boardSize = values[values.size() -1];
    if (( boardSize < 4 ) || ( boardSize > 7 ))
    {
        Message::putMessage( Result::FILE_ERROR_SIZE_IMPROPER );
        return false;
    }

    if ( values.size() != boardSize * boardSize + 1 )
    {
        Message::putMessage( Result::FILE_ERROR_SIZE_NOT_FIT_VALUES );
        return false;
    }

    std::vector<uint> testValues( boardSize * boardSize, 0 );
    std::iota( testValues.begin(), testValues.end(), 0 );

    for ( uint test : testValues )
    {
        if ( std::find( values.cbegin(), values.cend(), test ) == values.cend() )
        {
            Message::putMessage( Result::FILE_ERROR_VALUE_IMPROPER );
            return false;
        }
    }
    return true;
}

