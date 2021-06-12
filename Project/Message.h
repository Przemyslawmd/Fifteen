
#ifndef MESSAGE_H
#define MESSAGE_H

#include <map>
#include <queue>
#include <QString>

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
    static void putMessage( Result, uint arg );
    static QString getMessages();


private:

    static const std::map< Result, QString > message;
    static std::queue< QString > messageQueue;
};

#endif

