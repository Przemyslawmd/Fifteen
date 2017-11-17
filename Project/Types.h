
#ifndef TYPES_H
#define TYPES_H

#include <QString>

// Some enums not strongly typed because are used for indexing

enum BoardSize { FOUR = 4, FIVE, SIX, SEVEN };
enum GraphicMode { SCALED, CROPPED, GRAPHIC_MODE_COUNT };
enum class BoardMode { NUMERIC, GRAPHIC };

enum Move { UP, RIGHT, DOWN, LEFT, NOT_ALLOWED };

enum SquareSize { _50 = 50, _75 = 75, _100 = 100, _125 = 125, _150 = 150 };
enum FontSize   { _20 = 20, _25 = 25, _30  = 30,  _35  = 35,  _40  = 40  };

typedef struct SizeStruct
{
    SquareSize squareSize;
    int sliderIndex;
    FontSize fontSize;
} Sizes;

enum Color { BLUE, GREEN, RED, EMPTY_STYLE };

// Sometimes values of enum BoardSize are treated directly, it means that for example FIVE is 5.
// But in other cases these values are used for indexing of an array, then FIVE means 1 ( 5 - ALIGN ).
const int ALIGN = 4;

#endif // TYPES_H

