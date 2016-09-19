#include "WindowAbout.h"

WindowAbout::WindowAbout()
{
    setModal( true );
    setGeometry( 100, 100, 490, 180 );
    setMaximumSize( 490, 180 );
    setWindowTitle( " ");

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
    show();
}

