
#include "Fifteen.h"

#include "GraphicBoard/ImageProvider.h"
#include "GUI/GUIAbout.h"
#include "GUI/Panel.h"
#include "GUI/GUISetting.h"
#include "MappedValues.h"
#include "Message.h"
#include "Options.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QHBoxLayout>
#include <QGroupBox>


Fifteen::Fifteen( QWidget *parent ) : QMainWindow{ parent } {}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::initGame()
{
    resize( 850, 600 );
    controller = std::make_unique< Controller >();
    tilesBoard = std::make_unique< TilesBoard >( std::bind( &Fifteen::pressTile, this ));
    menuBar = std::make_unique< MenuBar >();
    panel = std::make_unique< Panel >();

    std::map< ActionMenu, std::function< void( void ) >> menuSlots =
    {
        { ActionMenu::OPEN_GRAPHIC, std::bind( &Fifteen::slotLoadGraphic, this )},
        { ActionMenu::REM_GRAPHIC,  std::bind( &Fifteen::slotRemoveGraphic, this )},
        { ActionMenu::SAVE_BOARD,   std::bind( &Fifteen::slotSaveBoard, this )},
        { ActionMenu::LOAD_BOARD,   std::bind( &Fifteen::slotReadBoard, this )},
        { ActionMenu::SETTINGS,     std::bind( &Fifteen::slotSettings, this )},
        { ActionMenu::ABOUT,        std::bind( &Fifteen::slotAbout, this )},
    };
    QMenuBar* menu = menuBar->createMenuBar( menuSlots, this );
    setMenuBar( menu );

    std::array< std::function< void( void ) >, 3 > panelSlots =
    {
        std::bind( &Fifteen::slotGenerateBoard, this ),
        std::bind( &Fifteen::slotSolveBoard, this ),
        std::bind( &Fifteen::slotUndoMove, this ),
    };
    QVBoxLayout* layout = panel->createLayout( panelSlots, this );

    QWidget* mainPanel = new QWidget();
    mainPanel->setContentsMargins( 20, 20, 0, 20 );

    QHBoxLayout* mainLayout = new QHBoxLayout( mainPanel );
    QGroupBox* boxImages = tilesBoard->getGroupBox();
    mainLayout->addWidget( boxImages );
    mainLayout->addLayout( layout );
    setCentralWidget( mainPanel );

    redrawTiles();
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::createTiles()
{
    auto [ boardSize, tileSize ] = controller->getBoardAttributes();
    tilesBoard->createTiles( boardSize, tileSize, this );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setTiles()
{
    BoardMode mode = controller->getBoardMode();
    if ( mode == BoardMode::NUMERIC )
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
    const auto& values = controller->getValues();

    int fontSizeInt = Maps::getFontSizeInt( Options::getTileSize() );
    QFont font;
    font.setPixelSize( fontSizeInt );
    auto tileColor = Options::getTileColor();

    auto& tiles = tilesBoard->getTiles();
    int valuesIndex = 0;
    for ( auto& tile : tiles )
    {
        tile->setText( QString::number( values[ valuesIndex++ ] + 1 ));
        tile->setStyleSheet( tileColor );
        tile->setFont( font );
    }

    uint nullValue = controller->getNullValue();
    auto iter = std::find( values.begin(), values.end(), nullValue );
    tiles[ std::distance( values.begin(), iter) ]->setStyleSheet( Maps::tileColorStyle.at( TileColor::EMPTY ));
    tiles[ std::distance( values.begin(), iter) ]->setText( nullptr );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setTilesGraphic()
{
    auto [ boardSizeInt, tileSizeInt ] = controller->getBoardAttributes();
    auto value = controller->getValues().begin();

    const auto& images = controller->getImages();
    QSize iconSize( tileSizeInt, tileSizeInt );

    int fontSizeInt = Maps::getFontSizeInt( Options::getTileSize() );
    NumberColor numberColor = Options::getNumberOnImageColor();
    QIcon icon;

    for ( auto& tile : tilesBoard->getTiles() )
    {
        QPixmap pixmap = QPixmap::fromImage( *images.at( *value ).get() );
        if ( numberColor == NumberColor::NO || *value == controller->getNullValue() )
        {
            icon.addPixmap( pixmap );
        }
        else
        {
            drawNumberOnTile( icon, pixmap, fontSizeInt, *value, numberColor );
        }
        tile->setIconSize( iconSize );
        tile->setIcon( icon );
        tile->setStyleSheet( "" );
        value++;
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::drawNumberOnTile( QIcon& icon, QPixmap& pixmap, int fontSize, uint number, NumberColor numberColor )
{
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
    BoardSize boardSize = panel->checkBoardSize();
    BoardMode boardMode = panel->checkBoardMode( BoardMode::GRAPHIC ) ? BoardMode::GRAPHIC : BoardMode::NUMERIC;

    if ( Result result = controller->generateBoard( boardSize, boardMode ); result != Result::OK )
    {
        QMessageBox::information( this, "", Message::getMessage( result ));
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
    auto [ move, row, col ] = controller->undoMove();
    if ( move == Move::NOT_ALLOWED )
    {
        QMessageBox::information( this, "", "There are no moves\t" );
        return;
    }

    makeMove( move, row, col );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::pressTile()
{
    uint tilePosition = ( static_cast< QPushButton* >( sender() ))->accessibleName().toUInt();
    auto [ move, row, col ] = controller->makeMove( tilePosition );
    if ( move != Move::NOT_ALLOWED )
    {
        makeMove( move, row, col );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::makeMove( Move move, uint row, uint col )
{
    auto [ boardSize, tileSize ] = controller->getBoardAttributes();
    auto moveTile = ( controller->getBoardMode() == BoardMode::NUMERIC ) ? &Fifteen::moveNumericTile :
                                                                           &Fifteen::moveGraphicTile;

    switch ( move )
    {
        case Move::UP:
            ( this->*moveTile )( row, col, row - 1, col, boardSize, tileSize );
            return;
        case Move::RIGHT:
            ( this->*moveTile )( row, col, row, col + 1, boardSize, tileSize );
            return;
        case Move::DOWN:
            ( this->*moveTile )( row, col, row + 1, col, boardSize, tileSize );
            return;
        case Move::LEFT:
            ( this->*moveTile )( row, col, row, col - 1, boardSize, tileSize );
            return;
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::moveNumericTile( uint rowSrc, uint colSrc, uint rowDst, uint colDst, uint boardSize, uint tileSize )
{
    auto& tiles = tilesBoard->getTiles();

    tiles.at( rowDst * boardSize + colDst )->setText( tiles.at( rowSrc * boardSize + colSrc )->text() );
    tiles.at( rowDst * boardSize + colDst )->setStyleSheet( Options::getTileColor() );
    tiles.at( rowSrc * boardSize + colSrc )->setText( "" );
    tiles.at( rowSrc * boardSize + colSrc )->setStyleSheet( Maps::tileColorStyle.at( TileColor::EMPTY ));
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::moveGraphicTile( uint rowSrc, uint colSrc, uint rowDst, uint colDst, uint boardSize, uint tileSize )
{
    auto& tiles = tilesBoard->getTiles();

    tiles.at( rowDst * boardSize + colDst )->setIcon( tiles.at( rowSrc * boardSize + colSrc )->icon() );
    QPixmap pixmap( tileSize, tileSize );
    pixmap.fill( Qt::white );
    QIcon nullIcon( pixmap );
    tiles.at( rowSrc * boardSize + colSrc )->setIcon( nullIcon );
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
        menuBar->setActionMenuState( ActionMenu::REM_GRAPHIC, true );
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
    menuBar->setActionMenuState( ActionMenu::REM_GRAPHIC, false );
    panel->setBoardMode( BoardMode::NUMERIC );
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

    if ( controller->readBoardFromFile( file.toStdString() ) == false)
    {
        QMessageBox::information( this, "", Message::getMessages() );
        return;
    }
    redrawTiles();
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setColor()
{
    auto tileColor = Options::getTileColor();

    for ( auto& tile : tilesBoard->getTiles() )
    {
        if ( tile->text() != nullptr )
        {
            tile->setStyleSheet( tileColor );
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

