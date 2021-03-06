
#include "Fifteen.h"

#include <QBuffer>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>

#include "FileBoard/IOBoard.h"
#include "GraphicBoard/ImageProvider.h"
#include "GUI/GUIAbout.h"
#include "GUI/GUIMain.h"
#include "GUI/GUISetting.h"
#include "MappedValues.h"
#include "Message.h"
#include "Options.h"


Fifteen::Fifteen( QWidget *parent ) : QMainWindow{ parent } {}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::initGame()
{
    resize( 850, 600 );
    board = std::make_unique< Board >( BoardSize::FOUR );
    gui = std::make_unique< GUI >( this );

    std::map< ActionMenu, std::function< void( void ) >> funcsMenu =
    {
        { ActionMenu::OPEN_GRAPHIC, std::bind( &Fifteen::slotLoadGraphic, this )},
        { ActionMenu::REM_GRAPHIC,  std::bind( &Fifteen::slotRemoveGraphic, this )},
        { ActionMenu::SAVE_BOARD,   std::bind( &Fifteen::slotSaveBoard, this )},
        { ActionMenu::LOAD_BOARD,   std::bind( &Fifteen::slotReadBoard, this )},
        { ActionMenu::SETTINGS,     std::bind( &Fifteen::slotSettings, this )},
        { ActionMenu::ABOUT,        std::bind( &Fifteen::slotAbout, this )},
    };
    gui->createMenu( funcsMenu );

    std::array< std::function< void( void ) >, 3 > funcsRightLayout =
    {
        std::bind( &Fifteen::slotGenerateBoard, this ),
        std::bind( &Fifteen::slotSolveBoard, this ),
        std::bind( &Fifteen::slotUndoMove, this ),
    };
    gui->createRightLayout( funcsRightLayout );

    gui->completeLayouts();
    redrawTiles();
    undoMoveService = std::make_unique< UndoMove >();
}

/*********************************************************************************/
/*********************************************************************************/

