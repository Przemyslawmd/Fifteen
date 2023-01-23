
#include "TilesBoard.h"

#include <QGroupBox>

#include <memory>


TilesBoard::TilesBoard() 
{
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing( 0 );
    tilesBox = new QGroupBox();
    tilesBox->setLayout( verticalLayout );
}

/*********************************************************************************/
/*********************************************************************************/

QGroupBox* TilesBoard::getGroupBox()
{
    return tilesBox;
}

/*********************************************************************************/
/*********************************************************************************/

void TilesBoard::createTiles( uint boardSize, uint tileSize, std::function< void( void )> func, QMainWindow* window )
{
    deleteTiles();
    verticalLayout->addStretch();

    for ( uint row = 0; row < boardSize; row++ )
    {
        horizontalLayouts.push_back( new QHBoxLayout() );
        horizontalLayouts[row]->setSpacing(0);
        horizontalLayouts[row]->addStretch();

        for ( uint col = 0; col < boardSize; col++ )
        {
            auto tile = std::make_unique< QPushButton >();
            tile->setAccessibleName( QString::number( row ) + QString::number( col ));
            tile->setMaximumSize( tileSize, tileSize );
            tile->setMinimumSize( tileSize, tileSize );
            QObject::connect( tile.get(), &QPushButton::clicked, window, func );
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

std::vector< std::unique_ptr< QPushButton >>& TilesBoard::getTiles()
{
    return tiles;
}

