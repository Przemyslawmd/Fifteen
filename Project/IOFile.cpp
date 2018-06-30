
#include "IOFile.h"

IOFile::IOFile( QString& fileName, QIODevice::OpenModeFlag mode ) : file( fileName )
{
    file.open( mode );
    stream = new QDataStream( &file );
    stream->setVersion( QDataStream::Qt_4_6 );
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

