#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    size = Size::FOUR;
    isNumber = true;
    isScaled = true;
    color = Color::BLUE;
    isPl = true;

    imagesLoad = new ImageLoad();
    imageProvider = nullptr;

    numberStyleRed = new QString("background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #800000, stop:1 #EE0000); color:white; font-size:20px; border:1px solid white;");
    numberStyleGreen = new QString("background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #004d00, stop:1 #009900); color:white; font-size:20px; border:1px solid white;");
    numberStyleBlue = new QString("background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #000080, stop:1 #0000EE); color:white; font-size:20px; border:1px solid white;");
    emptyStyle = new QString("background-color:white; color:white; font-size:20px; border:1px solid white;");
    board = new Board( size );

    resize( 750,550 );
    createMenu();
    createControls();
    createLayouts();
    createSquares();
    setSquaresNumber( false );

    text = new Text();
    setText();
}

/****************************************************************************************************************************/
/* CREATES MENU *************************************************************************************************************/

void MainWindow::createMenu()
{
    mainMenu = new QMenuBar();    
    fileMenu = new QMenu();

    // FILE MENU
    acOpenGraphic = new QAction(this);
    connect(acOpenGraphic, SIGNAL(triggered()),this, SLOT(slotLoadGraphic()));
    acRemoveGraphic = new QAction(this);
    acRemoveGraphic->setEnabled(false);
    connect(acRemoveGraphic, SIGNAL(triggered()), this, SLOT(slotRemoveGraphic()));
    acSaveBoard = new QAction(this);
    connect(acSaveBoard, SIGNAL(triggered()), this, SLOT(slotSaveBoard()));
    acLoadBoard = new QAction(this);
    connect(acLoadBoard, SIGNAL(triggered()), this, SLOT(slotReadBoard()));

    fileMenu->addAction(acOpenGraphic);
    fileMenu->addSeparator();
    fileMenu->addAction(acRemoveGraphic);
    fileMenu->addSeparator();
    fileMenu->addAction(acSaveBoard);
    fileMenu->addSeparator();
    fileMenu->addAction(acLoadBoard);

    acSettings = new QAction(this);
    connect(acSettings, SIGNAL(triggered()), this, SLOT(slotSettings()));

    infoMenu = new QAction( this );
    connect( infoMenu, SIGNAL(triggered()), this, SLOT( slotAbout()));

    mainMenu->addMenu(fileMenu);
    mainMenu->addAction(acSettings);    
    mainMenu->addAction( infoMenu );

    this->setMenuBar(mainMenu);
}

/***********************************************************************************************************/
/* CREATE SQUARE LAYOUT ************************************************************************************/

void MainWindow::createLayouts()
{
    layImageVertical = new QVBoxLayout;
    layImageVertical->setSpacing(0);

    boxImages = new QGroupBox();
    boxImages->setLayout(layImageVertical);

    mainLayout = new QHBoxLayout(window);
    mainLayout->addWidget(boxImages);
    mainLayout->addLayout(rightLayout);

    this->setCentralWidget(window);
}

/*************************************************************************************************************/
/* CREATE CONTROLS *******************************************************************************************/

