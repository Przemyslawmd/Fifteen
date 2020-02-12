
#include "GUIAbout.h"
#include <QVBoxLayout>
#include <QTextDocument>

GUIAbout::GUIAbout()
{
    setModal( true );
    setMinimumSize( 500, 200 );
    setMaximumSize( 500, 200 );
    setWindowTitle( " " );
    setAttribute( Qt::WA_DeleteOnClose );

    QVBoxLayout layout( this );
    QString html;

    html.append( "<br/><pre>  Version:      1.9" );
    html.append( "<pre>  Author:       Przemyslaw Madej, Warsaw 2018</pre>" );
    html.append( "<pre>  Page:         http://przemeknet.pl/fifteen</pre>" );

    QTextDocument* doc = new QTextDocument();
    doc->setHtml( html );
    browser.setDocument( doc );
    layout.addWidget( &browser );
    show();
}

