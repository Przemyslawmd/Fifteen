#ifndef WINDOWABOUT_H
#define WINDOWABOUT_H

#include <QMap>
#include <QDialog>
#include <QVBoxLayout>
#include <QTextDocument>
#include <QTextBrowser>

#define HTML(text) html.append(text)

class WindowAbout : public QDialog
{
public:
    WindowAbout( const QMap<QString, QString>* );
};

#endif // WINDOWABOUT_H
