
#ifndef GUI_SETTING_H
#define GUI_SETTING_H

#include "Fifteen.h"
#include "Types.h"
#include "Options.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QRadioButton>
#include <QSlider>

#include <memory>


class GUISetting : public QDialog
{
public:

    GUISetting( Fifteen& owner, BoardMode boardMode );
    GUISetting( const GUISetting& ) = delete;
    GUISetting operator=( const GUISetting& ) = delete;

private:

    Q_OBJECT

    std::map< GraphicMode, QRadioButton* > mapGraphicMode;
    std::map< BoardSize, QCheckBox* > mapImageToLoad;
    std::map< NumberColor, QRadioButton* > mapNumberOnImage;
    std::map< TileColor, QRadioButton* > mapTileColor;

    QSlider* slider;

    std::unique_ptr< OptionsData > currentOptions;

    Fifteen& owner;
    BoardMode boardMode;

    template< typename T > T getChoosenOption( std::map< T, QRadioButton* >&, const QButtonGroup* );

private slots:

    void acceptSettings();
};

#endif

