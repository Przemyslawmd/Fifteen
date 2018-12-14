
#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QColor>
#include <map>

enum class BoardSize    { FOUR, FIVE, SIX, SEVEN };
enum class GraphicMode  { SCALED, CROPPED };
enum class BoardMode    { NUMERIC, GRAPHIC };
enum class Move         { UP, RIGHT, DOWN, LEFT, NOT_ALLOWED };
enum class TileSize     { _50, _75, _100, _125, _150 };
enum class TileColor    { BLUE, GREEN, RED, EMPTY_STYLE };
enum class FontSize     { _20, _25, _30, _35, _40 };
enum class NumberColor  { NO, BLACK, WHITE };
enum class Action       { OPEN_GRAPHIC, REM_GRAPHIC, SAVE_BOARD, LOAD_BOARD, SETTINGS, ABOUT };


typedef struct
{
    BoardMode boardMode;
    GraphicMode graphicMode;
    bool imageToLoad_4;
    bool imageToLoad_5;
    bool imageToLoad_6;
    bool imageToLoad_7;
    TileColor squareColor;
    TileSize tileSize;
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

