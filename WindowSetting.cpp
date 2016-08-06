#include "WindowSetting.h"

WindowSetting::WindowSetting( Color& color, ImageLoad* images, bool& isScaled, bool& isPl, QMainWindow* parentParam, const QMap<QString, QString>* labels ) :
    color( color ), isScaled( isScaled ), isPl( isPl ), accept{ labels->value("acc") },
    boxRadioImage( labels->value("graphic")), boxRadioLang(labels->value("lan")),boxRadioColor(labels->value("color")),
    groupRadioImage(), groupRadioColor(), groupRadioLang()
{
    this->setModal(true);
    this->images = images;
    parent = parentParam;

    this->setWindowTitle(labels->value("title"));
    this->setGeometry(100,100,400,660);
    this->setMaximumSize(400,660);
    this->setMinimumSize(400,660);

    QVBoxLayout layWindow;

    // PREPARE RADIO CONTROLS ////////////////////////////////

    for (int i = 0; i < RADIOCOUNT; i++)
        radio[i].setStyleSheet( "margin-left:5px;" );

    radio[Radio::SCALE].setText( labels->value( "graphicScal" ));
    radio[Radio::CROP].setText( labels->value( "graphicCrop" ));
    radio[Radio::BLUE].setText( labels->value( "colorB" ));
    radio[Radio::GREEN].setText( labels->value( "colorG" ));
    radio[Radio::RED].setText( labels->value( "colorR" ));
    radio[Radio::PL].setText( labels->value( "pol" ));
    radio[Radio::EN].setText( labels->value( "eng"));

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

    groupRadioLang.addButton( &radio[Radio::PL] );
    groupRadioLang.addButton( &radio[Radio::EN] );

    radio[Radio::PL].setChecked( isPl );
    radio[Radio::EN].setChecked( !isPl );


    // PREPARE CHECKBOX CONTROLS /////////////////////////////

    for (int i = 0; i < CHECKCOUNT; i++)
        check[i].setStyleSheet( "margin-left:5px;" );

    check[Check::FOUR].setText( labels->value( "graphic4" ));
    check[Check::FIVE].setText( labels->value( "graphic5" ));
    check[Check::SIX].setText( labels->value( "graphic6" ));
    check[Check::SEVEN].setText( labels->value( "graphic7" ));

    check[Check::FOUR].setChecked( images->four.toLoad );
    check[Check::FIVE].setChecked( images->five.toLoad );
    check[Check::SIX].setChecked( images->six.toLoad );
    check[Check::SEVEN].setChecked( images->seven.toLoad );


    // PREPARE LAYOUT ////////////////////////////////////////

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


    QVBoxLayout layRadioColor;
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radio[Radio::BLUE] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radio[Radio::GREEN] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radio[Radio::RED] );
    layRadioColor.addSpacing( 7 );

    boxRadioColor.setLayout( &layRadioColor );


    QVBoxLayout layRadioLang;
    layRadioLang.addSpacing(7);
    layRadioLang.addWidget( &radio[Radio::PL] );
    layRadioLang.addSpacing(7);
    layRadioLang.addWidget( &radio[Radio::EN] );
    layRadioLang.addSpacing(7);

    boxRadioLang.setLayout( &layRadioLang );


    QHBoxLayout layControls;
    accept.setStyleSheet("height:20px;");
    connect( &accept, SIGNAL(clicked()), this, SLOT( saveSettings()) );

    layControls.addSpacing( 120 );
    layControls.addWidget( &accept );
    layControls.addSpacing( 120 );

    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxRadioImage );
    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxRadioColor);
    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxRadioLang);
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
    isPl = radio[Radio::PL].isChecked();

    MainWindow* parent2 = qobject_cast< MainWindow* >( parent );

    parent2->setText();
    parent2->setColor();
    this->close();
}
