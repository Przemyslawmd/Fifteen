#ifndef IMAGESTATE_H
#define IMAGESTATE_H

#include <QString>
#include <Types.h>

class ImagesState;

class State
{
    friend class ImagesState;

    private:
        State ( int size, bool toLoad, bool loaded, QString message ) :
                size( size ), toLoad( toLoad ), loaded( loaded ), message( message ) {}

    public:        
        int size;
        mutable bool toLoad;
        mutable bool loaded;        
        QString message;
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
