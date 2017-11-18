
#include "MainWindow.h"

MainWindow::MainWindow( QWidget *parent ) : QMainWindow{ parent }, mainPanel{ this }
{
    images = new ImagesState();
    board = Board::createBoard( Options::getBoardSize() );

    resize( 750, 550 );
    createMenu();
    createRightPanel();
    createLayouts();
    createSquares();
    setSquaresNumeric( false );
}

/******************************************************************************************************/
/* CREATE MENU BAR ************************************************************************************/

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

/*************************************************************************************************************/
/* CREATE RIGHT PANEL ****************************************************************************************/

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

    // Radio buttons for kind of a board

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

    // Right layout

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

/***********************************************************************************************************/
/* CREATE A LAYOUT FOR SQUARES *****************************************************************************/

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

/*******************************************************************************************************/
/* CREATE SQUARES **************************************************************************************/

void MainWindow::createSquares()
{
    BoardSize level = Options::getBoardSize();
    SquareSize squareSize = ( Options::getBoardMode() == BoardMode::NUMERIC ) ? Options::getSquareSize() : images->imageSize;

    control = new QPushButton*[level];

    for (int i = 0; i < level; i++)
        control[i] = new QPushButton[level];

    for ( int i = 0; i < level ; i++ )
    {
        for ( int j = 0; j < level; j++ )
        {
            control[i][j].setAccessibleName( QString::number(i) + QString::number( j ));
            control[i][j].setMaximumSize( squareSize, squareSize );
            control[i][j].setMinimumSize( squareSize, squareSize );
            connect( &control[i][j], SIGNAL( clicked() ), this, SLOT( pressSquare() ));
        }
    }

    boardHorizontalLayout = new QHBoxLayout[level];

    for ( int i = 0; i < level; i++ )
        boardHorizontalLayout[i].setSpacing(0);

    boardVerticalLayout->addStretch();

    for ( int i = 0; i < level; i++ )
    {
        boardHorizontalLayout[i].addStretch();

        for ( int j = 0; j < level; j++ )
            boardHorizontalLayout[i].addWidget( &control[i][j] );

        boardHorizontalLayout[i].addStretch();
        boardVerticalLayout->addLayout( &boardHorizontalLayout[i] );
    }
    boardVerticalLayout->addStretch();
}

/*********************************************************************************************************/
/* DELETE SQUARES ****************************************************************************************/

void MainWindow::deleteSquares()
{
    BoardSize level = Options::getBoardSize();
    QLayoutItem* child;

    while (( child = boardVerticalLayout->takeAt(0)) != 0 )
        boardVerticalLayout->removeItem(0);

    for ( int i = 0; i < level; i++ )
        delete[] control[i];

    delete[] control;
    delete[] boardHorizontalLayout;
}

/*********************************************************************************************************/
/* SET SQUARES NUMERIC ***********************************************************************************/

void MainWindow::setSquaresNumeric( bool isRandom )
{    
    BoardSize level = Options::getBoardSize();
    int** values = ( isRandom == false ) ? board->sendBoard() : board->randomBoard();
    QString& currentStyle = Options::getStyle();
    QFont font;
    font.setPixelSize( Options::getSquareSizeFont() );

    for ( int i = 0; i < level; i++ )
    {
        for ( int j = 0; j < level; j++ )
        {
            control[i][j].setText( QString::number( values[i][j] ));
            if ( values[i][j] == 0 )
                control[i][j].setStyleSheet( Options::getEmptyStyle() );
            else
                control[i][j].setStyleSheet( currentStyle );
            control[i][j].setFont( font );
        }
    }

    Options::setBoardMode( BoardMode::NUMERIC );
}

/*********************************************************************************************************/
/* SET SQUARES GRAPHIC ***********************************************************************************/

void MainWindow::setSquaresGraphic( bool isRandom )
{
    BoardSize level = Options::getBoardSize();
    SquareSize squareSize = images->imageSize;

    int** values = ( isRandom == false ) ? board->sendBoard() : board->randomBoard();
    QImage** pictures = ImageProvider::getInstance()->getImage( level );

    for ( int i = 0; i < level; i++ )
    {
        for ( int j = 0; j < level; j++ )
        {
            QPixmap* pixmap = new QPixmap();
            pixmap->convertFromImage( *pictures[values[i][j]] );
            QIcon icon( *pixmap );
            QSize iconSize( squareSize, squareSize );
            control[i][j].setIconSize( iconSize );
            control[i][j].setIcon( icon );
            control[i][j].setStyleSheet( "" );
            control[i][j].setText( "" );
        }
    }

    Options::setBoardMode( BoardMode::GRAPHIC );
}

/*********************************************************************************************************/
/* GENERATE BOARD ****************************************************************************************/

