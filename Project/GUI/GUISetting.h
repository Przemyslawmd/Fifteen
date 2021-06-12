
#ifndef GUI_SETTING_H
#define GUI_SETTING_H

#include <memory>

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

    GUISetting( Fifteen& owner );
    GUISetting( const GUISetting& ) = delete;
    GUISetting operator=( const GUISetting& ) = delete;

private:

    Q_OBJECT

    std::map< GraphicMode, QRadioButton* > mapRadioGraphicMode;

    std::map< BoardSize, QCheckBox* > mapCheckImageToChose;

    std::map< NumberColor, QRadioButton* > mapRadioNumberOnImage;
    QButtonGroup groupRadioNumberOnImage;

    std::map< TileColor, QRadioButton* > mapRadioColor;
    QButtonGroup groupRadioColor;

    QSlider* slider;

    std::unique_ptr< OptionsData > optionsCurrent;

    Fifteen& owner;

    template< typename T > T getChoosenOption( map< T, QRadioButton* >&, QButtonGroup& );

private slots:

    void acceptSettings();
};

#endif

