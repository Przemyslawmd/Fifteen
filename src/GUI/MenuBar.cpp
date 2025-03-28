
#include "MenuBar.h"


void MenuBar::bindSlot( ActionMenu actionMenu, std::function<void( void )> slot, QMainWindow* mainWindow, const QString& text )
{
    auto [it, _] = mapAction.emplace( actionMenu, mainWindow );
    it->second.setText( text );
    QObject::connect( &it->second, &QAction::triggered, mainWindow, slot );
}

/*********************************************************************************/
/*********************************************************************************/

QMenuBar* MenuBar::createMenuBar( QMainWindow* mainWindow )
{
    QMenu* fileMenu = new QMenu( "File", mainWindow );
    fileMenu->setStyleSheet( "padding-left:10px;" );

    using enum ActionMenu;
    fileMenu->addAction( &mapAction.at( OPEN_GRAPHIC ));
    fileMenu->addSeparator();
    fileMenu->addAction( &mapAction.at( REM_GRAPHIC ));
    mapAction.at( REM_GRAPHIC ).setEnabled( false );
    fileMenu->addSeparator();
    fileMenu->addAction( &mapAction.at( SAVE_BOARD ));
    fileMenu->addSeparator();
    fileMenu->addAction( &mapAction.at( LOAD_BOARD ));

    QMenuBar* menuBar = new QMenuBar( mainWindow );
    menuBar->addMenu( fileMenu );
    menuBar->addAction( &mapAction.at( SETTINGS ));
    menuBar->addAction( &mapAction.at( ABOUT ));
    menuBar->setStyleSheet( "padding-left: 5px; margin: 3px;" );
    return menuBar;
}

/*********************************************************************************/
/*********************************************************************************/

void MenuBar::setActionMenuState( ActionMenu actionMenu, bool state )
{
    mapAction.at( actionMenu ).setEnabled( state );
}

