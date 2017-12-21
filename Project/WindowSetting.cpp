
#include "WindowSetting.h"
#include <memory>

using std::unique_ptr;

WindowSetting::WindowSetting( MainWindow& parent ) :
    slider{ Qt::Horizontal, this }, accept{ "Accept" },
    boxRadioColor{ "Color of Numeric Board" }, boxSquareSize{ "Size of Square" },
    parent( parent )
{
    setModal( true );
    setWindowTitle( "" );
    setGeometry( 100, 100, 400, 560 );
    setMaximumSize( 400, 830 );
    setMinimumSize( 400, 830 );

    QVBoxLayout layWindow;
    unique_ptr< OptionsData > options( Options::sendData() );

    /***************************************************************/
    /* Graphic loading box *****************************************/

    for ( auto& radio : radioGraphic )
        radio.setStyleSheet( "margin-left:5px;" );

    radioGraphic[SCALED].setText( "Graphic is to be scalled" );
    radioGraphic[SCALED].setChecked( options->mode == GraphicMode::SCALED );
    radioGraphic[CROPPED].setText( "Graphic is to be cropped" );
    radioGraphic[CROPPED].setChecked( !radioGraphic[SCALED].isChecked() );

    groupRadioImage.addButton( &radioGraphic[SCALED] );
    groupRadioImage.addButton( &radioGraphic[CROPPED] );

    for ( auto& check : checkImage )
        check.setStyleSheet( "margin-left:5px;" );

    checkImage[FOUR].setText( "Graphic is to be loaded for a board  4x4" );
    checkImage[FOUR].setChecked( options->fourImageToBeLoaded );
    checkImage[FIVE].setText( "Graphic is to be loaded for a board  5x5" );
    checkImage[FIVE].setChecked( options->fiveImageToBeLoaded );
    checkImage[SIX].setText( "Graphic is to be loaded for a board  6x6" );
    checkImage[SIX].setChecked( options->sixImageToBeLoaded );
    checkImage[SEVEN].setText( "Graphic is to be loaded for a board  7x7" );
    checkImage[SEVEN].setChecked( options->sevenImageToBeLoaded );

    QVBoxLayout layRadioImage;
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &radioGraphic[SCALED] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &radioGraphic[CROPPED] );
    layRadioImage.addSpacing( 15 );
    layRadioImage.addWidget( &checkImage[FOUR] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &checkImage[FIVE] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &checkImage[SIX] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &checkImage[SEVEN] );
    layRadioImage.addSpacing( 15 );
    boxRadioImage.setLayout( &layRadioImage );
    boxRadioImage.setTitle( "Graphic loading" );

    /***************************************************************/
    /* Image text box **********************************************/

    checkImageText.setText( " Number on a graphic square" );
    radioImageTextColor[0].setText(" Blue ");
    radioImageTextColor[1].setText(" White ");
    radioImageTextColor[2].setText(" Black ");

    groupRadioImageTextColor.addButton( &radioImageTextColor[0] );
    groupRadioImageTextColor.addButton( &radioImageTextColor[1] );
    groupRadioImageTextColor.addButton( &radioImageTextColor[2] );

    QVBoxLayout layRadioImageText;
    layRadioImageText.addSpacing( 8 );
    layRadioImageText.addWidget( &checkImageText );
    layRadioImageText.addSpacing( 8 );
    layRadioImageText.addWidget( &radioImageTextColor[0] );
    layRadioImageText.addSpacing( 8 );
    layRadioImageText.addWidget( &radioImageTextColor[1] );
    layRadioImageText.addSpacing( 8 );
    layRadioImageText.addWidget( &radioImageTextColor[2] );
    layRadioImageText.addSpacing( 15 );
    boxRadioImageText.setLayout( &layRadioImageText );

    /***************************************************************/
    /* Color of numeric board **************************************/

    for ( auto& radio : radioColor )
        radio.setStyleSheet( "margin-left:5px;" );

    groupRadioColor.addButton( &radioColor[BLUE] );
    groupRadioColor.addButton( &radioColor[GREEN] );
    groupRadioColor.addButton( &radioColor[RED] );

    radioColor[ Options::getColor() ].setChecked( true );

    QVBoxLayout layRadioColor;
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radioColor[BLUE] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radioColor[GREEN] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radioColor[RED] );
    layRadioColor.addSpacing( 7 );
    boxRadioColor.setLayout( &layRadioColor );

    radioColor[BLUE].setText( "Blue" );
    radioColor[GREEN].setText( "Green" );
    radioColor[RED].setText( "Red" );

    /***************************************************************/
    /* Slider for square size **************************************/

    slider.setRange( 1, 5 );
    slider.setSingleStep( 1 );
    sliderLabels[0].setText( "50" );
    sliderLabels[1].setText( "  100" );
    sliderLabels[2].setText( "150" );
    sliderLabels[3].setText( "200  " );
    sliderLabels[4].setText( "250" );
    slider.setValue( Options::getSquareSizeIndex() );

    QGridLayout layoutSlider;
    layoutSlider.setContentsMargins( 30, 20, 30, 20 );
    layoutSlider.addWidget( &slider,          0, 0, 1, 5 );
    layoutSlider.addWidget( &sliderLabels[0], 1, 0, 1, 1, Qt::AlignLeft );
    layoutSlider.addWidget( &sliderLabels[1], 1, 1, 1, 1, Qt::AlignLeft );
    layoutSlider.addWidget( &sliderLabels[2], 1, 2, 1, 1, Qt::AlignCenter );
    layoutSlider.addWidget( &sliderLabels[3], 1, 3, 1, 1, Qt::AlignRight );
    layoutSlider.addWidget( &sliderLabels[4], 1, 4, 1, 1, Qt::AlignRight );
    boxSquareSize.setLayout( &layoutSlider );

    /***************************************************************/
    /* General layout **********************************************/

    QHBoxLayout layControls;
    accept.setStyleSheet( "height:20px;" );
    connect( &accept, SIGNAL( clicked() ), this, SLOT( acceptSettings() ));

    layControls.addSpacing( 120 );
    layControls.addWidget( &accept );
    layControls.addSpacing( 120 );

    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxRadioImage );
    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxRadioImageText );
    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxRadioColor);
    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxSquareSize );
    layWindow.addSpacing( 20 );
    layWindow.addLayout( &layControls );
    layWindow.addSpacing( 10 );
    layWindow.addStretch();

    this->setLayout( &layWindow );
    this->show();
}

