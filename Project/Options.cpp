
#include "Options.h"
#include "MappedValues.h"
#include <QtGlobal>

using std::make_unique;

TileColor Options::getTileColor()
{
    return Options::tileColor;
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
    unique_ptr< NumberOnImage > numOnImage = make_unique< NumberOnImage >();

    if ( numberColor == NumberColor::NO )
    {
        numOnImage->isNumberOnImage = false;
        return numOnImage;
    }

    numOnImage->isNumberOnImage = true;
    numOnImage->fontColor = numberColor == NumberColor::BLACK ? QColor{ 0, 0, 0 } : QColor{ 255, 255, 255 };
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

unique_ptr< OptionsData > Options::readOptions()
{
    unique_ptr< OptionsData > optionsData = make_unique< OptionsData >();
    optionsData->boardMode = boardMode;
    optionsData->graphicMode = graphicMode;
    optionsData->tileSize = tileSize;
    optionsData->imageToLoad_4 = imagesToLoad.at( BoardSize::FOUR );
    optionsData->imageToLoad_5 = imagesToLoad.at( BoardSize::FIVE );
    optionsData->imageToLoad_6 = imagesToLoad.at( BoardSize::SIX );
    optionsData->imageToLoad_7 = imagesToLoad.at( BoardSize::SEVEN );
    optionsData->squareColor = tileColor;
    optionsData->numberColor = numberColor;
    optionsData->undoEnabled = undoEnabled;
    return optionsData;
}

/*********************************************************************************/
/*********************************************************************************/

void Options::saveOptions( unique_ptr< OptionsData >  optionsData )
{
    graphicMode = optionsData->graphicMode;
    tileSize = optionsData->tileSize;
    imagesToLoad.at( BoardSize::FOUR ) = optionsData->imageToLoad_4;
    imagesToLoad.at( BoardSize::FIVE ) = optionsData->imageToLoad_5;
    imagesToLoad.at( BoardSize::SIX ) = optionsData->imageToLoad_6;
    imagesToLoad.at( BoardSize::SEVEN ) = optionsData->imageToLoad_7;
    tileColor = optionsData->squareColor;
    numberColor = optionsData->numberColor;
    undoEnabled = optionsData->undoEnabled;
}

/*********************************************************************************/
/*********************************************************************************/

BoardMode Options::boardMode = BoardMode::NUMERIC;
GraphicMode Options::graphicMode = GraphicMode::SCALED;
TileSize Options::tileSize = TileSize::_100;
TileColor Options::tileColor = TileColor::BLUE;
NumberColor Options::numberColor = NumberColor::NO;
bool Options::undoEnabled = false;

map< BoardSize, bool > Options::imagesToLoad
{
    { BoardSize::FOUR, true }, { BoardSize::FIVE, true },
    { BoardSize::SIX, true },  { BoardSize::SEVEN, true }
};

