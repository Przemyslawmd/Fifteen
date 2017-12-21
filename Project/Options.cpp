
#include "Options.h"

/***********************************************************************/
/* BOARD SIZE **********************************************************/

BoardSize Options::getBoardSize()
{
    return boardSize;
}


void Options::setBoardSize( BoardSize size )
{
    boardSize = size;
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
/* BOARD MODE **********************************************************/

BoardMode Options::getBoardMode()
{
    return boardMode;
}


void Options::setBoardMode( BoardMode mode )
{
    boardMode = mode;
}

/***********************************************************************/
/* GRAPHIC MODE ********************************************************/

GraphicMode Options::getGraphicMode()
{
    return graphicMode;
}


void Options::setGraphicMode( GraphicMode mode )
{
    graphicMode = mode;
}

/************************************************************************/
/* COLOR ****************************************************************/

Color Options::getColor()
{
    return currentColor;
}


void Options::setColor( Color color )
{
    currentColor = color;
}


QString& Options::getStyle()
{
    return styles[currentColor];
}


QString& Options::getEmptyStyle()
{
    return styles[Color::EMPTY_STYLE];
}

/************************************************************************/
/* IMAGES TO BE LOADED **************************************************/


bool Options::isImageToBeLoaded( BoardSize size )
{
    return imagesToBeLoaded[size - 4];
}


void Options::setImagesToBeLoaded( bool four, bool five , bool six , bool seven )
{
    imagesToBeLoaded[0] = four;
    imagesToBeLoaded[1] = five;
    imagesToBeLoaded[2] = six;
    imagesToBeLoaded[3] = seven;
}

/************************************************************************/
/* TEXT ON IMAGE ********************************************************/

bool Options::isTextOnImage()
{
    return textOnImage;
}


void Options::setTextOnImage( bool text )
{
    textOnImage = text;
}


ColorText Options::getTextOnImageColor()
{
    return textOnImageColor;
}


void Options::setTextOnImageColor( ColorText color )
{
    textOnImageColor = color;
}

/***********************************************************************/
/***********************************************************************/

BoardSize Options::boardSize = BoardSize::FOUR;
BoardMode Options::boardMode = BoardMode::NUMERIC;
GraphicMode Options::graphicMode = GraphicMode::SCALED;

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
    { BEGIN_STYLE ", stop:0 #800000, stop:1 #EE0000); " END_STYLE }, // Red style
    { "background-color:white; " END_STYLE }
};

bool Options::imagesToBeLoaded[] = { true, true, true, true };

bool Options::textOnImage = false;
ColorText Options::textOnImageColor = ColorText::BLACK;

