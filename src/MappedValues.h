
#ifndef FIFTEEN_MAPPED_VALUES_H
#define FIFTEEN_MAPPED_VALUES_H

#include <map>

#include <QString>

#include "Types.h"


class Maps
{
public:

    static const std::map<TileSize, size_t> tileSizeInt;
    static const std::map<FontSize, size_t> fontSizeInt;
    static const std::map<BoardSize, size_t> boardSizeInt;
    static const std::map<TileColor, const QString> tileColorStyle;
    static const std::map<size_t, TileSize> sliderTileSize;
    static const std::map<TileSize, FontSize> tileSizeFontSize;

    static int getFontSizeInt( TileSize tileSize );
    static BoardSize getBoardSizeByInt( size_t value );
    static TileSize getTileSizeByInt( size_t value );
    static int getSliderByTileSize( TileSize value );

private:

    template <typename T, typename U> 
    static T getMapKeyByValue( const std::map<T, U>&, U value );
};

#endif

