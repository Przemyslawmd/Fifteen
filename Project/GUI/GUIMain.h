
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

    void createMenu( QMainWindow*, std::array< std::function< void( void ) >, 6 > funcs );
    void createRightLayout( Fifteen* );
    void completeLayouts( QMainWindow* );

    void createTiles( Fifteen*, BoardSize, TileSize );
    void deleteTiles();
    vector< unique_ptr< QPushButton >>& getTiles();
    BoardSize checkRadioBoardSize();
    void setStatePushUndo( bool state );
    void setRadioSize( BoardSize );
    bool checkRadioBoardMode( BoardMode );
    void setRadioBoardMode( BoardMode );
    void setActionMenuState( ActionMenu, bool state );

private:

    GUI();
    void bindAction( QMainWindow*, QAction*&, std::function< void( void ) >, QString );

    static GUI* gui;

    vector< unique_ptr< QPushButton >> tiles;
    unique_ptr< QButtonGroup > groupRadioSize;
    unique_ptr< QPushButton > pushUndo;

    map< BoardSize, QRadioButton* > mapRadioBoardSize;
    map< BoardMode, QRadioButton* > mapRadioBoardMode;
    map< ActionMenu, QAction* > mapActionMenu;

    QVBoxLayout* layVerticalBoard;
    vector< QHBoxLayout* > layHorizontalBoard;
    QVBoxLayout* layRight;
    QGroupBox* boxImages;
};

#endif // GUI_H

