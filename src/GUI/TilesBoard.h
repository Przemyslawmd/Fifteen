
#ifndef GUI_TILES_BOARD_H
#define GUI_TILES_BOARD_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>

#include <memory>
#include <vector>


class TilesBoard
{
public:

    TilesBoard();
    TilesBoard( const TilesBoard& ) = delete;
    TilesBoard operator=( const TilesBoard& ) = delete;

    QGroupBox* getGroupBox();

    void createTiles( uint boardSize, uint tileSize, std::function< void( void ) > slot, QMainWindow* window );
    std::vector< std::unique_ptr< QPushButton >>& getTiles();

private:

    void deleteTiles();
    
    std::vector< std::unique_ptr< QPushButton >> tiles;
    QGroupBox* tilesBox;

    QVBoxLayout* verticalLayout;
    std::vector< QHBoxLayout* > horizontalLayouts;
};

#endif

