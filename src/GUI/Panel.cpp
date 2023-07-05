
#include "Panel.h"
#include "MappedValues.h"

#include <QGroupBox>

#include <memory>

constexpr const char STYLE_MARGIN_LEFT[] = "margin-left: 5px";
constexpr const char STYLE_HEIGHT[] = "height:20px";


QVBoxLayout* Panel::createLayout( std::array< std::function< void( void ) >, 3 >& panelSlots, QMainWindow* window )
{
    mapBoardSize[BoardSize::FOUR] = new QRadioButton( "4" );
    mapBoardSize[BoardSize::FIVE] = new QRadioButton( "5" );
    mapBoardSize[BoardSize::SIX] = new QRadioButton( "6" );
    mapBoardSize[BoardSize::SEVEN] = new QRadioButton( "7" );
    mapBoardSize[BoardSize::FOUR]->setChecked( true );

    QVBoxLayout* radioSizeLayout = new QVBoxLayout();
    for( auto& [_, radio] : mapBoardSize )
    {
        radioSizeLayout->addSpacing( 10 );
        radioSizeLayout->addWidget( radio );
        radio->setStyleSheet( STYLE_MARGIN_LEFT );
    }
    radioSizeLayout->addSpacing( 30 );

    QGroupBox* radioSizeBox = new QGroupBox( "Dimension of Board" );
    radioSizeBox->setLayout( radioSizeLayout );

    mapBoardMode[BoardMode::NUMERIC] = new QRadioButton( "Numeric" );
    mapBoardMode[BoardMode::GRAPHIC] = new QRadioButton( "Graphic" );
    mapBoardMode[BoardMode::NUMERIC]->setChecked( true );

    QVBoxLayout* radioKindLayout = new QVBoxLayout();
    for( auto& [_, radio] : mapBoardMode )
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
    if ( mapBoardSize.at( BoardSize::FOUR )->isChecked() )
    {
        return BoardSize::FOUR;
    }
    if ( mapBoardSize.at( BoardSize::FIVE )->isChecked() )
    {
        return BoardSize::FIVE;
    }
    if ( mapBoardSize.at( BoardSize::SIX )->isChecked() )
    {
        return BoardSize::SIX;
    }
    return BoardSize::SEVEN;
}

/*********************************************************************************/
/*********************************************************************************/

void Panel::setBoardSize( BoardSize boardSize )
{
    mapBoardSize.at( boardSize )->setChecked( true );
}

/*********************************************************************************/
/*********************************************************************************/

bool Panel::checkBoardMode( BoardMode boardMode )
{
    return mapBoardMode.at( boardMode )->isChecked();
}

/*********************************************************************************/
/*********************************************************************************/

void Panel::setBoardMode( BoardMode boardMode )
{
    mapBoardMode.at( boardMode )->setChecked( true );
}

