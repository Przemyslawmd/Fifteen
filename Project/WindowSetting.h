
#ifndef SETTING_H
#define SETTING_H

#include "MainWindow.h"
#include "Types.h"
#include "Options.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QSlider>
#include <QDialog>
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

    QGroupBox boxRadioImage;

    map< Color, QRadioButton* > mapRadioColor;
    QButtonGroup groupRadioColor;
    QGroupBox boxRadioColor;

    QSlider slider;
    array< QLabel, 5 > sliderLabels;
    QGroupBox boxSquareSize;

    QCheckBox checkUndoEnabled;
    QGroupBox boxUndoEnabled;

    unique_ptr< OptionsData > optionsCurrent;
    QPushButton accept;
    MainWindow& parent;

    template< typename T > T getChoosenOption( map< T, QRadioButton* >&, QButtonGroup& );

private slots:

    void acceptSettings();
};

#endif // SETTING_H

