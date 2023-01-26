
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

Result Controller::generateBoard( BoardSize boardSize, BoardMode boardMode )
{
    if ( boardMode == BoardMode::GRAPHIC && ( isGraphic( boardSize ) == false ))
    {
        return Result::CREATE_GRAPHIC_BOARD_NO_GRAPHIC;
    }
    board.reset( new Board( boardSize, boardMode ));
    board->randomBoard();
    undoMoveService->Reset();
    return Result::OK;
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

std::vector< uint >& Controller::getValues()
{
    return board->sendValues();
}

/*********************************************************************************/
/*********************************************************************************/

uint Controller::getNullValue()
{
    return board->getNullValue();
}

/*********************************************************************************/
/*********************************************************************************/

BoardMode Controller::getBoardMode()
{
    return board->getMode();
}

/*********************************************************************************/
/*********************************************************************************/

std::tuple< uint, uint > Controller::getBoardAttributes()
{
    BoardSize boardSize = board->getSize();
    uint tileSize = board->getMode() == BoardMode::NUMERIC ?
                        Options::getTileSize() : imageProvider->getTileSize( boardSize );
    return { Maps::boardSizeInt.at( boardSize ), tileSize };
}

/*********************************************************************************/
/*********************************************************************************/

uint Controller::getFontSize()
{
    return board->getMode() == BoardMode::NUMERIC ?
           Options::getFontSize() : imageProvider->getFontSize( board->getSize() );
}

/*********************************************************************************/
/*********************************************************************************/

std::tuple< Move, uint, uint > Controller::makeMove( uint tilePosition )
{
    uint row = tilePosition / 10;
    uint col = tilePosition % 10;
    Move move = board->checkMove( row, col );
    if ( move == Move::NOT_ALLOWED )
    {
        return { Move::NOT_ALLOWED, 0, 0 };
    }

    undoMoveService->PutMove( move, row, col );
    return { move, row, col };
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

bool Controller::removeGraphic()
{
    imageProvider.reset();

    if ( board->getMode() == BoardMode::GRAPHIC )
    {
        board->setMode( BoardMode::NUMERIC );
        return true;
    }
    return false;
}

/*********************************************************************************/
/*********************************************************************************/

std::vector< std::unique_ptr< QImage >>& Controller::getImages()
{
    return imageProvider->getImages( board->getSize() );
}

/*********************************************************************************/
/*********************************************************************************/

bool Controller::isGraphic( BoardSize boardSize )
{
    return imageProvider != nullptr && imageProvider->isGraphicBoard( boardSize );
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

bool Controller::readBoardFromFile( const std::string& file )
{
    IOBoard ioBoard;
    auto values = ioBoard.readBoardFromFile( file );
    if ( values == nullptr )
    {
        return false;
    }

    uint savedBoardSize = values->back();
    if ( savedBoardSize != board->getSizeInt() ) {
        Message::putMessage( Result::FILE_INFO_SIZE_IMPROPER, values->back() );
        return false;
    }

    values->pop_back();
    board.reset( new Board( *values, board->getSize(), board->getMode() ));
    return true;
}

/*********************************************************************************/
/*********************************************************************************/

std::tuple< Move, uint, uint > Controller::undoMove()
{
    uint position = undoMoveService->GetMove();
    if ( position == MOVE_STACK_EMPTY )
    {
        return { Move::NOT_ALLOWED, 0, 0 };
    }

    uint row = position / 10;
    uint col = position % 10;
    Move move = board->checkMove( row, col );
    return { move, row, col };
}

