
#include "WindowSetting.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <memory>

using std::unique_ptr;

WindowSetting::WindowSetting( MainWindow& parent ) : parent( parent )
{
    setModal( true );
    setWindowTitle( "" );
    setGeometry( 100, 100, 400, 560 );
    setMaximumSize( 400, 870 );
    setMinimumSize( 400, 870 );
    setAttribute( Qt::WA_DeleteOnClose );

    QVBoxLayout layWindow;
    optionsCurrent = Options::sendData();

    /* Graphic loading box *****************************************/

    mapRadioGraphicMode[GraphicMode::SCALED] = new QRadioButton( "Image is to be scalled" );
    mapRadioGraphicMode[GraphicMode::CROPPED] = new QRadioButton( "Image is to be cropped" );
    mapRadioGraphicMode[GraphicMode::SCALED]->setChecked( optionsCurrent->graphicMode == GraphicMode::SCALED );

    for ( auto& mapRadio : mapRadioGraphicMode )
    {
        mapRadio.second->setStyleSheet( "margin-left: 5px;" );
        groupRadioGraphicMode.addButton( mapRadio.second );
    }

    mapRadioGraphicMode[ optionsCurrent->graphicMode]->setChecked( true );

    mapCheckImageToChose[BoardSize::FOUR] = new QCheckBox( "Image is to be loaded for a board  4x4" );
    mapCheckImageToChose[BoardSize::FOUR]->setChecked( optionsCurrent->fourImageToBeLoaded );
    mapCheckImageToChose[BoardSize::FIVE] = new QCheckBox( "Image is to be loaded for a board  5x5" );
    mapCheckImageToChose[BoardSize::FIVE]->setChecked( optionsCurrent->fiveImageToBeLoaded );
    mapCheckImageToChose[BoardSize::SIX] = new QCheckBox( "Image is to be loaded for a board  6x6" );
    mapCheckImageToChose[BoardSize::SIX]->setChecked( optionsCurrent->sixImageToBeLoaded );
    mapCheckImageToChose[BoardSize::SEVEN] = new QCheckBox( "Image is to be loaded for a board  7x7" );
    mapCheckImageToChose[BoardSize::SEVEN]->setChecked( optionsCurrent->sevenImageToBeLoaded );

    for ( auto& check : mapCheckImageToChose )
    {
        check.second->setStyleSheet( "margin-left: 5px;" );
    }

    radioNumberOnImage[NumberColor::NO] = new QRadioButton( "Number on a graphic tile : No" );
    radioNumberOnImage[NumberColor::BLACK] = new QRadioButton( "Number on a graphic tile : Black" );
    radioNumberOnImage[NumberColor::WHITE] = new QRadioButton( "Number on a graphic tile : White" );

    for ( auto radioMap : radioNumberOnImage )
    {
        radioMap.second->setStyleSheet( "margin-left: 5px;" );
        groupRadioNumberOnImage.addButton( radioMap.second );
    }

    radioNumberOnImage[ optionsCurrent->numberColor ]->setChecked( true );

    QVBoxLayout layRadioImage;
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( mapRadioGraphicMode[GraphicMode::SCALED] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( mapRadioGraphicMode[GraphicMode::CROPPED] );
    layRadioImage.addSpacing( 15 );
    layRadioImage.addWidget( mapCheckImageToChose[BoardSize::FOUR] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( mapCheckImageToChose[BoardSize::FIVE] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( mapCheckImageToChose[BoardSize::SIX] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( mapCheckImageToChose[BoardSize::SEVEN] );
    layRadioImage.addSpacing( 15 );
    layRadioImage.addWidget( radioNumberOnImage[NumberColor::NO] );
    layRadioImage.addSpacing( 12 );
    layRadioImage.addWidget( radioNumberOnImage[NumberColor::BLACK] );
    layRadioImage.addSpacing( 12 );
    layRadioImage.addWidget( radioNumberOnImage[NumberColor::WHITE] );
    layRadioImage.addSpacing( 15 );
    QGroupBox* boxRadioImage = new QGroupBox( "Image for a graphic board" );
    boxRadioImage->setLayout( &layRadioImage );

    /* Color of numeric board **************************************/

    mapRadioColor[TileColor::BLUE] = new QRadioButton( "Blue" );
    mapRadioColor[TileColor::GREEN] = new QRadioButton( "Green" );
    mapRadioColor[TileColor::RED] = new QRadioButton( "Red" );

    for ( auto& radio : mapRadioColor )
    {
        radio.second->setStyleSheet( "margin-left:5px;" );
        groupRadioColor.addButton( radio.second );
    }

    mapRadioColor[ optionsCurrent->squareColor ]->setChecked( true );

    QVBoxLayout layRadioColor;
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( mapRadioColor[TileColor::BLUE] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( mapRadioColor[TileColor::GREEN] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( mapRadioColor[TileColor::RED] );
    layRadioColor.addSpacing( 7 );
    QGroupBox* boxRadioColor = new QGroupBox( "Color of numeric board" );
    boxRadioColor->setLayout( &layRadioColor );

    /* Slider for square size **************************************/

    slider = new QSlider( Qt::Horizontal, this );
    slider->setRange( 1, 5 );
    slider->setSingleStep( 1 );
    sliderLabels[0] = new QLabel( " 50" );
    sliderLabels[1] = new QLabel( "  100" );
    sliderLabels[2] = new QLabel( "150" );
    sliderLabels[3] = new QLabel( "200  " );
    sliderLabels[4] = new QLabel( "250" );
    slider->setValue( optionsCurrent->squareSizeIndex );

    QGridLayout layoutSlider;
    layoutSlider.setContentsMargins( 10, 20, 30, 20 );
    layoutSlider.addWidget( slider,          0, 0, 1, 5 );
    layoutSlider.addWidget( sliderLabels[0], 1, 0, 1, 1, Qt::AlignLeft );
    layoutSlider.addWidget( sliderLabels[1], 1, 1, 1, 1, Qt::AlignLeft );
    layoutSlider.addWidget( sliderLabels[2], 1, 2, 1, 1, Qt::AlignCenter );
    layoutSlider.addWidget( sliderLabels[3], 1, 3, 1, 1, Qt::AlignRight );
    layoutSlider.addWidget( sliderLabels[4], 1, 4, 1, 1, Qt::AlignRight );
    QGroupBox* boxSquareSize = new QGroupBox( "Size of tile ");
    boxSquareSize->setLayout( &layoutSlider );

    /* Undo availability *******************************************/

    checkUndoEnabled.setText( "Enable undo to ten moves" );
    checkUndoEnabled.setChecked( optionsCurrent->undoEnabled );
    checkUndoEnabled.setStyleSheet( "margin-left: 5px" );
    QVBoxLayout layoutUndoEnabled;
    layoutUndoEnabled.addSpacing( 10 );
    layoutUndoEnabled.addWidget( &checkUndoEnabled );
    layoutUndoEnabled.addSpacing( 10 );
    QGroupBox* boxUndoEnabled = new QGroupBox();
    boxUndoEnabled->setLayout( &layoutUndoEnabled );

    /* General layout **********************************************/

    QHBoxLayout layControls;
    pushAccept = new QPushButton( "Accept ");
    pushAccept->setStyleSheet( "height:20px;" );
    connect( pushAccept, SIGNAL( clicked() ), this, SLOT( acceptSettings() ));

    layControls.addSpacing( 120 );
    layControls.addWidget( pushAccept );
    layControls.addSpacing( 120 );

    layWindow.addSpacing( 20 );
    layWindow.addWidget( boxRadioImage );
    layWindow.addSpacing( 20 );
    layWindow.addWidget( boxRadioColor);
    layWindow.addSpacing( 20 );
    layWindow.addWidget( boxSquareSize );
    layWindow.addSpacing( 20 );
    layWindow.addWidget( boxUndoEnabled );
    layWindow.addSpacing( 20 );
    layWindow.addLayout( &layControls );
    layWindow.addSpacing( 10 );
    layWindow.addStretch();

    this->setLayout( &layWindow );
    this->show();
}

/*********************************************************************************/
/*********************************************************************************/

void WindowSetting::acceptSettings()
{
    unique_ptr< OptionsData > optionsNew ( new OptionsData );
    optionsNew->graphicMode = mapRadioGraphicMode[GraphicMode::SCALED]->isChecked() ? GraphicMode::SCALED : GraphicMode::CROPPED;
    optionsNew->fourImageToBeLoaded = mapCheckImageToChose[BoardSize::FOUR]->isChecked();
    optionsNew->fiveImageToBeLoaded = mapCheckImageToChose[BoardSize::FIVE]->isChecked();
    optionsNew->sixImageToBeLoaded = mapCheckImageToChose[BoardSize::SIX]->isChecked();
    optionsNew->sevenImageToBeLoaded = mapCheckImageToChose[BoardSize::SEVEN]->isChecked();
    optionsNew->squareSizeIndex = slider->value();
    optionsNew->numberColor = getChoosenOption< NumberColor >( radioNumberOnImage, groupRadioNumberOnImage );
    optionsNew->undoEnabled = checkUndoEnabled.isChecked();
    optionsNew->squareColor = getChoosenOption< TileColor >( mapRadioColor, groupRadioColor );

    bool numberImageChanged = optionsNew->numberColor != optionsCurrent->numberColor;
    bool squareSizeChanged = optionsNew->squareSizeIndex != optionsCurrent->squareSizeIndex;
    bool undoMovesChanged = optionsNew->undoEnabled != optionsCurrent->undoEnabled;
    bool colorChanged = optionsNew->squareColor != optionsCurrent->squareColor;

    Options::receiveData( std::move( optionsNew ));

    if ( squareSizeChanged && optionsCurrent->boardMode == BoardMode::NUMERIC )
    {
        parent.redrawTiles();
    }

    if ( numberImageChanged && optionsCurrent->boardMode == BoardMode::GRAPHIC )
    {
        parent.redrawTiles();
    }

    if ( colorChanged && optionsCurrent->boardMode == BoardMode::NUMERIC )
    {
        parent.setColor();
    }

    if ( undoMovesChanged )
    {
        if ( optionsCurrent->undoEnabled )
        {
            parent.deleteUndoMovesService();
        }
        else
        {
            parent.createUndoMovesService();
        }
    }

    close();
}

/*********************************************************************************/
/*********************************************************************************/

template< typename T > T WindowSetting::getChoosenOption( map< T, QRadioButton* >& mapButton, QButtonGroup& group )
{
    QRadioButton* choosen = static_cast< QRadioButton* >( group.checkedButton() );

    for ( auto it = mapButton.begin(); it != mapButton.end(); it++ )
    {
        if ( it->second == choosen )
        {
            return it->first;
        }
    }
    return mapButton.begin()->first;
}

