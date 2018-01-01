
#include "WindowSetting.h"
#include <memory>

using std::unique_ptr;

WindowSetting::WindowSetting( MainWindow& parent ) : slider{ Qt::Horizontal, this }, parent( parent )
{
    setModal( true );
    setWindowTitle( "" );
    setGeometry( 100, 100, 400, 560 );
    setMaximumSize( 400, 730 );
    setMinimumSize( 400, 730 );

    QVBoxLayout layWindow;
    optionsCurrent = Options::sendData();

    /***************************************************************/
    /* Graphic loading box *****************************************/

    for ( auto& radio : radioGraphic )
        radio.setStyleSheet( "margin-left: 5px;" );

    radioGraphic[SCALED].setText( "Graphic is to be scalled" );
    radioGraphic[SCALED].setChecked( optionsCurrent->graphicMode == GraphicMode::SCALED );
    radioGraphic[CROPPED].setText( "Graphic is to be cropped" );
    radioGraphic[CROPPED].setChecked( !radioGraphic[SCALED].isChecked() );

    groupRadioImage.addButton( &radioGraphic[SCALED] );
    groupRadioImage.addButton( &radioGraphic[CROPPED] );

    for ( auto& check : checkImage )
        check.setStyleSheet( "margin-left: 5px;" );

    checkImage[FOUR].setText( "Graphic is to be loaded for a board  4x4" );
    checkImage[FOUR].setChecked( optionsCurrent->fourImageToBeLoaded );
    checkImage[FIVE].setText( "Graphic is to be loaded for a board  5x5" );
    checkImage[FIVE].setChecked( optionsCurrent->fiveImageToBeLoaded );
    checkImage[SIX].setText( "Graphic is to be loaded for a board  6x6" );
    checkImage[SIX].setChecked( optionsCurrent->sixImageToBeLoaded );
    checkImage[SEVEN].setText( "Graphic is to be loaded for a board  7x7" );
    checkImage[SEVEN].setChecked( optionsCurrent->sevenImageToBeLoaded );

    checkImageText.setText( "Text with a number on a graphic square" );
    checkImageText.setChecked( optionsCurrent->numberOnImage );
    checkImageText.setStyleSheet( "margin-left: 5px" );

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
    layRadioImage.addSpacing( 12 );
    layRadioImage.addWidget( &checkImageText );
    layRadioImage.addSpacing( 15 );
    boxRadioImage.setLayout( &layRadioImage );
    boxRadioImage.setTitle( "Image fof graphic board" );

    /***************************************************************/
    /* Color of numeric board **************************************/

    for ( auto& radio : radioColor )
        radio.setStyleSheet( "margin-left:5px;" );

    groupRadioColor.addButton( &radioColor[BLUE] );
    groupRadioColor.addButton( &radioColor[GREEN] );
    groupRadioColor.addButton( &radioColor[RED] );

    radioColor[ optionsCurrent->squareColor ].setChecked( true );

    QVBoxLayout layRadioColor;
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radioColor[BLUE] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radioColor[GREEN] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radioColor[RED] );
    layRadioColor.addSpacing( 7 );
    boxRadioColor.setLayout( &layRadioColor );
    boxRadioColor.setTitle( "Color of Numeric Board" );

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
    slider.setValue( optionsCurrent->squareSizeIndex );

    QGridLayout layoutSlider;
    layoutSlider.setContentsMargins( 30, 20, 30, 20 );
    layoutSlider.addWidget( &slider,          0, 0, 1, 5 );
    layoutSlider.addWidget( &sliderLabels[0], 1, 0, 1, 1, Qt::AlignLeft );
    layoutSlider.addWidget( &sliderLabels[1], 1, 1, 1, 1, Qt::AlignLeft );
    layoutSlider.addWidget( &sliderLabels[2], 1, 2, 1, 1, Qt::AlignCenter );
    layoutSlider.addWidget( &sliderLabels[3], 1, 3, 1, 1, Qt::AlignRight );
    layoutSlider.addWidget( &sliderLabels[4], 1, 4, 1, 1, Qt::AlignRight );
    boxSquareSize.setLayout( &layoutSlider );
    boxSquareSize.setTitle( "Size of Square" );

    /***************************************************************/
    /* General layout **********************************************/

    QHBoxLayout layControls;
    accept.setStyleSheet( "height:20px;" );
    accept.setText( "Accept ");
    connect( &accept, SIGNAL( clicked() ), this, SLOT( acceptSettings() ));

    layControls.addSpacing( 120 );
    layControls.addWidget( &accept );
    layControls.addSpacing( 120 );

    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxRadioImage );
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
    unique_ptr< OptionsData > optionsNew ( new OptionsData );
    optionsNew->graphicMode = radioGraphic[SCALED].isChecked() ? GraphicMode::SCALED : GraphicMode::CROPPED;
    optionsNew->fourImageToBeLoaded = checkImage[FOUR].isChecked();
    optionsNew->fiveImageToBeLoaded = checkImage[FIVE].isChecked();
    optionsNew->sixImageToBeLoaded = checkImage[SIX].isChecked();
    optionsNew->sevenImageToBeLoaded = checkImage[SEVEN].isChecked();
    optionsNew->squareSizeIndex = slider.value();
    optionsNew->numberOnImage = checkImageText.isChecked();

    bool numberImageChanged = optionsNew->numberOnImage != optionsCurrent->numberOnImage;
    bool squareSizeChanged = optionsNew->squareSizeIndex != optionsCurrent->squareSizeIndex;

    if ( radioColor[BLUE].isChecked() )
    {
        optionsNew->squareColor = Color::BLUE;
    }
    else if ( radioColor[GREEN].isChecked() )
    {
        optionsNew->squareColor = Color::GREEN;
    }
    else if ( radioColor[RED].isChecked() )
    {
        optionsNew->squareColor = Color::RED;
    }
    bool colorChanged = optionsNew->squareColor != optionsCurrent->squareColor;

    Options::receiveData( std::move( optionsNew ));

    if ( squareSizeChanged && optionsCurrent->boardMode == BoardMode::NUMERIC )
        parent.redrawSquares();

    if ( numberImageChanged && optionsCurrent->boardMode == BoardMode::GRAPHIC )
        parent.redrawSquares();

    if ( colorChanged && optionsCurrent->boardMode == BoardMode::NUMERIC )
        parent.setColor();

    close();
}

