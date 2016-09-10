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
bool Options::isNumeric = true;
bool Options::isScaled = true;
Color Options::color = Color::BLUE;

