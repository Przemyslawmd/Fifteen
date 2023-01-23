
#include "MenuBar.h"
#include "MappedValues.h"

#include <QMenu>
#include <QMenuBar>

#include <memory>

constexpr const char STYLE_MARGIN_LEFT[] = "margin-left: 5px";
constexpr const char STYLE_HEIGHT[] = "height:20px";

using std::function;
using std::map;
using std::vector;
using std::unique_ptr;


QMenuBar* MenuBar::createMenuBar( map< ActionMenu, function< void( void ) >>& menuSlots, QMainWindow* window )
{
    QMenu* fileMenu = new QMenu( "File" );
    fileMenu->setStyleSheet( "padding-left:10px;" );

    bindAction( mapActionMenu[ActionMenu::OPEN_GRAPHIC], menuSlots.at( ActionMenu::OPEN_GRAPHIC ), "Load Graphic File",window );
    bindAction( mapActionMenu[ActionMenu::REM_GRAPHIC],  menuSlots.at( ActionMenu::REM_GRAPHIC ),  "Remove Graphic", window );
    bindAction( mapActionMenu[ActionMenu::SAVE_BOARD],   menuSlots.at( ActionMenu::SAVE_BOARD ),   "Save Board", window );
    bindAction( mapActionMenu[ActionMenu::LOAD_BOARD],   menuSlots.at( ActionMenu::LOAD_BOARD ),   "Load Board", window );
    bindAction( mapActionMenu[ActionMenu::SETTINGS],     menuSlots.at( ActionMenu::SETTINGS ),     "Settings", window );
    bindAction( mapActionMenu[ActionMenu::ABOUT],        menuSlots.at( ActionMenu::ABOUT ),        "About", window );

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
    return menuBar;
}

/*********************************************************************************/
/*********************************************************************************/

void MenuBar::bindAction( QAction*& action, function< void( void ) > slot, QString text, QMainWindow* window )
{
    action = new QAction( window );
    action->setText( text );
    QObject::connect( action, &QAction::triggered, window, slot );
}

/*********************************************************************************/
/*********************************************************************************/

void MenuBar::setActionMenuState( ActionMenu actionMenu, bool state )
{
    mapActionMenu.at( actionMenu )->setEnabled( state );
}

