
#include "Message.h"

/*******************************************************************************************/
/* PUT MESSAGE *****************************************************************************/

void Message::putMessage( MessageCode code )
{
    messageQueue.push( message[code] );
}

/*******************************************************************************************/
/* PUT MESSAGE ************ ****************************************************************/

void Message::putMessage( MessageCode code, int value )
{
    messageQueue.push( QString( message[code] + "%1 \t\n\n" ).arg( value ));
}

/*******************************************************************************************/
/* GET MESSAGES ****************************************************************************/

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

/*******************************************************************************************/
/*******************************************************************************************/

queue<QString> Message::messageQueue = {};

map< MessageCode, QString> Message::message =
{
    { MessageCode::GRAPHIC_LOAD_OK, "Graphic was loaded for a board " },
    { MessageCode::GRAPHIC_LOAD_FAILURE, "Failure of loading graphic for a board of size " },
    { MessageCode::GRAPHIC_TOO_LOW_SIZE, "Too low size of graphic for a board of size " },
};
