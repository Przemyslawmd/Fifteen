
#include "MainWindow.h"
#include "Message.h"
#include <QPainter>

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
/* CREATE MENU BAR ************************************************************************/

void MainWindow::createMenu()
{    
    fileMenu = new QMenu();
    fileMenu->setTitle( "File" );

    for ( int i = 0; i < Action::COUNTACTIONS; i++ )
      action[i] = new QAction( this );

    action[Action::OPENGRAPHIC]->setText( "Load Graphic File" );
    connect( action[Action::OPENGRAPHIC], SIGNAL( triggered()), this, SLOT( slotLoadGraphic() ));

    action[Action::REMGRAPHIC]->setText( "Remove Graphic" );
    action[Action::REMGRAPHIC]->setEnabled( false );
    connect( action[Action::REMGRAPHIC], SIGNAL( triggered()), this, SLOT( slotRemoveGraphic() ));

    action[Action::SAVEBOARD]->setText( "Save Board" );
    connect( action[Action::SAVEBOARD], SIGNAL( triggered()), this, SLOT( slotSaveBoard() ));

    action[Action::LOADBOARD]->setText( "Load Board" );
    connect( action[Action::LOADBOARD], SIGNAL( triggered()), SLOT( slotReadBoard() ));

    action[Action::SETTINGS]->setText( "Settings" );
    connect( action[Action::SETTINGS], SIGNAL( triggered()), this, SLOT( slotSettings() ));

    action[Action::ABOUT]->setText( "About" );
    connect( action[Action::ABOUT], SIGNAL( triggered()), this, SLOT( slotAbout() ));

    fileMenu->addAction( action[Action::OPENGRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( action[Action::REMGRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( action[Action::SAVEBOARD] );
    fileMenu->addSeparator();
    fileMenu->addAction( action[Action::LOADBOARD] );

    mainMenu = new QMenuBar();
    mainMenu->addMenu( fileMenu );
    mainMenu->addAction( action[Action::SETTINGS] );
    mainMenu->addAction( action[Action::ABOUT] );

    this->setMenuBar( mainMenu );
}

/********************************************************************************************/
/* CREATE RIGHT PANEL ***********************************************************************/

void MainWindow::createRightPanel()
{
    pushRandom = new QPushButton( "Generate Board");
    pushRandom->setStyleSheet( "height:20px;" );
    connect( pushRandom, SIGNAL( clicked() ), this, SLOT( slotGenerateBoard() ));

    pushSolve = new QPushButton( "Solve Board" );
    pushSolve->setStyleSheet( "height:20px;" );
    connect( pushSolve, SIGNAL( clicked() ), this, SLOT( slotSolveBoard() ));

    layRadioSize = new QVBoxLayout();
    groupRadioSize = new QButtonGroup();

    for( int i = EnumSize::FOUR, j = 4; i <= EnumSize::SEVEN; i++, j++ )
    {
       radioSize[i] = new QRadioButton();
       layRadioSize->addSpacing( 10 );
       layRadioSize->addWidget( radioSize[i] );
       radioSize[i]->setStyleSheet( "margin-left: 5px" );
       groupRadioSize->addButton( radioSize[i] );
       groupRadioSize->setId( radioSize[i], j );
    }
    layRadioSize->addSpacing( 30 );

    radioSize[EnumSize::FOUR]->setText( "4" );
    radioSize[EnumSize::FIVE]->setText( "5" );
    radioSize[EnumSize::SIX]->setText( "6" );
    radioSize[EnumSize::SEVEN]->setText( "7" );
    radioSize[EnumSize::FOUR]->setChecked( true );

    boxRadioSize = new QGroupBox();
    boxRadioSize->setTitle( "Dimension of Board" );
    boxRadioSize->setLayout( layRadioSize );


    layRadioKind = new QVBoxLayout();
    groupRadioKind = new QButtonGroup();

    for ( int i = 0; i < EnumKind::COUNT_KIND; i++ )
    {
        layRadioKind->addSpacing( 10 );
        radioKind[i] = new QRadioButton();
        layRadioKind->addWidget( radioKind[i] );
        radioKind[i]->setStyleSheet( "margin-left:5px;" );
        groupRadioKind->addButton( radioKind[i] );
    }
    layRadioKind->addSpacing( 30 );

    radioKind[EnumKind::NUMERIC]->setChecked(true);
    radioKind[EnumKind::NUMERIC]->setText( "Numeric" );
    radioKind[EnumKind::GRAPHIC]->setText( "Graphic" );

    boxRadioKind = new QGroupBox();
    boxRadioKind->setTitle( "Kind of Board" );
    boxRadioKind->setLayout( layRadioKind );

    rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins( 30, 0, 30, 0 );
    rightLayout->addWidget( pushRandom );
    rightLayout->addSpacing( 15 );
    rightLayout->addWidget( pushSolve );
    rightLayout->addSpacing( 30 );
    rightLayout->addWidget( boxRadioSize );
    rightLayout->addStretch();
    rightLayout->addWidget( boxRadioKind );
    rightLayout->addStretch();
}

/*********************************************************************************/
/* CREATE A LAYOUT FOR SQUARES ***************************************************/

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

    for ( int i = 0; i < boardSize; i++ )
    {
        squares.push_back( vector< QPushButton* >() );

        for ( int j = 0; j < boardSize; j++ )
            squares[i].push_back( new QPushButton() );
    }

    for ( int i = 0; i < boardSize ; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
        {
            squares[i][j]->setAccessibleName( QString::number(i) + QString::number( j ));
            squares[i][j]->setMaximumSize( squareSize, squareSize );
            squares[i][j]->setMinimumSize( squareSize, squareSize );
            connect( squares[i][j], SIGNAL( clicked() ), this, SLOT( pressSquare() ));
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
            boardHorizontalLayout[i].addWidget( squares[i][j] );

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

    for ( auto rowSquares : squares )
    {
        for ( auto button : rowSquares )
            delete button;

        rowSquares.clear();
    }

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
    BoardSize boardSize = board->getCurrentSize();

    for ( int i = 0, v = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
        {
            squares[i][j]->setText( QString::number( values.at( v )));
            if ( values.at( v ) == 0 )
                squares[i][j]->setStyleSheet( Options::getEmptyStyle() );
            else
                squares[i][j]->setStyleSheet( currentStyle );
            squares[i][j]->setFont( font );
            v++;
        }
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
    QImage** pictures = provider.getImage( boardSize );
    QPixmap pixmap;

    bool numberOnImage = Options::isNumberOnImage();

    for ( int i = 0, v = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
        {
            pixmap = QPixmap::fromImage( *pictures[values.at( v++ )]);

            if ( numberOnImage )
                drawNumberOnGraphicSquare( pixmap, values.at( v - 1 ));

            QIcon icon( pixmap );
            QSize iconSize( squareSize, squareSize );
            squares[i][j]->setIconSize( iconSize );
            squares[i][j]->setIcon( icon );
            squares[i][j]->setStyleSheet( "" );
        }
    }

    Options::setBoardMode( BoardMode::GRAPHIC );
}

/*******************************************************************************************/
/* DRAW NUMBER ON GRAPHIC SQUARE ***********************************************************/

void MainWindow::drawNumberOnGraphicSquare( QPixmap& pixmap, int number )
{
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
    BoardSize boardSize = static_cast< BoardSize >( groupRadioSize->checkedId() );

    // In case of graphic board check whether there is a proper image loaded
    if ( radioKind[EnumKind::GRAPHIC]->isChecked() )
    {
        ImageProvider& provider = ImageProvider::getInstance();

        if (( boardSize == BoardSize::FOUR ) && ( provider.isImage( BoardSize::FOUR ) == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 4x4\t" );
            return;
        }
        if (( boardSize == BoardSize::FIVE ) && ( provider.isImage( BoardSize::FIVE)  == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 5x5\t");
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

    if ( radioKind[EnumKind::NUMERIC]->isChecked() )
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
}

/*******************************************************************************************/
/* SOLVE BOARD *****************************************************************************/

void MainWindow::slotSolveBoard()
{
    board->solveBoard();

    if ( Options::getBoardMode() == BoardMode::NUMERIC )
        setSquaresNumeric( false );
    else         
        setSquaresGraphic( false );
}

/*******************************************************************************************/
/* MOVE SQUARE IF POSSIBLE *****************************************************************/

void MainWindow::pressSquare()
{
    int position = ( (QPushButton*)sender() )->accessibleName().toInt();

    int row = position / 10;
    int col = position % 10;
    Move move = board->checkMove( row, col );

    if ( move == Move::NOT_ALLOWED )
        return;

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
    squares[rowDest][colDest]->setText( squares[rowSource][colSource]->text() );
    squares[rowDest][colDest]->setStyleSheet( currentStyle );
    squares[rowSource][colSource]->setText( "" );
    squares[rowSource][colSource]->setStyleSheet( Options::getEmptyStyle() );
}

/*******************************************************************************************/
/* MOVE GRAPHIC SQUARES ********************************************************************/

void MainWindow::moveGraphicSquares( int rowSource, int colSource, int rowDest, int colDest )
{
    squares[rowDest][colDest]->setIcon( squares[rowSource][colSource]->icon() );
    SquareSize imageSize = ImageProvider::getInstance().getImageSquareSize();
    QPixmap pixmap( imageSize, imageSize );
    pixmap.fill( Qt::white );
    QIcon nullIcon( pixmap );
    squares[rowSource][colSource]->setIcon( nullIcon );
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
        action[Action::REMGRAPHIC]->setEnabled( true );

    QMessageBox::information( this, "", Message::getMessages() );
}

/*******************************************************************************************/
/* REMOVE GRAPHIC **************************************************************************/

void MainWindow::slotRemoveGraphic()
{
    ImageProvider::deleteInstance();    
    action[Action::REMGRAPHIC]->setEnabled( false );

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
    BoardSize boardSize = ( BoardSize ) values->back();
    values->pop_back();
    board = Board::createBoard( std::move( values ), boardSize );

    if ( Options::getBoardMode() == BoardMode::NUMERIC )
    {
        createSquares();
        setSquaresNumeric( false );
        radioKind[EnumKind::NUMERIC]->setChecked( true );
    }
    else
    {
        ImageProvider& provider = ImageProvider::getInstance();

        if ( boardSize == BoardSize::FOUR )
            radioSize[EnumSize::FOUR]->setChecked( provider.isImage( BoardSize::FOUR ));
        else if ( boardSize == BoardSize::FIVE )
            radioSize[EnumSize::FIVE]->setChecked( provider.isImage( BoardSize::FIVE ));
        else if ( boardSize == BoardSize::SIX )
            radioSize[EnumSize::SIX]->setChecked( provider.isImage( BoardSize::SIX ));
        else
            radioSize[EnumSize::SEVEN]->setChecked( provider.isImage( BoardSize::SEVEN ));

        createSquares();
        setSquaresGraphic( false );
        radioKind[EnumKind::GRAPHIC]->setChecked( true );
        action[Action::REMGRAPHIC]->setEnabled( true );
    }
}

/*********************************************************************************************************/
/* SET COLOR *********************************************************************************************/

void MainWindow::setColor()
{
    BoardSize boardSize = board->getCurrentSize();
    QString& currentStyle = Options::getStyle();

    for ( int i = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
        {
            if ( squares[i][j]->styleSheet() != Options::getEmptyStyle() )
                squares[i][j]->setStyleSheet( currentStyle );
        }
    }    
}

/*********************************************************************************************************/
/* REDRAW SQUARES ****************************************************************************************/

void MainWindow::redrawSquares()
{
    createSquares();

    if ( Options::getBoardMode() == BoardMode::NUMERIC)
        setSquaresNumeric( false );
    else
        setSquaresGraphic( false );
}

/***********************************************************************************************************/
/* SLOT SETTINGS *******************************************************************************************/

void MainWindow::slotSettings()
{
    new WindowSetting( *this );
}

/***********************************************************************************************************/
/* SLOT ABOUT **********************************************************************************************/

void MainWindow::slotAbout()
{
    new WindowAbout();
}

