
#include "IOBoard.h"
#include "../MappedValues.h"
#include "../Options.h"
#include "../GraphicBoard/ImageProvider.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


void IOBoard::writeBoardIntoFile( Board& board, const QString& fileName )
{
    std::ofstream ofs( fileName.toStdString() );
    auto values = board.sendBoard();

    for ( uint v : values ) {
        ofs << v <<',';
    }
    ofs << board.getSizeInt();
    ofs << '\n';
}

/*********************************************************************************/
/*********************************************************************************/

std::unique_ptr< std::vector< uint >> IOBoard::readBoardFromFile( const QString& fileName )
{
    std::ifstream ifs( fileName.toStdString() );
    if ( !ifs ) {
        Message::putMessage( Result::READ_BOARD_ERROR );
        return nullptr;
    }

    std::stringstream sstr;
    sstr << ifs.rdbuf();

    std::vector< uint > numbers;
    std::string number_as_string;
    uint boardValue;
    while( std::getline( sstr, number_as_string, ',' ))  {
        try
        {
            boardValue = std::stoi( number_as_string );
        }
        catch (...)
        {
            Message::putMessage( Result::FILE_ERROR_VALUE_NOT_NUMBER );
            return nullptr;
        }
        numbers.push_back( boardValue );
    }

    if ( validate( numbers ) == false ) {
        return nullptr;
    }

    return std::make_unique<std::vector< uint >>( numbers );
}

/*********************************************************************************/
/*********************************************************************************/

bool IOBoard::validate( const std::vector< uint >& values )
{
    uint boardSize = values[values.size() -1];

    if ( boardSize < 4 || boardSize > 7 )
    {
        Message::putMessage( Result::FILE_ERROR_IMPROPER_SIZE );
        return false;
    }

    if ( values.size() != boardSize * boardSize + 1 )
    {
        Message::putMessage( Result::FILE_ERROR_SIZE_NOT_FIT_VALUES );
        return false;
    }

    return true;
}

