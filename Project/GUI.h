
#ifndef GUI_H
#define GUI_H

#include "MainWindow.h"
#include "Types.h"
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <map>

typedef void ( MainWindow::*SlotMainWindow )();

class GUI : public QMainWindow
{

Q_OBJECT

public:

    static void createGUI( MainWindow& );
    static GUI* getGUI();

    void createMenu( map< Action, QAction* >& );
    QVBoxLayout* createRightLayout( QButtonGroup*&, QPushButton*&, map< BoardMode, QRadioButton* >&, map< BoardSize, QRadioButton* >& );
    void completeLayouts( QWidget* mainPanel, QVBoxLayout*&, QVBoxLayout* );

private:

    GUI( MainWindow& );
    void bindAction( QAction*&, SlotMainWindow, QString );

    static GUI* gui;
    MainWindow& owner;
};

#endif // GUI_H

