
#include "Fifteen.h"
#include "GUI/GUIMain.h"
#include "Message.h"
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

Fifteen::Fifteen( QWidget *parent ) : QMainWindow{ parent }
{
    board = Board::createBoard( BoardSize::FOUR );
    resize( 750, 550 );
    GUI::createGUI();
    GUI& gui = GUI::getGUI();
    gui.createMenu( this, action );
    gui.createRightLayout( this, radioKind, radioSize );
    gui.completeLayouts( this );
    createTiles();
    setTiles( false );
    undoMoveService = nullptr;
}

/*********************************************************************************/
/*********************************************************************************/

Fifteen::~Fifteen()
{
    ImageProvider::deleteInstance();
    GUI::releaseGUI();
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::createTiles()
{
    BoardSize boardSize = board->getSize();
    TileSize tileSize = Options::boardMode == BoardMode::NUMERIC ?
                        Options::tileSize : ImageProvider::getInstance().getTileSize( boardSize );

    GUI::getGUI().createTiles( this, boardSize, tileSize );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setTiles( bool isRandom )
{
    if ( Options::boardMode == BoardMode::NUMERIC )
    {
        setTilesNumeric( isRandom );
    }
    else
    {
        setTilesGraphic( isRandom );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setTilesNumeric( bool isRandom )
{    
    auto values = ( isRandom ) ? board->randomBoard() : board->sendBoard();
    auto iter = values.begin();

    int fontSizeInt = Mapped::fontSizeInt.at( Options::getFontSize() );
    QFont font;
    font.setPixelSize( fontSizeInt );

    uint emptyTile = board->getEmptyTile();

    for ( auto &tile : GUI::getGUI().getTiles() )
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

void Fifteen::setTilesGraphic( bool isRandom )
{
    BoardSize boardSize = board->getSize();
    ImageProvider& provider = ImageProvider::getInstance();
    vector< uint >& values = ( isRandom ) ? board->randomBoard() : board->sendBoard();
    vector< QImage* >& images = provider.getImages( boardSize );
    unique_ptr< NumberOnImage > numOnImage = Options::isNumberOnImage();

    TileSize tileSize = provider.getTileSize( boardSize );
    uint tileSizeInt = Mapped::tileSizeInt.at( tileSize );

    FontSize fontSize = Mapped::tileSizeFontSize.at( tileSize );
    uint fontSizeInt = Mapped::fontSizeInt.at( fontSize );

    QPainter painter;
    uint i = 0;
    for ( auto &tile : GUI::getGUI().getTiles() )
    {
        QPixmap pixmap = QPixmap::fromImage( *images.at( values.at( i )));

        if ( numOnImage->isNumberOnImage )
        {
            drawNumberOnGraphicTile( painter, pixmap, numOnImage->fontColor, fontSizeInt, values.at( i ));
        }

        QIcon icon( pixmap );
        painter.end();

        QSize iconSize( tileSizeInt, tileSizeInt );
        tile->setIconSize( iconSize );
        tile->setIcon( icon );
        tile->setStyleSheet( "" );
        i++;
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::drawNumberOnGraphicTile( QPainter& painter, QPixmap& pixmap, QColor penColor, int fontSize, uint number )
{
    if ( number != board->getEmptyTile() )
    {
        painter.begin( &pixmap );
        painter.setFont( QFont( "Times", fontSize, QFont::Bold ));
        painter.setPen( penColor );
        painter.drawText( pixmap.rect(), Qt::AlignCenter, QString::number( number + 1 ));
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotGenerateBoard()
{
    BoardSize boardSize = GUI::getGUI().checkRadioBoardSize();

    if ( radioKind[BoardMode::GRAPHIC]->isChecked() && ImageProvider::getInstance().isGraphicBoard( boardSize ) == false )
    {
        QMessageBox::information( this, "", "There is no loaded graphic for a chosen board size\t" );
        return;
    }

    board = Board::createBoard( boardSize );
    Options::boardMode = radioKind[BoardMode::NUMERIC]->isChecked() ? BoardMode::NUMERIC : BoardMode::GRAPHIC;
    createTiles();
    setTiles( true );

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
    setTiles( false );

    if ( undoMoveService )
    {
        undoMoveService->Reset();
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotUndoMove()
{
    int position = undoMoveService->GetMove();

    if ( position == -1 )
    {
        return;
    }

    int row = position / 10;
    int col = position % 10;
    Move move = board->checkMove( row, col );
    makeMove( move, row, col );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::pressTile()
{
    int position = ( (QPushButton*) sender() )->accessibleName().toInt();

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
            ( this->*moveTile )( row, col, row - 1, col );
            return;
        case Move::RIGHT:
            ( this->*moveTile )( row, col, row, col + 1 );
            return;
        case Move::DOWN:
            ( this->*moveTile )( row, col, row + 1, col );
            return;
        case Move::LEFT:
            ( this->*moveTile )( row, col, row, col - 1 );
            return;
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::moveNumericTile( uint rowSource, uint colSource, uint rowDest, uint colDest )
{
    const QString& currentStyle = Options::getStyle();
    uint boardSize = Mapped::boardSizeInt.at( board->getSize() );
    auto& tiles = GUI::getGUI().getTiles();

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
    auto& tiles = GUI::getGUI().getTiles();

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
        action[Action::REM_GRAPHIC]->setEnabled( true );
    }

    QMessageBox::information( this, "", Message::getMessages() );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotRemoveGraphic()
{
    ImageProvider::deleteInstance();    
    action[Action::REM_GRAPHIC]->setEnabled( false );
    radioKind[BoardMode::NUMERIC]->setChecked( true );

    if ( Options::boardMode == BoardMode::GRAPHIC )
    {
        Options::boardMode = BoardMode::NUMERIC;
        createTiles();
        setTiles( false );
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

    vector< uint >* values = ioBoard.readBoardFromFile( file );
    if ( values == nullptr )
    {
        QMessageBox::information( this, "", Message::getMessages() );
        return;
    }

    BoardSize boardSize = Mapped::getBoardSizeByInt( values->back() );
    values->pop_back();
    board = Board::createBoard( *values, boardSize );
    createTiles();
    setTiles( false );

    radioSize[boardSize]->setChecked( true );
    bool isNumeric = Options::boardMode == BoardMode::NUMERIC;
    radioKind[BoardMode::NUMERIC]->setChecked( isNumeric );
    radioKind[BoardMode::GRAPHIC]->setChecked( !isNumeric );
    action[Action::REM_GRAPHIC]->setEnabled( !isNumeric );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setColor()
{
    const QString& currentStyle = Options::getStyle();

    for ( auto &tile : GUI::getGUI().getTiles() )
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
    setTiles( false );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::createUndoMovesService()
{
    undoMoveService = unique_ptr< UndoMove >( new UndoMove() );
    GUI::getGUI().setStatePushUndo( false );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::deleteUndoMovesService()
{
    delete undoMoveService.release();
    GUI::getGUI().setStatePushUndo( true );
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

