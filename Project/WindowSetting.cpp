
#include "WindowSetting.h"

WindowSetting::WindowSetting( ImagesState& images, MainWindow& parent ) :
    slider{ Qt::Horizontal, this }, accept{ "Accept" },
    boxRadioColor{ "Color of Numeric Board" }, boxRadioImage{ "Graphic" }, boxSquareSize{ "Size of Square" },
    groupRadioImage(), groupRadioColor(), images( images ), parent( parent )
{
    setModal( true );    
    setWindowTitle( "" );
    setGeometry( 100, 100, 400, 560 );
    setMaximumSize( 400, 680 );
    setMinimumSize( 400, 680 );

    QVBoxLayout layWindow;

    /* Radio controls **********************************************/

    for ( auto& radio : radioColor )
        radio.setStyleSheet( "margin-left:5px;" );

    for ( auto& radio : radioGraphic )
        radio.setStyleSheet( "margin-left:5px;" );

    radioGraphic[SCALE].setText( "Graphic is to be scalled" );
    radioGraphic[CROP].setText( "Graphic is to be cropped" );
    radioColor[BLUE].setText( "Blue" );
    radioColor[GREEN].setText( "Green" );
    radioColor[RED].setText( "Red" );

    groupRadioImage.addButton( &radioGraphic[SCALE] );
    groupRadioImage.addButton( &radioGraphic[CROP] );

    radioGraphic[SCALE].setChecked( Options::isScaled() );
    radioGraphic[CROP].setChecked( !Options::isScaled() );

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


    /* Checkbox for images praparing  ********************************/

    for ( auto& check : checkBoardSize )
        check.setStyleSheet( "margin-left:5px;" );

    checkBoardSize[FOUR].setText( "Graphic is to be loaded for a board 4x4" );
    checkBoardSize[FIVE].setText( "Graphic is to be loaded for a board 5x5" );
    checkBoardSize[SIX].setText( "Graphic is to be loaded for a board 6x6" );
    checkBoardSize[SEVEN].setText( "Graphic is to be loaded for a board 7x7" );

    checkBoardSize[FOUR].setChecked( images.four.toLoad );
    checkBoardSize[FIVE].setChecked( images.five.toLoad );
    checkBoardSize[SIX].setChecked( images.six.toLoad );
    checkBoardSize[SEVEN].setChecked( images.seven.toLoad );

    QVBoxLayout layRadioImage;
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &radioGraphic[SCALE] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &radioGraphic[CROP] );
    layRadioImage.addSpacing( 15 );
    layRadioImage.addWidget( &checkBoardSize[FOUR] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &checkBoardSize[FIVE] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &checkBoardSize[SIX] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &checkBoardSize[SEVEN] );
    layRadioImage.addSpacing( 15 );
    boxRadioImage.setLayout( &layRadioImage );


    /* Slider for square size *************************************/

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


    /* General layout *********************************************/

    QHBoxLayout layControls;
    accept.setStyleSheet( "height:20px;" );
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
    images.four.toLoad = checkBoardSize[FOUR].isChecked();
    images.five.toLoad = checkBoardSize[FIVE].isChecked();
    images.six.toLoad = checkBoardSize[SIX].isChecked();
    images.seven.toLoad = checkBoardSize[SEVEN].isChecked();

    Options::setScaled( radioGraphic[SCALE].isChecked() );
    bool redraw = ( Options::isNumeric() ) ? true : false;

    if ( slider.value() != Options::getSquareSizeIndex() )
    {
        Options::setSquareSize( slider.value() );
        if ( redraw )
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

    if ( change == true && redraw == true )
        parent.setColor();

    close();
}