void MainWindow::createControls()
{
    window = new QWidget(this);
    window->setContentsMargins(20,20,0,10);

    pushRandom = new QPushButton();
    pushRandom->setStyleSheet("height:20px;");
    connect(pushRandom, SIGNAL(clicked()), this, SLOT(slotGenerateBoard()));

    pushSolve = new QPushButton();
    pushSolve->setStyleSheet("height:20px;");
    connect(pushSolve, SIGNAL(clicked()), this, SLOT(slotSolveBoard()));

    radioFour = new QRadioButton("4", window);
    radioFour->setStyleSheet("margin-left:5px;");
    radioFour->setChecked(true);
    radioFive = new QRadioButton("5", window);
    radioFive->setStyleSheet("margin-left:5px;");
    radioSix = new QRadioButton("6", window);
    radioSix->setStyleSheet("margin-left:5px;");
    radioSeven = new QRadioButton("7", window);
    radioSeven->setStyleSheet("margin-left:5px;");    

    groupRadioDimension = new QButtonGroup(window);
    groupRadioDimension->addButton(radioFour);
    groupRadioDimension->addButton(radioFive);
    groupRadioDimension->addButton(radioSix);
    groupRadioDimension->addButton(radioSeven);    

    layRadioDim = new QVBoxLayout();
    layRadioDim->addSpacing(10);
    layRadioDim->addWidget(radioFour);
    layRadioDim->addSpacing(10);
    layRadioDim->addWidget(radioFive);
    layRadioDim->addSpacing(10);
    layRadioDim->addWidget(radioSix);
    layRadioDim->addSpacing(10);
    layRadioDim->addWidget(radioSeven);
    layRadioDim->addSpacing(30);
    boxRadioDimension = new QGroupBox();
    boxRadioDimension->setLayout(layRadioDim);


    radioNumber = new QRadioButton();
    radioNumber->setChecked(true);
    radioNumber->setStyleSheet("margin-left:5px;");
    radioGraphic = new QRadioButton();
    radioGraphic->setEnabled(false);
    radioGraphic->setStyleSheet("margin-left:5px;");
    groupRadioKind = new QButtonGroup();
    groupRadioKind->addButton(radioNumber);
    groupRadioKind->addButton(radioGraphic);
    layRadioKind = new QVBoxLayout();
    layRadioKind->addSpacing(10);
    layRadioKind->addWidget(radioNumber);
    layRadioKind->addSpacing(10);
    layRadioKind->addWidget(radioGraphic);
    layRadioKind->addSpacing(30);
    boxRadioKind = new QGroupBox();
    boxRadioKind->setLayout(layRadioKind);

    rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins(30,0,30,0);
    rightLayout->addWidget(pushRandom);
    rightLayout->addSpacing(15);
    rightLayout->addWidget(pushSolve);
    rightLayout->addSpacing(30);
    rightLayout->addWidget(boxRadioDimension);
    rightLayout->addStretch();
    rightLayout->addWidget(boxRadioKind);
    rightLayout->addStretch();
}

/************************************************************************************************************************/
/* CREATE SQUARES *******************************************************************************************************/

void MainWindow::createSquares()
{
    control = new QPushButton*[size];
    for (int i = 0; i < size; i++)
        control[i] = new QPushButton[size];

    for (int i = 0; i < size ; i++)
    {
        for (int j = 0; j < size; j++)
        {
            control[i][j].setAccessibleName(QString::number(i) + QString::number(j));
            control[i][j].setMaximumSize(50,50);
            control[i][j].setMinimumSize(50,50);
            connect(&control[i][j], SIGNAL(clicked()), this, SLOT(passSignal()));
        }
    }

    layImageHorizontal = new QHBoxLayout*[size];

    for (int i = 0; i < size; i++)
    {
        layImageHorizontal[i] = new QHBoxLayout();
        layImageHorizontal[i]->setSpacing(0);
    }

    layImageVertical->addStretch();
    for (int i = 0; i < size; i++)
    {
        layImageHorizontal[i]->addStretch();

        for (int j = 0; j < size; j++)
            layImageHorizontal[i]->addWidget(&control[i][j]);

        layImageHorizontal[i]->addStretch();
        layImageVertical->addLayout(layImageHorizontal[i]);
    }
    layImageVertical->addStretch();
}

/***************************************************************************************************************************/
/* DELETE SQUARES **********************************************************************************************************/

void MainWindow::deleteSquares()
{
    QLayoutItem* child;
    while ((child = layImageVertical->takeAt(0)) != 0)
        layImageVertical->removeItem(0);

    for (int i = 0; i < size; i++)
        delete[] control[i];

    delete[] control;
    delete[] layImageHorizontal;
}


/***************************************************************************************************************************/
/* SET SQUARES NUMBER VALUES ***********************************************************************************************/

void MainWindow::setSquaresNumber( bool isRandom )
{
    int** values;

    if ( !isRandom )
        values = board->sendBoard();
    else
        values = board->randomBoard();

    if ( color == Color::BLUE )
        numberStyle = numberStyleBlue;
    else if ( color == Color::GREEN )
        numberStyle = numberStyleGreen;
    else
        numberStyle = numberStyleRed;


    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            control[i][j].setIcon(QIcon());
            control[i][j].setText(QString::number(values[i][j]));
            if (values[i][j] == 0)
                control[i][j].setStyleSheet(*emptyStyle);
            else
                control[i][j].setStyleSheet(*numberStyle);
        }
    }
}

