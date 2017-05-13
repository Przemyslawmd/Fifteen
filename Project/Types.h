
#ifndef TYPES_H
#define TYPES_H

// Not strongly typed enums because these enums are used for indexing an array

enum Color { BLUE, GREEN, RED };

enum BoardSize { FOUR = 4, FIVE, SIX, SEVEN };

enum SquareSize { _50 = 50, _75 = 75, _100 = 100, _125 = 125, _150 = 150 };

enum Move { UP, RIGHT, DOWN, LEFT, NOT_ALLOWED };

#endif // TYPES_H

