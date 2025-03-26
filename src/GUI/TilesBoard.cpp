
#include "TilesBoard.h"


TilesBoard::TilesBoard( std::function<void()> pressTileSlot ) : pressTileSlot( pressTileSlot ) {}

/*********************************************************************************/
/*********************************************************************************/

QGroupBox* TilesBoard::createGroupBox()
{
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing( 0 );
    QGroupBox* tilesBox = new QGroupBox();
    tilesBox->setLayout( verticalLayout );
    return tilesBox;
}

/*********************************************************************************/
/*********************************************************************************/

void TilesBoard::createTiles( size_t boardSize, size_t tileSize, QMainWindow* window )
{
    deleteTiles();
    verticalLayout->addStretch();

    for ( size_t row = 0; row < boardSize; row++ )
    {
        horizontalLayouts.emplace_back( new QHBoxLayout() );
        horizontalLayouts[row]->setSpacing(0);
        horizontalLayouts[row]->addStretch();

        for ( size_t col = 0; col < boardSize; col++ )
        {
            auto tile = std::make_unique<QPushButton>();
            tile->setAccessibleName( QString::number( row ) + QString::number( col ));
            tile->setMaximumSize( tileSize, tileSize );
            tile->setMinimumSize( tileSize, tileSize );
            QObject::connect( tile.get(), &QPushButton::clicked, window, pressTileSlot );
            horizontalLayouts[row]->addWidget( tile.get() );
            tiles.push_back( std::move( tile ));
        }

        horizontalLayouts[row]->addStretch();
        verticalLayout->addLayout( horizontalLayouts[row] );
    }
    verticalLayout->addStretch();
}

/*********************************************************************************/
/*********************************************************************************/

void TilesBoard::deleteTiles()
{
    tiles.clear();

    QLayoutItem* item;
    while (( item = verticalLayout->takeAt( 0 )))
    {
        verticalLayout->removeItem( 0 );
        delete item;
    }
    horizontalLayouts.clear();
}

/*********************************************************************************/
/*********************************************************************************/

std::vector<std::unique_ptr<QPushButton>>& TilesBoard::getTiles()
{
    return tiles;
}

