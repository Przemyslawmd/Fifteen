
#ifndef FIFTEEN_MENU_H
#define FIFTEEN_MENU_H

#include "Types.h"

#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include <QString>

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
    MenuBar( MenuBar&& ) = delete;
    MenuBar& operator=( const MenuBar& ) = delete;
    MenuBar& operator=( MenuBar&& ) = delete;

    QMenuBar* createMenuBar();
    void setActionMenuState( ActionMenu, bool state );

    void bindSlot( ActionMenu action, std::function< void( void )> slot, QMainWindow* window, const QString& text );

private:

    std::map< ActionMenu, QAction* > mapAction;
};

#endif

