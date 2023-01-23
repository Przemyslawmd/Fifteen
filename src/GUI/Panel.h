
#ifndef FIFTEEN_PANEL_H
#define FIFTEEN_PANEL_H

#include "Types.h"

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

#include <functional>
#include <map>
#include <memory>


class Panel
{
public:

    Panel() = default;
    Panel( const Panel& ) = delete;
    Panel operator=( const Panel& ) = delete;

    QVBoxLayout* createLayout( std::array< std::function< void( void ) >, 3 >& slots, QMainWindow* );

    BoardSize checkBoardSize();
    void setBoardSize( BoardSize );
    bool checkBoardMode( BoardMode );
    void setBoardMode( BoardMode );

private:

    std::map< BoardSize, QRadioButton* > mapBoardSize;
    std::map< BoardMode, QRadioButton* > mapBoardMode;
};

#endif

