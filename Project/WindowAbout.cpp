
#include "WindowAbout.h"

WindowAbout::WindowAbout()
{
    setModal( true );
    setGeometry( 100, 100, 520, 200 );
    setMaximumSize( 520, 200 );
    setWindowTitle( " " );

    QVBoxLayout layout( this );
    QString html;

    HTML( "<br/><pre>  Version:      1.2.1" );
    HTML( "<pre>  Author:       Przemyslaw Madej, Warsaw 2017</pre>" );
    HTML( "<pre>  Page:         http://przemeknet.pl/fifteenEn.aspx</pre>" );

    doc.setHtml( html );
    browser.setDocument( &doc );
    layout.addWidget( &browser );
    show();
}
