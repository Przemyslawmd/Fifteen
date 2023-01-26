
#include "MappedValues.h"
#include "Options.h"

using std::unique_ptr;


const QString& Options::getTileColor()
{
    return Maps::tileColorStyle.at( Options::tileColor );;
}

/*********************************************************************************/
/*********************************************************************************/

TileSize Options::getTileSize()
{
    return Options::tileSize;
}

/*********************************************************************************/
/*********************************************************************************/

uint Options::getFontSize()
{
    return Maps::fontSizeInt.at( Options::fontSize );
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
    fontSize = Maps::tileSizeFontSize.at( tileSize );
}

/*********************************************************************************/
/*********************************************************************************/

FontSize Options::fontSize = FontSize::_30;
GraphicMode Options::graphicMode = GraphicMode::SCALED;
TileSize Options::tileSize = TileSize::_100;
TileColor Options::tileColor = TileColor::BLUE;
NumberColor Options::numberColor = NumberColor::NO;

std::map< BoardSize, bool > Options::imagesToLoad
{
    { BoardSize::FOUR, true }, { BoardSize::FIVE, true },
    { BoardSize::SIX, true },  { BoardSize::SEVEN, true }
};

