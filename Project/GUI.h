
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

    GUI( MainWindow& );

    void createMenu( map< Action, QAction* >& );
    void completeLayouts( QWidget* mainPanel, QVBoxLayout*&, QVBoxLayout* );

private:

    void bindAction( QAction*&, SlotMainWindow, QString );

    MainWindow& owner;
};

#endif // GUI_H

