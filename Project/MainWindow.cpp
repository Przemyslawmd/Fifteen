#include "MainWindow.h"

MainWindow::MainWindow( QWidget *parent ) : QMainWindow( parent )
{
    images = new ImageLoad();
    board = new Board( Options::getLevel() );

    resize( 750, 550 );
    createMenu();
    createControls();
    createLayouts();
    createSquares();
    setSquaresNumber( false );    
}

/****************************************************************************************************************************/
/* CREATE MENU BAR **********************************************************************************************************/

void MainWindow::createMenu()
{
    mainMenu = new QMenuBar();    
    fileMenu = new QMenu();
    fileMenu->setTitle( "File" );

    for ( int i = 0; i < ACTION_COUNT; i++ )
      action[i] = new QAction( this );

    action[Action::OPENG]->setText( "Load Graphic File" );
    connect( action[Action::OPENG], SIGNAL( triggered()), this, SLOT( slotLoadGraphic() ));

    action[Action::REMG]->setText( "Remove Graphic" );
    action[Action::REMG]->setEnabled( false );
    connect( action[Action::REMG], SIGNAL( triggered()), this, SLOT( slotRemoveGraphic() ));

    action[Action::SAVE]->setText( "Save Board" );
    connect( action[Action::SAVE], SIGNAL( triggered()), this, SLOT( slotSaveBoard() ));

    action[Action::LOAD]->setText( "Load Board" );
    connect( action[Action::LOAD], SIGNAL( triggered()), this, SLOT( slotReadBoard() ));

    fileMenu->addAction( action[Action::OPENG] );
    fileMenu->addSeparator();
    fileMenu->addAction( action[Action::REMG] );
    fileMenu->addSeparator();
    fileMenu->addAction( action[Action::SAVE] );
    fileMenu->addSeparator();
    fileMenu->addAction( action[Action::LOAD] );

    action[Action::SETT]->setText( "Settings" );
    connect( action[Action::SETT], SIGNAL( triggered()), this, SLOT( slotSettings() ));

    action[Action::INFO]->setText( "About" );
    connect( action[Action::INFO], SIGNAL( triggered()), this, SLOT( slotAbout() ));

    mainMenu->addMenu( fileMenu );
    mainMenu->addAction( action[Action::SETT] );
    mainMenu->addAction( action[Action::INFO] );

    this->setMenuBar( mainMenu );
}

/***********************************************************************************************************/
/* CREATE A LAYOUT FOR SQUARES *****************************************************************************/

void MainWindow::createLayouts()
{
    layImageVertical = new QVBoxLayout;
    layImageVertical->setSpacing( 0 );

    boxImages = new QGroupBox();
    boxImages->setLayout( layImageVertical );

    mainLayout = new QHBoxLayout( window );
    mainLayout->addWidget( boxImages );
    mainLayout->addLayout( rightLayout );

    this->setCentralWidget( window );
}

/*************************************************************************************************************/
/* CREATE RIGHT PANEL FOR CONTROLS ***************************************************************************/

