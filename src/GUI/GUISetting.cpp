
#include "GUISetting.h"

#include <ranges>

#include <QGroupBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "MappedValues.h"


constexpr const char STYLE_MARGIN_LEFT[] = "margin-left: 5px";

using enum BoardSize;
using enum GraphicMode;
using enum GraphicTileCaption;
using enum TileColor;


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

    radioGraphicMode.emplace( SCALED, "Scalled image");
    radioGraphicMode[SCALED].setStyleSheet( STYLE_MARGIN_LEFT );

    radioGraphicMode.emplace( CROPPED, "Cropped image" );
    radioGraphicMode[CROPPED].setStyleSheet( STYLE_MARGIN_LEFT );
    radioGraphicMode[currentOptions.graphicMode].setChecked( true );

    boxImageToLoad.emplace( FOUR, "Load image for board  4x4" );
    boxImageToLoad[FOUR].setChecked( currentOptions.imageToLoad_4 );

    boxImageToLoad.emplace( FIVE, "Load Image for board  5x5" );
    boxImageToLoad[FIVE].setChecked( currentOptions.imageToLoad_5 );

    boxImageToLoad.emplace( SIX, "Load image for board  6x6" );
    boxImageToLoad[SIX].setChecked( currentOptions.imageToLoad_6 );

    boxImageToLoad.emplace( SEVEN, "Load image for board  7x7" );
    boxImageToLoad[SEVEN].setChecked( currentOptions.imageToLoad_7 );

    for ( auto& checkBox : boxImageToLoad | std::views::values )
    {
        checkBox.setStyleSheet( STYLE_MARGIN_LEFT );
    }

    radioTileCaption.emplace( NO, "Number caption on a graphic tile : No" );
    radioTileCaption.emplace( BLACK, "Number caption on a graphic tile : Black" );
    radioTileCaption.emplace( WHITE, "Number caption on a graphic tile : White" );
    radioTileCaption[currentOptions.tileCaption].setChecked( true );

    QButtonGroup* groupNumberOnImage = new QButtonGroup();
    for ( auto& radio : radioTileCaption | std::views::values )
    {
        radio.setStyleSheet( STYLE_MARGIN_LEFT );
        groupNumberOnImage->addButton( &radio );
    }

    QVBoxLayout* layoutImages = new QVBoxLayout();
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( &radioGraphicMode[SCALED] );
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( &radioGraphicMode[CROPPED] );
    layoutImages->addSpacing( 15 );
    layoutImages->addWidget( &boxImageToLoad[FOUR] );
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( &boxImageToLoad[FIVE] );
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( &boxImageToLoad[SIX] );
    layoutImages->addSpacing( 8 );
    layoutImages->addWidget( &boxImageToLoad[SEVEN] );
    layoutImages->addSpacing( 15 );
    layoutImages->addWidget( &radioTileCaption[NO] );
    layoutImages->addSpacing( 12 );
    layoutImages->addWidget( &radioTileCaption[BLACK] );
    layoutImages->addSpacing( 12 );
    layoutImages->addWidget( &radioTileCaption[WHITE] );
    layoutImages->addSpacing( 15 );

    QGroupBox* boxRadioImage = new QGroupBox( "Image for a graphic board" );
    boxRadioImage->setLayout( layoutImages );

    /* Color of numeric board **************************************/

    radioTileColor.emplace( BLUE, "Blue" );
    radioTileColor.emplace( GREEN, "Green" );
    radioTileColor.emplace( RED, "Red" );
    radioTileColor[currentOptions.squareColor].setChecked( true );

    QButtonGroup* groupRadioColor = new QButtonGroup();
    for ( auto& radio : radioTileColor | std::views::values )
    {
        radio.setStyleSheet( STYLE_MARGIN_LEFT );
        groupRadioColor->addButton( &radio );
    }   

    QVBoxLayout* layoutTileColor = new QVBoxLayout();
    layoutTileColor->addSpacing( 7 );
    layoutTileColor->addWidget( &radioTileColor[BLUE] );
    layoutTileColor->addSpacing( 7 );
    layoutTileColor->addWidget( &radioTileColor[GREEN] );
    layoutTileColor->addSpacing( 7 );
    layoutTileColor->addWidget( &radioTileColor[RED] );
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
    using enum BoardMode;
    OptionsData newOptions;

    newOptions.tileSize = Maps::sliderTileSize.at( slider->value() );
    bool tileSizeChanged = newOptions.tileSize != currentOptions.tileSize;
    if ( tileSizeChanged && boardMode == GRAPHIC )
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

    newOptions.graphicMode = radioGraphicMode[SCALED].isChecked() ? SCALED : CROPPED;
    newOptions.imageToLoad_4 = boxImageToLoad[FOUR].isChecked();
    newOptions.imageToLoad_5 = boxImageToLoad[FIVE].isChecked();
    newOptions.imageToLoad_6 = boxImageToLoad[SIX].isChecked();
    newOptions.imageToLoad_7 = boxImageToLoad[SEVEN].isChecked();
    newOptions.tileCaption = getChecked( radioTileCaption, radioTileCaption[NO].group() );
    newOptions.squareColor = getChecked( radioTileColor, radioTileColor[BLUE].group() );

    bool numberImageChanged = newOptions.tileCaption != currentOptions.tileCaption;
    bool colorChanged = newOptions.squareColor != currentOptions.squareColor;

    Options::saveOptions( newOptions );

    if (( tileSizeChanged && boardMode == NUMERIC ) ||
        ( numberImageChanged && boardMode == GRAPHIC ))
    {
        owner.redrawTiles();
    }
    if ( colorChanged && boardMode == NUMERIC )
    {
        owner.setColor();
    }
    close();
}

