
#ifndef SETTING_H
#define SETTING_H

#include "MainWindow.h"
#include "Types.h"
#include "Options.h"

#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QCheckBox>
#include <QSlider>
#include <QDialog>
#include <QLabel>
#include <array>

using std::array;
using std::map;

class WindowSetting : public QDialog
{

public:

    WindowSetting( MainWindow& parentWindow );

private:

    Q_OBJECT

    map< GraphicMode, QRadioButton* > mapRadioGraphicMode;
    QButtonGroup groupRadioGraphicMode;

    map< BoardSize, QCheckBox* > mapCheckImageToChose;

    map< NumberColor, QRadioButton* > radioNumberOnImage;
    QButtonGroup groupRadioNumberOnImage;

    map< TileColor, QRadioButton* > mapRadioColor;
    QButtonGroup groupRadioColor;

    QSlider* slider;
    array< QLabel*, 5 > sliderLabels;

    QCheckBox checkUndoEnabled;

    unique_ptr< OptionsData > optionsCurrent;
    QPushButton* pushAccept;
    MainWindow& parent;

    template< typename T > T getChoosenOption( map< T, QRadioButton* >&, QButtonGroup& );

private slots:

    void acceptSettings();
};

#endif // SETTING_H

