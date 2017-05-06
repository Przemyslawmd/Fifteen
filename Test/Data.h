
#ifndef DATATEST_H
#define DATATEST_H

// This class has defined values using while running tests

class Data{

public:

    static int* getMoves( int dataNumber );

    static int* getExcpectedBoard( int dataNumber );

private:

    static int* moves[];
    static int moves_1[];
    static int moves_2[];

    static int* expectedBoard[];
    static int expectedBoard_1[];
    static int expectedBoard_2[];
};

#endif // DATATEST_H
