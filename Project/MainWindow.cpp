
#include "MainWindow.h"
#include "GUI.h"
#include "Message.h"
#include "WindowSetting.h"
#include "WindowAbout.h"
#include "FileBoard/IOBoard.h"
#include "Options.h"
#include "GraphicBoard/ImageProvider.h"
#include "MappedValues.h"
#include <QPainter>
#include <QBuffer>
#include <QMessageBox>
#include <QFileDialog>
#include <QFont>

MainWindow::MainWindow( QWidget *parent ) : QMainWindow{ parent }
{
    board = Board::createBoard( BoardSize::FOUR );
    resize( 750, 550 );
    GUI::createGUI( *this );
    GUI& gui = GUI::getGUI();
    gui.createMenu( action );
    gui.createRightLayout( radioKind, radioSize );
    gui.completeLayouts();
    createSquares();
    setSquaresNumeric( false );
    undoMoveService = nullptr;
}

/*********************************************************************************/
/*********************************************************************************/

MainWindow::~MainWindow()
{
    GUI::releaseGUI();
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::createSquares()
{
    BoardSize boardSize = board->getCurrentSize();
    TileSize squareSize = ( Options::getBoardMode() == BoardMode::NUMERIC ) ?
                            Options::getSquareSize() : ImageProvider::getInstance().getImageSquareSize( boardSize );

    GUI::getGUI().createTiles( boardSize, squareSize );
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::setSquaresNumeric( bool isRandom )
{    
    vector< int >& values = ( isRandom ) ? board->randomBoard() : board->sendBoard();
    vector< int >::iterator iter = values.begin();
    QFont font;
    font.setPixelSize( Options::getSquareSizeFont() );

    vector< QPushButton* >& tiles = GUI::getGUI().getTiles();
    for ( auto tile : tiles )
    {
        if ( *iter != 0 )
        {
            tile->setText( QString::number( *iter ));
            tile->setStyleSheet( Options::getStyle() );
        }
        else
        {
            tile->setStyleSheet( Options::getEmptyStyle() );
        }

        tile->setFont( font );
        iter++;
    }

    Options::setBoardMode( BoardMode::NUMERIC );
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::setSquaresGraphic( bool isRandom )
{
    BoardSize boardSize = board->getCurrentSize();
    ImageProvider& provider = ImageProvider::getInstance();
    TileSize tileSize = provider.getImageSquareSize( boardSize );
    vector< int >& values = ( isRandom ) ? board->randomBoard() : board->sendBoard();
    vector< QImage* >& pictures = provider.getImages( boardSize );
    unique_ptr< NumberOnImage > numOnImage = Options::isNumberOnImage();
    QPixmap pixmap;
    QPainter* painter = nullptr;
    int tileSizeInt = MappedValues::tileSizeValues.at( tileSize );

    vector< QPushButton* >& tiles = GUI::getGUI().getTiles();
    int i = 0;
    for ( auto tile : tiles )
    {
        pixmap = QPixmap::fromImage( *pictures.at( values.at( i++ )));

        if ( numOnImage->isNumberOnImage )
        {
            painter = new QPainter();
            drawNumberOnGraphicSquare( *painter, pixmap, numOnImage->fontColor, numOnImage->fontSize, values.at( i - 1 ));
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
    }

    Options::setBoardMode( BoardMode::GRAPHIC );
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::drawNumberOnGraphicSquare( QPainter& painter, QPixmap& pixmap, QColor penColor, int fontSize, int number )
{
    if ( number == 0 )
    {
        return;
    }

    painter.begin( &pixmap );
    painter.setFont( QFont( "Times", fontSize, QFont::Bold ));
    painter.setPen( penColor );
    painter.drawText( pixmap.rect(), Qt::AlignCenter, QString::number( number ));
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::slotGenerateBoard()
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
    createSquares();

    if ( radioKind[BoardMode::NUMERIC]->isChecked() )
    {
        Options::setBoardMode( BoardMode::NUMERIC );
        setSquaresNumeric( true );
    }
    else
    {
        Options::setBoardMode( BoardMode::GRAPHIC );
        setSquaresGraphic( true );
    }

    if ( undoMoveService )
    {
        undoMoveService->Reset();
    }
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::slotSolveBoard()
{
    board->solveBoard();

    if ( Options::getBoardMode() == BoardMode::NUMERIC )
    {
        setSquaresNumeric( false );
    }
    else
    {
        setSquaresGraphic( false );
    }

    if ( undoMoveService )
    {
        undoMoveService->Reset();
    }
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::slotUndoMove()
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

void MainWindow::pressSquare()
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

void MainWindow::makeMove( Move move, int row, int col )
{
    moveSquare = ( Options::getBoardMode() == BoardMode::NUMERIC ) ? &MainWindow::moveNumericSquares :
                                                                     &MainWindow::moveGraphicSquares;

    switch ( move )
    {
        case Move::UP:
            ( this->*moveSquare )( row, col, row - 1, col );
            return;
        case Move::RIGHT:
            ( this->*moveSquare )( row, col, row, col + 1 );
            return;
        case Move::DOWN:
            ( this->*moveSquare )( row, col, row + 1, col );
            return;
        case Move::LEFT:
            ( this->*moveSquare )( row, col, row, col - 1 );
            return;
    }
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::moveNumericSquares( int rowSource, int colSource, int rowDest, int colDest )
{
    QString& currentStyle = Options::getStyle();
    BoardSize boardSize = board->getCurrentSize();
    vector< QPushButton* >& tiles = GUI::getGUI().getTiles();

    tiles.at( rowDest * boardSize + colDest )->setText( tiles.at( rowSource * boardSize + colSource )->text() );
    tiles.at( rowDest * boardSize + colDest )->setStyleSheet( currentStyle );
    tiles.at( rowSource * boardSize + colSource )->setText( "" );
    tiles.at( rowSource * boardSize + colSource )->setStyleSheet( Options::getEmptyStyle() );
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::moveGraphicSquares( int rowSource, int colSource, int rowDest, int colDest )
{
    BoardSize boardSize = board->getCurrentSize();
    vector< QPushButton* >& tiles = GUI::getGUI().getTiles();

    tiles.at( rowDest * boardSize + colDest )->setIcon( tiles.at( rowSource * boardSize + colSource )->icon() );
    TileSize tileSize = ImageProvider::getInstance().getImageSquareSize( boardSize );
    int tileSizeInt = MappedValues::tileSizeValues.at( tileSize );
    QPixmap pixmap( tileSizeInt, tileSizeInt );
    pixmap.fill( Qt::white );
    QIcon nullIcon( pixmap );
    tiles.at( rowSource * boardSize + colSource )->setIcon( nullIcon );
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::slotLoadGraphic()
{
    QString fileName = QFileDialog::getOpenFileName( this, "", QDir::currentPath(),
                                                     tr( "JPG, PNG, GIF, BMP (*.jpg *.png *.gif *.bmp)" ));

    if ( fileName.isEmpty() )
    {
        return;
    }

    QImage picture;
    picture.load( fileName );

    if ( picture.isNull() )
    {
        QMessageBox::information( this, "", "Failure of loading an image\t" );
        return;
    }

    ImageProvider& provider = ImageProvider::getInstance();
    provider.prepareGraphicBoard( picture, Options::getSquareSize() );

    if ( provider.isGraphicBoard( BoardSize::FOUR ) || provider.isGraphicBoard( BoardSize::FIVE ) ||
         provider.isGraphicBoard( BoardSize::SIX )  || provider.isGraphicBoard( BoardSize::SEVEN ))
    {
        action[Action::REM_GRAPHIC]->setEnabled( true );
    }

    QMessageBox::information( this, "", Message::getMessages() );
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::slotRemoveGraphic()
{
    ImageProvider::deleteInstance();    
    action[Action::REM_GRAPHIC]->setEnabled( false );
    radioKind[BoardMode::NUMERIC]->setChecked( true );

    if ( Options::getBoardMode() == BoardMode::GRAPHIC )
    {
        Options::setBoardMode( BoardMode::NUMERIC );
        createSquares();
        setSquaresNumeric( false );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::slotSaveBoard()
{
    QString fileName = QFileDialog::getSaveFileName( this, "", QDir::currentPath() );

    if ( fileName.isEmpty() )
    {
        return;
    }

    IOBoard ioBoard;
    if ( Options::getBoardMode() == BoardMode::NUMERIC )
    {
        ioBoard.saveNumericBoardInFile( *board, fileName );
    }
    else
    {
        ioBoard.saveGraphicBoardInFile( *board, fileName );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::slotReadBoard()
{    
    QString fileName = QFileDialog::getOpenFileName( this, "", QDir::currentPath() );

    if( fileName.isEmpty() )
    {
        return;
    }

    IOBoard ioBoard;
    vector< int > values( 0 );

    if ( ioBoard.readBoardFromFile( fileName, values ) == false )
    {
        QMessageBox::information( this, "", Message::getMessages() );
        return;
    }

    BoardSize boardSize = ( BoardSize ) values.back();
    values.pop_back();
    board = Board::createBoard( values, boardSize );
    createSquares();

    if ( Options::getBoardMode() == BoardMode::NUMERIC )
    {
        setSquaresNumeric( false );
        radioKind[BoardMode::NUMERIC]->setChecked( true );
    }
    else
    {
        setSquaresGraphic( false );
        radioSize[boardSize]->setChecked( true );
        radioKind[BoardMode::GRAPHIC]->setChecked( true );
        action[Action::REM_GRAPHIC]->setEnabled( true );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::setColor()
{
    QString& currentStyle = Options::getStyle();
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

void MainWindow::redrawSquares()
{
    createSquares();

    if ( Options::getBoardMode() == BoardMode::NUMERIC )
    {
        setSquaresNumeric( false );
    }
    else
    {
        setSquaresGraphic( false );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::createUndoMovesService()
{
    undoMoveService = unique_ptr< UndoMove >( new UndoMove() );
    GUI::getGUI().setStatePushUndo( false );
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::deleteUndoMovesService()
{
    UndoMove* undoMove = undoMoveService.release();// = nullptr;
    delete undoMove;
    GUI::getGUI().setStatePushUndo( true );
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::slotSettings()
{
    new WindowSetting( *this );
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::slotAbout()
{
    new WindowAbout();
}

