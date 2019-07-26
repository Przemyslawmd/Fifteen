
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
    GUI::createGUI( *this );
    GUI& gui = GUI::getGUI();
    gui.createMenu( action );
    gui.createRightLayout( radioKind, radioSize );
    gui.completeLayouts();
    createTiles();
    setTilesNumeric( false );
    undoMoveService = nullptr;
}

/*********************************************************************************/
/*********************************************************************************/

Fifteen::~Fifteen()
{
    GUI::releaseGUI();
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::createTiles()
{
    BoardSize boardSize = board->getSize();
    TileSize tileSize = Options::boardMode == BoardMode::NUMERIC ?
                        Options::getTileSize() : ImageProvider::getInstance().getTileSize( boardSize );

    GUI::getGUI().createTiles( boardSize, tileSize );
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

    for ( auto tile : GUI::getGUI().getTiles() )
    {
        if ( *iter != emptyTile )
        {
            tile->setText( QString::number( *iter + 1 ));
            tile->setStyleSheet( Options::getStyle() );
        }
        else
        {
            tile->setStyleSheet( Options::getEmptyStyle() );
        }

        tile->setFont( font );
        iter++;
    }

    Options::boardMode = BoardMode::NUMERIC;
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setTilesGraphic( bool isRandom )
{
    BoardSize boardSize = board->getSize();
    ImageProvider& provider = ImageProvider::getInstance();
    vector< uint >& values = ( isRandom ) ? board->randomBoard() : board->sendBoard();
    vector< QImage* >& pictures = provider.getImages( boardSize );
    unique_ptr< NumberOnImage > numOnImage = Options::isNumberOnImage();
    QPixmap pixmap;
    QPainter* painter = nullptr;

    TileSize tileSize = provider.getTileSize( boardSize );
    int tileSizeInt = Mapped::tileSizeInt.at( tileSize );

    FontSize fontSize = Mapped::tileSizeFontSize.at( tileSize );
    int fontSizeInt = Mapped::fontSizeInt.at( fontSize );

    vector< QPushButton* >& tiles = GUI::getGUI().getTiles();
    int i = 0;
    for ( auto tile : tiles )
    {
        pixmap = QPixmap::fromImage( *pictures.at( values.at( i )));

        if ( numOnImage->isNumberOnImage )
        {
            painter = new QPainter();
            drawNumberOnGraphicTile( *painter, pixmap, numOnImage->fontColor, fontSizeInt, values.at( i ));
        }

        QIcon icon( pixmap );
        pixmap.detach();
        if ( painter )
        {
            delete painter;
            painter = nullptr;
        }

        QSize iconSize( tileSizeInt, tileSizeInt );
        tile->setIconSize( iconSize );
        tile->setIcon( icon );
        tile->setStyleSheet( "" );
        i++;
    }

    Options::boardMode = BoardMode::GRAPHIC;
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::drawNumberOnGraphicTile( QPainter& painter, QPixmap& pixmap, QColor penColor, int fontSize, int number )
{
    if ( number != board->getEmptyTile() )
    {
        painter.begin( &pixmap );
        painter.setFont( QFont( "Times", fontSize, QFont::Bold ));
        painter.setPen( penColor );
        painter.drawText( pixmap.rect(), Qt::AlignCenter, QString::number( number + 1 ));;
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotGenerateBoard()
{
    BoardSize boardSize = GUI::getGUI().checkRadioBoardSize();

    if ( radioKind[BoardMode::GRAPHIC]->isChecked() )
    {
        ImageProvider& provider = ImageProvider::getInstance();
        if ( provider.isGraphicBoard( boardSize ) == false )
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a chosen board size\t" );
            return;
        }
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

    int row = position / 10;
    int col = position % 10;
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

void Fifteen::makeMove( Move move, int row, int col )
{
    moveTile = ( Options::boardMode == BoardMode::NUMERIC ) ? &Fifteen::moveNumericTile :
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

void Fifteen::moveNumericTile( int rowSource, int colSource, int rowDest, int colDest )
{
    const QString& currentStyle = Options::getStyle();
    int boardSize = Mapped::boardSizeInt.at( board->getSize() );
    vector< QPushButton* >& tiles = GUI::getGUI().getTiles();

    tiles.at( rowDest * boardSize + colDest )->setText( tiles.at( rowSource * boardSize + colSource )->text() );
    tiles.at( rowDest * boardSize + colDest )->setStyleSheet( currentStyle );
    tiles.at( rowSource * boardSize + colSource )->setText( "" );
    tiles.at( rowSource * boardSize + colSource )->setStyleSheet( Options::getEmptyStyle() );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::moveGraphicTile( int rowSource, int colSource, int rowDest, int colDest )
{
    BoardSize boardSize = board->getSize();
    int boardSizeInt = Mapped::boardSizeInt.at( boardSize );
    vector< QPushButton* >& tiles = GUI::getGUI().getTiles();

    tiles.at( rowDest * boardSizeInt + colDest )->setIcon( tiles.at( rowSource * boardSizeInt + colSource )->icon() );
    TileSize tileSize = ImageProvider::getInstance().getTileSize( boardSize );
    int tileSizeInt = Mapped::tileSizeInt.at( tileSize );
    QPixmap pixmap( tileSizeInt, tileSizeInt );
    pixmap.fill( Qt::white );
    QIcon nullIcon( pixmap );
    tiles.at( rowSource * boardSizeInt + colSource )->setIcon( nullIcon );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotLoadGraphic()
{
    QString fileName = QFileDialog::getOpenFileName( this, "", QDir::currentPath(),
                                                     tr( "JPG, PNG, GIF, BMP (*.jpg *.png *.gif *.bmp)" ));

    if ( fileName.isEmpty() )
    {
        return;
    }

    QImage image;
    image.load( fileName );

    if ( image.isNull() )
    {
        QMessageBox::information( this, "", "Failure of loading an image\t" );
        return;
    }

    ImageProvider& provider = ImageProvider::getInstance();
    provider.prepareGraphicBoard( image, Options::getTileSize() );

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
        setTilesNumeric( false );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotSaveBoard()
{
    QString fileName = QFileDialog::getSaveFileName( this, "", QDir::currentPath() );

    if ( fileName.isEmpty() )
    {
        return;
    }

    IOBoard ioBoard;
    ioBoard.writeBoardIntoFile( *board, Options::boardMode, fileName );
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::slotReadBoard()
{    
    QString fileName = QFileDialog::getOpenFileName( this, "", QDir::currentPath() );

    if( fileName.isEmpty() )
    {
        return;
    }

    IOBoard ioBoard;
    vector< uint > values( 0 );

    Result result = ioBoard.readBoardFromFile( fileName, values );
    if ( result != Result::OK )
    {
        QMessageBox::information( this, "", Message::message[ result ] );
        return;
    }

    BoardSize boardSize = Mapped::getBoardSizeByInt( values.back() );
    values.pop_back();
    board = Board::createBoard( values, boardSize );
    createTiles();
    setTiles( false );

    if ( Options::boardMode == BoardMode::NUMERIC )
    {
        radioKind[BoardMode::NUMERIC]->setChecked( true );
    }
    else
    {
        radioSize[boardSize]->setChecked( true );
        radioKind[BoardMode::GRAPHIC]->setChecked( true );
        action[Action::REM_GRAPHIC]->setEnabled( true );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Fifteen::setColor()
{
    const QString& currentStyle = Options::getStyle();
    vector< QPushButton* >& tiles = GUI::getGUI().getTiles();

    for ( auto tile : tiles )
    {
        if ( tile->styleSheet() != Options::getEmptyStyle() )
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
    UndoMove* undoMove = undoMoveService.release();
    delete undoMove;
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

