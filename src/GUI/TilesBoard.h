
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

    TilesBoard(const QMainWindow& mainWindow) : mainWindow{ mainWindow } {};
    TilesBoard( const TilesBoard& ) = delete;
    TilesBoard( TilesBoard&& ) = delete;
    TilesBoard& operator=( const TilesBoard& ) = delete;
    TilesBoard& operator=( TilesBoard&& ) = delete;

    QGroupBox* createGroupBox();

    void createTiles( size_t boardSize, size_t tileSize, std::function<void()> slot );
    std::vector<std::unique_ptr<QPushButton>>& getTiles();

private:

    void deleteTiles();

    const QMainWindow& mainWindow;

    std::vector<std::unique_ptr<QPushButton>> tiles;
    QVBoxLayout* verticalLayout;
    std::vector<QHBoxLayout*> horizontalLayouts;
};

#endif

