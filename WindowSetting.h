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
#define CHECKCOUNT 4

class WindowSetting : public QDialog
{

private:
    Q_OBJECT

    enum Radio { SCALE, CROP, BLUE, GREEN, RED, PL, EN };
    enum Check { FOUR, FIVE, SIX, SEVEN };

    QRadioButton radio[RADIOCOUNT];
    QCheckBox check[CHECKCOUNT];
    QPushButton accept;

    QButtonGroup groupRadioImage;
    QButtonGroup groupRadioColor;
    QButtonGroup groupRadioLang;

    QGroupBox boxRadioImage;
    QGroupBox boxRadioColor;
    QGroupBox boxRadioLang;

    Color& color;
    bool& isScaled;
    bool& isPl;
    ImageLoad* images;
    QMainWindow* parent;

private slots:
    void saveSettings();

public:
    WindowSetting( Color&, ImageLoad*, bool&, bool&, QMainWindow*, const QMap<QString, QString>* );
};

#endif // SETTING_H
