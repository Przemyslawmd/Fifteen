
#ifndef TYPES_H
#define TYPES_H

#include <QString>

// Not strongly typed enums because these enums are used for indexing an array

enum BoardSize { FOUR = 4, FIVE, SIX, SEVEN };
enum Move { UP, RIGHT, DOWN, LEFT, NOT_ALLOWED };

enum SquareSize { _50 = 50, _75 = 75, _100 = 100, _125 = 125, _150 = 150 };
enum FontSize   { _20 = 20, _25 = 25, _30  = 30,  _35  = 35,  _40  = 40  };

typedef struct SizeStruct
{
    SquareSize squareSize;
    int sliderIndex;
    FontSize fontSize;
} Sizes;

enum Color { BLUE, GREEN, RED };

#endif // TYPES_H

