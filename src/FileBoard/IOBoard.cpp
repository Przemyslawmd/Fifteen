
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
    ofs << Maps::boardSizeInt.at( board.getSize() );
    ofs << '\n';
}

/*********************************************************************************/
/*********************************************************************************/

std::unique_ptr< std::vector< uint >> IOBoard::readBoardFromFile( const QString& fileName )
{
    std::vector< uint > numbers;
    std::ifstream ifs( fileName.toStdString() );
    if ( !ifs ) {
        return nullptr;
    }

    std::stringstream sstr;
    sstr << ifs.rdbuf();

    std::string number_as_string;
    while(std::getline( sstr, number_as_string, ',' ))  {
        numbers.push_back( std::stoi(number_as_string ));
    }
    return std::make_unique<std::vector< uint >>( numbers );
}

