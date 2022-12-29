
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
    { Result::READ_BOARD_ERROR,                    "Error reading file" },
    { Result::FILE_ERROR_VALUE_IMPROPER,           "File error: improper value" },
    { Result::FILE_ERROR_VALUE_NOT_NUMBER,         "File error: board value is not a number" },
    { Result::FILE_ERROR_SIZE_IMPROPER,            "File error: read board size is not between five and seven" },
    { Result::FILE_ERROR_SIZE_NOT_FIT_VALUES,      "File error: read board size doesn't fit to read board values" },
    { Result::FILE_INFO_SIZE_IMPROPER,            "File error: board to restore and current board must have the same size: " },
};