void MainWindow::createControls()
{
    window = new QWidget( this );
    window->setContentsMargins( 20, 20, 0, 10 );

    pushRandom = new QPushButton();
    pushRandom->setStyleSheet( "height:20px;" );
    pushRandom->setText( "Generate Board" );
    connect( pushRandom, SIGNAL( clicked() ), this, SLOT( slotGenerateBoard() ));

    pushSolve = new QPushButton();
    pushSolve->setStyleSheet( "height:20px;" );
    pushSolve->setText( "Solve Board");
    connect( pushSolve, SIGNAL( clicked() ), this, SLOT( slotSolveBoard() ));

    radio[Radio::FOUR].setText( "4" );    
    radio[Radio::FIVE].setText( "5" );
    radio[Radio::SIX].setText( "6" );
    radio[Radio::SEVEN].setText( "7" );
    radio[Radio::FOUR].setChecked( true );

    layRadioDim = new QVBoxLayout();
    groupRadioDimension = new QButtonGroup( window );

    for( int i = Radio::FOUR, j = 4; i <= Radio::SEVEN; i++, j++ )
    {
       layRadioDim->addSpacing( 10 );
       layRadioDim->addWidget( &radio[i] );
       radio[i].setStyleSheet( "margin-left: 5px" );
       groupRadioDimension->addButton( &radio[i] );
       groupRadioDimension->setId( &radio[i], j );
    }
    layRadioDim->addSpacing( 30 );

    boxRadioDimension = new QGroupBox();
    boxRadioDimension->setTitle( "Dimension of Board" );
    boxRadioDimension->setLayout( layRadioDim );


    layRadioKind = new QVBoxLayout();
    groupRadioKind = new QButtonGroup();

    for ( int i = Radio::NUMERICAL; i <= Radio::GRAPHIC; i++)
    {
        layRadioKind->addSpacing( 10 );
        layRadioKind->addWidget( &radio[i] );
        radio[i].setStyleSheet( "margin-left:5px;" );
        groupRadioKind->addButton( &radio[i] );
    }
    layRadioKind->addSpacing( 30 );

    radio[Radio::NUMERICAL].setChecked(true);
    radio[Radio::NUMERICAL].setText( "Numeric" );
    radio[Radio::GRAPHIC].setText( "Graphic" );

    boxRadioKind = new QGroupBox();
    boxRadioKind->setTitle( "Kind of Board" );
    boxRadioKind->setLayout( layRadioKind );

    rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins( 30, 0, 30, 0 );
    rightLayout->addWidget( pushRandom );
    rightLayout->addSpacing( 15);
    rightLayout->addWidget( pushSolve );
    rightLayout->addSpacing( 30);
    rightLayout->addWidget( boxRadioDimension );
    rightLayout->addStretch();
    rightLayout->addWidget( boxRadioKind );
    rightLayout->addStretch();
}

/************************************************************************************************************************/
/* CREATE SQUARES *******************************************************************************************************/

void MainWindow::createSquares()
{
    Level level = Options::getLevel();
    SquareSize squareSize = ( Options::checkNumeric() ) ? Options::getSquareSize() : images->imageSize;

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

    layImageHorizontal = new QHBoxLayout*[level];

    for ( int i = 0; i < level; i++ )
    {
        layImageHorizontal[i] = new QHBoxLayout();
        layImageHorizontal[i]->setSpacing(0);
    }

    layImageVertical->addStretch();
    for ( int i = 0; i < level; i++ )
    {
        layImageHorizontal[i]->addStretch();

        for ( int j = 0; j < level; j++ )
            layImageHorizontal[i]->addWidget( &control[i][j] );

        layImageHorizontal[i]->addStretch();
        layImageVertical->addLayout( layImageHorizontal[i] );
    }
    layImageVertical->addStretch();
}

/***************************************************************************************************************************/
/* DELETE SQUARES **********************************************************************************************************/

void MainWindow::deleteSquares()
{
    Level level = Options::getLevel();
    QLayoutItem* child;

    while ((child = layImageVertical->takeAt(0)) != 0)
        layImageVertical->removeItem(0);

    for (int i = 0; i < level; i++)
        delete[] control[i];

    delete[] control;
    delete[] layImageHorizontal;
}

/**************************************************************************************************************/
/* SET NUMERIC SQUARES ****************************************************************************************/

void MainWindow::setSquaresNumber( bool isRandom )
{    
    Level level = Options::getLevel();
    int** values = ( isRandom == false ) ? board->sendBoard() : board->randomBoard();
    currentStyle = Options::getStyle();
    QFont font;
    font.setPixelSize( Options::getFontSquareSize() );

    for (int i = 0; i < level; i++)
    {
        for (int j = 0; j < level; j++)
        {
            control[i][j].setIcon( QIcon() );
            control[i][j].setText( QString::number( values[i][j] ));
            if ( values[i][j] == 0 )
                control[i][j].setStyleSheet( styleEmpty );
            else
                control[i][j].setStyleSheet( *currentStyle );
            control[i][j].setFont( font );
        }
    }

    Options::setNumeric( true );
}