/***************************************************************************************************************************/
/* SETS SQUARES GRAPHICAL VALUES *******************************************************************************************/

void MainWindow::setSquaresGraphic(bool isRandom)
{    
    int** values;

    if (!isRandom)
        values = board->sendBoard();
    else
        values = board->randomBoard();

    QImage** pictures = imageProvider->getImage( size );

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            QPixmap* pixmap = new QPixmap();
            pixmap->convertFromImage(*pictures[values[i][j]]);
            QIcon icon(*pixmap);
            QSize iconSize( 50, 50 );
            control[i][j].setIconSize(iconSize);
            control[i][j].setIcon(icon);
            control[i][j].setStyleSheet("");
            control[i][j].setText("");
        }
    }
}

/****************************************************************************************************************************/
/* GENERATE BOARD ***********************************************************************************************************/
/* Invoke proper method in board object *************************************************************************************/
/* Get an array of values and set controls **********************************************************************************/

void MainWindow::slotGenerateBoard()
{
    Size newSize;
    if ( radioFour->isChecked() )
        newSize = Size::FOUR;
    else if(radioFive->isChecked())
        newSize = Size::FIVE;
    else if (radioSix->isChecked())
        newSize = Size::SIX;
    else
        newSize = Size::SEVEN;

    // Checking whether in case of graphical board there is proper graphic loaded
    if (radioGraphic->isChecked())
    {
        if ( newSize == Size::FOUR && ( imagesLoad->four.loaded == false ))
        {
            QMessageBox::information(this,"", labelsMessages->value("noImage") + "4x4\t");
            return;
        }
        if ( newSize == Size::FIVE && ( imagesLoad->five.loaded == false ))
        {
            QMessageBox::information(this,"", labelsMessages->value("noImage") + "5x5\t");
            return;
        }
        if ( newSize == Size::SIX && ( imagesLoad->six.loaded == false ))
        {
            QMessageBox::information(this,"", labelsMessages->value("noImage") + "6x6\t");
            return;
        }
        if ( newSize == Size::SEVEN && ( imagesLoad->seven.loaded == false ))
        {
            QMessageBox::information(this,"", labelsMessages->value("noImage") + "7x7\t");
            return;
        }
    }

    // New size, new board needed
    if ( size != newSize )
    {
        delete board;
        deleteSquares();
        size = newSize;
        board = new Board( size );
        createSquares();        
    }

    if ( radioNumber->isChecked() )
    {
        setSquaresNumber( true );
        isNumber = true;
    }
    else
    {
        setSquaresGraphic( true );
        isNumber = false;
    }
}

/**************************************************************************************************************************/
/* SOLVES BOARD ***********************************************************************************************************/

void MainWindow::slotSolveBoard()
{
    int** values;

    values = board->solveBoard();

    if (isNumber)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                control[i][j].setText( QString::number(values[i][j]) );
                if (values[i][j] == 0)
                    control[i][j].setStyleSheet( *emptyStyle );
                else
                    control[i][j].setStyleSheet( *numberStyle );
            }
        }
    }

    else
    {
        QImage** pictures;
        pictures = imageProvider->getImage( size );

        int k = 1;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                QPixmap* pixmap = new QPixmap();

                if (i == (size - 1) && j == (size - 1))
                    pixmap->convertFromImage(*pictures[0]);
                else
                    pixmap->convertFromImage(*pictures[k++]);

                QIcon icon(*pixmap);
                QSize iconSize(50, 50);
                control[i][j].setIconSize(iconSize);
                control[i][j].setIcon(icon);
                control[i][j].setStyleSheet("");
                control[i][j].setText("");
            }
        }
    }
}

/****************************************************************************************************************************/
/* PASSES SIGNAL TO BOARD INSTANCE ******************************************************************************************/

