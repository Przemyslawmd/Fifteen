
#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QColor>

enum BoardSize { FOUR = 4, FIVE, SIX, SEVEN };
enum GraphicMode { SCALED, CROPPED, GRAPHIC_MODE_COUNT };
enum class BoardMode { NUMERIC, GRAPHIC };

enum class Move         { UP, RIGHT, DOWN, LEFT, NOT_ALLOWED };
enum class TileSize     { _50, _75, _100, _125, _150 };
enum class FontSize     { _20, _25, _30,  _35,  _40 };
enum Color              { BLUE, GREEN, RED, EMPTY_STYLE };
enum NumberColor        { NO, BLACK, WHITE };

enum class Action       { OPEN_GRAPHIC, REM_GRAPHIC, SAVE_BOARD, LOAD_BOARD, SETTINGS, ABOUT };

typedef struct
{
    BoardMode boardMode;
    GraphicMode graphicMode;
    bool fourImageToBeLoaded;
    bool fiveImageToBeLoaded;
    bool sixImageToBeLoaded;
    bool sevenImageToBeLoaded;
    Color squareColor;
    int squareSizeIndex;
    NumberColor numberColor;
    bool undoEnabled;
} OptionsData;

typedef struct
{
    bool isNumberOnImage;
    QColor fontColor;
    FontSize fontSize;
} NumberOnImage;

#endif // TYPES_H

