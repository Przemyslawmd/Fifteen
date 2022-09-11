
#include <QApplication>
#include <Fifteen.h>

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    Fifteen fifteen;
    fifteen.initGame();
    fifteen.show();
    return app.exec();
}

