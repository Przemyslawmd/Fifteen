
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
    return sizes[currentSquare].squareSize;
}


int Options::getSquareSizeIndex()
{
    return currentSquare + 1;
}


void Options::setSquareSize( int value )
{
    currentSquare = static_cast< SquareSize >( value - 1 );
}


int Options::getSquareSizeFont()
{
    return sizes[currentSquare].fontSize;
}

/***********************************************************************/
/* NUMERIC *************************************************************/

bool Options::isNumeric()
{
    return numeric;
}


void Options::setNumeric( bool numeric )
{
    Options::numeric = numeric;
}

/***********************************************************************/
/* SCALED **************************************************************/

bool Options::isScaled()
{
    return scaled;
}


void Options::setScaled( bool scaled )
{
    Options::scaled = scaled;
}

/************************************************************************/
/* COLOR ****************************************************************/

Color Options::getColor()
{
    return currentColor;
}


void Options::setColor( Color color )
{
    Options::currentColor = color;
}


QString& Options::getStyle()
{
    return styles[currentColor];
}

/***********************************************************************/
/***********************************************************************/

BoardSize Options::boardSize = BoardSize::FOUR;
bool Options::numeric = true;
bool Options::scaled = true;

int Options::currentSquare = 0;

Sizes Options::sizes[]
{
    { .squareSize = _50,  .sliderIndex = 1, .fontSize = _20 },
    { .squareSize = _75,  .sliderIndex = 2, .fontSize = _25 },
    { .squareSize = _100, .sliderIndex = 3, .fontSize = _30 },
    { .squareSize = _125, .sliderIndex = 4, .fontSize = _35 },
    { .squareSize = _150, .sliderIndex = 5, .fontSize = _40 }
};

Color Options::currentColor = Color::BLUE;

#define BEGIN_STYLE "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1"
#define END_STYLE   "color:white; border:1px solid white"

QString Options::styles[]
{
    { BEGIN_STYLE ", stop:0 #000080, stop:1 #0000EE); " END_STYLE }, // Blue style
    { BEGIN_STYLE ", stop:0 #004d00, stop:1 #009900); " END_STYLE }, // Green style
    { BEGIN_STYLE ", stop:0 #800000, stop:1 #EE0000); " END_STYLE }  // Red style
};

