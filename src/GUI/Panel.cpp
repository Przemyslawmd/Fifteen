
#include "Panel.h"

#include <memory>
#include <ranges>

#include <QGroupBox>

#include "MappedValues.h"


constexpr const char STYLE_MARGIN_LEFT[] = "margin-left: 5px";
constexpr const char STYLE_HEIGHT[] = "height:20px";


QVBoxLayout* Panel::createLayout( std::function<void()> slotGenerate, 
                                  std::function<void()> slotSolve, 
                                  std::function<void()> slotUndoMove, 
                                  QMainWindow* mainWindow )
{
    radioSize.emplace( BoardSize::FOUR, "4" );
    radioSize.emplace( BoardSize::FIVE, "5" );
    radioSize.emplace( BoardSize::SIX, "6" );
    radioSize.emplace( BoardSize::SEVEN, "7" );
    radioSize[BoardSize::FOUR].setChecked( true );

    QVBoxLayout* radioSizeLayout = new QVBoxLayout();
    for( auto& radio : radioSize | std::views::values )
    {
        radioSizeLayout->addSpacing( 10 );
        radioSizeLayout->addWidget( &radio );
        radio.setStyleSheet( STYLE_MARGIN_LEFT );
    }
    radioSizeLayout->addSpacing( 30 );

    QGroupBox* radioSizeBox = new QGroupBox( "Dimension of Board", mainWindow );
    radioSizeBox->setLayout( radioSizeLayout );

    radioMode.emplace( BoardMode::NUMERIC, "Numeric" );
    radioMode.emplace( BoardMode::GRAPHIC, "Graphic" );
    radioMode[BoardMode::NUMERIC].setChecked( true );

    QVBoxLayout* radioModeLayout = new QVBoxLayout();
    for( auto& radio : radioMode | std::views::values )
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
    QObject::connect( pushRandom, &QPushButton::clicked, slotGenerate );

    QPushButton* pushSolve = new QPushButton( "Solve Board", mainWindow );
    pushSolve->setStyleSheet( STYLE_HEIGHT );
    QObject::connect( pushSolve, &QPushButton::clicked, slotSolve );

    QPushButton* pushUndo = new QPushButton( "Undo Move", mainWindow );
    pushUndo->setStyleSheet( STYLE_HEIGHT );
    QObject::connect( pushUndo, &QPushButton::clicked, slotUndoMove );

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
    const auto it = std::find_if( radioSize.begin(), radioSize.end(), [] ( const auto& it ) { return it.second.isChecked(); });
    return it->first;
}

/*********************************************************************************/
/*********************************************************************************/

void Panel::setBoardSize( BoardSize boardSize )
{
    radioSize.at( boardSize ).setChecked( true );
}

/*********************************************************************************/
/*********************************************************************************/

bool Panel::checkBoardMode( BoardMode boardMode )
{
    return radioMode.at( boardMode ).isChecked();
}

/*********************************************************************************/
/*********************************************************************************/

void Panel::setBoardMode( BoardMode boardMode )
{
    radioMode.at( boardMode ).setChecked( true );
}

