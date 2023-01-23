
#include "GUIMain.h"
#include "MappedValues.h"

#include <QGroupBox>
#include <QMenu>
#include <QMenuBar>

#include <iostream>
#include <memory>

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

void GUI::completeLayouts( QVBoxLayout* layRight )
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

void GUI::createTiles( uint boardSize, uint tileSize, function< void( void )> func )
{
    deleteTiles();

    layVerticalBoard->addStretch();

    for ( uint row = 0; row < boardSize; row++ )
    {
        layHorizontalBoard.push_back( new QHBoxLayout() );
        layHorizontalBoard[row]->setSpacing(0);
        layHorizontalBoard[row]->addStretch();

        for ( uint col = 0; col < boardSize; col++ )
        {
            auto tile = std::make_unique< QPushButton >();
            tile->setAccessibleName( QString::number( row ) + QString::number( col ));
            tile->setMaximumSize( tileSize, tileSize );
            tile->setMinimumSize( tileSize, tileSize );
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

void GUI::setActionMenuState( ActionMenu actionMenu, bool state )
{
    mapActionMenu.at( actionMenu )->setEnabled( state );
}

