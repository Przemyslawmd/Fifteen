
#ifndef FIFTEEN_MESSAGE_H
#define FIFTEEN_MESSAGE_H

#include <QString>

#include <map>
#include <queue>


enum class Result
{
    OK,
    GRAPHIC_LOAD_OK,
    GRAPHIC_LOAD_FAILURE,
    GRAPHIC_TOO_LOW_SIZE,
    FILE_ERROR_IMPROPER_SIZE,
    FILE_ERROR_SIZE_NOT_FIT_VALUES,
    READ_BOARD_ERROR,
    FILE_ERROR_VALUE_NOT_NUMBER,
    READ_BOARD_SIZE_ERROR,
    READ_BOARD_SIZE_IMPROPER,
    READ_BOARD_VALUES_ERROR,
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

