
#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include <map>
#include <memory>

#include <QHBoxLayout>
#include <QMainWindow>

#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

#include "Types.h"


enum class ActionMenu {
    ABOUT,
    LOAD_BOARD,
    OPEN_GRAPHIC,
    REM_GRAPHIC,
    SAVE_BOARD,
    SETTINGS,
};


class GUI : public QMainWindow
{
public:

    GUI() = default;
    GUI( const GUI& ) = delete;
    GUI operator=( const GUI& ) = delete;

    void createMenu( QMainWindow*, std::map< ActionMenu, std::function< void( void ) >>& funcs );
    void createRightLayout( QMainWindow*, std::array< std::function< void( void ) >, 3 >& funcs );
    void completeLayouts( QMainWindow* );

    void createTiles( const QMainWindow*, BoardSize, TileSize, std::function< void( void ) > func );
    void deleteTiles();
    std::vector< std::unique_ptr< QPushButton >>& getTiles();
    BoardSize checkRadioBoardSize();
    void setRadioSize( BoardSize );
    bool checkRadioBoardMode( BoardMode );
    void setRadioBoardMode( BoardMode );
    void setActionMenuState( ActionMenu, bool state );

private:

    void bindAction( QMainWindow*, QAction*&, std::function< void( void ) >, QString );

    std::vector< std::unique_ptr< QPushButton >> tiles;

    std::map< BoardSize, QRadioButton* > mapRadioBoardSize;
    std::map< BoardMode, QRadioButton* > mapRadioBoardMode;
    std::map< ActionMenu, QAction* > mapActionMenu;

    QVBoxLayout* layVerticalBoard;
    std::vector< QHBoxLayout* > layHorizontalBoard;
    QVBoxLayout* layRight;
};

#endif

