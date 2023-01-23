
#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include "Types.h"

#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QGroupBox>

#include <functional>
#include <map>
#include <memory>


class GUI
{
public:

    GUI();
    GUI( const GUI& ) = delete;
    GUI operator=( const GUI& ) = delete;

    QGroupBox* getGroupBox();
    void createTiles( uint boardSize, uint tileSize, std::function< void( void ) > slot, QMainWindow* window );
    void deleteTiles();
    std::vector< std::unique_ptr< QPushButton >>& getTiles();

private:

    std::vector< std::unique_ptr< QPushButton >> tiles;
    QGroupBox* boxImages;

    QVBoxLayout* layVerticalBoard;
    std::vector< QHBoxLayout* > layHorizontalBoard;
};

#endif

