#include "MainWindow.h"

MainWindow::MainWindow( QWidget *parent ) : QMainWindow( parent )
{
    imagesLoad = new ImageLoad();    
    board = new Board( Options::getBoardSize() );

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

    action[Action::OPENG]->setText( "Load Graphical file" );
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

    for( int i = Radio::FOUR; i <= Radio::SEVEN; i++ )
    {
       layRadioDim->addSpacing( 10 );
       layRadioDim->addWidget( &radio[i] );
       radio[i].setStyleSheet( "margin-left: 5px" );
       groupRadioDimension->addButton( &radio[i] );
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
    radio[Radio::GRAPHIC].setEnabled(false);
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
    Size boardSize = Options::getBoardSize();
    SquareSize squareSize = ( Options::checkNumeric() ) ? Options::getSquareSize() : imagesLoad->squareSize;

    control = new QPushButton*[boardSize];

    for (int i = 0; i < boardSize; i++)
        control[i] = new QPushButton[boardSize];

    for ( int i = 0; i < boardSize ; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
        {
            control[i][j].setAccessibleName( QString::number(i) + QString::number( j ));
            control[i][j].setMaximumSize( squareSize, squareSize );
            control[i][j].setMinimumSize( squareSize, squareSize );
            connect( &control[i][j], SIGNAL( clicked() ), this, SLOT( passSignal() ));            
        }
    }

    layImageHorizontal = new QHBoxLayout*[boardSize];

    for ( int i = 0; i < boardSize; i++ )
    {
        layImageHorizontal[i] = new QHBoxLayout();
        layImageHorizontal[i]->setSpacing(0);
    }

    layImageVertical->addStretch();
    for ( int i = 0; i < boardSize; i++ )
    {
        layImageHorizontal[i]->addStretch();

        for ( int j = 0; j < boardSize; j++ )
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
    Size size = Options::getBoardSize();
    QLayoutItem* child;

    while ((child = layImageVertical->takeAt(0)) != 0)
        layImageVertical->removeItem(0);

    for (int i = 0; i < size; i++)
        delete[] control[i];

    delete[] control;
    delete[] layImageHorizontal;
}

/*************************************************************************************************************************/
/* SET NUMERICAL SQUARES *************************************************************************************************/

void MainWindow::setSquaresNumber( bool isRandom )
{    
    Size size = Options::getBoardSize();
    int** values = ( isRandom == false ) ? board->sendBoard() : board->randomBoard();
    Color color = Options::getColor();
    QFont font;
    font.setPixelSize( Options::getFontSquareSize() );

    if ( color == Color::BLUE )
        currentStyle = &styleBlue;
    else if ( color == Color::GREEN )
        currentStyle = &styleGreen;
    else
        currentStyle = &styleRed;


    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            control[i][j].setIcon( QIcon() );
            control[i][j].setText( QString::number(values[i][j]) );
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
    Size size = Options::getBoardSize();
    SquareSize squareSize = imagesLoad->squareSize;

    int** values = ( isRandom == false ) ? board->sendBoard() : board->randomBoard();

    QImage** pictures = ImageProvider::getInstance()->getImage( size );

    for ( int i = 0; i < size; i++ )
    {
        for ( int j = 0; j < size; j++ )
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
    Size boardSize;
    if ( radio[Radio::FOUR].isChecked() )
        boardSize = Size::FOUR;
    else if( radio[Radio::FIVE].isChecked() )
        boardSize = Size::FIVE;
    else if ( radio[Radio::SIX].isChecked() )
        boardSize = Size::SIX;
    else
        boardSize = Size::SEVEN;

    // Check whether in case of graphic board there is proper graphic loaded
    if ( radio[Radio::GRAPHIC].isChecked() )
    {
        if ( ( boardSize == Size::FOUR ) && ( imagesLoad->four.loaded == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 4x4\t" );
            return;
        }
        if ( ( boardSize == Size::FIVE ) && ( imagesLoad->five.loaded == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 5x5\t");
            return;
        }
        if ( ( boardSize == Size::SIX ) && ( imagesLoad->six.loaded == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 6x6\t");
            return;
        }
        if ( ( boardSize == Size::SEVEN ) && ( imagesLoad->seven.loaded == false ))
        {
            QMessageBox::information( this, "", "There is no loaded graphic for a board 7x7\t");
            return;
        }
    }

    delete board;
    deleteSquares();
    Options::setBoardSize( boardSize );
    board = new Board( boardSize );

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
/* SOLVES BOARD ***********************************************************************************************************/

void MainWindow::slotSolveBoard()
{    
    Size size = Options::getBoardSize();
    int** values = board->solveBoard();

    if ( Options::checkNumeric() )
    {
        for ( int i = 0; i < size; i++ )
        {
            for ( int j = 0; j < size; j++ )
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
        QImage** pictures = ImageProvider::getInstance()->getImage( size );

        int k = 1;
        for ( int i = 0; i < size; i++ )
        {
            for ( int j = 0; j < size; j++ )
            {
                QPixmap* pixmap = new QPixmap();

                if ( i == ( size - 1 ) && j == ( size - 1 ))
                    pixmap->convertFromImage( *pictures[0] );
                else
                    pixmap->convertFromImage( *pictures[k++] );

                QIcon icon( *pixmap );
                QSize iconSize( imagesLoad->squareSize, imagesLoad->squareSize );
                control[i][j].setIconSize( iconSize );
                control[i][j].setIcon( icon );
                control[i][j].setStyleSheet( "" );
                control[i][j].setText( "" );
            }
        }
    }
}

/****************************************************************************************************************************/
/* PASSES SIGNAL TO BOARD INSTANCE ******************************************************************************************/

void MainWindow::passSignal()
{
    int position = ( (QPushButton*)sender() )->accessibleName().toInt();

    int row = position / 10;
    int col = position % 10;
    int move = board->checkMove( row, col );

    if ( move != 0 )
    {
        // ACTION FOR A NUMBER BOARD
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

        // ACTION FOR A GRAPHICAL BOARD
        else
        {           
            QPixmap pixmap( imagesLoad->squareSize, imagesLoad->squareSize );
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
        ImageProvider::getInstance()->prepareBoardImage( &picture, &message, *imagesLoad, Options::getSquareSize() );
        QMessageBox::information( this, "", message );

        if ( imagesLoad->four.loaded == true || imagesLoad->five.loaded == true || imagesLoad->six.loaded == true || imagesLoad->seven.loaded == true )
        {
            radio[Radio::GRAPHIC].setEnabled( true );
            action[Action::REMG]->setEnabled( true );
            imagesLoad->squareSize = Options::getSquareSize();
        }
    }    
}

/***************************************************************************************************************************/
/* REMOVE GRAPHIC **********************************************************************************************************/

void MainWindow::slotRemoveGraphic()
{
    ImageProvider::deleteInstance();

    radio[Radio::GRAPHIC].setEnabled( false );
    radio[Radio::NUMERICAL].setChecked( true );
    action[Action::REMG]->setEnabled( false );
    imagesLoad->resetLoaded();

    // If active board is a graphic board
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

/*******************************************************************************************************************************/
/* WRITES BOARD STATE INTO A BINARY FILE ***************************************************************************************/

void MainWindow::slotSaveBoard()
{
    Size size = Options::getBoardSize();
    QFileDialog dialog;
    QString fileName = dialog.getSaveFileName(this, "", QDir::currentPath());

    if ( fileName.isEmpty() == false )
    {                
        QFile file( fileName );
        file.open( QIODevice::WriteOnly );
        QDataStream inData( &file );
        inData.setVersion( QDataStream::Qt_4_6 );

        inData << (bool)Options::checkNumeric();
        int temp = (quint32)size;
        inData << temp;

        // Board state        
        int** values = board->sendBoard();
        for ( int i = 0; i < size; i++ )
        {
            for ( int j = 0; j < size; j++ )
                inData << (qint32)values[i][j];
        }

        // If board is graphical then bitmaps are saved as well
        if ( Options::checkNumeric() == false )
        {
            QImage** pictures = ImageProvider::getInstance()->getImage( size );
            uchar buffer[10000];

            for (int i = 0; i < size * size; i++)
            {
                memcpy(buffer, pictures[i]->bits(), pictures[i]->byteCount());
                inData.writeRawData( (char*)&buffer, 10000 );
            }
        }

        file.close();
    }
}

/********************************************************************************************************************************/
/* READ AND RESTORE SAVED BOARD FROM A BINARY FILE ******************************************************************************************/

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

        bool tempIsNumber;
        int** tempValues;
        int size;

        outData >> tempIsNumber;
        outData >> size;

        if ( size == 4 )
            Options::setBoardSize( Size::FOUR );
        else if ( size == 5 )
            Options::setBoardSize( Size::FIVE );
        else if ( size == 6 )
            Options::setBoardSize( Size::SIX );
        else if ( size == 7 )
            Options::setBoardSize( Size::SEVEN );

        tempValues = new int*[size];
        for (int i = 0; i < size; i++)
        {
            tempValues[i] = new int[size];
            for (int j = 0; j < size; j++)
                outData >> tempValues[i][j];
        }

        board = new Board( tempValues, size );
        createSquares();

        if ( tempIsNumber == 1 )
        {
            setSquaresNumber( false );
            Options::setNumeric( true );
            radio[Radio::NUMERICAL].setChecked( true );
        }
        else
        {
           // This buffer is moved to an Image object which is responsible for releasing memory
           // This data must exist as long as restored image exists
           uchar* buffer = new uchar[10000 * size * size];
           for (int i = 0; i < ( size  * size ); i++)
               outData.readRawData((char*)(buffer + i * 10000), 10000);

           ImageProvider::deleteInstance();
           ImageProvider* imageProvider = ImageProvider::getInstance();

           try {
                if ( size == Size::FOUR )
                {
                    imagesLoad->four.loaded = imageProvider->restoreImageBoardFromFile( buffer, size );
                    radio[Radio::FOUR].setChecked( imagesLoad->four.loaded );
                }
                else if ( size == Size::FIVE )
                {
                    imagesLoad->five.loaded = imageProvider->restoreImageBoardFromFile( buffer, size );
                    radio[Radio::FIVE].setChecked( imagesLoad->five.loaded );
                }
                else if ( size == Size::SIX )
                {
                    imagesLoad->six.loaded = imageProvider->restoreImageBoardFromFile( buffer, size );
                    radio[Radio::SIX].setChecked( imagesLoad->six.loaded );
                }
                else
                {
                    imagesLoad->seven.loaded = imageProvider->restoreImageBoardFromFile( buffer, size );
                    radio[Radio::SEVEN].setChecked( imagesLoad->seven.loaded );
                }

           }
           catch( ... )
           {
                file.close();
                return;
           }

           setSquaresGraphic( false );
           radio[Radio::GRAPHIC].setEnabled( true );
           radio[Radio::GRAPHIC].setChecked( true );
           action[Action::REMG]->setEnabled( true );
           Options::setNumeric( false );
        }

        file.close();
    }
}

/********************************************************************************************************/
/* SET COLOR ********************************************************************************************/

void MainWindow::setColor()
{
    Size size = Options::getBoardSize();
    Color color = Options::getColor();

    if ( color == Color::BLUE )
        currentStyle = &styleBlue;
    else if ( color == Color::GREEN )
        currentStyle = &styleGreen;
    else
        currentStyle = &styleRed;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
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
    new WindowSetting( imagesLoad, this );
}

/*****************************************************************************************************************/

void MainWindow::slotAbout()
{
    new WindowAbout();
}

