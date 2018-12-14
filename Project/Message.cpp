
#include "Message.h"


void Message::putMessage( MessageCode code )
{
    messageQueue.push( message[code] );
}

/*********************************************************************************/
/*********************************************************************************/

void Message::putMessage( MessageCode code, int value )
{
    messageQueue.push( QString( message[code] + "%1 \t\n\n" ).arg( value ));
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

queue< QString > Message::messageQueue = {};

map< MessageCode, QString > Message::message =
{
    { MessageCode::GRAPHIC_LOAD_OK,                     "Graphic was loaded for a board " },
    { MessageCode::GRAPHIC_LOAD_FAILURE,                "Failure of loading graphic for a board of size " },
    { MessageCode::GRAPHIC_TOO_LOW_SIZE,                "Too low size of graphic for a board of size " },
    { MessageCode::READ_BOARD_SIZE_ERROR,               "Error reading file : size of a board" },
    { MessageCode::READ_BOARD_TYPE_ERROR,               "Error reading file : kind of a board" },
    { MessageCode::READ_BOARD_VALUES_ERROR,             "Error reading file : board values" },
    { MessageCode::READ_BOARD_IMAGES_DATA_ERROR,        "Error reading file : images" },
    { MessageCode::READ_BOARD_IMAGES_TILE_SIZE_ERROR,   "Error reading file : tile size" }
};

