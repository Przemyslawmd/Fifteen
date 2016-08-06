#include "WindowSetting.h"

WindowSetting::WindowSetting( Color& color, ImageLoad* images, bool* isScaled, bool* isPl, QMainWindow* parentParam, const QMap<QString, QString>* labels ) : color( color )
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


    // RADIO IMAGE ///////////////////////////////////////////////////////////////////////////////////////

    radioScale = new QRadioButton( labels->value("graphicScal") );
    radioScale->setStyleSheet( "margin-left:5px;" );
    radioCrop = new QRadioButton( labels->value("graphicCrop") );
    radioCrop->setStyleSheet( "margin-left:5px;" );
    if ( *isScaled )
        radioScale->setChecked( true);
    else
        radioCrop->setChecked( true );


    checkFour = new QCheckBox( labels->value("graphic4") );
    checkFour->setStyleSheet( "margin-left:5px;" );
    if ( images->four.toLoad == true )
        checkFour->setChecked( true );

    checkFive = new QCheckBox( labels->value("graphic4") );
    checkFive->setStyleSheet( "margin-left:5px;" );
    if ( images->five.toLoad == true )
        checkFive->setChecked( true );

    checkSix = new QCheckBox( labels->value("graphic4") );
    checkSix->setStyleSheet( "margin-left:5px;" );
    if ( images->six.toLoad == true )
        checkSix->setChecked( true );

    checkSeven = new QCheckBox( labels->value("graphic4") );
    checkSeven->setStyleSheet( "margin-left:5px;" );
    if ( images->seven.toLoad == true )
        checkSeven->setChecked( true );

    groupRadioImage = new QButtonGroup();
    groupRadioImage->addButton(radioScale);
    groupRadioImage->addButton(radioCrop);


    layRadioImage = new QVBoxLayout();
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget(radioScale);
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget(radioCrop);
    layRadioImage->addSpacing(15);
    layRadioImage->addWidget(checkFour);
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget(checkFive);
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget(checkSix);
    layRadioImage->addSpacing(8);
    layRadioImage->addWidget(checkSeven);
    layRadioImage->addSpacing(15);


    boxRadioImage = new QGroupBox(labels->value("graphic"));
    boxRadioImage->setLayout( layRadioImage );


    // RADIO COLOR //////////////////////////////////////////////////////////////////////////////////////

    radioBlue = new QRadioButton(labels->value("colorB"));
    radioBlue->setStyleSheet("margin-left:5px;");    
    radioGreen = new QRadioButton(labels->value("colorG"));
    radioGreen->setStyleSheet("margin-left:5px;");
    radioRed = new QRadioButton(labels->value("colorR"));
    radioRed->setStyleSheet("margin-left:5px;");

    if ( color == Color::BLUE )
        radioBlue->setChecked(true);
    else if ( color == Color::GREEN )
        radioGreen->setChecked(true);
    else
        radioRed->setChecked(true);

    groupRadioColor = new QButtonGroup();
    groupRadioColor->addButton(radioBlue);
    groupRadioColor->addButton(radioGreen);
    groupRadioColor->addButton(radioRed);

    layRadioColor = new QVBoxLayout();
    layRadioColor->addSpacing(7);
    layRadioColor->addWidget(radioBlue);
    layRadioColor->addSpacing(7);
    layRadioColor->addWidget(radioGreen);
    layRadioColor->addSpacing(7);
    layRadioColor->addWidget(radioRed);
    layRadioColor->addSpacing(7);

    boxRadioColor = new QGroupBox(labels->value("color"));
    boxRadioColor->setLayout(layRadioColor);

    // LANGUAGE /////////////////////////////////////////////////////////////////////////

    radioPl = new QRadioButton(labels->value("pol"));
    radioPl->setStyleSheet("margin-left:5px;");
    radioEn = new QRadioButton(labels->value("eng"));
    radioEn->setStyleSheet("margin-left:5px;");

    if (*isPl) radioPl->setChecked(true);
    else radioEn->setChecked(true);

    groupRadioLang = new QButtonGroup();
    groupRadioLang->addButton(radioPl);
    groupRadioLang->addButton(radioEn);

    layRadioLang = new QVBoxLayout();
    layRadioLang->addSpacing(7);
    layRadioLang->addWidget(radioPl);
    layRadioLang->addSpacing(7);
    layRadioLang->addWidget(radioEn);
    layRadioLang->addSpacing(7);

    boxRadioLang = new QGroupBox(labels->value("lan"));
    boxRadioLang->setLayout(layRadioLang);

    // CONTROLS /////////////////////////////////////////////////////////////////////////

    layControls = new QHBoxLayout();
    pushAccept = new QPushButton(labels->value("acc"));
    pushAccept->setStyleSheet("height:20px;");
    connect(pushAccept, SIGNAL(clicked()), this, SLOT(setColor()));

    layControls->addSpacing(120);
    layControls->addWidget(pushAccept);
    layControls->addSpacing(120);

    layWindow.addSpacing(20);
    layWindow.addWidget(boxRadioImage);
    layWindow.addSpacing(20);
    layWindow.addWidget(boxRadioColor);
    layWindow.addSpacing(20);
    layWindow.addWidget(boxRadioLang);
    layWindow.addSpacing(20);
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
    if (radioBlue->isChecked())
        color = Color::BLUE;
    else if (radioGreen->isChecked())
        color = Color::GREEN;
    else
        color = Color::RED;

    images->four.toLoad = ( checkFour->isChecked() ) ? true : false;
    images->five.toLoad = ( checkFive->isChecked() ) ? true : false;
    images->six.toLoad = ( checkSix->isChecked() ) ? true : false;
    images->seven.toLoad = ( checkSeven->isChecked() ) ? true : false;

    *isScaled = (radioScale->isChecked()) ? true : false;
    *isPl = (radioPl->isChecked()) ? true : false;

    MainWindow* parent2 = qobject_cast<MainWindow*>(parent);

    parent2->setText();
    parent2->setColor();
    this->close();
}
