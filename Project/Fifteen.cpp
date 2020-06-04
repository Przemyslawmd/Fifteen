
#include "Fifteen.h"
#include "Message.h"
#include "GUI/GUIMain.h"
#include "GUI/GUISetting.h"
#include "GUI/GUIAbout.h"
#include "FileBoard/IOBoard.h"
#include "Options.h"
#include "GraphicBoard/ImageProvider.h"
#include "MappedValues.h"
#include <QPainter>
#include <QBuffer>
#include <QMessageBox>
#include <QFileDialog>
#include <QFont>

Fifteen::Fifteen( QWidget *parent ) : QMainWindow{ parent } {}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::initGame()
{
    resize( 850, 600 );
    board = std::make_unique< Board >( BoardSize::FOUR );
    gui = std::make_unique< GUI >();

    map< ActionMenu, std::function< void( void ) >> funcsMenu =
    {
        { ActionMenu::OPEN_GRAPHIC, std::bind( &Fifteen::slotLoadGraphic, this )},
        { ActionMenu::REM_GRAPHIC,  std::bind( &Fifteen::slotRemoveGraphic, this )},
        { ActionMenu::SAVE_BOARD,   std::bind( &Fifteen::slotSaveBoard, this )},
        { ActionMenu::LOAD_BOARD,   std::bind( &Fifteen::slotReadBoard, this )},
        { ActionMenu::SETTINGS,     std::bind( &Fifteen::slotSettings, this )},
        { ActionMenu::ABOUT,        std::bind( &Fifteen::slotAbout, this )},
    };
    gui->createMenu( this, funcsMenu );

    array< std::function< void( void ) >, 3 > funcsRightLayout =
    {
        std::bind( &Fifteen::slotGenerateBoard, this ),
        std::bind( &Fifteen::slotSolveBoard, this ),
        std::bind( &Fifteen::slotUndoMove, this ),
    };
    gui->createRightLayout( this, funcsRightLayout );

    gui->completeLayouts( this );
    redrawTiles();
    undoMoveService = nullptr;
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
                        Options::tileSize : ImageProvider::getInstance().getTileSize( boardSize );

    gui->createTiles( this, boardSize, tileSize, std::bind( &Fifteen::pressTile, this ));
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
    auto values = board->sendBoard();
    auto iter = values.begin();

    int fontSizeInt = Mapped::fontSizeInt.at( Options::getFontSize() );
    QFont font;
    font.setPixelSize( fontSizeInt );

    uint emptyTile = board->getEmptyTile();

    for ( auto &tile : gui->getTiles() )
    {
        if ( *iter != emptyTile )
        {
            tile->setText( QString::number( *iter + 1 ));
            tile->setStyleSheet( Options::getStyle() );
        }
        else
        {
            tile->setStyleSheet( Mapped::tileColorStyle.at( TileColor::EMPTY_STYLE ));
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
    vector< uint >& values = board->sendBoard();

    ImageProvider& provider = ImageProvider::getInstance();
    auto& images = provider.getImages( boardSize );

    TileSize tileSize = provider.getTileSize( boardSize );
    uint tileSizeInt = Mapped::tileSizeInt.at( tileSize );
    QSize iconSize( tileSizeInt, tileSizeInt );

    FontSize fontSize = Mapped::tileSizeFontSize.at( tileSize );
    uint fontSizeInt = Mapped::fontSizeInt.at( fontSize );

    auto numOnImage = Options::isNumberOnImage();

    uint i = 0;
    for ( auto &tile : gui->getTiles() )
    {
        QPixmap pixmap = QPixmap::fromImage( *images.at( values.at( i )).get() );

        QIcon icon;
        if ( numOnImage->isNumberOnImage )
        {
            prepareIconWithNumber( icon, pixmap, numOnImage->fontColor, fontSizeInt, values.at( i ));
        }
        else
        {
            icon.addPixmap( pixmap );
        }

        tile->setIconSize( iconSize );
        tile->setIcon( icon );
        tile->setStyleSheet( "" );
        i++;
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::prepareIconWithNumber( QIcon& icon, QPixmap& pixmap, QColor penColor, int fontSize, uint number )
{
    if ( number != board->getEmptyTile() )
    {
        QPainter painter( &pixmap );
        painter.setFont( QFont( "Times", fontSize, QFont::Bold ));
        painter.setPen( penColor );
        painter.drawText( pixmap.rect(), Qt::AlignCenter, QString::number( number + 1 ));
        icon.addPixmap( pixmap );
        painter.end();
    }
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

    if ( undoMoveService )
    {
        undoMoveService->Reset();
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotSolveBoard()
{
    board->solveBoard();
    setTiles();

    if ( undoMoveService )
    {
        undoMoveService->Reset();
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotUndoMove()
{
    uint position = undoMoveService->GetMove();

    if ( position == MOVE_STACK_EMPTY )
    {
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

    if ( Options::isUndoEnabled() )
    {
        undoMoveService->PutMove( move, row, col );
    }

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
    const QString& currentStyle = Options::getStyle();
    uint boardSize = Mapped::boardSizeInt.at( board->getSize() );
    auto& tiles = gui->getTiles();

    tiles.at( rowDest * boardSize + colDest )->setText( tiles.at( rowSource * boardSize + colSource )->text() );
    tiles.at( rowDest * boardSize + colDest )->setStyleSheet( currentStyle );
    tiles.at( rowSource * boardSize + colSource )->setText( "" );
    tiles.at( rowSource * boardSize + colSource )->setStyleSheet( Mapped::tileColorStyle.at( TileColor::EMPTY_STYLE ));
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::moveGraphicTile( uint rowSource, uint colSource, uint rowDest, uint colDest )
{
    BoardSize boardSize = board->getSize();
    uint boardSizeInt = Mapped::boardSizeInt.at( boardSize );
    auto& tiles = gui->getTiles();

    tiles.at( rowDest * boardSizeInt + colDest )->setIcon( tiles.at( rowSource * boardSizeInt + colSource )->icon() );
    TileSize tileSize = ImageProvider::getInstance().getTileSize( boardSize );
    uint tileSizeInt = Mapped::tileSizeInt.at( tileSize );
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
    provider.prepareGraphicBoard( image, Options::tileSize );

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

    BoardSize boardSize = Mapped::getBoardSizeByInt( values->back() );
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
    const QString& currentStyle = Options::getStyle();

    for ( auto &tile : gui->getTiles() )
    {
        if ( tile->styleSheet() != Mapped::tileColorStyle.at( TileColor::EMPTY_STYLE ))
        {
            tile->setStyleSheet( currentStyle );
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

void Fifteen::createUndoMovesService()
{
    undoMoveService = unique_ptr< UndoMove >( new UndoMove() );
    gui->setStatePushUndo( false );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::deleteUndoMovesService()
{
    delete undoMoveService.release();
    gui->setStatePushUndo( true );
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

