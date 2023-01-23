
#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include "Types.h"

#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

#include <functional>
#include <map>
#include <memory>


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

    GUI( QMainWindow* widget );
    GUI( const GUI& ) = delete;
    GUI operator=( const GUI& ) = delete;

    void createMenu( std::map< ActionMenu, std::function< void( void ) >>& funcs );
    void completeLayouts( QVBoxLayout* layRight );

    void createTiles( uint boardSize, uint tileSize, std::function< void( void ) > func );
    void deleteTiles();
    std::vector< std::unique_ptr< QPushButton >>& getTiles();
    void setActionMenuState( ActionMenu, bool state );

private:

    void bindAction( QAction*&, std::function< void( void ) >, QString );

    QMainWindow* const widget;

    std::vector< std::unique_ptr< QPushButton >> tiles;

    std::map< ActionMenu, QAction* > mapActionMenu;

    QVBoxLayout* layVerticalBoard;
    std::vector< QHBoxLayout* > layHorizontalBoard;
};

#endif

