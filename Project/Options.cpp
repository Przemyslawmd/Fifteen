
#include "Options.h"
#include "MappedValues.h"
#include <QtGlobal>


TileSize Options::getTileSize()
{
    return tileSize;
}


FontSize Options::getFontSize()
{
    return Mapped::mapTileFont.at( tileSize );
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

const QString& Options::getStyle()
{
    return Mapped::tileColorStyles.at( currentColor );
}


const QString& Options::getEmptyStyle()
{
    return Mapped::tileColorStyles.at( TileColor::EMPTY_STYLE );
}

/*********************************************************************************/
/*********************************************************************************/

bool Options::isImageToBeLoaded( BoardSize boardSize )
{
    return imagesToLoad.at( boardSize );
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
    messageData->tileSize = tileSize;
    messageData->imageToLoad_4 = imagesToLoad.at( BoardSize::FOUR );
    messageData->imageToLoad_5 = imagesToLoad.at( BoardSize::FIVE );
    messageData->imageToLoad_6 = imagesToLoad.at( BoardSize::SIX );
    messageData->imageToLoad_7 = imagesToLoad.at( BoardSize::SEVEN );
    messageData->squareColor = currentColor;
    messageData->numberColor = numberColor;
    messageData->undoEnabled = undoEnabled;
    return messageData;
}


void Options::receiveData( unique_ptr< OptionsData >  messageData )
{
    graphicMode = messageData->graphicMode;
    tileSize = messageData->tileSize;
    imagesToLoad.at( BoardSize::FOUR ) = messageData->imageToLoad_4;
    imagesToLoad.at( BoardSize::FIVE ) = messageData->imageToLoad_5;
    imagesToLoad.at( BoardSize::SIX ) = messageData->imageToLoad_6;
    imagesToLoad.at( BoardSize::SEVEN ) = messageData->imageToLoad_7;
    currentColor = messageData->squareColor;
    numberColor = messageData->numberColor;
    undoEnabled = messageData->undoEnabled;
}

/*********************************************************************************/
/*********************************************************************************/

BoardMode Options::boardMode = BoardMode::NUMERIC;
GraphicMode Options::graphicMode = GraphicMode::SCALED;
TileSize Options::tileSize = TileSize::_50;
TileColor Options::currentColor = TileColor::BLUE;
NumberColor Options::numberColor = NumberColor::NO;
bool Options::undoEnabled = false;

std::map< BoardSize, bool > Options::imagesToLoad
{
    { BoardSize::FOUR, true }, { BoardSize::FIVE, true },
    { BoardSize::SIX, true },  { BoardSize::SEVEN, true }
};

