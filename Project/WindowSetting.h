
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

class WindowSetting : public QDialog
{

private:
    Q_OBJECT

    // Indicators for radio buttons and check boxes
    enum SquareColor { BLUE, GREEN, RED, COUNT_COLOR };
    enum BoardSize_   { FOUR, FIVE, SIX, SEVEN, COUNT_SIZE };

    array<QRadioButton, GRAPHIC_MODE_COUNT> radioGraphic;
    array<QCheckBox, COUNT_SIZE> checkImage;
    QButtonGroup groupRadioImage;
    QGroupBox boxRadioImage;

    QCheckBox checkImageText;
    array<QRadioButton, 3> radioImageTextColor;
    QButtonGroup groupRadioImageTextColor;
    QGroupBox boxRadioImageText;

    array<QRadioButton, COUNT_COLOR> radioColor;
    QButtonGroup groupRadioColor;
    QGroupBox boxRadioColor;

    QSlider slider;
    array<QLabel, 5> sliderLabels;
    QGroupBox boxSquareSize;

    unique_ptr< OptionsData > messageData;
    QPushButton accept;
    MainWindow& parent;

private slots:

    // Send changes to intances of Options and ImagesState classes
    void acceptSettings();

public:
    WindowSetting( MainWindow& parentWindow );
};

#endif // SETTING_H

