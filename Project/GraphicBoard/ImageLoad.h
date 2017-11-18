
#ifndef IMAGESTATE_H
#define IMAGESTATE_H

#include <QString>
#include "../Types.h"

class ImagesState;

class State
{
    friend class ImagesState;

    private:
        State ( int size ) :
                size( size ) {}

    public:        
        const int size;
};

class ImagesState
{
public:

    ImagesState();

    void resetLoaded();

    SquareSize imageSize;
    State four;
    State five;
    State six;
    State seven;
};


#endif // IMAGESTATE_H
