
#include "GUIMain.h"
#include "MappedValues.h"
#include <memory>
#include <iostream>


GUI::GUI() {}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createMenu( QMainWindow* mainWidget, array< function< void( void ) >, 6 > funcs )
{
    unique_ptr< QMenu > fileMenu = std::make_unique< QMenu >( "File" );
    fileMenu->setStyleSheet( "padding-left:10px;" );

    bindAction( mainWidget, mapActionMenu[ActionMenu::OPEN_GRAPHIC], funcs.at( 0 ), "Load Graphic File" );
    bindAction( mainWidget, mapActionMenu[ActionMenu::REM_GRAPHIC],  funcs.at( 1 ), "Remove Graphic" );
    bindAction( mainWidget, mapActionMenu[ActionMenu::SAVE_BOARD],   funcs.at( 2 ), "Save Board" );
    bindAction( mainWidget, mapActionMenu[ActionMenu::LOAD_BOARD],   funcs.at( 3 ), "Load Board" );
    bindAction( mainWidget, mapActionMenu[ActionMenu::SETTINGS],     funcs.at( 4 ), "Settings" );
    bindAction( mainWidget, mapActionMenu[ActionMenu::ABOUT],        funcs.at( 5 ), "About" );

    fileMenu->addAction( mapActionMenu[ActionMenu::OPEN_GRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( mapActionMenu[ActionMenu::REM_GRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( mapActionMenu[ActionMenu::SAVE_BOARD] );
    fileMenu->addSeparator();
    fileMenu->addAction( mapActionMenu[ActionMenu::LOAD_BOARD] );

    unique_ptr< QMenuBar > menuBar = std::make_unique< QMenuBar >();
    menuBar->addMenu( fileMenu.release() );
    menuBar->addAction( mapActionMenu[ActionMenu::SETTINGS] );
    menuBar->addAction( mapActionMenu[ActionMenu::ABOUT] );
    menuBar->setStyleSheet( "padding-left: 5px; margin: 3px;" );

    mainWidget->setMenuBar( menuBar.release() );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createRightLayout( QMainWindow* mainWidget, array< function< void( void ) >, 3 > funcs )
{
    mapRadioBoardSize[BoardSize::FOUR] = new QRadioButton( "4" );
    mapRadioBoardSize[BoardSize::FIVE] = new QRadioButton( "5" );
    mapRadioBoardSize[BoardSize::SIX] = new QRadioButton( "6" );
    mapRadioBoardSize[BoardSize::SEVEN] = new QRadioButton( "7" );
    mapRadioBoardSize[BoardSize::FOUR]->setChecked( true );

    QVBoxLayout* radioSizeLayout = new QVBoxLayout();
    groupRadioSize = unique_ptr< QButtonGroup >( new QButtonGroup () );
    for( std::pair< BoardSize, QRadioButton* > radioSizePair : mapRadioBoardSize )
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

    mapRadioBoardMode[BoardMode::NUMERIC] = new QRadioButton( "Numeric" );
    mapRadioBoardMode[BoardMode::GRAPHIC] = new QRadioButton( "Graphic" );
    mapRadioBoardMode[BoardMode::NUMERIC]->setChecked( true );

    QVBoxLayout* radioKindLayout = new QVBoxLayout();
    unique_ptr< QButtonGroup > groupRadioKind = unique_ptr< QButtonGroup >( new QButtonGroup() );
    for( std::pair< BoardMode, QRadioButton* > radioKindPair : mapRadioBoardMode )
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
    connect( pushRandom, &QPushButton::clicked, mainWidget, funcs.at( 0 ));

    QPushButton* pushSolve = new QPushButton(" Solve Board ");
    pushSolve->setStyleSheet( "height:20px;" );
    connect( pushSolve, &QPushButton::clicked, mainWidget, funcs.at( 1 ));

    pushUndo = unique_ptr< QPushButton>( new QPushButton(" Undo Move " ));
    pushUndo->setStyleSheet( "height:20px;" );
    pushUndo->setDisabled( true );
    connect( pushUndo.get(), &QPushButton::clicked, mainWidget, funcs.at( 2 ));

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

void GUI::completeLayouts( QMainWindow* mainWidget )
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

void GUI::bindAction( QMainWindow* mainWidget, QAction*& action, function< void( void ) > slot, QString text )
{
    action = new QAction( mainWidget );
    action->setText( text );
    connect( action, &QAction::triggered, mainWidget, slot );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createTiles( const QMainWindow* mainWidget, BoardSize boardSize, TileSize tileSize_, function< void( void )> func )
{
    deleteTiles();
    uint tileSizeInt = Mapped::tileSizeInt.at( tileSize_ );
    uint boardSizeInt = Mapped::boardSizeInt.at( boardSize );

    layVerticalBoard->addStretch();

    for ( uint row = 0; row < boardSizeInt ; row++ )
    {
        layHorizontalBoard.push_back( new QHBoxLayout() );
        layHorizontalBoard[row]->setSpacing(0);
        layHorizontalBoard[row]->addStretch();

        for ( uint col = 0; col < boardSizeInt; col++ )
        {
            auto tile = std::make_unique< QPushButton >();
            tile->setAccessibleName( QString::number( row ) + QString::number( col ));
            tile->setMaximumSize( tileSizeInt, tileSizeInt );
            tile->setMinimumSize( tileSizeInt, tileSizeInt );
            connect( tile.get(), &QPushButton::clicked, mainWidget, func );
            layHorizontalBoard[row]->addWidget( tile.get() );
            tiles.push_back( std::move( tile ));
        }

        layHorizontalBoard[row]->addStretch();
        layVerticalBoard->addLayout( layHorizontalBoard[row] );
    }

    layVerticalBoard->addStretch();
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::deleteTiles()
{
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

vector< unique_ptr< QPushButton >>& GUI::getTiles()
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

void GUI::setRadioSize( BoardSize boardSize )
{
    mapRadioBoardSize.at( boardSize )->setChecked( true );
}

/*********************************************************************************/
/*********************************************************************************/

bool GUI::checkRadioBoardMode( BoardMode boardMode )
{
    return mapRadioBoardMode.at( boardMode )->isChecked();
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::setRadioBoardMode( BoardMode boardMode )
{
    mapRadioBoardMode.at( boardMode )->setChecked( true );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::setActionMenuState( ActionMenu actionMenu, bool state )
{
    mapActionMenu.at( actionMenu )->setEnabled( state );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::setStatePushUndo( bool state )
{
    pushUndo->setDisabled( state );
}

