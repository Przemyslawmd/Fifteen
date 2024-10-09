
#include "GUIAbout.h"

#include <QVBoxLayout>
#include <QTextDocument>
#include <QTextBrowser>


GUIAbout::GUIAbout()
{
    setModal( true );
    setMinimumSize( 500, 170 );
    setMaximumSize( 500, 170 );
    setWindowTitle( " " );
    setAttribute( Qt::WA_DeleteOnClose );

    QVBoxLayout layout( this );
    QString html;

    html.append( "<br/><pre>  Author:       Przemyslaw Madej</pre>" );
    html.append( "<pre>  Web page:     http://przemeknet.pl/fifteen.html</pre>" );

    QTextDocument* doc = new QTextDocument( this );
    doc->setHtml( html );
    QTextBrowser* browser = new QTextBrowser( this );
    browser->setDocument( doc );
    layout.addWidget( browser );
    show();
}

