#include "GraphicBoard/ImageLoad.h"

ImagesState::ImagesState() :    four( 4, true, false ), five( 5, true, false  ),
                                six( 6, true, false ), seven( 7, true, false ){}

/*******************************************************************************************************/
/* RESET NUMBER OF LOADED IMAGES ***********************************************************************/

void ImagesState::resetLoaded()
{
    four.loaded = false;
    five.loaded = false;
    six.loaded = false;
    seven.loaded = false;
}

