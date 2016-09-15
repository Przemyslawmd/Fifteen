#ifndef IMAGESTATE_H
#define IMAGESTATE_H

#include <QString>
#include <Types.h>

class ImageLoad;

class State
{
    friend class ImageLoad;

    private:
        State ( int size, bool toLoad, bool loaded, QString message ) :
                size( size ), toLoad( toLoad ), loaded( loaded ), message( message ) {}

    public:        
        int size;
        mutable bool toLoad;
        mutable bool loaded;        
        QString message;
};

class ImageLoad
{
public:

    ImageLoad();

    void resetLoaded();

    SquareSize squareSize;
    State four;
    State five;
    State six;
    State seven;
};


#endif // IMAGESTATE_H
