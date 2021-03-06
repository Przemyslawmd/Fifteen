
#include "GUIMain.h"

#include <iostream>
#include <memory>

#include <QGroupBox>
#include <QMenu>
#include <QMenuBar>

#include "MappedValues.h"

constexpr const char STYLE_MARGIN_LEFT[] = "margin-left: 5px";
constexpr const char STYLE_HEIGHT[] = "height:20px";

using std::function;
using std::map;
using std::vector;
using std::unique_ptr;


GUI::GUI( QMainWindow* widget ) : widget( widget ) {}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createMenu( map< ActionMenu, function< void( void ) >>& funcs )
{
    QMenu* fileMenu = new QMenu( "File" );
    fileMenu->setStyleSheet( "padding-left:10px;" );

    bindAction( mapActionMenu[ActionMenu::OPEN_GRAPHIC], funcs.at( ActionMenu::OPEN_GRAPHIC ), "Load Graphic File" );
    bindAction( mapActionMenu[ActionMenu::REM_GRAPHIC],  funcs.at( ActionMenu::REM_GRAPHIC ),  "Remove Graphic" );
    bindAction( mapActionMenu[ActionMenu::SAVE_BOARD],   funcs.at( ActionMenu::SAVE_BOARD ),   "Save Board" );
    bindAction( mapActionMenu[ActionMenu::LOAD_BOARD],   funcs.at( ActionMenu::LOAD_BOARD ),   "Load Board" );
    bindAction( mapActionMenu[ActionMenu::SETTINGS],     funcs.at( ActionMenu::SETTINGS ),     "Settings" );
    bindAction( mapActionMenu[ActionMenu::ABOUT],        funcs.at( ActionMenu::ABOUT ),        "About" );

    fileMenu->addAction( mapActionMenu[ActionMenu::OPEN_GRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( mapActionMenu[ActionMenu::REM_GRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( mapActionMenu[ActionMenu::SAVE_BOARD] );
    fileMenu->addSeparator();
    fileMenu->addAction( mapActionMenu[ActionMenu::LOAD_BOARD] );

    QMenuBar* menuBar = new QMenuBar();
    menuBar->addMenu( fileMenu );
    menuBar->addAction( mapActionMenu[ActionMenu::SETTINGS] );
    menuBar->addAction( mapActionMenu[ActionMenu::ABOUT] );
    menuBar->setStyleSheet( "padding-left: 5px; margin: 3px;" );

    widget->setMenuBar( menuBar );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createRightLayout( std::array< function< void( void ) >, 3 >& funcs )
{
    mapRadioBoardSize[BoardSize::FOUR] = new QRadioButton( "4" );
    mapRadioBoardSize[BoardSize::FIVE] = new QRadioButton( "5" );
    mapRadioBoardSize[BoardSize::SIX] = new QRadioButton( "6" );
    mapRadioBoardSize[BoardSize::SEVEN] = new QRadioButton( "7" );
    mapRadioBoardSize[BoardSize::FOUR]->setChecked( true );

    QVBoxLayout* radioSizeLayout = new QVBoxLayout();
    for( std::pair< BoardSize, QRadioButton* > radioSizePair : mapRadioBoardSize )
    {
        radioSizeLayout->addSpacing( 10 );
        radioSizeLayout->addWidget( radioSizePair.second );
        radioSizePair.second->setStyleSheet( STYLE_MARGIN_LEFT );
    }
    radioSizeLayout->addSpacing( 30 );

    QGroupBox* radioSizeBox = new QGroupBox( "Dimension of Board" );
    radioSizeBox->setLayout( radioSizeLayout );

    mapRadioBoardMode[BoardMode::NUMERIC] = new QRadioButton( "Numeric" );
    mapRadioBoardMode[BoardMode::GRAPHIC] = new QRadioButton( "Graphic" );
    mapRadioBoardMode[BoardMode::NUMERIC]->setChecked( true );

    QVBoxLayout* radioKindLayout = new QVBoxLayout();
    for( std::pair< BoardMode, QRadioButton* > radioKindPair : mapRadioBoardMode )
    {
        radioKindLayout->addSpacing( 10 );
        radioKindLayout->addWidget( radioKindPair.second );
        radioKindPair.second->setStyleSheet( STYLE_MARGIN_LEFT );
    }
    radioKindLayout->addSpacing( 30 );

    QGroupBox* radioKindBox = new QGroupBox( "Kind of Board" );
    radioKindBox->setLayout( radioKindLayout );

    QPushButton* pushRandom = new QPushButton( "Generate Board" );
    pushRandom->setStyleSheet( STYLE_HEIGHT );
    connect( pushRandom, &QPushButton::clicked, widget, funcs.at( 0 ));

    QPushButton* pushSolve = new QPushButton( "Solve Board" );
    pushSolve->setStyleSheet( STYLE_HEIGHT );
    connect( pushSolve, &QPushButton::clicked, widget, funcs.at( 1 ));

    QPushButton* pushUndo = new QPushButton( "Undo Move" );
    pushUndo->setStyleSheet( STYLE_HEIGHT );
    connect( pushUndo, &QPushButton::clicked, widget, funcs.at( 2 ));

    layRight = new QVBoxLayout();
    layRight->setContentsMargins( 30, 0, 20, 0 );
    layRight->addWidget( pushRandom );
    layRight->addSpacing( 15 );
    layRight->addWidget( pushSolve );
    layRight->addSpacing( 15 );
    layRight->addWidget( pushUndo );
    layRight->addSpacing( 30 );
    layRight->addWidget( radioSizeBox );
    layRight->addStretch();
    layRight->addWidget( radioKindBox );
    layRight->addStretch();
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::completeLayouts()
{
    QWidget* mainPanel = new QWidget();
    mainPanel->setContentsMargins( 20, 20, 0, 20 );

    layVerticalBoard = new QVBoxLayout();
    layVerticalBoard->setSpacing( 0 );

    QGroupBox* boxImages = new QGroupBox();
    boxImages->setLayout( layVerticalBoard );

    QHBoxLayout* mainLayout = new QHBoxLayout( mainPanel );
    mainLayout->addWidget( boxImages );
    mainLayout->addLayout( layRight );

    widget->setCentralWidget( mainPanel );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::bindAction( QAction*& action, function< void( void ) > slot, QString text )
{
    action = new QAction( widget );
    action->setText( text );
    connect( action, &QAction::triggered, widget, slot );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createTiles( BoardSize boardSize, TileSize tileSize_, function< void( void )> func )
{
    deleteTiles();
    uint tileSizeInt = Maps::tileSizeInt.at( tileSize_ );
    uint boardSizeInt = Maps::boardSizeInt.at( boardSize );

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
            connect( tile.get(), &QPushButton::clicked, widget, func );
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
    if ( mapRadioBoardSize.at( BoardSize::FOUR )->isChecked() )
    {
        return BoardSize::FOUR;
    }
    if ( mapRadioBoardSize.at( BoardSize::FIVE )->isChecked() )
    {
        return BoardSize::FIVE;
    }
    if ( mapRadioBoardSize.at( BoardSize::SIX )->isChecked() )
    {
        return BoardSize::SIX;
    }
    return BoardSize::SEVEN;
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

