#include "Options.h"

/***********************************************************************/
/* BOARD SIZE **********************************************************/

Size Options::getBoardSize()
{
    return boardSize;
}


void Options::setBoardSize( Size size )
{
    boardSize = size;
}

/**********************************************************************/
/* SQUARE SIZE ********************************************************/

SquareSize Options::getSquareSize()
{
    return squareSize;
}


int Options::getSquareSizeIndex()
{
    if ( squareSize == SquareSize::_50 )
        return 1;
    else if ( squareSize == SquareSize::_75 )
        return 2;
    else if ( squareSize == SquareSize::_100 )
        return 3;
    else if ( squareSize == SquareSize::_125 )
        return 4;
    else
        return 5;
}


void Options::setSquareSize( int value )
{
    if ( value == 1 )
        squareSize = SquareSize::_50;
    else if ( value == 2 )
        squareSize = SquareSize::_75;
    else if ( value == 3 )
        squareSize = SquareSize::_100;
    else if ( value == 4 )
        squareSize = SquareSize::_125;
    else if ( value == 5 )
        squareSize = SquareSize::_150;
}

/***********************************************************************/
/* KIND OF BOARD *******************************************************/

bool Options::checkNumeric()
{
    return isNumeric;
}


void Options::setNumeric( bool numeric )
{
    isNumeric = numeric;
}

/***********************************************************************/
/* WAY OF PREPARING GRAPHICAL BOARD ************************************/

bool Options::checkScaled()
{
    return isScaled;
}


void Options::setScaled( bool scaled )
{
    isScaled = scaled;
}

/************************************************************************/
/* BOARD COLOR **********************************************************/

Color Options::getColor()
{
    return color;
}


void Options::setColor( Color requestedColor )
{
    color = requestedColor;
}

/***********************************************************************/
/***********************************************************************/

Size Options::boardSize = Size::FOUR;
SquareSize Options::squareSize = SquareSize::_50;
bool Options::isNumeric = true;
bool Options::isScaled = true;
Color Options::color = Color::BLUE;

