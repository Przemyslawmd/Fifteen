
#include "MenuBar.h"


void MenuBar::bindSlot( ActionMenu actionMenu, std::function< void( void )> slot, QMainWindow* window, const QString& text )
{
    mapAction[ actionMenu ] = new QAction();
    mapAction.at( actionMenu )->setText( text );
    QObject::connect( mapAction.at( actionMenu ), &QAction::triggered, window, slot );
}

/*********************************************************************************/
/*********************************************************************************/

QMenuBar* MenuBar::createMenuBar()
{
    QMenu* fileMenu = new QMenu( "File" );
    fileMenu->setStyleSheet( "padding-left:10px;" );

    fileMenu->addAction( mapAction.at( ActionMenu::OPEN_GRAPHIC ));
    fileMenu->addSeparator();
    fileMenu->addAction( mapAction.at( ActionMenu::REM_GRAPHIC ));
    mapAction.at( ActionMenu::REM_GRAPHIC )->setEnabled( false );
    fileMenu->addSeparator();
    fileMenu->addAction( mapAction.at( ActionMenu::SAVE_BOARD ));
    fileMenu->addSeparator();
    fileMenu->addAction( mapAction.at( ActionMenu::LOAD_BOARD ));

    QMenuBar* menuBar = new QMenuBar();
    menuBar->addMenu( fileMenu );
    menuBar->addAction( mapAction.at( ActionMenu::SETTINGS ));
    menuBar->addAction( mapAction.at( ActionMenu::ABOUT ));
    menuBar->setStyleSheet( "padding-left: 5px; margin: 3px;" );
    return menuBar;
}

/*********************************************************************************/
/*********************************************************************************/

void MenuBar::setActionMenuState( ActionMenu actionMenu, bool state )
{
    mapAction.at( actionMenu )->setEnabled( state );
}