/*************************************************************************************************************************/
/* SET GRAPHICAL SQUARES *************************************************************************************************/

void MainWindow::setSquaresGraphic( bool isRandom )
{
    Level level = Options::getLevel();
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

    Options::setNumeric( false );
}

/****************************************************************************************************************************/
/* GENERATE BOARD ***********************************************************************************************************/

void MainWindow::slotGenerateBoard()
{
    Level level = static_cast< Level >( groupRadioDimension->checkedId() );

    // In case of graphic board check whether there is a proper image loaded
    if ( radio[Radio::GRAPHIC].isChecked() )
    {
        if ( ( level == Level::FOUR ) && ( images->four.loaded == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 4x4\t" );
            return;
        }
        if ( ( level == Level::FIVE ) && ( images->five.loaded == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 5x5\t");
            return;
        }
        if ( ( level == Level::SIX ) && ( images->six.loaded == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 6x6\t");
            return;
        }
        if ( ( level == Level::SEVEN ) && ( images->seven.loaded == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 7x7\t");
            return;
        }
    }

    delete board;
    deleteSquares();
    Options::setLevel( level );
    board = new Board( level );

    if ( radio[Radio::NUMERICAL].isChecked() )
    {
        Options::setNumeric( true );
        createSquares();
        setSquaresNumber( true );

    }
    else
    {
        Options::setNumeric( false );
        createSquares();
        setSquaresGraphic( true );
    }
}

/**************************************************************************************************************************/
/* SOLVE BOARD ***********************************************************************************************************/

void MainWindow::slotSolveBoard()
{    
    Level level = Options::getLevel();
    int** values = board->solveBoard();

    if ( Options::checkNumeric() )
    {
        for ( int i = 0; i < level; i++ )
        {
            for ( int j = 0; j < level; j++ )
            {
                control[i][j].setText( QString::number( values[i][j] ));
                if ( values[i][j] == 0 )
                    control[i][j].setStyleSheet( styleEmpty );
                else
                    control[i][j].setStyleSheet( *currentStyle );
            }
        }
    }

    else
    {        
        QImage** pictures = ImageProvider::getInstance()->getImage( level );

        int k = 1;
        for ( int i = 0; i < level; i++ )
        {
            for ( int j = 0; j < level; j++ )
            {
                QPixmap* pixmap = new QPixmap();

                if ( i == ( level - 1 ) && j == ( level - 1 ))
                    pixmap->convertFromImage( *pictures[0] );
                else
                    pixmap->convertFromImage( *pictures[k++] );

                QIcon icon( *pixmap );
                QSize iconSize( images->imageSize, images->imageSize );
                control[i][j].setIconSize( iconSize );
                control[i][j].setIcon( icon );
                control[i][j].setStyleSheet( "" );
                control[i][j].setText( "" );
            }
        }
    }
}

/****************************************************************************************************************************/
/* MOVE A SQUARE IF IT'S POSSIBLE *******************************************************************************************/

void MainWindow::pressSquare()
{
    int position = ( (QPushButton*)sender() )->accessibleName().toInt();

    int row = position / 10;
    int col = position % 10;
    int move = board->checkMove( row, col );

    if ( move != 0 )
    {
        // An action for a numeric board
        if ( Options::checkNumeric() )
        {
            switch ( move )
            {
                case 1:
                    control[row - 1][col].setText( control[row][col].text() );
                    control[row - 1][col].setStyleSheet( *currentStyle );
                break;

                case 2:
                    control[row][col + 1].setText( control[row][col].text() );
                    control[row][col + 1].setStyleSheet( *currentStyle );
                break;

                case 3:
                    control[row + 1][col].setText( control[row][col].text() );
                    control[row + 1][col].setStyleSheet( *currentStyle );
                break;

                case 4:
                    control[row][col - 1].setText( control[row][col].text() );
                    control[row][col - 1].setStyleSheet( *currentStyle );
                break;
            }
            control[row][col].setText( "" );
            control[row][col].setStyleSheet( styleEmpty );
        }

        // An action for a graphic board
        else
        {           
            QPixmap pixmap( images->imageSize, images->imageSize );
            pixmap.fill( Qt::white );
            QIcon icon( pixmap );

            switch ( move )
            {
                case 1:
                control[row - 1][col].setIcon( control[row][col].icon() );
                break;

                case 2:
                control[row][col + 1].setIcon( control[row][col].icon() );
                break;

                case 3:
                control[row + 1][col].setIcon( control[row][col].icon() );
                break;

                case 4:
                control[row][col - 1].setIcon( control[row][col].icon() );
                break;
            }
            control[row][col].setIcon( icon );
        }
    }
}

/****************************************************************************************************************************/
/* OPEN GRAPHIC *************************************************************************************************************/

void MainWindow::slotLoadGraphic()
{
  QString fileName = QFileDialog::getOpenFileName( this, "", QDir::currentPath(), tr( "JPG, PNG, GIF, BMP (*.jpg *.png *.gif *.bmp)" ));

  if (!fileName.isEmpty() )
  {
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
            action[Action::REMG]->setEnabled( true );
            images->imageSize = Options::getSquareSize();
        }
    }    
}

/***************************************************************************************************************************/
/* REMOVE GRAPHIC **********************************************************************************************************/

void MainWindow::slotRemoveGraphic()
{
    ImageProvider::deleteInstance();    
    action[Action::REMG]->setEnabled( false );
    images->resetLoaded();

    // Graphic board is active
    if ( Options::checkNumeric() == false )
    {
        QLayoutItem *child;
        while (( child = layImageVertical->takeAt(0)) != 0 )
            layImageVertical->removeItem( 0 );

        deleteSquares();
        createSquares();
        setSquaresNumber( false );
        Options::setNumeric( true );
    }

    QMessageBox::information( this, "", "Graphic removed\t");
}

/***********************************************************************************************************************/
/* WRITE BOARD STATE INTO A BINARY FILE ********************************************************************************/

void MainWindow::slotSaveBoard()
{
    Level boardSize = Options::getLevel();
    QFileDialog dialog;
    QString fileName = dialog.getSaveFileName( this, "", QDir::currentPath() );

    if ( fileName.isEmpty() == false )
    {                
        QFile file( fileName );
        file.open( QIODevice::WriteOnly );
        QDataStream inData( &file );
        inData.setVersion( QDataStream::Qt_4_6 );

        inData << Options::checkNumeric();
        inData << boardSize;

        // Board state        
        int** values = board->sendBoard();
        for ( int i = 0; i < boardSize; i++ )
        {
            for ( int j = 0; j < boardSize; j++ )
                inData << values[i][j];
        }

        // If board to be saved is graphic then bitmaps are being saved as well
        if ( Options::checkNumeric() == false )
        {
            inData << ( quint32 )images->imageSize;
            QImage** pictures = ImageProvider::getInstance()->getImage( boardSize );
            int byteCount = pictures[0]->byteCount();
            inData << byteCount;
            uchar* buffer = new uchar[ byteCount ];

            for (int i = 0; i < boardSize * boardSize; i++)
            {                
                memcpy( buffer, pictures[i]->bits(), byteCount );
                inData.writeRawData( (char*)buffer, byteCount );
            }
            delete [] buffer;
        }

        file.close();        
    }
}

/**********************************************************************************************************************/
/* READ AND RESTORE BOARD FROM A BINARY FILE **************************************************************************/

void MainWindow::slotReadBoard()
{    
    QString fileName = QFileDialog::getOpenFileName( this, "", QDir::currentPath() );

    if( !fileName.isEmpty() )
    {
        QFile file( fileName );
        file.open( QIODevice::ReadOnly );
        QDataStream outData( &file );

        QLayoutItem *child;
        while ((child = layImageVertical->takeAt(0)) != 0)
            layImageVertical->removeItem(0);

        delete board;
        deleteSquares();

        bool isNumeric;
        int** values;
        int level;
        int imageSize;

        outData >> isNumeric;
        outData >> level;

        Options::setLevel( static_cast< Level >( level ));

        values = new int*[level];
        for (int i = 0; i < level; i++)
        {
            values[i] = new int[level];
            for (int j = 0; j < level; j++)
                outData >> values[i][j];
        }

        board = new Board( values, level );


        if ( isNumeric == 1 )
        {
            Options::setNumeric( true );
            createSquares();
            setSquaresNumber( false );
            radio[Radio::NUMERICAL].setChecked( true );
        }
        else
        {
           outData >> imageSize;
           images->imageSize = ( SquareSize )imageSize;
           int byteCount;
           outData >> byteCount;

           // This buffer is moved to an Image object which is responsible for release memory
           // and must exist as long as restored image exists
           uchar* buffer = new uchar[byteCount * level * level];
           for ( int i = 0; i < ( level  * level ); i++ )
               outData.readRawData( (char*)( buffer + i * byteCount ), byteCount );

           ImageProvider::deleteInstance();
           ImageProvider* imageProvider = ImageProvider::getInstance();

           try {
                if ( level == Level::FOUR )
                {
                    images->four.loaded = imageProvider->restoreImageBoardFromFile( buffer, level, images->imageSize, byteCount );
                    radio[Radio::FOUR].setChecked( images->four.loaded );
                }
                else if ( level == Level::FIVE )
                {
                    images->five.loaded = imageProvider->restoreImageBoardFromFile( buffer, level, images->imageSize, byteCount );
                    radio[Radio::FIVE].setChecked( images->five.loaded );
                }
                else if ( level == Level::SIX )
                {
                    images->six.loaded = imageProvider->restoreImageBoardFromFile( buffer, level, images->imageSize, byteCount );
                    radio[Radio::SIX].setChecked( images->six.loaded );
                }
                else
                {
                    images->seven.loaded = imageProvider->restoreImageBoardFromFile( buffer, level, images->imageSize, byteCount );
                    radio[Radio::SEVEN].setChecked( images->seven.loaded );
                }

           }
           catch( ... )
           {
                file.close();
                return;
           }

           Options::setNumeric( false );
           createSquares();
           setSquaresGraphic( false );           
           radio[Radio::GRAPHIC].setChecked( true );
           action[Action::REMG]->setEnabled( true );
        }

        file.close();
    }
}

/********************************************************************************************************/
/* SET COLOR ********************************************************************************************/

void MainWindow::setColor()
{
    Level boardSize = Options::getLevel();
    currentStyle = Options::getStyle();

    for ( int i = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
        {
            if ( control[i][j].styleSheet() != styleEmpty )
                control[i][j].setStyleSheet( *currentStyle );
        }
    }    
}

/**************************************************************************************************************/
/* REDRAW SQUARES WHEN SQUARE SIZE IS CHANGED VIA SETTING WINDOW **********************************************/

void MainWindow::redrawSquares()
{
    deleteSquares();
    createSquares();
    setSquaresNumber( false );
}

/***************************************************************************************************************/
/* CHILD WINDOWS ***********************************************************************************************/

void MainWindow::slotSettings()
{
    new WindowSetting( *images, *this );
}

/*****************************************************************************************************************/

void MainWindow::slotAbout()
{
    new WindowAbout();
}

