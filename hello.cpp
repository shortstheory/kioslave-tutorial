#include "hello.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>
class KIOPluginForMetaData : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.kio.slave.hello" FILE "hello.json")
};
extern "C"
{
    int Q_DECL_EXPORT kdemain( int argc, char **argv )
    {
      qDebug() << "main function";
      ////KComponentData instance( "kio_hello" );
      QCoreApplication app(argc, argv);
      if (argc != 4)
      {
        fprintf( stderr, "Usage: kio_hello protocol domain-socket1 domain-socket2\n");
        exit( -1 );
      }
      hello slave(argv[2], argv[3]);
      slave.dispatchLoop();
      return 0;
    }
}

bool hello::rewriteUrl(const QUrl& url, QUrl& newUrl)
{
    if (url.scheme() != QLatin1String("file"))
        return false;

    newUrl = url;
    return true;
}

/*void hello::get( const QUrl &url )
{
  qDebug() << "Entering function.";
  mimeType( "text/plain" );
  QByteArray str( "Hello pluto! ~kioslave\n" );
  data( str );
  finished();
  qDebug() << "Leaving function";
}*/

void hello::listDir(const QUrl &url)
{
    //KIO::ForwardingSlaveBase::listRecursive(QUrl("file:///home/nic/gsoc-2016"));
    const QString tag("hello-world");
    KIO::UDSEntry uds;
    uds.insert(KIO::UDSEntry::UDS_NAME, tag);
    uds.insert(KIO::UDSEntry::UDS_DISPLAY_NAME, tag);
    uds.insert(KIO::UDSEntry::UDS_FILE_TYPE, S_IFDIR);
    uds.insert(KIO::UDSEntry::UDS_MIME_TYPE, QStringLiteral("inode/directory"));
    uds.insert(KIO::UDSEntry::UDS_DISPLAY_TYPE, QStringLiteral("Tag"));
    uds.insert(KIO::UDSEntry::UDS_ACCESS, 0700);
    //uds.insert(KIO::UDSEntry::UDS_USER, KUser().loginName());
    uds.insert(KIO::UDSEntry::UDS_ICON_NAME, QStringLiteral("tag"));

    KIO::UDSEntry tmp = uds;
    listEntry(tmp);
}

hello::hello( const QByteArray &pool, const QByteArray &app )
: KIO::ForwardingSlaveBase( "hello", pool, app ) {}

#include "hello.moc"
