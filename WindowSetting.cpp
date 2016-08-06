#include "WindowSetting.h"

WindowSetting::WindowSetting( Color& color, ImageLoad* images, bool* isScaled, bool* isPl, QMainWindow* parentParam, const QMap<QString, QString>* labels ) :
    color( color ),
    radioScale{ labels->value("graphicScal") }, radioCrop{ labels->value("graphicCrop") },
    radioBlue{ labels->value("colorB") }, radioGreen{ labels->value("colorG")}, radioRed{ labels->value("colorR")},
    radioPl{ labels->value("pol") }, radioEn{ labels->value("eng")},
    checkFour{ labels->value("graphic4")} , checkFive{ labels->value("graphic5")}, checkSix{ labels->value("graphic6")}, checkSeven{ labels->value("graphic7")},
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


    radioScale.setStyleSheet( "margin-left:5px;" );
    radioCrop.setStyleSheet( "margin-left:5px;" );
    if ( *isScaled )
        radioScale.setChecked( true);
    else
        radioCrop.setChecked( true );

    groupRadioImage = new QButtonGroup();
    groupRadioImage->addButton( &radioScale );
    groupRadioImage->addButton( &radioCrop );


    checkFour.setStyleSheet( "margin-left:5px;" );
    if ( images->four.toLoad == true )
        checkFour.setChecked( true );

    checkFive.setStyleSheet( "margin-left:5px;" );
    if ( images->five.toLoad == true )
        checkFive.setChecked( true );

    checkSix.setStyleSheet( "margin-left:5px;" );
    if ( images->six.toLoad == true )
        checkSix.setChecked( true );

    checkSeven.setStyleSheet( "margin-left:5px;" );
    if ( images->seven.toLoad == true )
        checkSeven.setChecked( true );


    layRadioImage = new QVBoxLayout();
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget( &radioScale );
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget( &radioCrop );
    layRadioImage->addSpacing(15);
    layRadioImage->addWidget( &checkFour );
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget( &checkFive );
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget( &checkSix );
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget( &checkSeven );
    layRadioImage->addSpacing(15);

    boxRadioImage.setLayout( layRadioImage );

    radioBlue.setStyleSheet( "margin-left:5px;" );
    radioGreen.setStyleSheet( "margin-left:5px;" );
    radioRed.setStyleSheet( "margin-left:5px;" );

    if ( color == Color::BLUE )
        radioBlue.setChecked(true);
    else if ( color == Color::GREEN )
        radioGreen.setChecked(true);
    else
        radioRed.setChecked(true);

    groupRadioColor = new QButtonGroup();
    groupRadioColor->addButton( &radioBlue );
    groupRadioColor->addButton( &radioGreen );
    groupRadioColor->addButton( &radioRed );

    QVBoxLayout layRadioColor;
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radioBlue );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radioGreen );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( &radioRed );
    layRadioColor.addSpacing( 7 );

    boxRadioColor.setLayout( &layRadioColor );

    // LANGUAGE /////////////////////////////////////////////////////////////////////////    
    radioPl.setStyleSheet("margin-left:5px;");
    radioEn.setStyleSheet("margin-left:5px;");

    if ( *isPl )
        radioPl.setChecked( true );
    else
        radioEn.setChecked( true );

    groupRadioLang = new QButtonGroup();
    groupRadioLang->addButton( &radioPl);
    groupRadioLang->addButton( &radioEn);

    QVBoxLayout layRadioLang;
    layRadioLang.addSpacing(7);
    layRadioLang.addWidget( &radioPl );
    layRadioLang.addSpacing(7);
    layRadioLang.addWidget( &radioEn );
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
    if ( radioBlue.isChecked() )
        color = Color::BLUE;
    else if ( radioGreen.isChecked() )
        color = Color::GREEN;
    else
        color = Color::RED;

    images->four.toLoad = ( checkFour.isChecked() ) ? true : false;
    images->five.toLoad = ( checkFive.isChecked() ) ? true : false;
    images->six.toLoad = ( checkSix.isChecked() ) ? true : false;
    images->seven.toLoad = ( checkSeven.isChecked() ) ? true : false;

    *isScaled = ( radioScale.isChecked() ) ? true : false;
    *isPl = ( radioPl.isChecked() ) ? true : false;

    MainWindow* parent2 = qobject_cast<MainWindow*>(parent);

    parent2->setText();
    parent2->setColor();
    this->close();
}
