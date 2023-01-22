
#include "Fifteen.h"

#include "GraphicBoard/ImageProvider.h"
#include "GUI/GUIAbout.h"
#include "GUI/GUIMain.h"
#include "GUI/GUISetting.h"
#include "MappedValues.h"
#include "Message.h"
#include "Options.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>


Fifteen::Fifteen( QWidget *parent ) : QMainWindow{ parent } {}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::initGame()
{
    resize( 850, 600 );
    controller = std::make_unique< Controller >();
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
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::createTiles()
{
    auto [ boardSize, tileSize ] = controller->getBoardAttributes();
    gui->createTiles( boardSize, tileSize, std::bind( &Fifteen::pressTile, this ));
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setTiles()
{
    Board& board = controller->getBoard();
    if ( board.getMode() == BoardMode::NUMERIC )
    {
        setTilesNumeric( board );
    }
    else
    {
        setTilesGraphic( board );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setTilesNumeric( Board& board )
{    
    auto iter = board.sendBoard().begin();

    int fontSizeInt = Maps::getFontSizeInt( Options::getTileSize() );
    QFont font;
    font.setPixelSize( fontSizeInt );

    uint emptyTile = board.getEmptyTile();
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

void Fifteen::setTilesGraphic( Board& board )
{
    auto [ boardSizeInt, tileSizeInt ] = controller->getBoardAttributes();
    auto iter = board.sendBoard().begin();

    const auto& images = controller->getImages();
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
    Board& board = controller->getBoard();
    if ( numberColor == NumberColor::NO || number == board.getEmptyTile() )
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
    BoardMode boardMode = gui->checkRadioBoardMode( BoardMode::GRAPHIC ) ? BoardMode::GRAPHIC : BoardMode::NUMERIC;

    if ( controller->generateBoard( boardSize, boardMode ) == false )
    {
        QMessageBox::information( this, "", "There is no loaded graphic for a chosen board size\t" );
        return;
    }
    redrawTiles();
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotSolveBoard()
{
    controller->solveBoard();
    setTiles();
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotUndoMove()
{
    uint position = controller->getUndoMove();

    if ( position == MOVE_STACK_EMPTY )
    {
        QMessageBox::information( this, "", "There are no moves\t" );
        return;
    }

    uint row = position / 10;
    uint col = position % 10;
    Board& board = controller->getBoard();
    Move move = board.checkMove( row, col );
    makeMove( move, row, col );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::pressTile()
{
    uint position = ( static_cast< QPushButton* >( sender() ))->accessibleName().toUInt();

    uint row = position / 10;
    uint col = position % 10;
    Board& board = controller->getBoard();
    Move move = board.checkMove( row, col );

    if ( move == Move::NOT_ALLOWED )
    {
        return;
    }

    controller->putMove( move, row, col );
    makeMove( move, row, col );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::makeMove( Move move, uint row, uint col )
{
    Board& board = controller->getBoard();
    auto [ boardSize, tileSize ] = controller->getBoardAttributes();
    auto moveTile = ( board.getMode() == BoardMode::NUMERIC ) ? &Fifteen::moveNumericTile :
                                                                &Fifteen::moveGraphicTile;

    switch ( move )
    {
        case Move::UP:
            return ( this->*moveTile )( row, col, row - 1, col, boardSize, tileSize );
        case Move::RIGHT:
            return ( this->*moveTile )( row, col, row, col + 1, boardSize, tileSize );
        case Move::DOWN:
            return ( this->*moveTile )( row, col, row + 1, col, boardSize, tileSize );
        case Move::LEFT:
            return ( this->*moveTile )( row, col, row, col - 1, boardSize, tileSize );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::moveNumericTile( uint rowSource, uint colSource, uint rowDest, uint colDest, uint boardSize, uint tileSize )
{
    auto tileColorStyle = Maps::tileColorStyle.at( Options::getTileColor() );
    auto& tiles = gui->getTiles();

    tiles.at( rowDest * boardSize + colDest )->setText( tiles.at( rowSource * boardSize + colSource )->text() );
    tiles.at( rowDest * boardSize + colDest )->setStyleSheet( tileColorStyle );
    tiles.at( rowSource * boardSize + colSource )->setText( "" );
    tiles.at( rowSource * boardSize + colSource )->setStyleSheet( Maps::tileColorStyle.at( TileColor::EMPTY_STYLE ));
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::moveGraphicTile( uint rowSource, uint colSource, uint rowDest, uint colDest, uint boardSize, uint tileSize )
{
    auto& tiles = gui->getTiles();

    tiles.at( rowDest * boardSize + colDest )->setIcon( tiles.at( rowSource * boardSize + colSource )->icon() );
    QPixmap pixmap( tileSize, tileSize );
    pixmap.fill( Qt::white );
    QIcon nullIcon( pixmap );
    tiles.at( rowSource * boardSize + colSource )->setIcon( nullIcon );
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

    if ( controller->loadGraphic( image ))
    {
        gui->setActionMenuState( ActionMenu::REM_GRAPHIC, true );
    }
    QMessageBox::information( this, "", Message::getMessages() );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotRemoveGraphic()
{
    if ( controller->removeGraphic() )
    {
        redrawTiles();
    }
    gui->setActionMenuState( ActionMenu::REM_GRAPHIC, false );
    gui->setRadioBoardMode( BoardMode::NUMERIC );
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

    controller->writeBoardIntoFile( file.toStdString() );
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

    controller->readBoardFromFile( file.toStdString() );
    redrawTiles();
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setColor()
{
    auto tileColorStyle = Maps::tileColorStyle.at( Options::getTileColor() );

    for ( auto& tile : gui->getTiles() )
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

