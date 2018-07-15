
#ifndef MESSAGE_H
#define MESSAGE_H

#include <map>
#include <queue>
#include <QString>

using std::map;
using std::queue;

enum class MessageCode
{
    GRAPHIC_LOAD_OK,
    GRAPHIC_LOAD_FAILURE,
    GRAPHIC_TOO_LOW_SIZE,
    READ_BOARD_SIZE_ERROR,
    READ_BOARD_TYPE_ERROR,
    READ_BOARD_VALUES_ERROR,
    READ_BOARD_IMAGES_ERROR,
    READ_BOARD_ERROR
};

class Message
{
public:

    static void putMessage( MessageCode code );
    static void putMessage( MessageCode code, int arg );
    static QString getMessages();

private:

    static queue< QString > messageQueue;
    static map< MessageCode, QString > message;
};

#endif // MESSAGE_H

