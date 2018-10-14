
#ifndef GUI_H
#define GUI_H

#include <map>
#include "MainWindow.h"
#include "Types.h"
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>

typedef void ( MainWindow::*SlotMainWindow )();

class GUI : public QMainWindow
{

Q_OBJECT

public:
    GUI();

    void bindMenuActions( MainWindow*, map< Action, QAction* >& actions );

private:

    void bindAction( QAction*& action, SlotMainWindow, MainWindow*, QString );
};

#endif // GUI_H

