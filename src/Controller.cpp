
#include "Controller.h"
#include "Options.h"
#include "MappedValues.h"


Controller::Controller() 
{
    board = std::make_unique< Board >( BoardSize::FOUR, BoardMode::NUMERIC );
    undoMoveService = std::make_unique< UndoMove >();
}

/*********************************************************************************/
/*********************************************************************************/

Board* Controller::getBoard()
{
    return board.get();
}

/*********************************************************************************/
/*********************************************************************************/

void Controller::generateBoard( BoardSize boardSize, BoardMode boardMode )
{
    board.reset( new Board( boardSize, boardMode ));
    board->randomBoard();
    undoMoveService->Reset();
}

/*********************************************************************************/
/*********************************************************************************/

void Controller::solveBoard()
{
    board->solveBoard();
    undoMoveService->Reset();
}

/*********************************************************************************/
/*********************************************************************************/

std::tuple< uint, uint > Controller::getBoardAttributes()
{
    BoardSize boardSize = board->getSize();
    TileSize tileSize = board->getMode() == BoardMode::NUMERIC ?
                        Options::getTileSize() : getTileSize( boardSize );
    return { Maps::boardSizeInt.at( boardSize ), Maps::tileSizeInt.at( tileSize ) };
}

/*********************************************************************************/
/*********************************************************************************/

bool Controller::loadGraphic( QImage& image )
{
    imageProvider = std::make_unique< ImageProvider >();
    imageProvider->prepareGraphicBoard( image, Options::getTileSize() );

    return imageProvider->isGraphicBoard( BoardSize::FOUR ) || imageProvider->isGraphicBoard( BoardSize::FIVE ) ||
           imageProvider->isGraphicBoard( BoardSize::SIX )  || imageProvider->isGraphicBoard( BoardSize::SEVEN );
}

/*********************************************************************************/
/*********************************************************************************/

void Controller::removeGraphic()
{
    imageProvider.reset();
}

/*********************************************************************************/
/*********************************************************************************/

std::vector< std::unique_ptr< QImage >>& Controller::getImages( BoardSize boardSize )
{
    return imageProvider->getImages( boardSize );
}

/*********************************************************************************/
/*********************************************************************************/

bool Controller::isGraphic( BoardSize boardSize )
{
    return imageProvider != nullptr && imageProvider->isGraphicBoard( boardSize );
}

/*********************************************************************************/
/*********************************************************************************/

TileSize Controller::getTileSize( BoardSize boardSize )
{
    return imageProvider->getTileSize( boardSize );
}

/*********************************************************************************/
/*********************************************************************************/

void Controller::writeBoardIntoFile( const std::string& file )
{
    IOBoard ioBoard;
    ioBoard.writeBoardIntoFile( *board, file );
}

/*********************************************************************************/
/*********************************************************************************/

void Controller::readBoardFromFile( const std::string& file )
{
    IOBoard ioBoard;
    auto values = ioBoard.readBoardFromFile( file );
    if ( values == nullptr )
    {
        return;
    }

    uint savedBoardSize = values->back();
    if ( savedBoardSize != board->getSizeInt() ) {
        Message::putMessage( Result::FILE_INFO_SIZE_IMPROPER, values->back() );
        return;
    }

    values->pop_back();
    board.reset( new Board( *values, board->getSize(), board->getMode() ));
}

/*********************************************************************************/
/*********************************************************************************/

void Controller::putMove( Move move, uint row, uint col )
{
    undoMoveService->PutMove( move, row, col );
}

/*********************************************************************************/
/*********************************************************************************/

uint Controller::getUndoMove()
{
    return undoMoveService->GetMove();
}

