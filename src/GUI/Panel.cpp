
#include "Panel.h"
#include "MappedValues.h"

#include <QGroupBox>

#include <memory>

constexpr const char STYLE_MARGIN_LEFT[] = "margin-left: 5px";
constexpr const char STYLE_HEIGHT[] = "height:20px";


QVBoxLayout* Panel::createLayout( std::array< std::function<void()>, 3>& panelSlots, QMainWindow* window )
{
    mapSize[BoardSize::FOUR] = new QRadioButton( "4" );
    mapSize[BoardSize::FIVE] = new QRadioButton( "5" );
    mapSize[BoardSize::SIX] = new QRadioButton( "6" );
    mapSize[BoardSize::SEVEN] = new QRadioButton( "7" );
    mapSize[BoardSize::FOUR]->setChecked( true );

    QVBoxLayout* radioSizeLayout = new QVBoxLayout();
    for( auto& [_, radio] : mapSize )
    {
        radioSizeLayout->addSpacing( 10 );
        radioSizeLayout->addWidget( radio );
        radio->setStyleSheet( STYLE_MARGIN_LEFT );
    }
    radioSizeLayout->addSpacing( 30 );

    QGroupBox* radioSizeBox = new QGroupBox( "Dimension of Board" );
    radioSizeBox->setLayout( radioSizeLayout );

    mapMode[BoardMode::NUMERIC] = new QRadioButton( "Numeric" );
    mapMode[BoardMode::GRAPHIC] = new QRadioButton( "Graphic" );
    mapMode[BoardMode::NUMERIC]->setChecked( true );

    QVBoxLayout* radioKindLayout = new QVBoxLayout();
    for( auto& [_, radio] : mapMode )
    {
        radioKindLayout->addSpacing( 10 );
        radioKindLayout->addWidget( radio );
        radio->setStyleSheet( STYLE_MARGIN_LEFT );
    }
    radioKindLayout->addSpacing( 30 );

    QGroupBox* radioKindBox = new QGroupBox( "Kind of Board" );
    radioKindBox->setLayout( radioKindLayout );

    QPushButton* pushRandom = new QPushButton( "Generate Board" );
    pushRandom->setStyleSheet( STYLE_HEIGHT );
    QObject::connect( pushRandom, &QPushButton::clicked, window, panelSlots[0] );

    QPushButton* pushSolve = new QPushButton( "Solve Board" );
    pushSolve->setStyleSheet( STYLE_HEIGHT );
    QObject::connect( pushSolve, &QPushButton::clicked, window, panelSlots[1] );

    QPushButton* pushUndo = new QPushButton( "Undo Move" );
    pushUndo->setStyleSheet( STYLE_HEIGHT );
    QObject::connect( pushUndo, &QPushButton::clicked, window, panelSlots[2] );

    QVBoxLayout* panelLayout = new QVBoxLayout();
    panelLayout->setContentsMargins( 30, 0, 20, 0 );
    panelLayout->addWidget( pushRandom );
    panelLayout->addSpacing( 15 );
    panelLayout->addWidget( pushSolve );
    panelLayout->addSpacing( 15 );
    panelLayout->addWidget( pushUndo );
    panelLayout->addSpacing( 30 );
    panelLayout->addWidget( radioSizeBox );
    panelLayout->addStretch();
    panelLayout->addWidget( radioKindBox );
    panelLayout->addStretch();
    return panelLayout;
}

/*********************************************************************************/
/*********************************************************************************/

BoardSize Panel::checkBoardSize()
{
    const auto it = std::find_if( mapSize.begin(), mapSize.end(), [] ( const auto &it ) { return it.second->isChecked() == true; });
    return it->first;
}

/*********************************************************************************/
/*********************************************************************************/

void Panel::setBoardSize( BoardSize boardSize )
{
    mapSize.at( boardSize )->setChecked( true );
}

/*********************************************************************************/
/*********************************************************************************/

bool Panel::checkBoardMode( BoardMode boardMode )
{
    return mapMode.at( boardMode )->isChecked();
}

/*********************************************************************************/
/*********************************************************************************/

void Panel::setBoardMode( BoardMode boardMode )
{
    mapMode.at( boardMode )->setChecked( true );
}

