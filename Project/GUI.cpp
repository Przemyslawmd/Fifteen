
#include "GUI.h"
#include <QGroupBox>

void GUI::createGUI( MainWindow& owner )
{
    gui = new GUI( owner );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::releaseGUI()
{
    delete gui;
}

/*********************************************************************************/
/*********************************************************************************/

GUI& GUI::getGUI()
{
    return *gui;
}

/*********************************************************************************/
/*********************************************************************************/

GUI::GUI( MainWindow& owner ) : owner( owner ){}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createMenu( map< Action, QAction* >& actions )
{
    QMenu* fileMenu = new QMenu();
    fileMenu->setTitle( "File" );
    fileMenu->setStyleSheet( "padding-left:10px;" );

    bindAction( actions[Action::OPEN_GRAPHIC], &MainWindow::slotLoadGraphic,   "Load Graphic File" );
    bindAction( actions[Action::REM_GRAPHIC],  &MainWindow::slotRemoveGraphic, "Remove Graphic" );
    bindAction( actions[Action::SAVE_BOARD],   &MainWindow::slotSaveBoard,     "Save Board" );
    bindAction( actions[Action::LOAD_BOARD],   &MainWindow::slotReadBoard,     "Load Board" );
    bindAction( actions[Action::SETTINGS],     &MainWindow::slotSettings,      "Settings" );
    bindAction( actions[Action::ABOUT],        &MainWindow::slotAbout,         "About" );

    fileMenu->addAction( actions[Action::OPEN_GRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( actions[Action::REM_GRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( actions[Action::SAVE_BOARD] );
    fileMenu->addSeparator();
    fileMenu->addAction( actions[Action::LOAD_BOARD] );

    QMenuBar* menuBar = new QMenuBar();
    menuBar->addMenu( fileMenu );
    menuBar->addAction( actions[Action::SETTINGS] );
    menuBar->addAction( actions[Action::ABOUT] );
    menuBar->setStyleSheet( "padding-left: 5px; margin: 3px;" );

    owner.setMenuBar( menuBar );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createRightLayout( QButtonGroup*& radioSizeGroup, QPushButton*& pushUndo,
                             map< BoardMode, QRadioButton* >& mapRadioKind, map< BoardSize, QRadioButton* >& mapRadioSize)
{
    mapRadioSize[BoardSize::FOUR] = new QRadioButton();
    mapRadioSize[BoardSize::FIVE] = new QRadioButton();
    mapRadioSize[BoardSize::SIX] = new QRadioButton();
    mapRadioSize[BoardSize::SEVEN] = new QRadioButton();

    QVBoxLayout* radioSizeLayout = new QVBoxLayout();
    radioSizeGroup = new QButtonGroup();
    for( std::pair< BoardSize, QRadioButton* > radioSizePair : mapRadioSize )
    {
        radioSizeLayout->addSpacing( 10 );
        radioSizeLayout->addWidget( radioSizePair.second );
        radioSizePair.second->setStyleSheet( "margin-left:5px;" );
        radioSizeGroup->addButton( radioSizePair.second );
        radioSizeGroup->setId( radioSizePair.second, radioSizePair.first );
    }
    radioSizeLayout->addSpacing( 30 );

    mapRadioSize[BoardSize::FOUR]->setText( "4" );
    mapRadioSize[BoardSize::FIVE]->setText( "5" );
    mapRadioSize[BoardSize::SIX]->setText( "6" );
    mapRadioSize[BoardSize::SEVEN]->setText( "7" );
    mapRadioSize[BoardSize::FOUR]->setChecked( true );

    unique_ptr< QGroupBox > radioSizeBox = unique_ptr< QGroupBox >( new QGroupBox( " Dimension of Board " ));
    radioSizeBox->setLayout( radioSizeLayout );

    mapRadioKind[BoardMode::NUMERIC] = new QRadioButton();
    mapRadioKind[BoardMode::GRAPHIC] = new QRadioButton();

    mapRadioKind[BoardMode::NUMERIC]->setChecked( true );
    mapRadioKind[BoardMode::NUMERIC]->setText( "Numeric" );
    mapRadioKind[BoardMode::GRAPHIC]->setText( "Graphic" );

    QVBoxLayout* radioKindLayout = new QVBoxLayout();
    QButtonGroup* radioKindGroup = new QButtonGroup();
    for( std::pair< BoardMode, QRadioButton* > radioKindPair : mapRadioKind )
    {
        radioKindLayout->addSpacing( 10 );
        radioKindLayout->addWidget( radioKindPair.second );
        radioKindPair.second->setStyleSheet( "margin-left:5px;" );
        radioKindGroup->addButton( radioKindPair.second );
    }
    radioKindLayout->addSpacing( 30 );

    unique_ptr< QGroupBox > radioKindBox = unique_ptr< QGroupBox> (new QGroupBox(" Kind of Board "));
    radioKindBox->setLayout( radioKindLayout );

    QPushButton* pushRandom = new QPushButton(" Generate Board ");
    pushRandom->setStyleSheet( "height:20px;" );
    connect( pushRandom, &QPushButton::clicked, &owner, &MainWindow::slotGenerateBoard );

    QPushButton* pushSolve = new QPushButton(" Solve Board ");
    pushSolve->setStyleSheet( "height:20px;" );
    connect( pushSolve, &QPushButton::clicked, &owner, &MainWindow::slotSolveBoard );

    pushUndo = new QPushButton(" Undo Move ");
    pushUndo->setText("Undo Move");
    pushUndo->setStyleSheet( "height:20px;" );
    pushUndo->setDisabled( true );
    connect( pushUndo, &QPushButton::clicked, &owner, &MainWindow::slotUndoMove );

    layRight = new QVBoxLayout();
    layRight->setContentsMargins( 30, 0, 20, 0 );
    layRight->addWidget( pushRandom );
    layRight->addSpacing( 15 );
    layRight->addWidget( pushSolve );
    layRight->addSpacing( 15 );
    layRight->addWidget( pushUndo );
    layRight->addSpacing( 30 );
    layRight->addWidget( radioSizeBox.release() );
    layRight->addStretch();
    layRight->addWidget( radioKindBox.release() );
    layRight->addStretch();
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::completeLayouts()
{
    QWidget* mainPanel = new QWidget();
    mainPanel->setContentsMargins( 20, 20, 0, 10 );

    layVerticalBoard = new QVBoxLayout();
    layVerticalBoard->setSpacing( 0 );

    QGroupBox* boxImages = new QGroupBox();
    boxImages->setLayout( layVerticalBoard );

    QHBoxLayout* mainLayout = new QHBoxLayout( mainPanel );
    mainLayout->addWidget( boxImages );
    mainLayout->addLayout( layRight );

    owner.setCentralWidget( mainPanel );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::bindAction( QAction*& action, SlotMainWindow slot, QString text )
{
    action = new QAction( &owner );
    action->setText( text );
    connect( action, &QAction::triggered, &owner, slot );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createTiles( BoardSize boardSize, SquareSize tileSize )
{
    deleteTiles();

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        tiles.push_back( new QPushButton() );
    }

    for ( int i = 0; i < boardSize ; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
        {
            tiles.at( i * boardSize + j )->setAccessibleName( QString::number( i ) + QString::number( j ));
            tiles.at( i * boardSize + j )->setMaximumSize( tileSize, tileSize );
            tiles.at( i * boardSize + j )->setMinimumSize( tileSize, tileSize );
            connect( tiles.at( i * boardSize + j ), &QPushButton::clicked, &owner, &MainWindow::pressSquare );
        }
    }

    layVerticalBoard->addStretch();

    for ( int i = 0; i < boardSize; i++ )
    {
        layHorizontalBoard.push_back( new QHBoxLayout() );
        layHorizontalBoard[i]->setSpacing(0);
        layHorizontalBoard[i]->addStretch();

        for ( int j = 0; j < boardSize; j++ )
        {
            layHorizontalBoard[i]->addWidget( tiles.at( i * boardSize + j ));
        }

        layHorizontalBoard[i]->addStretch();
        layVerticalBoard->addLayout( layHorizontalBoard[i] );
    }

    layVerticalBoard->addStretch();
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::deleteTiles()
{
    if ( tiles.empty() )
    {
        return;
    }

    for ( auto tile : tiles )
    {
        delete tile;
    }
    tiles.clear();

    QLayoutItem* child;
    while (( child = layVerticalBoard->takeAt( 0 )))
    {
        layVerticalBoard->removeItem( 0 );
    }

    for ( auto layout : layHorizontalBoard )
    {
        delete layout;
    }
    layHorizontalBoard.clear();
}

/*********************************************************************************/
/*********************************************************************************/

vector< QPushButton* >& GUI::getTiles()
{
    return tiles;
}

/*********************************************************************************/
/*********************************************************************************/

GUI* GUI::gui = nullptr;

