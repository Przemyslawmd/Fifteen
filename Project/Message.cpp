
#include "Message.h"


void Message::putMessage( Result code )
{
    messageQueue.push( message.at( code ));
}

/*********************************************************************************/
/*********************************************************************************/

void Message::putMessage( Result code, uint value )
{
    messageQueue.push( QString( message.at( code ) + "%1 \t\n\n" ).arg( value ));
}

/*********************************************************************************/
/*********************************************************************************/

QString Message::getMessages()
{
    QString message;
    while ( messageQueue.empty() == false )
    {
        message += messageQueue.front();
        messageQueue.pop();
    }

    return message;
}

/*********************************************************************************/
/*********************************************************************************/

std::queue< QString > Message::messageQueue = {};

const std::map< Result, QString > Message::message =
{
    { Result::GRAPHIC_LOAD_OK,                     "Graphic was loaded for a board " },
    { Result::GRAPHIC_LOAD_FAILURE,                "Failure of loading graphic for a board of size " },
    { Result::GRAPHIC_TOO_LOW_SIZE,                "Too low size of graphic for a board of size " },
    { Result::READ_BOARD_SIZE_ERROR,               "Error reading file : size of a board" },
    { Result::READ_BOARD_TYPE_ERROR,               "Error reading file : kind of a board" },
    { Result::READ_BOARD_VALUES_ERROR,             "Error reading file : board values" },
    { Result::READ_BOARD_IMAGES_DATA_ERROR,        "Error reading file : images" },
    { Result::READ_BOARD_IMAGES_TILE_SIZE_ERROR,   "Error reading file : tile size" }
};

