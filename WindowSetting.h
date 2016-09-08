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
#include <Images/ImageLoad.h>
#include <Types.h>

#define RADIOCOUNT 7
#define CHECKCOUNT 4

class WindowSetting : public QDialog
{

private:
    Q_OBJECT

    enum Radio { SCALE, CROP, BLUE, GREEN, RED };
    enum Check { FOUR, FIVE, SIX, SEVEN };

    QRadioButton radio[RADIOCOUNT];
    QCheckBox check[CHECKCOUNT];
    QSlider slider;
    QLabel sliderLabels[5];
    QPushButton accept;

    QButtonGroup groupRadioImage;
    QButtonGroup groupRadioColor;

    QGroupBox boxRadioImage;
    QGroupBox boxRadioColor;
    QGroupBox boxSquareSize;

    Color& color;
    bool& isScaled;

    ImageLoad* images;
    QMainWindow* parent;

private slots:
    void saveSettings();

public:
    WindowSetting( Color&, ImageLoad*, bool&, QMainWindow* );
};

#endif // SETTING_H
