
#include "Options.h"

/***********************************************************************/
/* BOARD SIZE **********************************************************/

BoardSize Options::getBoardSize()
{
    return boardSize;
}


void Options::setBoardSize( BoardSize boardSize )
{
    Options::boardSize = boardSize;
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


int Options::getFontSquareSize()
{
    if ( squareSize == SquareSize::_50 )
        return 20;
    else if ( squareSize == SquareSize::_75 )
        return 25;
    else if ( squareSize == SquareSize::_100 )
        return 30;
    else if ( squareSize == SquareSize::_125 )
        return 35;
    else
        return 40;

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


QString* Options::getStyle()
{
    if ( color == Color::BLUE )
        return &styleBlue;
    else if ( color == Color::RED )
        return &styleRed;
    return &styleGreen;
}

/***********************************************************************/
/***********************************************************************/

BoardSize Options::boardSize = BoardSize::FOUR;
SquareSize Options::squareSize = SquareSize::_50;
bool Options::isNumeric = true;
bool Options::isScaled = true;
Color Options::color = Color::BLUE;

#define BEGIN_STYLE "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1"
#define END_STYLE "color:white; border:1px solid white"

QString Options::styleBlue { BEGIN_STYLE ", stop:0 #000080, stop:1 #0000EE); " END_STYLE };
QString Options::styleRed { BEGIN_STYLE ", stop:0 #800000, stop:1 #EE0000); " END_STYLE  };
QString Options::styleGreen { BEGIN_STYLE ", stop:0 #004d00, stop:1 #009900); " END_STYLE };

#undef BEGIN_STYLE
#undef END_STYLE


