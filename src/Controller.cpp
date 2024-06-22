
#include "Controller.h"
#include "Options.h"
#include "MappedValues.h"


Controller::Controller() 
{
    board = std::make_unique<Board>( BoardSize::FOUR, BoardMode::NUMERIC );
    undoMoveService = std::make_unique<UndoMove>();
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
    board->generateBoard();
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

std::vector<size_t>& Controller::getValues()
{
    return board->getBoardValues();
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

std::tuple<size_t, size_t> Controller::getBoardAttributes()
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

std::tuple<Move, size_t, size_t> Controller::makeMove( uint tilePosition )
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
    imageProvider = std::make_unique<ImageProvider>();
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
    if ( values == std::nullopt )
    {
        return false;
    }

    uint savedBoardSize = values->back();
    if ( savedBoardSize != board->getSizeInt() ) {
        Message::putMessage( Result::FILE_INFO_SIZE_IMPROPER, values->back() );
        return false;
    }

    values.value().pop_back();
    board.reset( new Board( std::move( values.value() ), board->getSize(), board->getMode() ));
    return true;
}

/*********************************************************************************/
/*********************************************************************************/

std::tuple<Move, size_t, size_t> Controller::undoMove()
{
    std::optional<size_t> position = undoMoveService->GetMove();
    if ( position == std::nullopt )
    {
        return { Move::NOT_ALLOWED, 0, 0 };
    }

    uint row = position.value() / 10;
    uint col = position.value() % 10;
    Move move = board->checkMove( row, col );
    return { move, row, col };
}

