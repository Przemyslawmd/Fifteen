
#include "ImageLoad.h"

ImagesState::ImagesState() :    four( 4, false ), five( 5, false  ),
                                six( 6, false ), seven( 7, false ){}

/*******************************************************************************************************/
/* RESET NUMBER OF LOADED IMAGES ***********************************************************************/

void ImagesState::resetLoaded()
{
    four.loaded = false;
    five.loaded = false;
    six.loaded = false;
    seven.loaded = false;
}
