
#include <QApplication>
#include <MainWindow.h>

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    Fifteen fifteen;
    fifteen.show();
    return app.exec();
}

