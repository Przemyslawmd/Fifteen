
#ifndef FIFTEEN_MESSAGE_H
#define FIFTEEN_MESSAGE_H

#include <map>
#include <queue>

#include <QString>


enum class Result
{
    OK,
    CREATE_GRAPHIC_BOARD_NO_GRAPHIC,
    GRAPHIC_LOAD_OK,
    GRAPHIC_LOAD_FAILURE,
    GRAPHIC_TOO_LOW_SIZE,
    FILE_ERROR_SIZE_IMPROPER,
    FILE_ERROR_SIZE_NOT_FIT_VALUES,
    READ_BOARD_ERROR,
    FILE_ERROR_VALUE_IMPROPER,
    FILE_ERROR_VALUE_NOT_NUMBER,
    FILE_INFO_SIZE_IMPROPER,
};


class Message
{
public:

    static const QString& getMessage( Result );
    static void putMessage( Result );
    static void putMessage( Result, size_t arg );
    static QString getMessages();

private:

    static const std::map<Result, QString> message;
    static std::queue<QString> messageQueue;
};

#endif

