
#include "GUI.h"

GUI::GUI() {}

/*********************************************************************************/
/*********************************************************************************/

void GUI::bindMenuActions( MainWindow* window, map< Action, QAction* >& actions )
{
    bindAction( actions[Action::OPEN_GRAPHIC], &MainWindow::slotLoadGraphic,   window, "Load Graphic File" );
    bindAction( actions[Action::REM_GRAPHIC],  &MainWindow::slotRemoveGraphic, window, "Remove Graphic" );
    bindAction( actions[Action::SAVE_BOARD],   &MainWindow::slotSaveBoard,     window, "Save Board" );
    bindAction( actions[Action::LOAD_BOARD],   &MainWindow::slotReadBoard,     window, "Load Board" );
    bindAction( actions[Action::SETTINGS],     &MainWindow::slotSettings,      window, "Settings" );
    bindAction( actions[Action::ABOUT],        &MainWindow::slotAbout,         window, "About" );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::bindAction( QAction*& action, SlotMainWindow slot, MainWindow* window, QString text )
{
    action = new QAction( window );
    action->setText( text );
    connect( action, &QAction::triggered, window, slot );
}

