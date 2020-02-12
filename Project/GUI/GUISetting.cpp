
#include "GUISetting.h"
#include "MappedValues.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <memory>

using std::unique_ptr;

GUISetting::GUISetting( Fifteen& owner ) : owner( owner )
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

    mapRadioGraphicMode[GraphicMode::SCALED] = new QRadioButton( "Scalled image" );
    mapRadioGraphicMode[GraphicMode::CROPPED] = new QRadioButton( "Cropped image" );
    mapRadioGraphicMode[GraphicMode::SCALED]->setChecked( optionsCurrent->graphicMode == GraphicMode::SCALED );

    for ( auto radio : mapRadioGraphicMode )
    {
        radio.second->setStyleSheet( "margin-left: 5px;" );
        groupRadioGraphicMode.addButton( radio.second );
    }

    mapRadioGraphicMode[ optionsCurrent->graphicMode]->setChecked( true );

    mapCheckImageToChose[BoardSize::FOUR] = new QCheckBox( "Load image for board  4x4" );
    mapCheckImageToChose[BoardSize::FOUR]->setChecked( optionsCurrent->imageToLoad_4 );
    mapCheckImageToChose[BoardSize::FIVE] = new QCheckBox( "Load Image for board  5x5" );
    mapCheckImageToChose[BoardSize::FIVE]->setChecked( optionsCurrent->imageToLoad_5 );
    mapCheckImageToChose[BoardSize::SIX] = new QCheckBox( "Load image for board  6x6" );
    mapCheckImageToChose[BoardSize::SIX]->setChecked( optionsCurrent->imageToLoad_6 );
    mapCheckImageToChose[BoardSize::SEVEN] = new QCheckBox( "Load image for board  7x7" );
    mapCheckImageToChose[BoardSize::SEVEN]->setChecked( optionsCurrent->imageToLoad_7 );

    for ( auto& check : mapCheckImageToChose )
    {
        check.second->setStyleSheet( "margin-left: 5px;" );
    }

    mapRadioNumberOnImage[NumberColor::NO] = new QRadioButton( "Number on graphic tile : No" );
    mapRadioNumberOnImage[NumberColor::BLACK] = new QRadioButton( "Number on graphic tile : Black" );
    mapRadioNumberOnImage[NumberColor::WHITE] = new QRadioButton( "Number on graphic tile : White" );

    for ( auto radio : mapRadioNumberOnImage )
    {
        radio.second->setStyleSheet( "margin-left: 5px;" );
        groupRadioNumberOnImage.addButton( radio.second );
    }

    mapRadioNumberOnImage[ optionsCurrent->numberColor ]->setChecked( true );

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
    layRadioImage.addWidget( mapRadioNumberOnImage[NumberColor::NO] );
    layRadioImage.addSpacing( 12 );
    layRadioImage.addWidget( mapRadioNumberOnImage[NumberColor::BLACK] );
    layRadioImage.addSpacing( 12 );
    layRadioImage.addWidget( mapRadioNumberOnImage[NumberColor::WHITE] );
    layRadioImage.addSpacing( 15 );
    QGroupBox* boxRadioImage = new QGroupBox( "Image for a graphic board" );
    boxRadioImage->setLayout( &layRadioImage );

    /* Color of numeric board **************************************/

    mapRadioColor[TileColor::BLUE] = new QRadioButton( "Blue" );
    mapRadioColor[TileColor::GREEN] = new QRadioButton( "Green" );
    mapRadioColor[TileColor::RED] = new QRadioButton( "Red" );

    for ( auto radio : mapRadioColor )
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
    slider->setRange( 0, 4 );
    slider->setSingleStep( 1 );
    sliderLabels[0] = new QLabel( " 50" );
    sliderLabels[1] = new QLabel( "   75" );
    sliderLabels[2] = new QLabel( "100" );
    sliderLabels[3] = new QLabel( "125  " );
    sliderLabels[4] = new QLabel( "150" );

    slider->setValue( Mapped::getSliderByTileSize( optionsCurrent->tileSize ));

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

void GUISetting::acceptSettings()
{
    unique_ptr< OptionsData > optionsNew ( new OptionsData );
    optionsNew->graphicMode = mapRadioGraphicMode[GraphicMode::SCALED]->isChecked() ? GraphicMode::SCALED : GraphicMode::CROPPED;
    optionsNew->imageToLoad_4 = mapCheckImageToChose[BoardSize::FOUR]->isChecked();
    optionsNew->imageToLoad_5 = mapCheckImageToChose[BoardSize::FIVE]->isChecked();
    optionsNew->imageToLoad_6 = mapCheckImageToChose[BoardSize::SIX]->isChecked();
    optionsNew->imageToLoad_7 = mapCheckImageToChose[BoardSize::SEVEN]->isChecked();
    optionsNew->numberColor = getChoosenOption< NumberColor >( mapRadioNumberOnImage, groupRadioNumberOnImage );
    optionsNew->undoEnabled = checkUndoEnabled.isChecked();
    optionsNew->squareColor = getChoosenOption< TileColor >( mapRadioColor, groupRadioColor );

    optionsNew->tileSize = Mapped::sliderTileSize.at( slider->value() );

    bool numberImageChanged = optionsNew->numberColor != optionsCurrent->numberColor;
    bool squareSizeChanged = optionsNew->tileSize != optionsCurrent->tileSize;
    bool undoMovesChanged = optionsNew->undoEnabled != optionsCurrent->undoEnabled;
    bool colorChanged = optionsNew->squareColor != optionsCurrent->squareColor;

    Options::receiveData( std::move( optionsNew ));

    if (( squareSizeChanged && optionsCurrent->boardMode == BoardMode::NUMERIC  ) ||
        ( numberImageChanged && optionsCurrent->boardMode == BoardMode::GRAPHIC ))
    {
        owner.redrawTiles();
    }

    if ( colorChanged && optionsCurrent->boardMode == BoardMode::NUMERIC )
    {
        owner.setColor();
    }

    if ( undoMovesChanged )
    {
        if ( optionsCurrent->undoEnabled )
        {
            owner.deleteUndoMovesService();
        }
        else
        {
            owner.createUndoMovesService();
        }
    }

    close();
}

/*********************************************************************************/
/*********************************************************************************/

template< typename T > T GUISetting::getChoosenOption( map< T, QRadioButton* >& mapButton, QButtonGroup& group )
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

