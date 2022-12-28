
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
            Message::putMessage( Result::READ_BOARD_ERROR_VALUE_NOT_NUMBER );
            return nullptr;
        }
        numbers.push_back( boardValue );
    }
    return std::make_unique<std::vector< uint >>( numbers );
}

bool IOBoard::validate( const std::vector< uint > )
{
    return true;
}

