
#ifndef GUI_H
#define GUI_H

#include "MainWindow.h"
#include "Types.h"
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QButtonGroup>
#include <map>
#include <memory>

typedef void ( MainWindow::*SlotMainWindow )();

class GUI : public QMainWindow
{

Q_OBJECT

public:

    static void createGUI( MainWindow& );
    static void releaseGUI();
    static GUI& getGUI();

    void createMenu( map< Action, QAction* >& );
    void createRightLayout( map< BoardMode, QRadioButton* >&, map< BoardSize, QRadioButton* >& );
    void completeLayouts();

    void createTiles( BoardSize, SquareSize );
    void deleteTiles();
    vector< QPushButton* >& getTiles();
    BoardSize checkRadioBoardSize();
    void setStatePushUndo( bool state );

private:

    GUI( MainWindow& );
    void bindAction( QAction*&, SlotMainWindow, QString );

    static GUI* gui;
    MainWindow& owner;

    vector< QPushButton* > tiles;
    unique_ptr< QButtonGroup > groupRadioSize;
    unique_ptr< QPushButton > pushUndo;

    QVBoxLayout* layVerticalBoard;
    vector< QHBoxLayout* > layHorizontalBoard;
    QVBoxLayout* layRight;
};

#endif // GUI_H

