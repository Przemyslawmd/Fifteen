
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


class GUI : public QMainWindow
{
public:

    GUI( QMainWindow* widget );
    GUI( const GUI& ) = delete;
    GUI operator=( const GUI& ) = delete;

    void completeLayouts( QVBoxLayout* layRight );

    void createTiles( uint boardSize, uint tileSize, std::function< void( void ) > func );
    void deleteTiles();
    std::vector< std::unique_ptr< QPushButton >>& getTiles();

private:

    QMainWindow* const widget;

    std::vector< std::unique_ptr< QPushButton >> tiles;

    QVBoxLayout* layVerticalBoard;
    std::vector< QHBoxLayout* > layHorizontalBoard;
};

#endif

