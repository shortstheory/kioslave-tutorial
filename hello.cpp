#include "hello.h"
#include <QDebug>
class KIOPluginForMetaData : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.kio.slave.hello" FILE "hello.json")
};
extern "C"
{
    int Q_DECL_EXPORT kdemain( int argc, char **argv )
    {
      qDebug() << "Entering function";
      ////KComponentData instance( "kio_hello" );

      if (argc != 4)
      {
        fprintf( stderr, "Usage: kio_hello protocol domain-socket1 domain-socket2\n");
        exit( -1 );
      }
      hello slave( argv[2], argv[3] );
      slave.dispatchLoop();
      return 0;
    }
}

void hello::get( const QUrl &url )
{
  qDebug() << "Entering function";
  mimeType( "text/plain" );
  QByteArray str( "Hello_world" );
  data( str );
  finished();
  qDebug() << "Leaving function";
}

hello::hello( const QByteArray &pool, const QByteArray &app )
: SlaveBase( "hello", pool, app ) {}

#include "hello.moc"
