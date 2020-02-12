
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
    static GraphicMode graphicMode;
    static TileSize tileSize;

    static FontSize getFontSize();

    static const QString& getStyle();

    static bool isImageToBeLoaded( BoardSize size );

    static unique_ptr< NumberOnImage > isNumberOnImage();
    static bool isUndoEnabled();

    static unique_ptr< OptionsData > readOptions();
    static void saveOptions( unique_ptr< OptionsData > messageData );

private:

    static TileColor currentColor;

    static std::map< BoardSize, bool > imagesToLoad;

    static NumberColor numberColor;
    static bool undoEnabled;
};

#endif // OPTIONS_H

