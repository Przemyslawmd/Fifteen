
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

class MainWindow;

enum class FontColor { BLACK, WHITE };

class WindowSetting : public QDialog
{

private:
    Q_OBJECT

    array<QRadioButton, GRAPHIC_MODE_COUNT> radioGraphic;
    array<QCheckBox, 4> checkImage;

    array< QRadioButton, 3 > radioNumberOnImage;
    QButtonGroup groupRadioNumberOnImage;
    QGroupBox boxRadioNumberOnImage;

    QCheckBox checkImageText;
    QButtonGroup groupRadioImage;
    QGroupBox boxRadioImage;

    array<QRadioButton, 3> radioColor;
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

private slots:

    void acceptSettings();

public:
    WindowSetting( MainWindow& parentWindow );
};

#endif // SETTING_H

