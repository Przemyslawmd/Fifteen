#include "WindowAbout.h"

WindowAbout::WindowAbout( const QMap<QString, QString>* labels ) : doc{}, browser{}
{
    this->setModal( true );
    this->setGeometry( 100, 100, 490, 210 );
    this->setMaximumSize( 490, 210 );
    this->setWindowTitle( labels->value( "about" ));

    QVBoxLayout layout( this );
    QString html;

    HTML("<html><head><style> p {margin-left:15px; line-height:20px;} </style></head><body><br/>");
    HTML(labels->value("aboutVer"));
    HTML(labels->value("aboutAuth"));
    HTML(labels->value("aboutWeb"));    
    HTML("</body></html>");

    doc.setHtml( html );
    browser.setDocument( &doc );
    layout.addWidget( &browser );
    this->show();
}

