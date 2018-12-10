
#include "Options.h"
#include "MappedValues.h"
#include <QtGlobal>


TileSize Options::getTileSize()
{
    return std::get< 0 >( Mapped::tileStyles.at( currentTileIndex ));
}


FontSize Options::getFontSize()
{
    return std::get< 1 >( Mapped::tileStyles.at( currentTileIndex ));
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
    numOnImage->fontSize = std::get< 1 >( Mapped::tileStyles.at( currentTileIndex ));
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
    messageData->imageToLoad_4 = imagesToLoad.at( BoardSize::FOUR );
    messageData->imageToLoad_5 = imagesToLoad.at( BoardSize::FIVE );
    messageData->imageToLoad_6 = imagesToLoad.at( BoardSize::SIX );
    messageData->imageToLoad_7 = imagesToLoad.at( BoardSize::SEVEN );
    messageData->squareColor = currentColor;
    messageData->squareSizeIndex = currentTileIndex + 1;
    messageData->numberColor = numberColor;
    messageData->undoEnabled = undoEnabled;
    return messageData;
}


void Options::receiveData( unique_ptr< OptionsData >  messageData )
{
    graphicMode = messageData->graphicMode;
    imagesToLoad.at( BoardSize::FOUR ) = messageData->imageToLoad_4;
    imagesToLoad.at( BoardSize::FIVE ) = messageData->imageToLoad_5;
    imagesToLoad.at( BoardSize::SIX ) = messageData->imageToLoad_6;
    imagesToLoad.at( BoardSize::SEVEN ) = messageData->imageToLoad_7;
    currentColor = messageData->squareColor;
    currentTileIndex = messageData->squareSizeIndex - 1;
    numberColor = messageData->numberColor;
    undoEnabled = messageData->undoEnabled;
}

/*********************************************************************************/
/*********************************************************************************/

BoardMode Options::boardMode = BoardMode::NUMERIC;
GraphicMode Options::graphicMode = GraphicMode::SCALED;
int Options::currentTileIndex = 0;
TileColor Options::currentColor = TileColor::BLUE;
NumberColor Options::numberColor = NumberColor::NO;
bool Options::undoEnabled = false;

std::map< BoardSize, bool > Options::imagesToLoad
{
    { BoardSize::FOUR, true }, { BoardSize::FIVE, true },
    { BoardSize::SIX, true },  { BoardSize::SEVEN, true }
};
