
#include "GUI.h"

GUI::GUI() {}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createMenu( MainWindow* window, map< Action, QAction* >& actions )
{
    QMenu* fileMenu = new QMenu();
    fileMenu->setTitle( "File" );
    fileMenu->setStyleSheet( "padding-left:10px;" );

    bindAction( actions[Action::OPEN_GRAPHIC], &MainWindow::slotLoadGraphic,   window, "Load Graphic File" );
    bindAction( actions[Action::REM_GRAPHIC],  &MainWindow::slotRemoveGraphic, window, "Remove Graphic" );
    bindAction( actions[Action::SAVE_BOARD],   &MainWindow::slotSaveBoard,     window, "Save Board" );
    bindAction( actions[Action::LOAD_BOARD],   &MainWindow::slotReadBoard,     window, "Load Board" );
    bindAction( actions[Action::SETTINGS],     &MainWindow::slotSettings,      window, "Settings" );
    bindAction( actions[Action::ABOUT],        &MainWindow::slotAbout,         window, "About" );

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

    window->setMenuBar( menuBar );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::bindAction( QAction*& action, SlotMainWindow slot, MainWindow* window, QString text )
{
    action = new QAction( window );
    action->setText( text );
    connect( action, &QAction::triggered, window, slot );
}

