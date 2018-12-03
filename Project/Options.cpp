
#include "Options.h"
#include <QtGlobal>


TileSize Options::getSquareSize()
{
    return tileStyles.at( currentTileIndex ).tileSize;
}


int Options::getSquareSizeFont()
{
    return tileStyles.at( currentTileIndex ).fontSize;
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

unique_ptr< NumberOnImage > Options::isNumberOnImage()
{
    unique_ptr< NumberOnImage > numOnImage( new NumberOnImage );

    if ( numberColor == NumberColor::NO )
    {
        numOnImage->isNumberOnImage = false;
        return numOnImage;
    }

    if ( numberColor == NumberColor::BLACK )
    {
        numOnImage->fontColor = QColor{ 0, 0, 0 };
    }
    if ( numberColor == NumberColor::WHITE )
    {
        numOnImage->fontColor = QColor{ 255, 255, 255 };
    }

    numOnImage->isNumberOnImage = true;
    numOnImage->fontSize = tileStyles.at( currentTileIndex ).fontSize;
    return numOnImage;
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
    messageData->squareSizeIndex = currentTileIndex + 1;
    messageData->numberColor = numberColor;
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
    currentTileIndex = static_cast< TileSize >( messageData->squareSizeIndex - 1 );
    numberColor = messageData->numberColor;
    undoEnabled = messageData->undoEnabled;
}

/*********************************************************************************/
/*********************************************************************************/

BoardMode Options::boardMode = BoardMode::NUMERIC;
GraphicMode Options::graphicMode = GraphicMode::SCALED;

int Options::currentTileIndex = 0;

std::map< int, TileStyle > Options::tileStyles
{
    { 0, { .tileSize = _50,  .fontSize = _20 } },
    { 1, { .tileSize = _75,  .fontSize = _25 } },
    { 2, { .tileSize = _100, .fontSize = _30 } },
    { 3, { .tileSize = _125, .fontSize = _35 } },
    { 4, { .tileSize = _150, .fontSize = _40 } }
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
NumberColor Options::numberColor = NumberColor::NO;
bool Options::undoEnabled = false;

