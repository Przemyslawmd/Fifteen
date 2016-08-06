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

class WindowSetting : public QDialog
{

private:
    Q_OBJECT

    QRadioButton radioScale;
    QRadioButton radioCrop;
    QRadioButton radioBlue;
    QRadioButton radioGreen;
    QRadioButton radioRed;
    QRadioButton radioPl;
    QRadioButton radioEn;

    QButtonGroup* groupRadioImage;
    QButtonGroup* groupRadioColor;
    QButtonGroup* groupRadioLang;

    QCheckBox checkFour;
    QCheckBox checkFive;
    QCheckBox checkSix;
    QCheckBox checkSeven;

    QGroupBox* boxRadioImage;
    QGroupBox* boxRadioColor;
    QGroupBox* boxRadioLang;

    QVBoxLayout* layRadioImage;
    QVBoxLayout* layRadioColor;
    QVBoxLayout* layRadioLang;

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
