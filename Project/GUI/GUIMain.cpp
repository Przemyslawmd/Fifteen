
#include "GUIMain.h"
#include "MappedValues.h"
#include <memory>
#include <iostream>


void GUI::createGUI()
{
    gui = new GUI();
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

GUI::GUI() {}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createMenu( Fifteen* mainWidget, map< Action, QAction* >& actions )
{
    unique_ptr< QMenu > fileMenu = std::make_unique< QMenu >();
    fileMenu->setTitle( "File" );
    fileMenu->setStyleSheet( "padding-left:10px;" );

    bindAction( mainWidget, actions[Action::OPEN_GRAPHIC], &Fifteen::slotLoadGraphic,   "Load Graphic File" );
    bindAction( mainWidget, actions[Action::REM_GRAPHIC],  &Fifteen::slotRemoveGraphic, "Remove Graphic" );
    bindAction( mainWidget, actions[Action::SAVE_BOARD],   &Fifteen::slotSaveBoard,     "Save Board" );
    bindAction( mainWidget, actions[Action::LOAD_BOARD],   &Fifteen::slotReadBoard,     "Load Board" );
    bindAction( mainWidget, actions[Action::SETTINGS],     &Fifteen::slotSettings,      "Settings" );
    bindAction( mainWidget, actions[Action::ABOUT],        &Fifteen::slotAbout,         "About" );

    fileMenu->addAction( actions[Action::OPEN_GRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( actions[Action::REM_GRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( actions[Action::SAVE_BOARD] );
    fileMenu->addSeparator();
    fileMenu->addAction( actions[Action::LOAD_BOARD] );

    unique_ptr< QMenuBar > menuBar = std::make_unique< QMenuBar >();
    menuBar->addMenu( fileMenu.release() );
    menuBar->addAction( actions[Action::SETTINGS] );
    menuBar->addAction( actions[Action::ABOUT] );
    menuBar->setStyleSheet( "padding-left: 5px; margin: 3px;" );

    mainWidget->setMenuBar( menuBar.release() );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createRightLayout( Fifteen* mainWidget, map< BoardMode, QRadioButton* >& mapRadioKind, map< BoardSize, QRadioButton* >& mapRadioSize )
{
    mapRadioSize[BoardSize::FOUR] = new QRadioButton( "4" );
    mapRadioSize[BoardSize::FIVE] = new QRadioButton( "5" );
    mapRadioSize[BoardSize::SIX] = new QRadioButton( "6" );
    mapRadioSize[BoardSize::SEVEN] = new QRadioButton( "7" );
    mapRadioSize[BoardSize::FOUR]->setChecked( true );

    QVBoxLayout* radioSizeLayout = new QVBoxLayout();
    groupRadioSize = unique_ptr< QButtonGroup >( new QButtonGroup () );
    for( std::pair< BoardSize, QRadioButton* > radioSizePair : mapRadioSize )
    {
        radioSizeLayout->addSpacing( 10 );
        radioSizeLayout->addWidget( radioSizePair.second );
        radioSizePair.second->setStyleSheet( "margin-left:5px;" );
        groupRadioSize->addButton( radioSizePair.second );
        groupRadioSize->setId( radioSizePair.second, Mapped::boardSizeInt.at( radioSizePair.first ));
    }
    radioSizeLayout->addSpacing( 30 );

    unique_ptr< QGroupBox > radioSizeBox = unique_ptr< QGroupBox >( new QGroupBox( " Dimension of Board " ));
    radioSizeBox->setLayout( radioSizeLayout );

    mapRadioKind[BoardMode::NUMERIC] = new QRadioButton( "Numeric" );
    mapRadioKind[BoardMode::GRAPHIC] = new QRadioButton( "Graphic" );
    mapRadioKind[BoardMode::NUMERIC]->setChecked( true );

    QVBoxLayout* radioKindLayout = new QVBoxLayout();
    unique_ptr< QButtonGroup > groupRadioKind = unique_ptr< QButtonGroup >( new QButtonGroup() );
    for( std::pair< BoardMode, QRadioButton* > radioKindPair : mapRadioKind )
    {
        radioKindLayout->addSpacing( 10 );
        radioKindLayout->addWidget( radioKindPair.second );
        radioKindPair.second->setStyleSheet( "margin-left:5px;" );
        groupRadioKind->addButton( radioKindPair.second );
    }
    radioKindLayout->addSpacing( 30 );

    unique_ptr< QGroupBox > radioKindBox = unique_ptr< QGroupBox> (new QGroupBox(" Kind of Board "));
    radioKindBox->setLayout( radioKindLayout );

    QPushButton* pushRandom = new QPushButton(" Generate Board ");
    pushRandom->setStyleSheet( "height:20px;" );
    connect( pushRandom, &QPushButton::clicked, mainWidget, &Fifteen::slotGenerateBoard );

    QPushButton* pushSolve = new QPushButton(" Solve Board ");
    pushSolve->setStyleSheet( "height:20px;" );
    connect( pushSolve, &QPushButton::clicked, mainWidget, &Fifteen::slotSolveBoard );

    pushUndo = unique_ptr< QPushButton>( new QPushButton(" Undo Move " ));
    pushUndo->setStyleSheet( "height:20px;" );
    pushUndo->setDisabled( true );
    connect( pushUndo.get(), &QPushButton::clicked, mainWidget, &Fifteen::slotUndoMove );

    layRight = new QVBoxLayout();
    layRight->setContentsMargins( 30, 0, 20, 0 );
    layRight->addWidget( pushRandom );
    layRight->addSpacing( 15 );
    layRight->addWidget( pushSolve );
    layRight->addSpacing( 15 );
    layRight->addWidget( pushUndo.get() );
    layRight->addSpacing( 30 );
    layRight->addWidget( radioSizeBox.release() );
    layRight->addStretch();
    layRight->addWidget( radioKindBox.release() );
    layRight->addStretch();
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::completeLayouts( Fifteen* mainWidget )
{
    QWidget* mainPanel = new QWidget();
    mainPanel->setContentsMargins( 20, 20, 0, 10 );

    layVerticalBoard = new QVBoxLayout();
    layVerticalBoard->setSpacing( 0 );

    boxImages = new QGroupBox();
    boxImages->setLayout( layVerticalBoard );

    QHBoxLayout* mainLayout = new QHBoxLayout( mainPanel );
    mainLayout->addWidget( boxImages );
    mainLayout->addLayout( layRight );

    mainWidget->setCentralWidget( mainPanel );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::bindAction( Fifteen* mainWidget, QAction*& action, SlotMainWindow slot, QString text )
{
    action = new QAction( mainWidget );
    action->setText( text );
    connect( action, &QAction::triggered, mainWidget, slot );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createTiles( Fifteen* mainWidget, BoardSize boardSize, TileSize tileSize_ )
{
    deleteTiles();

    int tileSize = Mapped::tileSizeInt.at( tileSize_ );
    int boardSizeInt = Mapped::boardSizeInt.at( boardSize );

    for ( int i = 0; i < boardSizeInt ; i++ )
    {
        for ( int j = 0; j < boardSizeInt; j++ )
        {
            tiles.push_back( new QPushButton() );
            tiles.at( i * boardSizeInt + j )->setAccessibleName( QString::number( i ) + QString::number( j ));
            tiles.at( i * boardSizeInt + j )->setMaximumSize( tileSize, tileSize );
            tiles.at( i * boardSizeInt + j )->setMinimumSize( tileSize, tileSize );
            connect( tiles.at( i * boardSizeInt + j ), &QPushButton::clicked, mainWidget, &Fifteen::pressTile );
        }
    }

    layVerticalBoard->addStretch();

    for ( int i = 0; i < boardSizeInt; i++ )
    {
        layHorizontalBoard.push_back( new QHBoxLayout() );
        layHorizontalBoard[i]->setSpacing(0);
        layHorizontalBoard[i]->addStretch();

        for ( int j = 0; j < boardSizeInt; j++ )
        {
            layHorizontalBoard[i]->addWidget( tiles.at( i * boardSizeInt + j ));
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

    QLayoutItem* item;
    while (( item = layVerticalBoard->takeAt( 0 )))
    {
        layVerticalBoard->removeItem( 0 );
        delete item;
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

BoardSize GUI::checkRadioBoardSize()
{
    int id = groupRadioSize->checkedId();
    return Mapped::getBoardSizeByInt( id );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::setStatePushUndo( bool state )
{
    pushUndo->setDisabled( state );
}

/*********************************************************************************/
/*********************************************************************************/

GUI* GUI::gui = nullptr;

