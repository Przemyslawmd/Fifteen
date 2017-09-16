
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
#include <MainWindow.h>
#include <GraphicBoard/ImageLoad.h>
#include <Types.h>
#include <Options.h>
#include <array>

using std::array;

class MainWindow;

class WindowSetting : public QDialog
{

private:
    Q_OBJECT

    // Indicators for radio buttons and check boxes
    enum GraphicMode { SCALE, CROP, COUNT_MODE };
    enum SquareColor { BLUE, GREEN, RED, COUNT_COLOR };
    enum BoardSize   { FOUR, FIVE, SIX, SEVEN, COUNT_SIZE };

    array<QRadioButton, COUNT_COLOR> radioColor;
    array<QRadioButton, COUNT_MODE> radioGraphic;
    array<QCheckBox, COUNT_SIZE> checkBoardSize;
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

