
#include "GUIMain.h"
#include "MappedValues.h"

#include <QGroupBox>
#include <QMenu>
#include <QMenuBar>

#include <iostream>
#include <memory>

constexpr const char STYLE_MARGIN_LEFT[] = "margin-left: 5px";
constexpr const char STYLE_HEIGHT[] = "height:20px";

using std::function;
using std::map;
using std::vector;
using std::unique_ptr;


GUI::GUI() 
{
    layVerticalBoard = new QVBoxLayout();
    layVerticalBoard->setSpacing( 0 );

    boxImages = new QGroupBox();
    boxImages->setLayout( layVerticalBoard );
}

/*********************************************************************************/
/*********************************************************************************/

QGroupBox* GUI::getGroupBox()
{
    return boxImages;
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createTiles( uint boardSize, uint tileSize, function< void( void )> func, QMainWindow* window )
{
    deleteTiles();
    layVerticalBoard->addStretch();

    for ( uint row = 0; row < boardSize; row++ )
    {
        layHorizontalBoard.push_back( new QHBoxLayout() );
        layHorizontalBoard[row]->setSpacing(0);
        layHorizontalBoard[row]->addStretch();

        for ( uint col = 0; col < boardSize; col++ )
        {
            auto tile = std::make_unique< QPushButton >();
            tile->setAccessibleName( QString::number( row ) + QString::number( col ));
            tile->setMaximumSize( tileSize, tileSize );
            tile->setMinimumSize( tileSize, tileSize );
            QObject::connect( tile.get(), &QPushButton::clicked, window, func );
            layHorizontalBoard[row]->addWidget( tile.get() );
            tiles.push_back( std::move( tile ));
        }

        layHorizontalBoard[row]->addStretch();
        layVerticalBoard->addLayout( layHorizontalBoard[row] );
    }

    layVerticalBoard->addStretch();
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::deleteTiles()
{
    tiles.clear();

    QLayoutItem* item;
    while (( item = layVerticalBoard->takeAt( 0 )))
    {
        layVerticalBoard->removeItem( 0 );
        delete item;
    }

    layHorizontalBoard.clear();
}

/*********************************************************************************/
/*********************************************************************************/

vector< unique_ptr< QPushButton >>& GUI::getTiles()
{
    return tiles;
}

