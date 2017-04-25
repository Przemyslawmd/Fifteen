#include "Images/GraphicBoard.h"

/*************************************************************************************************************************/
/* CONSTRUCTOR ***********************************************************************************************************/

GraphicBoard::GraphicBoard( int level ) : level( level )
{
    image = new QImage*[level  * level];
    for (int i = 0; i < ( level * level ); i++)
        image[i] = 0;    
}

/**************************************************************************************************************************/
/* DESTRUCTOR *************************************************************************************************************/

GraphicBoard::~GraphicBoard()
{
    if ( image[0] != 0 )
    {
        for ( int i = 0; i < ( level * level ); i++ )
            delete image[i];
        delete[] image;
    }    
}

/**************************************************************************************************************************/
/* SEND IMAGE *************************************************************************************************************/

QImage** GraphicBoard::getImage()
{
    return image;
}

/***************************************************************************************************************************/
/* CHECK WHETHER AN IMAGE CAN BE LOADED FOR A SCALE MODE *******************************************************************/

void GraphicBoard::prepareScaledImage( QImage& picture, State& state, QString& message, SquareSize squareSize )
{
    int boardSize = state.size * squareSize;    

    if ( createSquareImage( new QImage( picture.scaled( boardSize, boardSize )), state.size, squareSize ))
    {
        state.loaded = true;
        message.append( "Graphic was loaded for a board " + state.message );
    }
    else
        message.append( "Failure of loading graphic for a board " + state.message );
}

/****************************************************************************************************************************/
/* CHECK WHETHER AN IMAGE CAN BE LOADED FOR A CROP MODE *********************************************************************/

void GraphicBoard::prepareCroppedImage( QImage& picture, State& state, QString& message, SquareSize squareSize )
{
    int boardSize = state.size * squareSize;    

    if ( createSquareImage( new QImage( picture.copy(( picture.width() - boardSize )/2, ( picture.height() - boardSize )/2, boardSize, boardSize )), state.size, squareSize ))
    {
        state.loaded = true;
        message.append( "Graphic was loaded for a board" + state.message );
    }
    else
        message.append( "Failure of loading graphic for a board " + state.message );
}

/**************************************************************************************************************************/
/* MAKE IMAGE FOR EACH SQUARE *********************************************************************************************/

bool GraphicBoard::createSquareImage( QImage* picture, int size, SquareSize squareSize )
{
    // Prepare an empty square
    image[0] = new QImage( squareSize, squareSize, QImage::Format_RGB32 );
    for (int i = 0; i < squareSize; i++)
    {
        for (int j = 0; j < squareSize; j++)
            image[0]->setPixel( i, j, qRgb( 255, 255, 255 ));
    }

    int x = 0;

    for ( int i = 0; i < size * squareSize; i += squareSize )
    {
        for ( int j = 0; j < size * squareSize; j += squareSize )
        {
            if (( i == size * squareSize - squareSize ) && ( j == size * squareSize - squareSize ))
                return true;

            try
            {
                image[++x] = new QImage( squareSize, squareSize, QImage::Format_RGB32 );

                for ( int k = 0; k < squareSize; k++ )
                {
                    for ( int l = 0; l < squareSize; l++ )
                        image[x]->setPixel( k, l, picture->pixel( k + j, l + i ));
                }
            }
            catch (...)
            {
                return false;
            }
        }
    }
    return true;
}

/*****************************************************************************************************/
/* RESTORE IMAGES FROM FILE BUFFER *******************************************************************/

bool GraphicBoard::restoreImagesFromFile( uchar* data, SquareSize imageSize, int byteCount )
{
    bufferRestored = std::move( data );

    try
    {
        for ( int i = 0; i < level * level; i++ )
            image[i] = new QImage( bufferRestored + i * byteCount, imageSize, imageSize, QImage::Format_RGB32 );
    }
    catch(...)
    {
        return false;
    }
    return true;
}
