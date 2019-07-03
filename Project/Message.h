
#ifndef MESSAGE_H
#define MESSAGE_H

#include <map>
#include <queue>
#include <QString>

using std::map;
using std::queue;

enum class Result
{
    OK,
    GRAPHIC_LOAD_OK,
    GRAPHIC_LOAD_FAILURE,
    GRAPHIC_TOO_LOW_SIZE,
    READ_BOARD_SIZE_ERROR,
    READ_BOARD_TYPE_ERROR,
    READ_BOARD_VALUES_ERROR,
    READ_BOARD_IMAGES_DATA_ERROR,
    READ_BOARD_IMAGES_TILE_SIZE_ERROR
};

class Message
{
public:

    static void putMessage( Result );
    static void putMessage( Result, int arg );
    static QString getMessages();
    static map< Result, QString > message;

private:

    static queue< QString > messageQueue;
};

#endif // MESSAGE_H

