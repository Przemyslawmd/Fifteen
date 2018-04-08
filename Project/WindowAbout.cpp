
#include "WindowAbout.h"

WindowAbout::WindowAbout()
{
    setModal( true );
    setMinimumSize( 500, 200 );
    setMaximumSize( 500, 200 );
    setWindowTitle( " " );

    QVBoxLayout layout( this );
    QString html;

    html.append( "<br/><pre>  Version:      1.4.0" );
    html.append( "<pre>  Author:       Przemyslaw Madej, Warsaw 2018</pre>" );
    html.append( "<pre>  Page:         http://przemeknet.pl/fifteen</pre>" );

    doc.setHtml( html );
    browser.setDocument( &doc );
    layout.addWidget( &browser );
    show();
}
