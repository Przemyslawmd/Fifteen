#ifndef IMAGESTATE_H
#define IMAGESTATE_H

#include <QString>

class ImageLoad;

class State
{
    friend class ImageLoad;

    private:
        State ( int resolution, int size, bool toLoad, bool loaded, QString message ) :
                resolution( resolution ), size( size ), toLoad( toLoad ), loaded( loaded ), message( message ) {}

    public:
        int resolution;
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
    State four;
    State five;
    State six;
    State seven;
};


#endif // IMAGESTATE_H
