
#include "Options.h"
#include "MappedValues.h"
#include <QtGlobal>


TileSize Options::getSquareSize()
{
    return std::get< 0 >( Mapped::tileStyles.at( currentTileIndex ));
}


FontSize Options::getSquareSizeFont()
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

bool Options::isImageToBeLoaded( BoardSize size )
{
    int boardSizeInt = Mapped::BoardSizeInt.at( size );
    return imagesToBeLoaded[boardSizeInt - 4];
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
bool Options::imagesToBeLoaded[] = { true, true, true, true };
NumberColor Options::numberColor = NumberColor::NO;
bool Options::undoEnabled = false;

