
#ifndef FIFTEEN_MENU_H
#define FIFTEEN_MENU_H

#include "Types.h"

#include <QMainWindow>

#include <functional>
#include <map>

enum class ActionMenu {
    ABOUT,
    LOAD_BOARD,
    OPEN_GRAPHIC,
    REM_GRAPHIC,
    SAVE_BOARD,
    SETTINGS,
};


class MenuBar
{
public:

    MenuBar() = default;
    MenuBar( const MenuBar& ) = delete;
    MenuBar operator=( const MenuBar& ) = delete;

    QMenuBar* createMenuBar( std::map< ActionMenu, std::function< void( void ) >>& menuSlots, QMainWindow* window );
    void setActionMenuState( ActionMenu, bool state );

private:

    void bindAction( QAction*& action, std::function< void( void ) > slot, QString text, QMainWindow* window );
    std::map< ActionMenu, QAction* > mapActionMenu;
};

#endif

