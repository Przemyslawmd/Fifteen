#ifndef TYPES_H
#define TYPES_H

// Not strongly typed enums because these enums are used for indexing an array

// BLUE has value 2 because of an array of radio controls in WindowSetting class
enum Color { BLUE = 2, GREEN, RED };

enum BoardSize { FOUR = 4, FIVE, SIX, SEVEN };

enum SquareSize { _50 = 50, _75 = 75, _100 = 100, _125 = 125, _150 = 150 };

#endif // TYPES_H


