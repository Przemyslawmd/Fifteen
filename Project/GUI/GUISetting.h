
#ifndef SETTING_H
#define SETTING_H

#include "Fifteen.h"
#include "Types.h"
#include "Options.h"

#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QCheckBox>
#include <QSlider>
#include <QDialog>
#include <QLabel>
#include <array>

using std::array;
using std::map;
using std::unique_ptr;

class GUISetting : public QDialog
{
public:

    GUISetting( Fifteen& owner );
    GUISetting( const GUISetting& ) = delete;
    GUISetting operator=( const GUISetting& ) = delete;

private:

    Q_OBJECT

    map< GraphicMode, QRadioButton* > mapRadioGraphicMode;
    QButtonGroup groupRadioGraphicMode;

    map< BoardSize, QCheckBox* > mapCheckImageToChose;

    map< NumberColor, QRadioButton* > mapRadioNumberOnImage;
    QButtonGroup groupRadioNumberOnImage;

    map< TileColor, QRadioButton* > mapRadioColor;
    QButtonGroup groupRadioColor;

    QSlider* slider;
    array< QLabel*, 5 > sliderLabels;

    unique_ptr< OptionsData > optionsCurrent;
    QPushButton* pushAccept;
    Fifteen& owner;

    template< typename T > T getChoosenOption( map< T, QRadioButton* >&, QButtonGroup& );

private slots:

    void acceptSettings();
};

#endif