void MainWindow::passSignal()
{
    int position = ((QPushButton*)sender())->accessibleName().toInt();

    int row = position / 10;
    int col = position % 10;

    int move = board->checkMove(row, col);

    if (move != 0)
    {
        // ACTION FOR NUMBER BOARD
        if (isNumber)
        {
            switch (move)
            {
                case 1:
                    control[row - 1][col].setText(control[row][col].text());
                    control[row - 1][col].setStyleSheet(*numberStyle);
                break;

                case 2:
                    control[row][col + 1].setText(control[row][col].text());
                    control[row][col + 1].setStyleSheet(*numberStyle);
                break;

                case 3:
                    control[row + 1][col].setText(control[row][col].text());
                    control[row + 1][col].setStyleSheet(*numberStyle);
                break;

                case 4:
                    control[row][col - 1].setText(control[row][col].text());
                    control[row][col - 1].setStyleSheet(*numberStyle);
                break;
            }
            control[row][col].setText("");
            control[row][col].setStyleSheet(*emptyStyle);
        }

        // ACTION FOR GRAPHICAL BOARD
        else
        {           
            QPixmap pixmap(50, 50);
            pixmap.fill(Qt::white);
            QIcon icon(pixmap);

            switch (move)
            {
                case 1:
                control[row - 1][col].setIcon(control[row][col].icon());
                break;

                case 2:
                control[row][col + 1].setIcon(control[row][col].icon());
                break;

                case 3:
                control[row + 1][col].setIcon(control[row][col].icon());
                break;

                case 4:
                control[row][col - 1].setIcon(control[row][col].icon());
                break;
            }
            control[row][col].setIcon(icon);
        }
    }
}

/****************************************************************************************************************************/
/* OPEN GRAPHIC *************************************************************************************************************/

void MainWindow::slotLoadGraphic()
{
  QString fileName = QFileDialog::getOpenFileName(this,"",QDir::currentPath(), tr("JPG, PNG, GIF, BMP (*.jpg *.png *.gif *.bmp)"));

  if(!fileName.isEmpty())
  {
        QImage* picture = new QImage();
        picture->load(fileName);

        if(picture->isNull())
        {
            QMessageBox::information(this,"",labelsMessages->value("openGFail"));
            return;
        }

        QString message;
        imageProvider = ImageProvider::getInstance();
        imageProvider->prepareBoardImage( picture, &message, labelsMessages, *imagesLoad, isScaled );
        QMessageBox::information( this, "", message );

        if ( imagesLoad->four.loaded == true || imagesLoad->five.loaded == true || imagesLoad->six.loaded == true || imagesLoad->seven.loaded == true )
        {
            radioGraphic->setEnabled( true );
            acRemoveGraphic->setEnabled( true );
        }
    }    
}

/***************************************************************************************************************************/
/* REMOVE GRAPHIC **********************************************************************************************************/

void MainWindow::slotRemoveGraphic()
{
    ImageProvider::deleteInstance();

    radioGraphic->setEnabled( false );
    radioNumber->setChecked( true );
    acRemoveGraphic->setEnabled( false );
    imagesLoad->resetLoaded();

    // If active boards is graphical board
    if ( !isNumber )
    {
        QLayoutItem *child;
        while (( child = layImageVertical->takeAt(0)) != 0 )
            layImageVertical->removeItem( 0 );

        deleteSquares();
        createSquares();
        setSquaresNumber( false );
        isNumber = true;
    }

    QMessageBox::information( this,"",labelsMessages->value("remG") );
}

/*******************************************************************************************************************************/
/* WRITES BOARD STATE INTO A BINARY FILE ***************************************************************************************/

void MainWindow::slotSaveBoard()
{
    QFileDialog dialog;
    QString fileName = dialog.getSaveFileName(this, "", QDir::currentPath());

    if (!fileName.isEmpty())
    {                
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QDataStream inData(&file);
        inData.setVersion(QDataStream::Qt_4_6);

        inData << (bool)isNumber;
        inData << (qint32)size;

        // Board state        
        int** values = board->sendBoard();
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                inData << (qint32)values[i][j];
        }

        // If board is graphical then bitmaps are saved as well
        if (!isNumber)
        {
            QImage** pictures = imageProvider->getImage(size);
            uchar* buffer = new uchar[10000];

            for (int i = 0; i < size * size; i++)
            {
                memcpy(buffer, pictures[i]->bits(), pictures[i]->byteCount());
                inData.writeRawData((char*)buffer, 10000);
            }
        }

        file.close();
    }
}