/*******************************************************************************/
/* ACCEPT SETTINGS *************************************************************/

void WindowSetting::acceptSettings()
{
    unique_ptr< OptionsData > dataMessage ( new OptionsData );
    dataMessage->mode = radioGraphic[SCALED].isChecked() ? GraphicMode::SCALED : GraphicMode::CROPPED;
    dataMessage->fourImageToBeLoaded = checkImage[FOUR].isChecked();
    dataMessage->fiveImageToBeLoaded = checkImage[FIVE].isChecked();
    dataMessage->sixImageToBeLoaded = checkImage[SIX].isChecked();
    dataMessage->sevenImageToBeLoaded = checkImage[SEVEN].isChecked();

    Options::receiveData( std::move( dataMessage ));

    //Options::setImagesToBeLoaded( checkImage[FOUR].isChecked(), checkImage[FIVE].isChecked(), checkImage[SIX].isChecked(), checkImage[SEVEN].isChecked());
    //Options::setGraphicMode(( radioGraphic[SCALED].isChecked() ? GraphicMode::SCALED : GraphicMode::CROPPED ));
    BoardMode boardMode = Options::getBoardMode();

    if ( slider.value() != Options::getSquareSizeIndex() )
    {
        Options::setSquareSize( slider.value() );
        if ( boardMode == BoardMode::NUMERIC )
            parent.redrawSquares();
    }

    bool change = false;
    if ( radioColor[BLUE].isChecked() && Options::getColor() != Color::BLUE )
    {
        Options::setColor( Color::BLUE );
        change = true;
    }
    else if ( radioColor[GREEN].isChecked() && Options::getColor() != Color::GREEN )
    {
        Options::setColor( Color::GREEN );
        change = true;
    }
    else if ( radioColor[RED].isChecked() && Options::getColor() != Color::RED )
    {
        Options::setColor( Color::RED );
        change = true;
    }

    if ( change && boardMode == BoardMode::NUMERIC )
        parent.setColor();

    close();
}

