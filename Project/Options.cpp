
#include "Options.h"
#include "MappedValues.h"


TileColor Options::getTileColor()
{
    return Options::tileColor;
}

/*********************************************************************************/
/*********************************************************************************/

TileSize Options::getTileSize()
{
    return Options::tileSize;
}

/*********************************************************************************/
/*********************************************************************************/

bool Options::isImageToBeLoaded( BoardSize boardSize )
{
    return imagesToLoad.at( boardSize );
}

/*********************************************************************************/
/*********************************************************************************/

NumberColor Options::getNumberOnImageColor()
{
    return Options::numberColor;
}

/*********************************************************************************/
/*********************************************************************************/

unique_ptr< OptionsData > Options::readOptions()
{
    unique_ptr< OptionsData > optionsData = std::make_unique< OptionsData >();
    optionsData->boardMode = boardMode;
    optionsData->graphicMode = graphicMode;
    optionsData->tileSize = tileSize;
    optionsData->imageToLoad_4 = imagesToLoad.at( BoardSize::FOUR );
    optionsData->imageToLoad_5 = imagesToLoad.at( BoardSize::FIVE );
    optionsData->imageToLoad_6 = imagesToLoad.at( BoardSize::SIX );
    optionsData->imageToLoad_7 = imagesToLoad.at( BoardSize::SEVEN );
    optionsData->squareColor = tileColor;
    optionsData->numberColor = numberColor;
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
}

/*********************************************************************************/
/*********************************************************************************/

BoardMode Options::boardMode = BoardMode::NUMERIC;
GraphicMode Options::graphicMode = GraphicMode::SCALED;
TileSize Options::tileSize = TileSize::_100;
TileColor Options::tileColor = TileColor::BLUE;
NumberColor Options::numberColor = NumberColor::NO;

map< BoardSize, bool > Options::imagesToLoad
{
    { BoardSize::FOUR, true }, { BoardSize::FIVE, true },
    { BoardSize::SIX, true },  { BoardSize::SEVEN, true }
};

