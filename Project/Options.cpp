
#include "Options.h"
#include <QtGlobal>


SquareSize Options::getSquareSize()
{
    return squareStyles[currentSquare].squareSize;
}


int Options::getSquareSizeFont()
{
    return squareStyles[currentSquare].fontSize;
}

/*********************************************************************************/
/*********************************************************************************/

BoardMode Options::getBoardMode()
{
    return boardMode;
}


void Options::setBoardMode( BoardMode mode )
{
    boardMode = mode;
}

/*********************************************************************************/
/*********************************************************************************/

GraphicMode Options::getGraphicMode()
{
    return graphicMode;
}

/*********************************************************************************/
/*********************************************************************************/

QString& Options::getStyle()
{
    return styles[currentColor];
}


QString& Options::getEmptyStyle()
{
    return styles[Color::EMPTY_STYLE];
}

/*********************************************************************************/
/*********************************************************************************/

bool Options::isImageToBeLoaded( BoardSize size )
{
    return imagesToBeLoaded[size - 4];
}

/*********************************************************************************/
/*********************************************************************************/

NumberOnImage Options::isNumberOnImage()
{
    return numberOnImage;
}

/*********************************************************************************/
/*********************************************************************************/

bool Options::isUndoEnabled()
{
    return undoEnabled;
}

/*********************************************************************************/
/*********************************************************************************/

unique_ptr< OptionsData > Options::sendData()
{
    unique_ptr< OptionsData > messageData( new OptionsData );
    messageData->boardMode = boardMode;
    messageData->graphicMode = graphicMode;
    messageData->fourImageToBeLoaded = imagesToBeLoaded[0];
    messageData->fiveImageToBeLoaded = imagesToBeLoaded[1];
    messageData->sixImageToBeLoaded = imagesToBeLoaded[2];
    messageData->sevenImageToBeLoaded = imagesToBeLoaded[3];
    messageData->squareColor = currentColor;
    messageData->squareSizeIndex = currentSquare + 1;
    messageData->numberOnImage = numberOnImage;
    messageData->undoEnabled = undoEnabled;
    return messageData;
}


void Options::receiveData( unique_ptr< OptionsData >  messageData )
{
    graphicMode = messageData->graphicMode;
    imagesToBeLoaded[0] = messageData->fourImageToBeLoaded;
    imagesToBeLoaded[1] = messageData->fiveImageToBeLoaded;
    imagesToBeLoaded[2] = messageData->sixImageToBeLoaded;
    imagesToBeLoaded[3] = messageData->sevenImageToBeLoaded;
    currentColor = messageData->squareColor;
    currentSquare = static_cast< SquareSize >( messageData->squareSizeIndex - 1 );
    numberOnImage = messageData->numberOnImage;
    undoEnabled = messageData->undoEnabled;
}

/*********************************************************************************/
/*********************************************************************************/

BoardMode Options::boardMode = BoardMode::NUMERIC;
GraphicMode Options::graphicMode = GraphicMode::SCALED;

int Options::currentSquare = 0;

SquareStyle Options::squareStyles[]
{
    { .squareSize = _50,  .fontSize = _20, .sliderIndex = 1 },
    { .squareSize = _75,  .fontSize = _25, .sliderIndex = 2 },
    { .squareSize = _100, .fontSize = _30, .sliderIndex = 3 },
    { .squareSize = _125, .fontSize = _35, .sliderIndex = 4 },
    { .squareSize = _150, .fontSize = _40, .sliderIndex = 5 }
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
NumberOnImage Options::numberOnImage = NumberOnImage::NO;
bool Options::undoEnabled = false;

