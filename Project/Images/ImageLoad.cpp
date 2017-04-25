#include "Images/ImageLoad.h"

ImageLoad::ImageLoad() :    four( 4, true, false, "4x4\n\n" ), five( 5, true, false, "5x5\n\n" ),
                            six( 6, true, false, "6x6\n\n" ), seven( 7, true, false, "7x7\n\n" ){}

/*******************************************************************************************************/
/* RESET NUMBER OF LOADED IMAGES ***********************************************************************/

void ImageLoad::resetLoaded()
{
    four.loaded = false;
    five.loaded = false;
    six.loaded = false;
    seven.loaded = false;
}

