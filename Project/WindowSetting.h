
#ifndef SETTING_H
#define SETTING_H

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
#include "MainWindow.h"
#include "Types.h"
#include "Options.h"

using std::array;
using std::map;

class MainWindow;

class WindowSetting : public QDialog
{

private:
    Q_OBJECT

    map< GraphicMode, QRadioButton* > mapRadioGraphicMode;
    QButtonGroup groupRadioGraphicMode;

    map< BoardSize, QCheckBox* > checkImage;

    map< NumberColor, QRadioButton* > radioNumberOnImage;
    QButtonGroup groupRadioNumberOnImage;
    QGroupBox boxRadioNumberOnImage;


    QGroupBox boxRadioImage;

    map< Color, QRadioButton* > radioColor;
    QButtonGroup groupRadioColor;
    QGroupBox boxRadioColor;

    QSlider slider;
    array<QLabel, 5> sliderLabels;
    QGroupBox boxSquareSize;

    QCheckBox checkUndoEnabled;
    QGroupBox boxUndoEnabled;

    unique_ptr< OptionsData > optionsCurrent;
    QPushButton accept;
    MainWindow& parent;

    template< typename T > T getChoosenOption( map< T, QRadioButton* >&, QButtonGroup& );

private slots:

    void acceptSettings();

public:
    WindowSetting( MainWindow& parentWindow );
};

#endif // SETTING_H

