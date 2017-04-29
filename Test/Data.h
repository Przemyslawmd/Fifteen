#ifndef DATATEST_H
#define DATATEST_H

#endif // DATATEST_H

// This class has defined values used to test

class Data{

public:

    static int* getMoves( int dataNumber );

    static int* getExcpectedBoard( int dataNumber );

private:

    // For board 4x4
    static int moves_1[];

    // For board 5x5
    //static int* moves_2 {};

    // For board 4x4
    static int expectedBoard_1[];
    // For board 5x5
    //static int* expectedBoard_2{};


};

