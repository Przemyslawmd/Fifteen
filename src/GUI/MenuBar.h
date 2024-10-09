
#ifndef FIFTEEN_MENU_H
#define FIFTEEN_MENU_H

#include <functional>
#include <map>

#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include <QString>

#include "Types.h"


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

    QMenuBar* createMenuBar( QMainWindow* mainWindow );
    void setActionMenuState( ActionMenu, bool state );

    void bindSlot( ActionMenu action, std::function<void( void )> slot, QMainWindow* mainWindow, const QString& text );

private:

    std::map<ActionMenu, QAction*> mapAction;
};

#endif

