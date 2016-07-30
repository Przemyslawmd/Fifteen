#ifndef IMAGESTATE_H
#define IMAGESTATE_H

#include <QString>

class State
{
    public:
        State ( int resolution, int size, bool toLoad, bool loaded, QString message ) :
                resolution( resolution ), size( size ), toLoad( toLoad ), loaded( loaded ), message( message ) {}

        int resolution;
        int size;
        QString message;
        mutable bool loaded;
        mutable bool toLoad;
};

class ImageLoad
{
public:

    ImageLoad();

    void resetLoaded();
    State four;
    State five;
    State six;
    State seven;
};


#endif // IMAGESTATE_H
