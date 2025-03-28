
#include "GUISetting.h"

#include <ranges>

#include <QGroupBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "MappedValues.h"


constexpr const char STYLE_MARGIN_LEFT[] = "margin-left: 5px";


GUISetting::GUISetting( Fifteen& owner, BoardMode boardMode ) : owner( owner ), boardMode( boardMode )
{
    setModal( true );
    setWindowTitle( "" );
    setGeometry( 100, 100, 400, 560 );
    setMaximumSize( 400, 800 );
    setMinimumSize( 400, 800 );
    setAttribute( Qt::WA_DeleteOnClose );

    currentOptions = Options::readOptions();

    /* Graphic loading box *****************************************/

    mapGraphicMode.emplace( GraphicMode::SCALED, "Scalled image");
    mapGraphicMode[GraphicMode::SCALED].setStyleSheet( STYLE_MARGIN_LEFT );
    
    mapGraphicMode.emplace( GraphicMode::CROPPED, "Cropped image" );
    mapGraphicMode[GraphicMode::CROPPED].setStyleSheet( STYLE_MARGIN_LEFT );
    mapGraphicMode[currentOptions.graphicMode].setChecked( true );

    mapImageToLoad.emplace( BoardSize::FOUR, "Load image for board  4x4" );
    mapImageToLoad[BoardSize::FOUR].setChecked( currentOptions.imageToLoad_4 );
    
    mapImageToLoad.emplace( BoardSize::FIVE, "Load Image for board  5x5" );
    mapImageToLoad[BoardSize::FIVE].setChecked( currentOptions.imageToLoad_5 );
    
    mapImageToLoad.emplace( BoardSize::SIX, "Load image for board  6x6" );
    mapImageToLoad[BoardSize::SIX].setChecked( currentOptions.imageToLoad_6 );
    
    mapImageToLoad.emplace( BoardSize::SEVEN, "Load image for board  7x7" );
    mapImageToLoad[BoardSize::SEVEN].setChecked( currentOptions.imageToLoad_7 );

    for ( auto& checkBox : mapImageToLoad | std::views::values )
    {
        checkBox.setStyleSheet( STYLE_MARGIN_LEFT );
    }
    mapNumberOnImage.emplace( NumberColor::NO, "Number on graphic tile : No" );
    mapNumberOnImage.emplace( NumberColor::BLACK, "Number on graphic tile : Black" );
    mapNumberOnImage.emplace( NumberColor::WHITE, "Number on graphic tile : White" );
    mapNumberOnImage[currentOptions.numberColor].setChecked( true );

    QButtonGroup* groupNumberOnImage = new QButtonGroup();
    for ( auto& radio : mapNumberOnImage | std::views::values )
    {
        radio.setStyleSheet( STYLE_MARGIN_LEFT );
        groupNumberOnImage->addButton( &radio );
    }

    QVBoxLayout* layoutImages = new QVBoxLayout();
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( &mapGraphicMode[GraphicMode::SCALED] );
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( &mapGraphicMode[GraphicMode::CROPPED] );
    layoutImages->addSpacing( 15 );
    layoutImages->addWidget( &mapImageToLoad[BoardSize::FOUR] );
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( &mapImageToLoad[BoardSize::FIVE] );
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( &mapImageToLoad[BoardSize::SIX] );
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( &mapImageToLoad[BoardSize::SEVEN] );
    layoutImages->addSpacing( 15 );
    layoutImages->addWidget( &mapNumberOnImage[NumberColor::NO] );
    layoutImages->addSpacing( 12 );
    layoutImages->addWidget( &mapNumberOnImage[NumberColor::BLACK] );
    layoutImages->addSpacing( 12 );
    layoutImages->addWidget( &mapNumberOnImage[NumberColor::WHITE] );
    layoutImages->addSpacing( 15 );

    QGroupBox* boxRadioImage = new QGroupBox( "Image for a graphic board" );
    boxRadioImage->setLayout( layoutImages );

    /* Color of numeric board **************************************/

    mapTileColor.emplace(TileColor::BLUE, "Blue" );
    mapTileColor.emplace(TileColor::GREEN, "Green" );
    mapTileColor.emplace(TileColor::RED, "Red" );
    mapTileColor[currentOptions.squareColor].setChecked( true );

    QButtonGroup* groupRadioColor = new QButtonGroup();
    for ( auto& radio : mapTileColor | std::views::values )
    {
        radio.setStyleSheet( STYLE_MARGIN_LEFT );
        groupRadioColor->addButton( &radio );
    }   

    QVBoxLayout* layoutTileColor = new QVBoxLayout();
    layoutTileColor->addSpacing( 7 );
    layoutTileColor->addWidget( &mapTileColor[TileColor::BLUE] );
    layoutTileColor->addSpacing( 7 );
    layoutTileColor->addWidget( &mapTileColor[TileColor::GREEN] );
    layoutTileColor->addSpacing( 7 );
    layoutTileColor->addWidget( &mapTileColor[TileColor::RED] );
    layoutTileColor->addSpacing( 7 );

    QGroupBox* boxRadioColor = new QGroupBox( "Color of numeric board" );
    boxRadioColor->setLayout( layoutTileColor );

    /* Slider for square size **************************************/

    slider = new QSlider( Qt::Horizontal, this );
    slider->setRange( 0, 4 );
    slider->setSingleStep( 1 );
    slider->setValue( Maps::getSliderByTileSize( currentOptions.tileSize ));

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
    OptionsData newOptions;

    newOptions.tileSize = Maps::sliderTileSize.at( slider->value() );
    bool tileSizeChanged = newOptions.tileSize != currentOptions.tileSize;
    if ( tileSizeChanged && boardMode == BoardMode::GRAPHIC )
    {
        QMessageBox::information( this, "",
                                  "\nSize of a tile can not be changed in graphic mode\t \nwhen an image has been loaded" );
        return;
    }

    const auto getChecked = [](const auto& mapRadio, const QButtonGroup* group)
    {
        QAbstractButton* checked = group->checkedButton();
        for ( const auto& [key, value] : mapRadio )
        {
            if ( &value == checked )
            {
                return key;
            }
        }
        return mapRadio.begin()->first;
    };

    newOptions.graphicMode = mapGraphicMode[GraphicMode::SCALED].isChecked() ? GraphicMode::SCALED : GraphicMode::CROPPED;
    newOptions.imageToLoad_4 = mapImageToLoad[BoardSize::FOUR].isChecked();
    newOptions.imageToLoad_5 = mapImageToLoad[BoardSize::FIVE].isChecked();
    newOptions.imageToLoad_6 = mapImageToLoad[BoardSize::SIX].isChecked();
    newOptions.imageToLoad_7 = mapImageToLoad[BoardSize::SEVEN].isChecked();
    newOptions.numberColor = getChecked( mapNumberOnImage, mapNumberOnImage[NumberColor::NO].group() );
    newOptions.squareColor = getChecked( mapTileColor, mapTileColor[TileColor::BLUE].group() );

    bool numberImageChanged = newOptions.numberColor != currentOptions.numberColor;
    bool colorChanged = newOptions.squareColor != currentOptions.squareColor;

    Options::saveOptions( newOptions );

    if (( tileSizeChanged && boardMode == BoardMode::NUMERIC  ) ||
        ( numberImageChanged && boardMode == BoardMode::GRAPHIC ))
    {
        owner.redrawTiles();
    }
    if ( colorChanged && boardMode == BoardMode::NUMERIC )
    {
        owner.setColor();
    }
    close();
}

