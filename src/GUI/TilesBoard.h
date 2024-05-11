
#ifndef GUI_TILES_BOARD_H
#define GUI_TILES_BOARD_H

#include <functional>
#include <memory>
#include <vector>

#include <QGroupBox>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>


class TilesBoard
{
public:

    TilesBoard( std::function<void( void )> pressTileSlot );
    TilesBoard( const TilesBoard& ) = delete;
    TilesBoard( TilesBoard&& ) = delete;
    TilesBoard& operator=( const TilesBoard& ) = delete;
    TilesBoard& operator=( TilesBoard&& ) = delete;

    QGroupBox* createGroupBox();

    void createTiles( uint boardSize, uint tileSize, QMainWindow* window );
    std::vector<std::unique_ptr<QPushButton >>& getTiles();

private:

    void deleteTiles();
    
    std::vector<std::unique_ptr<QPushButton>> tiles;
    std::function<void()> pressTileSlot;

    QVBoxLayout* verticalLayout;
    std::vector<QHBoxLayout*> horizontalLayouts;
};

#endif

