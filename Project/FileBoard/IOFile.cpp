
#include "IOFile.h"

IOFile::IOFile( const QString& fileName, QIODevice::OpenModeFlag mode ) : file( fileName )
{
    file.open( mode );
    stream = new QDataStream( &file );
    stream->setVersion( QDataStream::Qt_5_0 );
}

/*********************************************************************************/
/*********************************************************************************/

IOFile::~IOFile()
{
    delete stream;
    file.close();
}

/*********************************************************************************/
/*********************************************************************************/

QDataStream& IOFile::getDataStream()
{
    return *stream;
}

