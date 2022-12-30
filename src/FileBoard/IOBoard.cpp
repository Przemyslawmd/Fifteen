
#include "IOBoard.h"
#include "../MappedValues.h"
#include "../Message.h"

#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>


void IOBoard::writeBoardIntoFile( Board& board, const QString& fileName )
{
    std::ofstream ofs( fileName.toStdString() );
    auto values = board.sendBoard();

    for ( uint value : values )
    {
        ofs << value <<',';
    }
    ofs << board.getSizeInt() << '\n';
}

/*********************************************************************************/
/*********************************************************************************/

std::unique_ptr< std::vector< uint >> IOBoard::readBoardFromFile( const QString& fileName )
{
    std::ifstream ifs( fileName.toStdString() );
    if ( !ifs )
    {
        Message::putMessage( Result::READ_BOARD_ERROR );
        return nullptr;
    }

    std::stringstream sstr;
    sstr << ifs.rdbuf();

    std::vector< uint > values;
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
            return nullptr;
        }
        values.push_back( boardValue );
    }

    if ( validate( values ) == false )
    {
        return nullptr;
    }
    return std::make_unique<std::vector< uint >>( values );
}

/*********************************************************************************/
/*********************************************************************************/

bool IOBoard::validate( const std::vector< uint >& values )
{
    uint boardSize = values[values.size() -1];
    if ( boardSize < 4 || boardSize > 7 )
    {
        Message::putMessage( Result::FILE_ERROR_SIZE_IMPROPER );
        return false;
    }

    if ( values.size() != boardSize * boardSize + 1 )
    {
        Message::putMessage( Result::FILE_ERROR_SIZE_NOT_FIT_VALUES );
        return false;
    }

    std::vector< uint > testValues;
    testValues.resize( boardSize * boardSize );
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

