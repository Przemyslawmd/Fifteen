#ifndef SETTING_H
#define SETTING_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QDialog>
#include <MainWindow.h>
#include <ImageLoad.h>
#include <Types.h>

#define RADIOCOUNT 7

class WindowSetting : public QDialog
{

private:
    Q_OBJECT

    enum Radio { SCALE, CROP, BLUE, GREEN, RED, PL, EN };

    QRadioButton radio[RADIOCOUNT];

    QButtonGroup* groupRadioImage;
    QButtonGroup* groupRadioColor;
    QButtonGroup* groupRadioLang;

    QCheckBox checkFour;
    QCheckBox checkFive;
    QCheckBox checkSix;
    QCheckBox checkSeven;

    QGroupBox boxRadioImage;
    QGroupBox boxRadioColor;
    QGroupBox boxRadioLang;

    QVBoxLayout* layRadioImage;

    QHBoxLayout* layControls;

    QPushButton* pushAccept;

    Color& color;
    bool* isScaled;
    bool* isPl;
    ImageLoad* images;
    QMainWindow* parent;

private slots:
    void setColor();

public:
    WindowSetting( Color&, ImageLoad*, bool*, bool*, QMainWindow*, const QMap<QString, QString>* );
    ~WindowSetting();

};

#endif // SETTING_H
