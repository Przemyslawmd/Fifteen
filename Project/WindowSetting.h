
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
#include "GraphicBoard/ImageLoad.h"
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

    array<QRadioButton, COUNT_COLOR> radioColor;
    array<QRadioButton, GRAPHIC_MODE_COUNT> radioGraphic;
    array<QCheckBox, COUNT_SIZE> checkImage;
    QSlider slider;
    array<QLabel, 5> sliderLabels;
    QPushButton accept;    

    QGroupBox boxRadioColor;
    QGroupBox boxRadioImage;
    QGroupBox boxSquareSize;

    QButtonGroup groupRadioImage;
    QButtonGroup groupRadioColor;

    // Reference to a class that stores state of images
    // This window sets there for what board dimensions an image is to be loaded
    ImagesState& images;

    MainWindow& parent;

private slots:

    // Send changes to intances of Options and ImagesState classes
    void acceptSettings();

public:
    WindowSetting( ImagesState& imagesState, MainWindow& parentWindow );
};

#endif // SETTING_H

