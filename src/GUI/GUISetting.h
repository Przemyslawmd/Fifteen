
#ifndef GUI_SETTING_H
#define GUI_SETTING_H

#include <map>

#include <QButtonGroup>
#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QRadioButton>
#include <QSlider>

#include "Fifteen.h"
#include "Types.h"
#include "Options.h"


class GUISetting : public QDialog
{
public:

    GUISetting( Fifteen& owner, BoardMode boardMode );
    GUISetting( const GUISetting& ) = delete;
    GUISetting( GUISetting&& ) = delete;
    GUISetting& operator=( const GUISetting& ) = delete;
    GUISetting& operator=( GUISetting&& ) = delete;

private:

    Q_OBJECT

    std::map<GraphicMode, QRadioButton> radioGraphicMode;
    std::map<BoardSize, QCheckBox> boxImageToLoad;
    std::map<GraphicTileCaption, QRadioButton> radioTileCaption;
    std::map<TileColor, QRadioButton> radioTileColor;

    QSlider* slider;

    OptionsData currentOptions;

    Fifteen& owner;
    BoardMode boardMode;

private slots:

    void acceptSettings();
};

#endif

