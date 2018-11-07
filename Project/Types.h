
#ifndef TYPES_H
#define TYPES_H

#include <QString>

enum BoardSize { FOUR = 4, FIVE, SIX, SEVEN };
enum GraphicMode { SCALED, CROPPED, GRAPHIC_MODE_COUNT };
enum class BoardMode { NUMERIC, GRAPHIC };

enum Move            { UP, RIGHT, DOWN, LEFT, NOT_ALLOWED };
enum SquareSize      { _50 = 50, _75 = 75, _100 = 100, _125 = 125, _150 = 150 };
enum FontSize        { _20 = 20, _25 = 25, _30  = 30,  _35  = 35,  _40  = 40  };
enum Color           { BLUE, GREEN, RED, EMPTY_STYLE };
enum NumberOnImage   { NO, BLACK, WHITE };

enum class Action { OPEN_GRAPHIC, REM_GRAPHIC, SAVE_BOARD, LOAD_BOARD, SETTINGS, ABOUT };

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
    NumberOnImage numberOnImage;
    bool undoEnabled;
} OptionsData;

#endif // TYPES_H

