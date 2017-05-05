
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

class MainWindow;

class WindowSetting : public QDialog
{

private:
    Q_OBJECT

    // Indicators for radio buttons and check boxes
    enum Radio { SCALE, CROP, BLUE, GREEN, RED, RADIOCOUNT };
    enum Check { FOUR, FIVE, SIX, SEVEN, CHECKCOUNT };

    QRadioButton radio[RADIOCOUNT];
    QCheckBox check[CHECKCOUNT];
    QSlider slider;
    QLabel sliderLabels[5];
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
