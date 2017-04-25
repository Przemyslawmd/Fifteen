#ifndef WINDOWABOUT_H
#define WINDOWABOUT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextDocument>
#include <QTextBrowser>

#define HTML(text) html.append(text)

class WindowAbout : public QDialog
{

public:
    WindowAbout();

private:    
    QTextBrowser browser;
    QTextDocument doc;
};

#endif // WINDOWABOUT_H
