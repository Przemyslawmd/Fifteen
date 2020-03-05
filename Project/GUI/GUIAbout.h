
#ifndef GUI_ABOUT_H
#define GUI_ABOUT_H

#include <QDialog>
#include <QTextBrowser>

class GUIAbout : public QDialog
{
public:

    GUIAbout();

private:

    QTextBrowser browser;
};

#endif

