SOURCES += \
    WindowSetting.cpp \
    MainWindow.cpp \
    Board.cpp \
    Entry.cpp \
    WindowAbout.cpp \
    Images/ImageLoad.cpp \
    Images/ImageProvider.cpp \
    Options.cpp \
    Images/GraphicBoard.cpp

HEADERS += \
    WindowSetting.h \
    MainWindow.h \
    Board.h \
    WindowAbout.h \
    Types.h \
    Images/ImageLoad.h \
    Images/ImageProvider.h \
    Options.h \
    Images/GraphicBoard.h

QMAKE_CFLAGS_DEBUG  = -g
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



































