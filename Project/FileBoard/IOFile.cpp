
#include "IOFile.h"


IOFile::IOFile( const QString& fileName, QIODevice::OpenModeFlag mode ) : file( fileName )
{
    file.open( mode );
    stream = std::make_unique< QDataStream >( &file );
    stream->setVersion( QDataStream::Qt_5_0 );
}

/*********************************************************************************/
/*********************************************************************************/

IOFile::~IOFile()
{
    file.close();
}

/*********************************************************************************/
/*********************************************************************************/

QDataStream& IOFile::getDataStream()
{
    return *stream;
}

