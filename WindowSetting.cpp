#include "WindowSetting.h"

WindowSetting::WindowSetting( Color& color, ImageLoad* images, bool& isScaled, QMainWindow* parentParam ) :
    color{ color }, isScaled{ isScaled }, accept{ "Accept" },
    boxRadioImage{ "Graphic" }, boxRadioColor{ "Color of Numeric Board" }, boxSquareSize{ "Size of Square" },
    slider{ Qt::Horizontal, this }, groupRadioImage(), groupRadioColor()
{
    this->setModal( true );
    this->images = images;
    parent = parentParam;

    this->setWindowTitle( "Settings" );
    this->setGeometry( 100, 100, 400, 560 );
    this->setMaximumSize( 400, 680 );
    this->setMinimumSize( 400, 680 );

    QVBoxLayout layWindow;

    /* RADIO COLOR *********************************/

    for (int i = 0; i < RADIOCOUNT; i++)
        radio[i].setStyleSheet( "margin-left:5px;" );

    radio[Radio::SCALE].setText( "Graphic is to be scalled" );
    radio[Radio::CROP].setText( "Graphic is to be cropped" );
    radio[Radio::BLUE].setText( "Blue" );
    radio[Radio::GREEN].setText( "Green" );
    radio[Radio::RED].setText( "Red" );

    groupRadioImage.addButton( &radio[Radio::SCALE] );
    groupRadioImage.addButton( &radio[Radio::CROP] );
    radio[Radio::SCALE].setChecked( isScaled );
    radio[Radio::CROP].setChecked( !isScaled );

    groupRadioColor.addButton( &radio[Radio::BLUE] );
    groupRadioColor.addButton( &radio[Radio::GREEN] );
    groupRadioColor.addButton( &radio[Radio::RED] );

    if ( color == Color::BLUE )
        radio[Radio::BLUE].setChecked( true );
    else if ( color == Color::GREEN )
        radio[Radio::GREEN].setChecked( true );
    else
        radio[Radio::RED].setChecked( true );

    QVBoxLayout layRadioColor;
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radio[Radio::BLUE] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radio[Radio::GREEN] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radio[Radio::RED] );
    layRadioColor.addSpacing( 7 );
    boxRadioColor.setLayout( &layRadioColor );


    /* CHECKBOX IMAGE SIZE ********************************/

    for (int i = 0; i < CHECKCOUNT; i++)
        check[i].setStyleSheet( "margin-left:5px;" );

    check[Check::FOUR].setText( "Graphic is to be loaded for a board 4x4" );
    check[Check::FIVE].setText( "Graphic is to be loaded for a board 5x5" );
    check[Check::SIX].setText( "Graphic is to be loaded for a board 6x6" );
    check[Check::SEVEN].setText( "Graphic is to be loaded for a board 7x7" );

    check[Check::FOUR].setChecked( images->four.toLoad );
    check[Check::FIVE].setChecked( images->five.toLoad );
    check[Check::SIX].setChecked( images->six.toLoad );
    check[Check::SEVEN].setChecked( images->seven.toLoad );

    QVBoxLayout layRadioImage;
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &radio[Radio::SCALE] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &radio[Radio::CROP] );
    layRadioImage.addSpacing( 15 );
    layRadioImage.addWidget( &check[Check::FOUR] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &check[Check::FIVE] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &check[Check::SIX] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( &check[Check::SEVEN] );
    layRadioImage.addSpacing( 15 );
    boxRadioImage.setLayout( &layRadioImage );


    /* SLIDER SQUARE SIZE ***************************************/

    slider.setRange( 1, 5 );
    slider.setSingleStep( 1 );
    sliderLabels[0].setText( "50" );
    sliderLabels[1].setText( "100" );
    sliderLabels[2].setText( "150" );
    sliderLabels[3].setText( "200" );
    sliderLabels[4].setText( "250" );

    QGridLayout layoutSlider;
    layoutSlider.setContentsMargins( 30, 20, 30, 20 );
    layoutSlider.addWidget( &slider,          0, 0, 1, 5 );
    layoutSlider.addWidget( &sliderLabels[0], 1, 0, 1, 1, Qt::AlignLeft );
    layoutSlider.addWidget( &sliderLabels[1], 1, 1, 1, 1, Qt::AlignLeft );
    layoutSlider.addWidget( &sliderLabels[2], 1, 2, 1, 1, Qt::AlignCenter );
    layoutSlider.addWidget( &sliderLabels[3], 1, 3, 1, 1, Qt::AlignRight );
    layoutSlider.addWidget( &sliderLabels[4], 1, 4, 1, 1, Qt::AlignRight );    
    boxSquareSize.setLayout( &layoutSlider );


    /* GENERAL LAYOUT *********************************************/

    QHBoxLayout layControls;
    accept.setStyleSheet("height:20px;");
    connect( &accept, SIGNAL( clicked() ), this, SLOT( saveSettings() ));

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
    layWindow.addSpacing(10);
    layWindow.addStretch();

    this->setLayout( &layWindow );
    this->show();
}

/********************************************************************************************************************************/
/* SAVE SETTINGS ****************************************************************************************************************/

void WindowSetting::saveSettings()
{   
    if ( radio[Radio::BLUE].isChecked() )
        color = Color::BLUE;
    else if ( radio[Radio::GREEN].isChecked() )
        color = Color::GREEN;
    else
        color = Color::RED;

    images->four.toLoad = check[Check::FOUR].isChecked();
    images->five.toLoad = check[Check::FIVE].isChecked();
    images->six.toLoad = check[Check::SIX].isChecked();
    images->seven.toLoad = check[Check::SEVEN].isChecked();

    isScaled = radio[Radio::SCALE].isChecked();

    qobject_cast< MainWindow* >( parent )->setColor();
    this->close();
}
