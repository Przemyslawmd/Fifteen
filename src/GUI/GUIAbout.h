
#ifndef GUI_ABOUT_H
#define GUI_ABOUT_H

#include <QDialog>


class GUIAbout : public QDialog
{
public:

    GUIAbout();
    GUIAbout( const GUIAbout& ) = delete;
    GUIAbout operator=( const GUIAbout& ) = delete;
};

#endif

