
#include "Panel.h"
#include "MappedValues.h"

#include <QGroupBox>

#include <memory>

constexpr const char STYLE_MARGIN_LEFT[] = "margin-left: 5px";
constexpr const char STYLE_HEIGHT[] = "height:20px";


QVBoxLayout* Panel::createLayout( std::array< std::function<void()>, 3>& panelSlots, QMainWindow* mainWindow )
{
    radioSizeMap.emplace( BoardSize::FOUR, "4" );
    radioSizeMap.emplace( BoardSize::FIVE, "5" );
    radioSizeMap.emplace( BoardSize::SIX, "6" );
    radioSizeMap.emplace( BoardSize::SEVEN, "7" );
    radioSizeMap[BoardSize::FOUR].setChecked( true );

    QVBoxLayout* radioSizeLayout = new QVBoxLayout();
    for( auto& [_, radio] : radioSizeMap )
    {
        radioSizeLayout->addSpacing( 10 );
        radioSizeLayout->addWidget( &radio );
        radio.setStyleSheet( STYLE_MARGIN_LEFT );
    }
    radioSizeLayout->addSpacing( 30 );

    QGroupBox* radioSizeBox = new QGroupBox( "Dimension of Board", mainWindow );
    radioSizeBox->setLayout( radioSizeLayout );

    radioModeMap.emplace( BoardMode::NUMERIC, "Numeric" );
    radioModeMap.emplace( BoardMode::GRAPHIC, "Graphic" );
    radioModeMap[BoardMode::NUMERIC].setChecked( true );

    QVBoxLayout* radioModeLayout = new QVBoxLayout();
    for( auto& [_, radio] : radioModeMap )
    {
        radioModeLayout->addSpacing( 10 );
        radioModeLayout->addWidget( &radio );
        radio.setStyleSheet( STYLE_MARGIN_LEFT );
    }
    radioModeLayout->addSpacing( 30 );

    QGroupBox* radioModeBox = new QGroupBox( "Kind of Board", mainWindow );
    radioModeBox->setLayout( radioModeLayout );

    QPushButton* pushRandom = new QPushButton( "Generate Board", mainWindow );
    pushRandom->setStyleSheet( STYLE_HEIGHT );
    QObject::connect( pushRandom, &QPushButton::clicked, panelSlots[0] );

    QPushButton* pushSolve = new QPushButton( "Solve Board", mainWindow );
    pushSolve->setStyleSheet( STYLE_HEIGHT );
    QObject::connect( pushSolve, &QPushButton::clicked, panelSlots[1] );

    QPushButton* pushUndo = new QPushButton( "Undo Move", mainWindow );
    pushUndo->setStyleSheet( STYLE_HEIGHT );
    QObject::connect( pushUndo, &QPushButton::clicked, panelSlots[2] );

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
    panelLayout->addWidget( radioModeBox );
    panelLayout->addStretch();
    return panelLayout;
}

/*********************************************************************************/
/*********************************************************************************/

BoardSize Panel::checkBoardSize()
{
    const auto it = std::find_if( radioSizeMap.begin(), radioSizeMap.end(), [] ( const auto &it ) { return it.second.isChecked() == true; });
    return it->first;
}

/*********************************************************************************/
/*********************************************************************************/

void Panel::setBoardSize( BoardSize boardSize )
{
    radioSizeMap.at( boardSize ).setChecked( true );
}

/*********************************************************************************/
/*********************************************************************************/

bool Panel::checkBoardMode( BoardMode boardMode )
{
    return radioModeMap.at( boardMode ).isChecked();
}

/*********************************************************************************/
/*********************************************************************************/

void Panel::setBoardMode( BoardMode boardMode )
{
    radioModeMap.at( boardMode ).setChecked( true );
}

