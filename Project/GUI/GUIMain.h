
#ifndef GUI_H
#define GUI_H

#include "Fifteen.h"
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

typedef void ( Fifteen::*SlotMainWindow )();

class GUI : public QMainWindow
{
public:

    static void createGUI();
    static void releaseGUI();
    static GUI& getGUI();

    void createMenu( Fifteen*, map< Action, QAction* >& );
    void createRightLayout( Fifteen*, map< BoardMode, QRadioButton* >&, map< BoardSize, QRadioButton* >& );
    void completeLayouts( Fifteen* );

    void createTiles( Fifteen*, BoardSize, TileSize );
    void deleteTiles();
    vector< unique_ptr< QPushButton >>& getTiles();
    BoardSize checkRadioBoardSize();
    void setStatePushUndo( bool state );

private:

    GUI();
    void bindAction( Fifteen*, QAction*&, SlotMainWindow, QString );

    static GUI* gui;

    vector< unique_ptr< QPushButton >> tiles;
    unique_ptr< QButtonGroup > groupRadioSize;
    unique_ptr< QPushButton > pushUndo;

    QVBoxLayout* layVerticalBoard;
    vector< QHBoxLayout* > layHorizontalBoard;
    QVBoxLayout* layRight;
    QGroupBox* boxImages;
};

#endif // GUI_H