Fifteen::~Fifteen()
{
    ImageProvider::deleteInstance();
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::createTiles()
{
    BoardSize boardSize = board->getSize();
    TileSize tileSize = Options::boardMode == BoardMode::NUMERIC ?
                        Options::getTileSize() : ImageProvider::getInstance().getTileSize( boardSize );

    gui->createTiles( boardSize, tileSize, std::bind( &Fifteen::pressTile, this ));
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setTiles()
{
    if ( Options::boardMode == BoardMode::NUMERIC )
    {
        setTilesNumeric();
    }
    else
    {
        setTilesGraphic();
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setTilesNumeric()
{    
    auto iter = board->sendBoard().begin();

    int fontSizeInt = Maps::getFontSizeInt( Options::getTileSize() );
    QFont font;
    font.setPixelSize( fontSizeInt );

    uint emptyTile = board->getEmptyTile();
    auto tileColorStyle = Maps::tileColorStyle.at( Options::getTileColor() );

    for ( auto& tile : gui->getTiles() )
    {
        if ( *iter != emptyTile )
        {
            tile->setText( QString::number( *iter + 1 ));
            tile->setStyleSheet( tileColorStyle );
        }
        else
        {
            tile->setStyleSheet( Maps::tileColorStyle.at( TileColor::EMPTY_STYLE ));
        }

        tile->setFont( font );
        iter++;
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setTilesGraphic()
{
    BoardSize boardSize = board->getSize();
    auto iter = board->sendBoard().begin();

    ImageProvider& provider = ImageProvider::getInstance();
    auto& images = provider.getImages( boardSize );

    TileSize tileSize = provider.getTileSize( boardSize );
    uint tileSizeInt = Maps::tileSizeInt.at( tileSize );
    QSize iconSize( tileSizeInt, tileSizeInt );

    int fontSizeInt = Maps::getFontSizeInt( Options::getTileSize() );
    NumberColor numberColor = Options::getNumberOnImageColor();
    QIcon icon;

    for ( auto& tile : gui->getTiles() )
    {
        QPixmap pixmap = QPixmap::fromImage( *images.at( *iter ).get() );
        prepareQIconForTile( icon, pixmap, fontSizeInt, *iter, numberColor );
        tile->setIconSize( iconSize );
        tile->setIcon( icon );
        tile->setStyleSheet( "" );
        iter++;
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::prepareQIconForTile( QIcon& icon, QPixmap& pixmap, int fontSize, uint number, NumberColor numberColor )
{
    if ( numberColor == NumberColor::NO || number == board->getEmptyTile() )
    {
        icon.addPixmap( pixmap );
        return;
    }

    QPainter painter( &pixmap );
    painter.setFont( QFont( "Times", fontSize, QFont::Bold ));
    QColor color = numberColor == NumberColor::WHITE ? QColor( 255, 255, 255 ) : QColor( 0, 0, 0 );
    painter.setPen( color );
    painter.drawText( pixmap.rect(), Qt::AlignCenter, QString::number( number + 1 ));
    icon.addPixmap( pixmap );
    painter.end();
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotGenerateBoard()
{
    BoardSize boardSize = gui->checkRadioBoardSize();
    BoardMode requestedBoardMode = gui->checkRadioBoardMode( BoardMode::GRAPHIC ) ? BoardMode::GRAPHIC : BoardMode::NUMERIC;

    if ( requestedBoardMode == BoardMode::GRAPHIC && ImageProvider::getInstance().isGraphicBoard( boardSize ) == false )
    {
        QMessageBox::information( this, "", "There is no loaded graphic for a chosen board size\t" );
        return;
    }

    Options::boardMode = requestedBoardMode;
    board.reset( new Board( boardSize ));
    board->randomBoard();
    redrawTiles();
    undoMoveService->Reset();
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotSolveBoard()
{
    board->solveBoard();
    setTiles();
    undoMoveService->Reset();
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotUndoMove()
{
    uint position = undoMoveService->GetMove();

    if ( position == MOVE_STACK_EMPTY )
    {
        QMessageBox::information( this, "", "There are no moves\t" );
        return;
    }

    uint row = position / 10;
    uint col = position % 10;
    Move move = board->checkMove( row, col );
    makeMove( move, row, col );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::pressTile()
{
    uint position = ( static_cast< QPushButton* >( sender() ))->accessibleName().toUInt();

    uint row = position / 10;
    uint col = position % 10;
    Move move = board->checkMove( row, col );

    if ( move == Move::NOT_ALLOWED )
    {
        return;
    }

    undoMoveService->PutMove( move, row, col );
    makeMove( move, row, col );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::makeMove( Move move, uint row, uint col )
{
    auto moveTile = ( Options::boardMode == BoardMode::NUMERIC ) ? &Fifteen::moveNumericTile :
                                                                   &Fifteen::moveGraphicTile;

    switch ( move )
    {
        case Move::UP:
            return ( this->*moveTile )( row, col, row - 1, col );
        case Move::RIGHT:
            return ( this->*moveTile )( row, col, row, col + 1 );
        case Move::DOWN:
            return ( this->*moveTile )( row, col, row + 1, col );
        case Move::LEFT:
            return ( this->*moveTile )( row, col, row, col - 1 );
        default:
            return;
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::moveNumericTile( uint rowSource, uint colSource, uint rowDest, uint colDest )
{
    auto tileColorStyle = Maps::tileColorStyle.at( Options::getTileColor() );
    uint boardSize = Maps::boardSizeInt.at( board->getSize() );
    auto& tiles = gui->getTiles();

    tiles.at( rowDest * boardSize + colDest )->setText( tiles.at( rowSource * boardSize + colSource )->text() );
    tiles.at( rowDest * boardSize + colDest )->setStyleSheet( tileColorStyle );
    tiles.at( rowSource * boardSize + colSource )->setText( "" );
    tiles.at( rowSource * boardSize + colSource )->setStyleSheet( Maps::tileColorStyle.at( TileColor::EMPTY_STYLE ));
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::moveGraphicTile( uint rowSource, uint colSource, uint rowDest, uint colDest )
{
    BoardSize boardSize = board->getSize();
    uint boardSizeInt = Maps::boardSizeInt.at( boardSize );
    auto& tiles = gui->getTiles();

    tiles.at( rowDest * boardSizeInt + colDest )->setIcon( tiles.at( rowSource * boardSizeInt + colSource )->icon() );
    TileSize tileSize = ImageProvider::getInstance().getTileSize( boardSize );
    uint tileSizeInt = Maps::tileSizeInt.at( tileSize );
    QPixmap pixmap( tileSizeInt, tileSizeInt );
    pixmap.fill( Qt::white );
    QIcon nullIcon( pixmap );
    tiles.at( rowSource * boardSizeInt + colSource )->setIcon( nullIcon );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotLoadGraphic()
{
    QString file = nullptr;
    if ( file = QFileDialog::getOpenFileName( this, "", QDir::currentPath(), tr( "JPG, PNG, GIF, BMP (*.jpg *.png *.gif *.bmp)" ));
         file.isEmpty())
    {
        return;
    }

    QImage image;
    if ( image.load( file ); image.isNull() )
    {
        QMessageBox::information( this, "", "Failure of loading an image\t" );
        return;
    }

    ImageProvider& provider = ImageProvider::getInstance();
    provider.prepareGraphicBoard( image, Options::getTileSize() );

    if ( provider.isGraphicBoard( BoardSize::FOUR ) || provider.isGraphicBoard( BoardSize::FIVE ) ||
         provider.isGraphicBoard( BoardSize::SIX )  || provider.isGraphicBoard( BoardSize::SEVEN ))
    {
        gui->setActionMenuState( ActionMenu::REM_GRAPHIC, true );
    }

    QMessageBox::information( this, "", Message::getMessages() );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotRemoveGraphic()
{
    ImageProvider::deleteInstance();    
    gui->setActionMenuState( ActionMenu::REM_GRAPHIC, false );
    gui->setRadioBoardMode( BoardMode::NUMERIC );

    if ( Options::boardMode == BoardMode::GRAPHIC )
    {
        Options::boardMode = BoardMode::NUMERIC;
        redrawTiles();
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotSaveBoard()
{
    QString file = nullptr;
    if ( file = QFileDialog::getSaveFileName( this, "", QDir::currentPath() );
         file.isEmpty() )
    {
        return;
    }

    IOBoard ioBoard;
    ioBoard.writeBoardIntoFile( *board, Options::boardMode, file );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotReadBoard()
{    
    QString file = nullptr;
    if ( file = QFileDialog::getOpenFileName( this, "", QDir::currentPath() );
         file.isEmpty() )
    {
        return;
    }

    IOBoard ioBoard;
    auto values = ioBoard.readBoardFromFile( file );
    if ( values == nullptr )
    {
        QMessageBox::information( this, "", Message::getMessages() );
        return;
    }

    BoardSize boardSize = Maps::getBoardSizeByInt( values->back() );
    values->pop_back();
    board.reset( new Board( *values, boardSize ));
    redrawTiles();

    gui->setRadioSize( boardSize );
    gui->setRadioBoardMode( Options::boardMode );
    gui->setActionMenuState( ActionMenu::REM_GRAPHIC, Options::boardMode == BoardMode::GRAPHIC );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setColor()
{
    auto tileColorStyle = Maps::tileColorStyle.at( Options::getTileColor() );

    for ( auto &tile : gui->getTiles() )
    {
        if ( tile->styleSheet() != Maps::tileColorStyle.at( TileColor::EMPTY_STYLE ))
        {
            tile->setStyleSheet( tileColorStyle );
        }
    }    
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::redrawTiles()
{
    createTiles();
    setTiles();
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotSettings()
{
    new GUISetting( *this );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotAbout()
{
    new GUIAbout();
}

