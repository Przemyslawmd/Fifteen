
#include "MenuBar.h"


void MenuBar::bindSlot( ActionMenu actionMenu, std::function<void( void )> slot, QMainWindow* mainWindow, const QString& text )
{
    auto [it, _] = actions.emplace( actionMenu, mainWindow );
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
    fileMenu->addAction( &actions.at( OPEN_GRAPHIC ));
    fileMenu->addSeparator();
    fileMenu->addAction( &actions.at( REM_GRAPHIC ));
    actions.at( REM_GRAPHIC ).setEnabled( false );
    fileMenu->addSeparator();
    fileMenu->addAction( &actions.at( SAVE_BOARD ));
    fileMenu->addSeparator();
    fileMenu->addAction( &actions.at( LOAD_BOARD ));

    QMenuBar* menuBar = new QMenuBar( mainWindow );
    menuBar->addMenu( fileMenu );
    menuBar->addAction( &actions.at( SETTINGS ));
    menuBar->addAction( &actions.at( ABOUT ));
    menuBar->setStyleSheet( "padding-left: 5px; margin: 3px;" );
    return menuBar;
}

/*********************************************************************************/
/*********************************************************************************/

void MenuBar::setActionMenuState( ActionMenu actionMenu, bool state )
{
    actions.at( actionMenu ).setEnabled( state );
}

