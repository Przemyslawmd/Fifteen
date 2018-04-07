
#include "MainWindow.h"
#include "Message.h"
#include "WindowSetting.h"
#include "WindowAbout.h"
#include "IOFile.h"
#include "Options.h"
#include "GraphicBoard/ImageProvider.h"
#include <QPainter>
#include <QBuffer>
#include <QMessageBox>
#include <QFileDialog>
#include <QFont>

MainWindow::MainWindow( QWidget *parent ) : QMainWindow{ parent }, mainPanel{ this }
{
    board = Board::createBoard( BoardSize::FOUR );
    resize( 750, 550 );
    createMenu();
    createRightPanel();
    createLayouts();
    createSquares();
    setSquaresNumeric( false );
}

/******************************************************************************************/
/* CREATE MENU ****************************************************************************/

void MainWindow::createMenu()
{    
    fileMenu = new QMenu();
    fileMenu->setTitle( "File" );
    fileMenu->setStyleSheet( "padding-left:10px;" );

    action[Action::OPEN_GRAPHIC ] = new QAction( this );
    action[Action::OPEN_GRAPHIC]->setText( "Load Graphic File" );
    connect( action[Action::OPEN_GRAPHIC], SIGNAL( triggered()), this, SLOT( slotLoadGraphic()));

    action[Action::REM_GRAPHIC ] = new QAction( this );
    action[Action::REM_GRAPHIC]->setText( "Remove Graphic" );
    action[Action::REM_GRAPHIC]->setEnabled( false );
    connect( action[Action::REM_GRAPHIC], SIGNAL( triggered()), this, SLOT( slotRemoveGraphic()));

    action[Action::SAVE_BOARD] = new QAction( this );
    action[Action::SAVE_BOARD]->setText( "Save Board" );
    connect( action[Action::SAVE_BOARD], SIGNAL( triggered()), this, SLOT( slotSaveBoard()));

    action[Action::LOAD_BOARD] = new QAction( this );
    action[Action::LOAD_BOARD]->setText( "Load Board" );
    connect( action[Action::LOAD_BOARD], SIGNAL( triggered()), SLOT( slotReadBoard()));

    action[Action::SETTINGS] = new QAction( this );
    action[Action::SETTINGS]->setText( "Settings" );
    connect( action[Action::SETTINGS], SIGNAL( triggered()), this, SLOT( slotSettings()));

    action[Action::ABOUT] = new QAction( this );
    action[Action::ABOUT]->setText( "About" );
    connect( action[Action::ABOUT], SIGNAL( triggered()), this, SLOT( slotAbout()));

    fileMenu->addAction( action[Action::OPEN_GRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( action[Action::REM_GRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( action[Action::SAVE_BOARD] );
    fileMenu->addSeparator();
    fileMenu->addAction( action[Action::LOAD_BOARD] );

    mainMenu = new QMenuBar();
    mainMenu->addMenu( fileMenu );
    mainMenu->addAction( action[Action::SETTINGS] );
    mainMenu->addAction( action[Action::ABOUT] );
    mainMenu->setStyleSheet( "padding-left: 5px; margin: 3px;" );

    this->setMenuBar( mainMenu );
}

/********************************************************************************************/
/********************************************************************************************/

void MainWindow::createRightPanel()
{
    pushRandom.setText( "Generate Board" );
    pushRandom.setStyleSheet( "height:20px;" );
    connect( &pushRandom, SIGNAL( clicked() ), this, SLOT( slotGenerateBoard() ));

    pushSolve.setText( "Solve Board" );
    pushSolve.setStyleSheet( "height:20px;" );
    connect( &pushSolve, SIGNAL( clicked() ), this, SLOT( slotSolveBoard() ));

    pushUndo.setText("Undo Move");
    pushUndo.setStyleSheet( "height:20px;" );
    pushUndo.setDisabled( true );
    connect( &pushUndo, SIGNAL( clicked() ), this, SLOT( slotUndoMove() ));

    layRadioSize = new QVBoxLayout();
    groupRadioSize = new QButtonGroup();

    radioSize[BoardSize::FOUR] = new QRadioButton();
    radioSize[BoardSize::FIVE] = new QRadioButton();
    radioSize[BoardSize::SIX] = new QRadioButton();
    radioSize[BoardSize::SEVEN] = new QRadioButton();

    for( std::pair< BoardSize, QRadioButton* > radioSizePair : radioSize )
    {
        layRadioSize->addSpacing( 10 );
        layRadioSize->addWidget( radioSizePair.second );
        radioSizePair.second->setStyleSheet( "margin-left:5px;" );
        groupRadioSize->addButton( radioSizePair.second );
        groupRadioSize->setId( radioSizePair.second, radioSizePair.first );
    }
    layRadioSize->addSpacing( 30 );

    radioSize[BoardSize::FOUR]->setText( "4" );
    radioSize[BoardSize::FIVE]->setText( "5" );
    radioSize[BoardSize::SIX]->setText( "6" );
    radioSize[BoardSize::SEVEN]->setText( "7" );
    radioSize[BoardSize::FOUR]->setChecked( true );

    boxRadioSize = new QGroupBox();
    boxRadioSize->setTitle( "Dimension of Board" );
    boxRadioSize->setLayout( layRadioSize );

    layRadioKind = new QVBoxLayout();
    groupRadioKind = new QButtonGroup();

    radioKind[BoardMode::NUMERIC] = new QRadioButton();
    radioKind[BoardMode::GRAPHIC] = new QRadioButton();

    for( std::pair< BoardMode, QRadioButton* > radioKindPair : radioKind )
    {
        layRadioKind->addSpacing( 10 );
        layRadioKind->addWidget( radioKindPair.second );
        radioKindPair.second->setStyleSheet( "margin-left:5px;" );
        groupRadioKind->addButton( radioKindPair.second );
    }
    layRadioKind->addSpacing( 30 );

    radioKind[BoardMode::NUMERIC]->setChecked(true);
    radioKind[BoardMode::NUMERIC]->setText( "Numeric" );
    radioKind[BoardMode::GRAPHIC]->setText( "Graphic" );

    boxRadioKind = new QGroupBox();
    boxRadioKind->setTitle( "Kind of Board" );
    boxRadioKind->setLayout( layRadioKind );

    rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins( 30, 0, 20, 0 );
    rightLayout->addWidget( &pushRandom );
    rightLayout->addSpacing( 15 );
    rightLayout->addWidget( &pushSolve );
    rightLayout->addSpacing( 15 );
    rightLayout->addWidget( &pushUndo );
    rightLayout->addSpacing( 30 );
    rightLayout->addWidget( boxRadioSize );
    rightLayout->addStretch();
    rightLayout->addWidget( boxRadioKind );
    rightLayout->addStretch();
}

/*********************************************************************************/
/* CREATE LAYOUTS ****************************************************************/

void MainWindow::createLayouts()
{
    mainPanel = new QWidget();
    mainPanel->setContentsMargins( 20, 20, 0, 10 );

    boardVerticalLayout = new QVBoxLayout;
    boardVerticalLayout->setSpacing( 0 );

    boxImages = new QGroupBox();
    boxImages->setLayout( boardVerticalLayout );

    mainLayout = new QHBoxLayout( mainPanel );
    mainLayout->addWidget( boxImages );
    mainLayout->addLayout( rightLayout );

    this->setCentralWidget( mainPanel );
}

/***********************************************************************************/
/* CREATE SQUARES ******************************************************************/

void MainWindow::createSquares()
{
    deleteSquares();
    BoardSize boardSize = board->getCurrentSize();
    SquareSize squareSize = ( Options::getBoardMode() == BoardMode::NUMERIC ) ? Options::getSquareSize() : ImageProvider::getInstance().getImageSquareSize();

    for ( int i = 0; i < boardSize * boardSize; i++ )
        squares.push_back( new QPushButton() );

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
        boardHorizontalLayout[i].setSpacing(0);

    boardVerticalLayout->addStretch();

    for ( int i = 0; i < boardSize; i++ )
    {
        boardHorizontalLayout[i].addStretch();

        for ( int j = 0; j < boardSize; j++ )
            boardHorizontalLayout[i].addWidget( squares.at( i * boardSize + j ));

        boardHorizontalLayout[i].addStretch();
        boardVerticalLayout->addLayout( &boardHorizontalLayout[i] );
    }
    boardVerticalLayout->addStretch();
}

/*********************************************************************************/
/* DELETE SQUARES ****************************************************************/

void MainWindow::deleteSquares()
{
    if ( squares.empty() )
        return;

    for ( auto square : squares )
        delete square;

    squares.clear();

    QLayoutItem* child;
    while ((  child = boardVerticalLayout->takeAt( 0 )))
        boardVerticalLayout->removeItem( 0 );

    delete[] boardHorizontalLayout;
}

/*************************************************************************************/
/* SET SQUARES NUMERIC ***************************************************************/

void MainWindow::setSquaresNumeric( bool isRandom )
{    
    vector<int>& values = ( isRandom ) ? board->randomBoard() : board->sendBoard();
    QString& currentStyle = Options::getStyle();
    QFont font;
    font.setPixelSize( Options::getSquareSizeFont() );

    int i = 0;
    for ( auto square : squares )
    {
        square->setText( QString::number( values.at( i )));
        if ( values.at( i ) == 0 )
            square->setStyleSheet( Options::getEmptyStyle() );
        else
            square->setStyleSheet( currentStyle );
        square->setFont( font );
        i++;
    }

    Options::setBoardMode( BoardMode::NUMERIC );
}

/*******************************************************************************************/
/* SET SQUARES GRAPHIC *********************************************************************/

void MainWindow::setSquaresGraphic( bool isRandom )
{
    ImageProvider& provider = ImageProvider::getInstance();
    SquareSize squareSize = provider.getImageSquareSize();
    vector<int>& values = ( isRandom ) ? board->randomBoard() : board->sendBoard();
    BoardSize boardSize = board->getCurrentSize();
    vector< QImage* >* pictures = provider.getImages( boardSize );
    QPixmap pixmap;

    bool numberOnImage = Options::isNumberOnImage();

    int i = 0;
    for ( auto square : squares )
    {
        pixmap = QPixmap::fromImage( *pictures->at( values.at( i++ )));

        if ( numberOnImage )
            drawNumberOnGraphicSquare( pixmap, values.at( i - 1 ));

        QIcon icon( pixmap );
        QSize iconSize( squareSize, squareSize );
        square->setIconSize( iconSize );
        square->setIcon( icon );
        square->setStyleSheet( "" );
    }

    Options::setBoardMode( BoardMode::GRAPHIC );
}

/*******************************************************************************************/
/* DRAW NUMBER ON GRAPHIC SQUARE ***********************************************************/

void MainWindow::drawNumberOnGraphicSquare( QPixmap& pixmap, int number )
{
    if ( number == 0 )
        return;

    QPainter painter( &pixmap );
    QColor penColor( 0, 0, 0 );
    painter.setPen( QPen( penColor ));
    int font = Options::getSquareSizeFont();
    painter.setFont( QFont("Times", font, QFont::Bold ));
    painter.drawText( pixmap.rect(), Qt::AlignCenter, QString::number( number ));
}

/*******************************************************************************************/
/* GENERATE BOARD **************************************************************************/

void MainWindow::slotGenerateBoard()
{
    BoardSize boardSize = static_cast< BoardSize >( groupRadioSize->checkedId());

    // In case of graphic board check whether there is a proper image loaded
    if ( radioKind[BoardMode::GRAPHIC]->isChecked() )
    {
        ImageProvider& provider = ImageProvider::getInstance();

        if (( boardSize == BoardSize::FOUR ) && ( provider.isImage( BoardSize::FOUR ) == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 4x4\t" );
            return;
        }
        if (( boardSize == BoardSize::FIVE ) && ( provider.isImage( BoardSize::FIVE)  == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 5x5\t" );
            return;
        }
        if (( boardSize == BoardSize::SIX ) && ( provider.isImage( BoardSize::SIX ) == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 6x6\t");
            return;
        }
        if (( boardSize == BoardSize::SEVEN ) && ( provider.isImage( BoardSize::SEVEN ) == false ))
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

/*******************************************************************************************/
/*******************************************************************************************/

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

/*******************************************************************************************/
/*******************************************************************************************/

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

/*******************************************************************************************/
/*******************************************************************************************/

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

/*******************************************************************************************/
/*******************************************************************************************/

void MainWindow::makeMove( Move move, int row, int col )
{
    // Set pointer to a method for moving squares, according to kind of a board
    moveSquare = ( Options::getBoardMode() == BoardMode::NUMERIC ) ? &MainWindow::moveNumericSquares : &MainWindow::moveGraphicSquares;

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

/*******************************************************************************************/
/* MOVE NUMERIC SQUARES ********************************************************************/

void MainWindow::moveNumericSquares( int rowSource, int colSource, int rowDest, int colDest )
{
    QString& currentStyle = Options::getStyle();
    BoardSize boardSize = board->getCurrentSize();

    squares.at( rowDest * boardSize + colDest )->setText( squares.at( rowSource * boardSize + colSource )->text() );
    squares.at( rowDest * boardSize + colDest )->setStyleSheet( currentStyle );
    squares.at( rowSource * boardSize + colSource )->setText( "" );
    squares.at( rowSource * boardSize + colSource )->setStyleSheet( Options::getEmptyStyle() );
}

/*******************************************************************************************/
/* MOVE GRAPHIC SQUARES ********************************************************************/

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

/*******************************************************************************************/
/* LOAD GRAPHIC FILE ***********************************************************************/

void MainWindow::slotLoadGraphic()
{
    QString fileName = QFileDialog::getOpenFileName( this, "", QDir::currentPath(), tr( "JPG, PNG, GIF, BMP (*.jpg *.png *.gif *.bmp)" ));

    if ( fileName.isEmpty() )
        return;

    QImage picture;
    picture.load( fileName );

    if ( picture.isNull() )
    {
        QMessageBox::information( this, "", "Failure of loading an image\t" );
        return;
    }

    ImageProvider& provider = ImageProvider::getInstance();
    provider.prepareBoardImage( picture, Options::getSquareSize() );

    if ( provider.isImage( BoardSize::FOUR ) || provider.isImage( BoardSize::FIVE ) || provider.isImage( BoardSize::SIX ) || provider.isImage( BoardSize::SEVEN ))
        action[Action::REM_GRAPHIC]->setEnabled( true );

    QMessageBox::information( this, "", Message::getMessages() );
}

/*******************************************************************************************/
/* REMOVE GRAPHIC **************************************************************************/

void MainWindow::slotRemoveGraphic()
{
    ImageProvider::deleteInstance();    
    action[Action::REM_GRAPHIC]->setEnabled( false );

    if ( Options::getBoardMode() == BoardMode::GRAPHIC )
    {
        Options::setBoardMode( BoardMode::NUMERIC );
        createSquares();
        setSquaresNumeric( false );
    }
}

/*******************************************************************************************/
/* SLOT SAVE BOARD *************************************************************************/

void MainWindow::slotSaveBoard()
{
    QString fileName = QFileDialog::getSaveFileName( this, "", QDir::currentPath() );

    if ( fileName.isEmpty() )
        return;

    IOFile ioFile;
    if ( Options::getBoardMode() == BoardMode::NUMERIC )
        ioFile.saveNumericBoardInFile( board, fileName );
    else
        ioFile.saveGraphicBoardInFile( board, fileName );
}

/*******************************************************************************************/
/* RESTORE BOARD FROM FILE *****************************************************************/

void MainWindow::slotReadBoard()
{    
    QString fileName = QFileDialog::getOpenFileName( this, "", QDir::currentPath() );

    if( fileName.isEmpty() )
        return;

    IOFile ioFile;
    unique_ptr< vector<int> > values = ioFile.readBoardFromFile( fileName );

    if ( values == nullptr )
    {
        QMessageBox::information( this, "", Message::getMessages() );
        return;
    }

    BoardSize boardSize = ( BoardSize ) values->back();
    values->pop_back();
    board = Board::createBoard( std::move( values ), boardSize );

    if ( Options::getBoardMode() == BoardMode::NUMERIC )
    {
        createSquares();
        setSquaresNumeric( false );
        radioKind[BoardMode::NUMERIC]->setChecked( true );
    }
    else
    {
        ImageProvider& provider = ImageProvider::getInstance();

        if ( boardSize == BoardSize::FOUR )
            radioSize[BoardSize::FOUR]->setChecked( provider.isImage( BoardSize::FOUR ));
        else if ( boardSize == BoardSize::FIVE )
            radioSize[BoardSize::FIVE]->setChecked( provider.isImage( BoardSize::FIVE ));
        else if ( boardSize == BoardSize::SIX )
            radioSize[BoardSize::SIX]->setChecked( provider.isImage( BoardSize::SIX ));
        else
            radioSize[BoardSize::SEVEN]->setChecked( provider.isImage( BoardSize::SEVEN ));

        createSquares();
        setSquaresGraphic( false );
        radioKind[BoardMode::GRAPHIC]->setChecked( true );
        action[Action::REM_GRAPHIC]->setEnabled( true );
    }
}

/*********************************************************************************************************/
/* SET COLOR *********************************************************************************************/

void MainWindow::setColor()
{
    QString& currentStyle = Options::getStyle();

    for ( auto square : squares )
    {
        if ( square->styleSheet() != Options::getEmptyStyle() )
            square->setStyleSheet( currentStyle );
    }    
}

/*****************************************************************************************/
/* REDRAW SQUARES ************************************************************************/

void MainWindow::redrawSquares()
{
    createSquares();

    if ( Options::getBoardMode() == BoardMode::NUMERIC)
        setSquaresNumeric( false );
    else
        setSquaresGraphic( false );
}

/*******************************************************************************************/
/*******************************************************************************************/

void MainWindow::createUndoMovesService()
{
    undoMoveService = new UndoMove();
    pushUndo.setDisabled( false );
}

/*******************************************************************************************/
/*******************************************************************************************/

void MainWindow::deleteUndoMovesService()
{
    delete undoMoveService;
    undoMoveService = nullptr;
    pushUndo.setDisabled( true );
}

/*******************************************************************************************/
/*******************************************************************************************/

void MainWindow::slotSettings()
{
    new WindowSetting( *this );
}

/*******************************************************************************************/
/* SLOT ABOUT ******************************************************************************/

void MainWindow::slotAbout()
{
    new WindowAbout();
}