void MainWindow::slotGenerateBoard()
{
    BoardSize boardSize = static_cast< BoardSize >( groupRadioSize->checkedId() );

    // In case of graphic board check whether there is a proper image loaded
    if ( radioKind[EnumKind::GRAPHIC]->isChecked() )
    {
        if (( boardSize == BoardSize::FOUR ) && ( images->four.loaded == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 4x4\t" );
            return;
        }
        if (( boardSize == BoardSize::FIVE ) && ( images->five.loaded == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 5x5\t");
            return;
        }
        if (( boardSize == BoardSize::SIX ) && ( images->six.loaded == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 6x6\t");
            return;
        }
        if (( boardSize == BoardSize::SEVEN ) && ( images->seven.loaded == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 7x7\t");
            return;
        }
    }

    deleteSquares();
    Options::setBoardSize( boardSize );
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

/*********************************************************************************************************/
/* SOLVE BOARD *******************************************************************************************/

void MainWindow::slotSolveBoard()
{
    board->solveBoard();

    if ( Options::getBoardMode() == BoardMode::NUMERIC )
        setSquaresNumeric( false );
    else         
        setSquaresGraphic( false );
}

/*********************************************************************************************************/
/* MOVE SQUARE IF POSSIBLE *******************************************************************************/

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

/*********************************************************************************************************/
/* MOVE NUMERIC SQUARES **********************************************************************************/

void MainWindow::moveNumericSquares( int rowSource, int colSource, int rowDest, int colDest )
{
    QString& currentStyle = Options::getStyle();
    control[rowDest][colDest].setText( control[rowSource][colSource].text() );
    control[rowDest][colDest].setStyleSheet( currentStyle );
    control[rowSource][colSource].setText( "" );
    control[rowSource][colSource].setStyleSheet( Options::getEmptyStyle() );
}

/*********************************************************************************************************/
/* MOVE GRAPHIC SQUARES **********************************************************************************/

void MainWindow::moveGraphicSquares( int rowSource, int colSource, int rowDest, int colDest )
{
    control[rowDest][colDest].setIcon( control[rowSource][colSource].icon() );
    QPixmap pixmap( images->imageSize, images->imageSize );
    pixmap.fill( Qt::white );
    QIcon nullIcon( pixmap );
    control[rowSource][colSource].setIcon( nullIcon );
}

/*********************************************************************************************************/
/* LOAD GRAPHIC FILE *************************************************************************************/

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

    QString message;
    ImageProvider::getInstance()->prepareBoardImage( picture, message, *images, Options::getSquareSize() );
    QMessageBox::information( this, "", message );

    if ( images->four.loaded || images->five.loaded || images->six.loaded || images->seven.loaded )
    {
        action[Action::REMGRAPHIC]->setEnabled( true );
        images->imageSize = Options::getSquareSize();
    }
}

/*********************************************************************************************************/
/* REMOVE GRAPHIC ****************************************************************************************/

void MainWindow::slotRemoveGraphic()
{
    ImageProvider::deleteInstance();    
    action[Action::REMGRAPHIC]->setEnabled( false );
    images->resetLoaded();

    // Graphic board is active
    if ( Options::getBoardMode() == BoardMode::GRAPHIC )
    {
        QLayoutItem *child;
        while (( child = boardVerticalLayout->takeAt(0)) != 0 )
            boardVerticalLayout->removeItem( 0 );

        deleteSquares();
        createSquares();
        setSquaresNumeric( false );
        Options::setBoardMode( BoardMode::NUMERIC );
    }

    QMessageBox::information( this, "", "Graphic removed\t");
}

/*********************************************************************************************************/
/* SLOT SAVE BOARD ***************************************************************************************/

void MainWindow::slotSaveBoard()
{
    QString fileName = QFileDialog::getSaveFileName( this, "", QDir::currentPath() );

    if ( fileName.isEmpty() )
        return;

    IOFile ioFile;
    if ( Options::getBoardMode() == BoardMode::NUMERIC )
        ioFile.saveNumericBoardInFile( board, fileName );
    else
        ioFile.saveGraphicBoardInFile( board, images, fileName );
}

/*********************************************************************************************************/
/* RESTORE BOARD FROM FILE *******************************************************************************/

void MainWindow::slotReadBoard()
{    
    QString fileName = QFileDialog::getOpenFileName( this, "", QDir::currentPath() );

    if( fileName.isEmpty() )
        return;

    QLayoutItem *child;
    while (( child = boardVerticalLayout->takeAt(0)) != 0)
        boardVerticalLayout->removeItem(0);

    deleteSquares();

    IOFile ioFile;
    int** values = ioFile.readBoardFromFile( fileName, images );
    int boardSize = Options::getBoardSize();
    board = Board::createBoard( values, boardSize );

    if ( Options::getBoardMode() == BoardMode::NUMERIC )
    {
        createSquares();
        setSquaresNumeric( false );
        radioKind[EnumKind::NUMERIC]->setChecked( true );
    }
    else
    {
        if ( boardSize == BoardSize::FOUR )
            radioSize[EnumSize::FOUR]->setChecked( images->four.loaded );
        else if ( boardSize == BoardSize::FIVE )
            radioSize[EnumSize::FIVE]->setChecked( images->five.loaded );
        else if ( boardSize == BoardSize::SIX )
            radioSize[EnumSize::SIX]->setChecked( images->six.loaded );
        else
            radioSize[EnumSize::SEVEN]->setChecked( images->seven.loaded );

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
    BoardSize boardSize = Options::getBoardSize();
    QString& currentStyle = Options::getStyle();

    for ( int i = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
        {
            if ( control[i][j].styleSheet() != Options::getEmptyStyle() )
                control[i][j].setStyleSheet( currentStyle );
        }
    }    
}

/*********************************************************************************************************/
/* REDRAW SQUARES ****************************************************************************************/

void MainWindow::redrawSquares()
{
    deleteSquares();
    createSquares();
    setSquaresNumeric( false );
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

