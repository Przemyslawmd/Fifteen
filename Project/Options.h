
#ifndef OPTIONS_H
#define OPTIONS_H

#include "Types.h"
#include <QString>
#include <QColor>
#include <map>
#include <memory>

using std::unique_ptr;

class Options
{
public:

    static BoardMode boardMode;

    static TileSize getTileSize();
    static FontSize getFontSize();

    static GraphicMode getGraphicMode();

    static const QString& getStyle();
    static const QString& getEmptyStyle();

    static bool isImageToBeLoaded( BoardSize size );

    static unique_ptr< NumberOnImage > isNumberOnImage();
    static bool isUndoEnabled();

    static unique_ptr< OptionsData > sendData();
    static void receiveData( unique_ptr< OptionsData > messageData );

private:

    static GraphicMode graphicMode;

    static TileSize tileSize;
    static TileColor currentColor;

    static std::map< BoardSize, bool > imagesToLoad;

    static NumberColor numberColor;
    static bool undoEnabled;
};

#endif // OPTIONS_H

