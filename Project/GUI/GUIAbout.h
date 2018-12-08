
#ifndef WINDOWABOUT_H
#define WINDOWABOUT_H

#include <QDialog>
#include <QTextBrowser>

class WindowAbout : public QDialog
{

public:
    WindowAbout();

private:
    QTextBrowser browser;
};

#endif // WINDOWABOUT_H

