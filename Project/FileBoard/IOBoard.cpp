
#include "IOBoard.h"
#include "IODataModel.h"
#include "IOFile.h"
#include "../MappedValues.h"
#include "../Options.h"
#include "../Message.h"
#include "../GraphicBoard/ImageProvider.h"
#include <memory>

using std::unique_ptr;

IOBoard::IOBoard(){}

/*********************************************************************************/
/*********************************************************************************/

void IOBoard::writeBoardIntoFile( Board& board, BoardMode boardMode, const QString& fileName )
{
    IOFile file( fileName, QIODevice::WriteOnly );
    QDataStream& stream = file.getDataStream();

    IODataModel dataModel( board, boardMode );
    dataModel.writeDataIntoStream( stream );
}

/*********************************************************************************/
/*********************************************************************************/

vector< uint >* IOBoard::readBoardFromFile( const QString& fileName )
{
    IOFile file( fileName, QIODevice::ReadOnly );
    QDataStream& stream = file.getDataStream();

    IODataModel dataModel;
    if ( auto result = dataModel.readDataFromStream( stream ); result != Result::OK )
    {
        Message::putMessage( result );
        return nullptr;
    }

    BoardMode boardMode = static_cast< BoardMode >( dataModel.boardMode );
    vector< uint >* boardNumbers = dataModel.values;

    if ( boardMode == BoardMode::GRAPHIC )
    {
        if ( auto result = ImageProvider::getInstance().restoreGraphicBoardFromFile( dataModel ); result != Result::OK )
        {
            Message::putMessage( result );
            return nullptr;
        }
    }

    Options::boardMode = boardMode;
    boardNumbers->push_back( Mapped::boardSizeInt.at( dataModel.boardSize ));
    return boardNumbers;
}

