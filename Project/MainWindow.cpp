
#include "MainWindow.h"
#include "Message.h"
#include "WindowSetting.h"
#include "WindowAbout.h"
#include "FileBoard/IOBoard.h"
#include "Options.h"
#include "GraphicBoard/ImageProvider.h"
#include <QPainter>
#include <QBuffer>
#include <QMessageBox>
#include <QFileDialog>
#include <QFont>
#include <GUI.h>

MainWindow::MainWindow( QWidget *parent ) : QMainWindow{ parent }, mainPanel{ this }
{
    board = Board::createBoard( BoardSize::FOUR );
    resize( 750, 550 );
    GUI gui( *this );
    gui.createMenu( action );
    QVBoxLayout* rightLayout = gui.createRightLayout( radioSizeGroup, pushUndo, radioKind, radioSize );
    gui.completeLayouts( mainPanel, boardVerticalLayout, rightLayout );
    createSquares();
    setSquaresNumeric( false );
    undoMoveService = nullptr;
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::createSquares()
{
    deleteSquares();
    BoardSize boardSize = board->getCurrentSize();
    SquareSize squareSize = ( Options::getBoardMode() == BoardMode::NUMERIC ) ?
                              Options::getSquareSize() : ImageProvider::getInstance().getImageSquareSize( boardSize );

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        squares.push_back( new QPushButton() );
    }

    for ( int i = 0; i < boardSize ; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
        {
            squares.at( i * boardSize + j )->setAccessibleName( QString::number( i ) + QString::number( j ));
            squares.at( i * boardSize + j )->setMaximumSize( squareSize, squareSize );
            squares.at( i * boardSize + j )->setMinimumSize( squareSize, squareSize );
            connect( squares.at( i * boardSize + j ), SIGNAL( clicked() ), this, SLOT( pressSquare() ));
        }
    }

    boardHorizontalLayout = new QHBoxLayout[boardSize];

    for ( int i = 0; i < boardSize; i++ )
    {
        boardHorizontalLayout[i].setSpacing(0);
    }

    boardVerticalLayout->addStretch();

    for ( int i = 0; i < boardSize; i++ )
    {
        boardHorizontalLayout[i].addStretch();

        for ( int j = 0; j < boardSize; j++ )
        {
            boardHorizontalLayout[i].addWidget( squares.at( i * boardSize + j ));
        }

        boardHorizontalLayout[i].addStretch();
        boardVerticalLayout->addLayout( &boardHorizontalLayout[i] );
    }
    boardVerticalLayout->addStretch();
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::deleteSquares()
{
    if ( squares.empty() )
    {
        return;
    }

    for ( auto square : squares )
    {
        delete square;
    }

    squares.clear();

    QLayoutItem* child;
    while (( child = boardVerticalLayout->takeAt( 0 )))
    {
        boardVerticalLayout->removeItem( 0 );
    }

    delete[] boardHorizontalLayout;
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::setSquaresNumeric( bool isRandom )
{    
    vector< int >& values = ( isRandom ) ? board->randomBoard() : board->sendBoard();
    vector< int >::iterator iter = values.begin();
    QFont font;
    font.setPixelSize( Options::getSquareSizeFont() );

    for ( auto square : squares )
    {
        if ( *iter != 0 )
        {
            square->setText( QString::number( *iter ));
            square->setStyleSheet( Options::getStyle() );
        }
        else
        {
            square->setStyleSheet( Options::getEmptyStyle() );
        }

        square->setFont( font );
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
    SquareSize squareSize = provider.getImageSquareSize( boardSize );
    vector< int >& values = ( isRandom ) ? board->randomBoard() : board->sendBoard();
    vector< QImage* >& pictures = provider.getImages( boardSize );
    unique_ptr< NumberOnImage > numOnImage = Options::isNumberOnImage();
    QPixmap pixmap;
    QPainter* painter = nullptr;

    int i = 0;
    for ( auto square : squares )
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

        QSize iconSize( squareSize, squareSize );
        square->setIconSize( iconSize );
        square->setIcon( icon );
        square->setStyleSheet( "" );
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
    BoardSize boardSize = static_cast< BoardSize >( radioSizeGroup->checkedId() );

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

    squares.at( rowDest * boardSize + colDest )->setText( squares.at( rowSource * boardSize + colSource )->text() );
    squares.at( rowDest * boardSize + colDest )->setStyleSheet( currentStyle );
    squares.at( rowSource * boardSize + colSource )->setText( "" );
    squares.at( rowSource * boardSize + colSource )->setStyleSheet( Options::getEmptyStyle() );
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::moveGraphicSquares( int rowSource, int colSource, int rowDest, int colDest )
{
    BoardSize boardSize = board->getCurrentSize();
    squares.at( rowDest * boardSize + colDest )->setIcon( squares.at( rowSource * boardSize + colSource )->icon() );
    SquareSize imageSize = ImageProvider::getInstance().getImageSquareSize( boardSize );
    QPixmap pixmap( imageSize, imageSize );
    pixmap.fill( Qt::white );
    QIcon nullIcon( pixmap );
    squares.at( rowSource * boardSize + colSource )->setIcon( nullIcon );
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

    for ( auto square : squares )
    {
        if ( square->styleSheet() != Options::getEmptyStyle() )
        {
            square->setStyleSheet( currentStyle );
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
    undoMoveService = new UndoMove();
    pushUndo->setDisabled( false );
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::deleteUndoMovesService()
{
    delete undoMoveService;
    undoMoveService = nullptr;
    pushUndo->setDisabled( true );
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
