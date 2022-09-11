
#include <QGroupBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "GUISetting.h"
#include "MappedValues.h"

constexpr const char STYLE_MARGIN_LEFT[] = "margin-left: 5px";

using std::map;
using std::unique_ptr;


GUISetting::GUISetting( Fifteen& owner ) : owner( owner )
{
    setModal( true );
    setWindowTitle( "" );
    setGeometry( 100, 100, 400, 560 );
    setMaximumSize( 400, 800 );
    setMinimumSize( 400, 800 );
    setAttribute( Qt::WA_DeleteOnClose );

    optionsCurrent = Options::readOptions();

    /* Graphic loading box *****************************************/

    mapRadioGraphicMode[GraphicMode::SCALED] = new QRadioButton( "Scalled image" );
    mapRadioGraphicMode[GraphicMode::CROPPED] = new QRadioButton( "Cropped image" );

    for ( auto radio : mapRadioGraphicMode )
    {
        radio.second->setStyleSheet( STYLE_MARGIN_LEFT );
    }

    mapRadioGraphicMode[optionsCurrent->graphicMode]->setChecked( true );

    mapCheckImageToChose[BoardSize::FOUR] = new QCheckBox( "Load image for board  4x4" );
    mapCheckImageToChose[BoardSize::FOUR]->setChecked( optionsCurrent->imageToLoad_4 );
    mapCheckImageToChose[BoardSize::FIVE] = new QCheckBox( "Load Image for board  5x5" );
    mapCheckImageToChose[BoardSize::FIVE]->setChecked( optionsCurrent->imageToLoad_5 );
    mapCheckImageToChose[BoardSize::SIX] = new QCheckBox( "Load image for board  6x6" );
    mapCheckImageToChose[BoardSize::SIX]->setChecked( optionsCurrent->imageToLoad_6 );
    mapCheckImageToChose[BoardSize::SEVEN] = new QCheckBox( "Load image for board  7x7" );
    mapCheckImageToChose[BoardSize::SEVEN]->setChecked( optionsCurrent->imageToLoad_7 );

    for ( auto check : mapCheckImageToChose )
    {
        check.second->setStyleSheet( STYLE_MARGIN_LEFT );
    }

    mapRadioNumberOnImage[NumberColor::NO] = new QRadioButton( "Number on graphic tile : No" );
    mapRadioNumberOnImage[NumberColor::BLACK] = new QRadioButton( "Number on graphic tile : Black" );
    mapRadioNumberOnImage[NumberColor::WHITE] = new QRadioButton( "Number on graphic tile : White" );

    for ( auto radio : mapRadioNumberOnImage )
    {
        radio.second->setStyleSheet( STYLE_MARGIN_LEFT );
        groupRadioNumberOnImage.addButton( radio.second );
    }

    mapRadioNumberOnImage[optionsCurrent->numberColor]->setChecked( true );

    QVBoxLayout* layoutImages = new QVBoxLayout();
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( mapRadioGraphicMode[GraphicMode::SCALED] );
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( mapRadioGraphicMode[GraphicMode::CROPPED] );
    layoutImages->addSpacing( 15 );
    layoutImages->addWidget( mapCheckImageToChose[BoardSize::FOUR] );
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( mapCheckImageToChose[BoardSize::FIVE] );
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( mapCheckImageToChose[BoardSize::SIX] );
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( mapCheckImageToChose[BoardSize::SEVEN] );
    layoutImages->addSpacing( 15 );
    layoutImages->addWidget( mapRadioNumberOnImage[NumberColor::NO] );
    layoutImages->addSpacing( 12 );
    layoutImages->addWidget( mapRadioNumberOnImage[NumberColor::BLACK] );
    layoutImages->addSpacing( 12 );
    layoutImages->addWidget( mapRadioNumberOnImage[NumberColor::WHITE] );
    layoutImages->addSpacing( 15 );

    QGroupBox* boxRadioImage = new QGroupBox( "Image for a graphic board" );
    boxRadioImage->setLayout( layoutImages );

    /* Color of numeric board **************************************/

    mapRadioColor[TileColor::BLUE] = new QRadioButton( "Blue" );
    mapRadioColor[TileColor::GREEN] = new QRadioButton( "Green" );
    mapRadioColor[TileColor::RED] = new QRadioButton( "Red" );

    for ( auto radio : mapRadioColor )
    {
        radio.second->setStyleSheet( STYLE_MARGIN_LEFT );
        groupRadioColor.addButton( radio.second );
    }

    mapRadioColor[ optionsCurrent->squareColor ]->setChecked( true );

    QVBoxLayout* layoutTileColor = new QVBoxLayout();
    layoutTileColor->addSpacing( 7 );
    layoutTileColor->addWidget( mapRadioColor[TileColor::BLUE] );
    layoutTileColor->addSpacing( 7 );
    layoutTileColor->addWidget( mapRadioColor[TileColor::GREEN] );
    layoutTileColor->addSpacing( 7 );
    layoutTileColor->addWidget( mapRadioColor[TileColor::RED] );
    layoutTileColor->addSpacing( 7 );

    QGroupBox* boxRadioColor = new QGroupBox( "Color of numeric board" );
    boxRadioColor->setLayout( layoutTileColor );

    /* Slider for square size **************************************/

    slider = new QSlider( Qt::Horizontal, this );
    slider->setRange( 0, 4 );
    slider->setSingleStep( 1 );
    slider->setValue( Maps::getSliderByTileSize( optionsCurrent->tileSize ));

    QGridLayout* layoutSlider = new QGridLayout();
    layoutSlider->setContentsMargins( 10, 20, 30, 20 );
    layoutSlider->addWidget( slider,          0, 0, 1, 5 );
    layoutSlider->addWidget( new QLabel( " 50" ),   1, 0, 1, 1, Qt::AlignLeft );
    layoutSlider->addWidget( new QLabel( "   75" ), 1, 1, 1, 1, Qt::AlignLeft );
    layoutSlider->addWidget( new QLabel( "100" ),   1, 2, 1, 1, Qt::AlignCenter );
    layoutSlider->addWidget( new QLabel( "125  " ), 1, 3, 1, 1, Qt::AlignRight );
    layoutSlider->addWidget( new QLabel( "150" ),   1, 4, 1, 1, Qt::AlignRight );

    QGroupBox* boxSquareSize = new QGroupBox( "Size of tile" );
    boxSquareSize->setLayout( layoutSlider );

    /* General layout **********************************************/

    QVBoxLayout layWindow;

    QPushButton* pushAccept = new QPushButton( "Accept" );
    pushAccept->setStyleSheet( "height:20px;" );
    connect( pushAccept, SIGNAL( clicked() ), this, SLOT( acceptSettings() ));

    QHBoxLayout* layoutAccept = new QHBoxLayout();
    layoutAccept->addSpacing( 120 );
    layoutAccept->addWidget( pushAccept );
    layoutAccept->addSpacing( 120 );

    layWindow.addSpacing( 20 );
    layWindow.addWidget( boxRadioImage );
    layWindow.addSpacing( 20 );
    layWindow.addWidget( boxRadioColor);
    layWindow.addSpacing( 20 );
    layWindow.addWidget( boxSquareSize );
    layWindow.addSpacing( 20 );
    layWindow.addLayout( layoutAccept );
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

    optionsNew->tileSize = Maps::sliderTileSize.at( slider->value() );
    bool tileSizeChanged = optionsNew->tileSize != optionsCurrent->tileSize;
    if ( tileSizeChanged && optionsCurrent->boardMode == BoardMode::GRAPHIC )
    {
        QMessageBox::information( this, "",
                                  "\nSize of a tile can not be changed in graphic mode\t \nwhen an image has been loaded" );
        return;
    }

    optionsNew->graphicMode = mapRadioGraphicMode[GraphicMode::SCALED]->isChecked() ? GraphicMode::SCALED : GraphicMode::CROPPED;
    optionsNew->imageToLoad_4 = mapCheckImageToChose[BoardSize::FOUR]->isChecked();
    optionsNew->imageToLoad_5 = mapCheckImageToChose[BoardSize::FIVE]->isChecked();
    optionsNew->imageToLoad_6 = mapCheckImageToChose[BoardSize::SIX]->isChecked();
    optionsNew->imageToLoad_7 = mapCheckImageToChose[BoardSize::SEVEN]->isChecked();
    optionsNew->numberColor = getChoosenOption< NumberColor >( mapRadioNumberOnImage, groupRadioNumberOnImage );
    optionsNew->squareColor = getChoosenOption< TileColor >( mapRadioColor, groupRadioColor );

    bool numberImageChanged = optionsNew->numberColor != optionsCurrent->numberColor;
    bool colorChanged = optionsNew->squareColor != optionsCurrent->squareColor;

    Options::saveOptions( std::move( optionsNew ));

    if (( tileSizeChanged && optionsCurrent->boardMode == BoardMode::NUMERIC  ) ||
        ( numberImageChanged && optionsCurrent->boardMode == BoardMode::GRAPHIC ))
    {
        owner.redrawTiles();
    }

    if ( colorChanged && optionsCurrent->boardMode == BoardMode::NUMERIC )
    {
        owner.setColor();
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

