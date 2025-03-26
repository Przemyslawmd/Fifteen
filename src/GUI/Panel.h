
#ifndef FIFTEEN_PANEL_H
#define FIFTEEN_PANEL_H

#include <functional>
#include <map>

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

#include "Types.h"


class Panel
{
public:

    Panel() = default;
    Panel( const Panel& ) = delete;
    Panel( Panel&& ) = delete;
    Panel& operator=( const Panel& ) = delete;
    Panel& operator=( Panel&& ) = delete;

    QVBoxLayout* createLayout( std::function<void()>, std::function<void()>, std::function<void()>, QMainWindow* );

    BoardSize checkBoardSize();
    void setBoardSize( BoardSize );
    bool checkBoardMode( BoardMode );
    void setBoardMode( BoardMode );

private:

    std::map<BoardSize, QRadioButton> radioSize;
    std::map<BoardMode, QRadioButton> radioMode;
};

#endif

