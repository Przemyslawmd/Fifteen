#include "WindowSetting.h"

WindowSetting::WindowSetting( Color& color, ImageLoad* images, bool* isScaled, bool* isPl, QMainWindow* parentParam, const QMap<QString, QString>* labels ) :
    color( color ),
    boxRadioImage( labels->value("graphic")), boxRadioLang(labels->value("lan")),boxRadioColor(labels->value("color"))
{
    this->setModal(true);
    this->images = images;
    this->isScaled = isScaled;
    this->isPl = isPl;
    parent = parentParam;

    this->setWindowTitle(labels->value("title"));
    this->setGeometry(100,100,400,660);
    this->setMaximumSize(400,660);
    this->setMinimumSize(400,660);

    QVBoxLayout layWindow;

    for (int i = 0; i < RADIOCOUNT; i++)
        radio[i].setStyleSheet( "margin-left:5px;" );

    radio[Radio::SCALE].setText( labels->value( "graphicScal" ));
    radio[Radio::CROP].setText( labels->value( "graphicCrop" ));
    radio[Radio::BLUE].setText( labels->value( "colorB" ));
    radio[Radio::GREEN].setText( labels->value( "colorG" ));
    radio[Radio::RED].setText( labels->value( "colorR" ));
    radio[Radio::PL].setText( labels->value( "pol" ));
    radio[Radio::EN].setText( labels->value( "eng"));


    for (int i = 0; i < CHECKCOUNT; i++)
        check[i].setStyleSheet( "margin-left:5px;" );

    check[Check::FOUR].setText(labels->value("graphic4"));
    check[Check::FIVE].setText(labels->value("graphic5"));
    check[Check::SIX].setText(labels->value("graphic6"));
    check[Check::SEVEN].setText(labels->value("graphic7"));


    if ( *isScaled )
        radio[Radio::SCALE].setChecked( true);
    else
        radio[Radio::CROP].setChecked( true );

    groupRadioImage = new QButtonGroup();
    groupRadioImage->addButton( &radio[Radio::SCALE] );
    groupRadioImage->addButton( &radio[Radio::CROP] );


    if ( images->four.toLoad == true )
        check[Check::FOUR].setChecked( true );

    if ( images->five.toLoad == true )
        check[Check::FIVE].setChecked( true );

    if ( images->six.toLoad == true )
        check[Check::SIX].setChecked( true );

    if ( images->seven.toLoad == true )
       check[Check::SEVEN].setChecked( true );


    layRadioImage = new QVBoxLayout();
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget( &radio[Radio::SCALE] );
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget( &radio[Radio::CROP] );
    layRadioImage->addSpacing(15);
    layRadioImage->addWidget( &check[Check::FOUR] );
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget( &check[Check::FIVE] );
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget( &check[Check::SIX] );
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget( &check[Check::SEVEN] );
    layRadioImage->addSpacing(15);

    boxRadioImage.setLayout( layRadioImage );

    if ( color == Color::BLUE )
        radio[Radio::BLUE].setChecked( true );
    else if ( color == Color::GREEN )
        radio[Radio::GREEN].setChecked( true );
    else
        radio[Radio::RED].setChecked( true );

    groupRadioColor = new QButtonGroup();
    groupRadioColor->addButton( &radio[Radio::BLUE] );
    groupRadioColor->addButton( &radio[Radio::GREEN] );
    groupRadioColor->addButton( &radio[Radio::RED] );

    QVBoxLayout layRadioColor;
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radio[Radio::BLUE] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radio[Radio::GREEN] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radio[Radio::RED] );
    layRadioColor.addSpacing( 7 );

    boxRadioColor.setLayout( &layRadioColor );

    // LANGUAGE /////////////////////////////////////////////////////////////////////////    

    if ( *isPl )
        radio[Radio::PL].setChecked( true );
    else
        radio[Radio::EN].setChecked( true );

    groupRadioLang = new QButtonGroup();
    groupRadioLang->addButton( &radio[Radio::PL] );
    groupRadioLang->addButton( &radio[Radio::EN] );

    QVBoxLayout layRadioLang;
    layRadioLang.addSpacing(7);
    layRadioLang.addWidget( &radio[Radio::PL] );
    layRadioLang.addSpacing(7);
    layRadioLang.addWidget( &radio[Radio::EN] );
    layRadioLang.addSpacing(7);


    boxRadioLang.setLayout( &layRadioLang );

    // CONTROLS /////////////////////////////////////////////////////////////////////////

    layControls = new QHBoxLayout();
    pushAccept = new QPushButton(labels->value("acc"));
    pushAccept->setStyleSheet("height:20px;");
    connect(pushAccept, SIGNAL(clicked()), this, SLOT(setColor()));

    layControls->addSpacing(120);
    layControls->addWidget(pushAccept);
    layControls->addSpacing(120);

    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxRadioImage );
    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxRadioColor);
    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxRadioLang);
    layWindow.addSpacing( 20 );
    layWindow.addLayout(layControls);
    layWindow.addSpacing(10);
    layWindow.addStretch();

    this->setLayout( &layWindow );
    this->show();
}

/*******************************************************************************************************************************/
/*******************************************************************************************************************************/

WindowSetting::~WindowSetting(){}

/********************************************************************************************************************************/
/* SETS NUMBER SQUARE COLOR *****************************************************************************************************/

void WindowSetting::setColor()
{   
    if ( radio[Radio::BLUE].isChecked() )
        color = Color::BLUE;
    else if ( radio[Radio::GREEN].isChecked() )
        color = Color::GREEN;
    else
        color = Color::RED;

    images->four.toLoad = ( check[Check::FOUR].isChecked() ) ? true : false;
    images->five.toLoad = ( check[Check::FIVE].isChecked() ) ? true : false;
    images->six.toLoad = ( check[Check::SIX].isChecked() ) ? true : false;
    images->seven.toLoad = ( check[Check::SEVEN].isChecked() ) ? true : false;

    *isScaled = ( radio[Radio::SCALE].isChecked() ) ? true : false;
    *isPl = ( radio[Radio::PL].isChecked() ) ? true : false;

    MainWindow* parent2 = qobject_cast<MainWindow*>(parent);

    parent2->setText();
    parent2->setColor();
    this->close();
}