/********************************************************************************************************************************/
/* READ AND RESTORE SAVED BOARD FROM A BINARY FILE ******************************************************************************************/

void MainWindow::slotReadBoard()
{
    QString fileName = QFileDialog::getOpenFileName(this,"",QDir::currentPath());

    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        QDataStream outData(&file);

        QLayoutItem *child;
        while ((child = layImageVertical->takeAt(0)) != 0)
            layImageVertical->removeItem(0);

        delete board;
        deleteSquares();

        bool tempIsNumber;
        int** tempValues;

        int tempSize;

        outData >> tempIsNumber;
        outData >> tempSize;

        if ( tempSize == 4 )
            size = Size::FOUR;
        else if ( tempSize == 5 )
            size == Size::FIVE;
        else if ( tempSize == 6 )
            size = Size::SIX;
        else if ( tempSize == 7 )
            size == Size::SEVEN;

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
            setSquaresNumber(false);
            isNumber = true;
        }
        else
        {
           uchar* buffer = new uchar[10000 * size * size];

           for (int i = 0; i < ( size  * size ); i++)
               outData.readRawData((char*)(buffer + i * 10000), 10000);

           ImageProvider::deleteInstance();
           imageProvider = ImageProvider::getInstance();

           if (size == 4)
                imagesLoad->four.loaded = imageProvider->restoreImageBoardFromFile( buffer, size );
           else if (size == 5)
               imagesLoad->five.loaded = imageProvider->restoreImageBoardFromFile( buffer, size );
           else if (size == 6)
               imagesLoad->six.loaded = imageProvider->restoreImageBoardFromFile( buffer, size );
           else
               imagesLoad->seven.loaded = imageProvider->restoreImageBoardFromFile( buffer, size );

           setSquaresGraphic(false);
           radioGraphic->setEnabled(true);
           acRemoveGraphic->setEnabled(true);
           isNumber = false;
        }

        file.close();
    }
}

/********************************************************************************************************************/
/* SET TEXT *********************************************************************************************************/

void MainWindow::setText()
{
    if (isPl)
        text->setPl(&labelsMenu, &labelsSettings, &labelsControls, &labelsMessages, &labelsAbout);
    else
        text->setEn(&labelsMenu, &labelsSettings, &labelsControls, &labelsMessages, &labelsAbout);

    fileMenu->setTitle(labelsMenu->value("file"));
    acOpenGraphic->setText(labelsMenu->value("fOpenG"));
    acRemoveGraphic->setText(labelsMenu->value("fRemG"));
    acSaveBoard->setText(labelsMenu->value("fSaveB"));
    acLoadBoard->setText(labelsMenu->value("fLoadB"));

    acSettings->setText(labelsMenu->value("settings"));

    infoMenu->setText(labelsMenu->value("info"));

    pushRandom->setText(labelsControls->value("random"));
    pushSolve->setText(labelsControls->value("set"));

    boxRadioDimension->setTitle(labelsControls->value("dim"));
    radioNumber->setText(labelsControls->value("num"));
    radioGraphic->setText(labelsControls->value("graph"));
    boxRadioKind->setTitle(labelsControls->value("kind"));
}

/********************************************************************************************************************/
/* SET COLOR ********************************************************************************************************/

void MainWindow::setColor()
{
    if ( color == Color::BLUE )
        numberStyle = numberStyleBlue;
    else if ( color == Color::GREEN )
        numberStyle = numberStyleGreen;
    else
        numberStyle = numberStyleRed;

    if ( isNumber == false )
        return;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ( control[i][j].styleSheet() != *emptyStyle)
                control[i][j].setStyleSheet(*numberStyle);
        }
    }    
}

/***************************************************************************************************************************/
/* CHILD WINDOWS ***********************************************************************************************************/

void MainWindow::slotSettings()
{
    new WindowSetting( color, imagesLoad, isScaled, isPl, this, labelsSettings );
}

/****************************************************************************************************************************/

void MainWindow::slotAbout()
{
    new WindowAbout(labelsAbout);
}

