
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
    SquareSize squareSize = ( Options::getBoardMode() == BoardMode::NUMERIC ) ? Options::getSquareSize() :
                                                                                ImageProvider::getInstance().getImageSquareSize();

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
    ImageProvider& provider = ImageProvider::getInstance();
    SquareSize squareSize = provider.getImageSquareSize();
    vector< int >& values = ( isRandom ) ? board->randomBoard() : board->sendBoard();
    BoardSize boardSize = board->getCurrentSize();
    vector< QImage* >& pictures = provider.getImages( boardSize );
    QPixmap pixmap;

    bool numberOnImage = Options::isNumberOnImage();

    int i = 0;
    for ( auto square : squares )
    {
        pixmap = QPixmap::fromImage( *pictures.at( values.at( i++ )));

        if ( numberOnImage )
        {
            drawNumberOnGraphicSquare( pixmap, values.at( i - 1 ));
        }

        QIcon icon( pixmap );
        QSize iconSize( squareSize, squareSize );
        square->setIconSize( iconSize );
        square->setIcon( icon );
        square->setStyleSheet( "" );
    }

    Options::setBoardMode( BoardMode::GRAPHIC );
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::drawNumberOnGraphicSquare( QPixmap& pixmap, int number )
{
    if ( number == 0 )
    {
        return;
    }

    QPainter painter( &pixmap );
    QColor penColor( 0, 0, 0 );
    painter.setPen( QPen( penColor ));
    int font = Options::getSquareSizeFont();
    painter.setFont( QFont( "Times", font, QFont::Bold ));
    painter.drawText( pixmap.rect(), Qt::AlignCenter, QString::number( number ));
}

/*********************************************************************************/
/*********************************************************************************/

void MainWindow::slotGenerateBoard()
{
    BoardSize boardSize = static_cast< BoardSize >( radioSizeGroup->checkedId() );

    // In case of graphic board check whether there is a proper image loaded
    if ( radioKind[BoardMode::GRAPHIC]->isChecked() )
    {
        ImageProvider& provider = ImageProvider::getInstance();

        if (( boardSize == BoardSize::FOUR ) && ( provider.isGraphicBoard( BoardSize::FOUR ) == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 4x4\t" );
            return;
        }
        if (( boardSize == BoardSize::FIVE ) && ( provider.isGraphicBoard( BoardSize::FIVE)  == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 5x5\t" );
            return;
        }
        if (( boardSize == BoardSize::SIX ) && ( provider.isGraphicBoard( BoardSize::SIX ) == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 6x6\t");
            return;
        }
        if (( boardSize == BoardSize::SEVEN ) && ( provider.isGraphicBoard( BoardSize::SEVEN ) == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 7x7\t");
            return;
        }
    }

    board = Board::createBoard( boardSize );

    if ( radioKind[BoardMode::NUMERIC]->isChecked() )
    {
        Options::setBoardMode( BoardMode::NUMERIC );
        createSquares();
        setSquaresNumeric( true );
    }
    else
    {
        Options::setBoardMode( BoardMode::GRAPHIC );
        createSquares();
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
            break;

        case Move::RIGHT:
            ( this->*moveSquare )( row, col, row, col + 1 );
            break;

        case Move::DOWN:
            ( this->*moveSquare )( row, col, row + 1, col );
            break;

        case Move::LEFT:
            ( this->*moveSquare )( row, col, row, col - 1 );
            break;
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
    SquareSize imageSize = ImageProvider::getInstance().getImageSquareSize();
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

    if ( Options::getBoardMode() == BoardMode::NUMERIC )
    {
        createSquares();
        setSquaresNumeric( false );
        radioKind[BoardMode::NUMERIC]->setChecked( true );
    }
    else
    {
        ImageProvider& provider = ImageProvider::getInstance();

        switch ( boardSize )
        {
            case BoardSize::FOUR:
                radioSize[BoardSize::FOUR]->setChecked( provider.isGraphicBoard( BoardSize::FOUR ));
                break;
            case BoardSize::FIVE:
                radioSize[BoardSize::FIVE]->setChecked( provider.isGraphicBoard( BoardSize::FIVE ));
                break;
            case BoardSize::SIX:
                radioSize[BoardSize::SIX]->setChecked( provider.isGraphicBoard( BoardSize::SIX ));
                break;
            case BoardSize::SEVEN:
                radioSize[BoardSize::SEVEN]->setChecked( provider.isGraphicBoard( BoardSize::SEVEN ));
                break;
        }

        createSquares();
        setSquaresGraphic( false );
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

