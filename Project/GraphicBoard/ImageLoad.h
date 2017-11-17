
#ifndef IMAGESTATE_H
#define IMAGESTATE_H

#include <QString>
#include "../Types.h"

class ImagesState;

class State
{
    friend class ImagesState;

    private:
        State ( int size, bool loaded ) :
                size( size ), loaded( loaded ) {}

    public:        
        const int size;
        bool loaded;
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
