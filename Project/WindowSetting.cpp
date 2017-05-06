
#include "WindowSetting.h"

WindowSetting::WindowSetting( ImagesState& images, MainWindow& parent ) :
    slider{ Qt::Horizontal, this }, accept{ "Accept" },
    boxRadioColor{ "Color of Numeric Board" }, boxRadioImage{ "Graphic" }, boxSquareSize{ "Size of Square" },
    groupRadioImage(), groupRadioColor(), images( images ), parent( parent )
{
    setModal( true );    
    setWindowTitle( " " );
    setGeometry( 100, 100, 400, 560 );
    setMaximumSize( 400, 680 );
    setMinimumSize( 400, 680 );

    QVBoxLayout layWindow;

    /* Radio controls **********************************************/

    for ( int i = 0; i < countColor; i++ )
        radioColor[i].setStyleSheet( "margin-left:5px;" );

    for ( int i = 0; i < countGraphic; i++ )
        radioGraphic[i].setStyleSheet( "margin-left:5px;" );

    radioGraphic[scale].setText( "Graphic is to be scalled" );
    radioGraphic[crop].setText( "Graphic is to be cropped" );
    radioColor[blue].setText( "Blue" );
    radioColor[green].setText( "Green" );
    radioColor[red].setText( "Red" );

    groupRadioImage.addButton( &radioGraphic[scale] );
    groupRadioImage.addButton( &radioGraphic[crop] );

    radioGraphic[scale].setChecked( Options::checkScaled() );
    radioGraphic[crop].setChecked( !Options::checkScaled() );

    groupRadioColor.addButton( &radioColor[blue] );
    groupRadioColor.addButton( &radioColor[green] );
    groupRadioColor.addButton( &radioColor[red] );

    radioColor[ Options::getColor() ].setChecked( true );

    QVBoxLayout layRadioColor;
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radioColor[blue] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radioColor[green] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radioColor[red] );
    layRadioColor.addSpacing( 7 );
    boxRadioColor.setLayout( &layRadioColor );


    /* Checkbox for images praparing  ********************************/

    for ( int i = 0; i < countBoard; i++ )
        checkBoardSize[i].setStyleSheet( "margin-left:5px;" );

    checkBoardSize[four].setText( "Graphic is to be loaded for a board 4x4" );
    checkBoardSize[five].setText( "Graphic is to be loaded for a board 5x5" );
    checkBoardSize[six].setText( "Graphic is to be loaded for a board 6x6" );
    checkBoardSize[seven].setText( "Graphic is to be loaded for a board 7x7" );

    checkBoardSize[four].setChecked( images.four.toLoad );
    checkBoardSize[five].setChecked( images.five.toLoad );
    checkBoardSize[six].setChecked( images.six.toLoad );
    checkBoardSize[seven].setChecked( images.seven.toLoad );

    QVBoxLayout layRadioImage;
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &radioGraphic[scale] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &radioGraphic[crop] );
    layRadioImage.addSpacing( 15 );
    layRadioImage.addWidget( &checkBoardSize[four] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &checkBoardSize[five] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &checkBoardSize[six] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &checkBoardSize[seven] );
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
    images.four.toLoad = checkBoardSize[four].isChecked();
    images.five.toLoad = checkBoardSize[five].isChecked();
    images.six.toLoad = checkBoardSize[six].isChecked();
    images.seven.toLoad = checkBoardSize[seven].isChecked();

    Options::setScaled( radioGraphic[scale].isChecked() );
    bool redraw = ( Options::checkNumeric() ) ? true : false;

    if ( slider.value() != Options::getSquareSizeIndex() )
    {
        Options::setSquareSize( slider.value() );
        if ( redraw )
            parent.redrawSquares();
    }

    bool change = false;
    if ( radioColor[blue].isChecked() && Options::getColor() != Color::BLUE )
    {
        Options::setColor( Color::BLUE );
        change = true;
    }
    else if ( radioColor[green].isChecked() && Options::getColor() != Color::GREEN )
    {
        Options::setColor( Color::GREEN );
        change = true;
    }
    else if ( radioColor[red].isChecked() && Options::getColor() != Color::RED )
    {
        Options::setColor( Color::RED );
        change = true;
    }

    if ( change == true && redraw == true )
        parent.setColor();

    close();
}

