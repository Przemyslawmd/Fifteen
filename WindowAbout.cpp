#include "WindowAbout.h"

WindowAbout::WindowAbout() : doc{}, browser{}
{
    this->setModal( true );
    this->setGeometry( 100, 100, 490, 210 );
    this->setMaximumSize( 490, 210 );
    this->setWindowTitle( "About Application");

    QVBoxLayout layout( this );
    QString html;

    HTML( "<html><head><style> p {margin-left:15px; line-height:20px;} </style></head><body><br/>" );
    HTML( "<pre>  Version:      1.1.2" );
    HTML( "<pre>  Author:       Przemyslaw Madej, Cracow 2016</pre>" );
    HTML( "<pre>  Page:         http://przemeknet.pl/fifteenEn.aspx</pre>" );
    HTML( "</body></html>" );

    doc.setHtml( html );
    browser.setDocument( &doc );
    layout.addWidget( &browser );
    this->show();
}

