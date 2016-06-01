#include "hello.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>
#include <QDir>
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

QStringList hello::serveEntries(const QString &path)
{
    QDir dir(path);
    return dir.entryList(QDir::Dirs | QDir::Files | QDir::Hidden);
}

void hello::listDir(const QUrl &url)
{
    QUrl mrl = QUrl("file:///home/nic/gsoc-2016");
    QString fileId;
    QString relativePath;

    //listing
    const QStringList entryNames = serveEntries(mrl.path());
    KIO::UDSEntry entry;
    for(auto entryIterator = entryNames.begin(), entryEnd = entryNames.end(); entryIterator != entryEnd; ++entryIterator)
    {
        const QString fileName = *entryIterator;
        if(fileName == QLatin1String("..")) {
            continue;
        }
        const QString filePath = mrl.path() + QLatin1Char('/') + fileName;
        entry.clear();
        if(createUDSEntry(mrl.path(), fileName, fileName, entry));
        {
            listEntry(entry);
        }
    }
    entry.clear();
    finished();
}

bool hello::createUDSEntry(const QString &physicalPath, const QString &displayFileName, const QString &internalFileName, KIO::UDSEntry &entry)
{
    entry.insert(KIO::UDSEntry::UDS_LOCAL_PATH, physicalPath);
    //entry.insert(KIO::UDSEntry::UDS_GUESSED_MIME_TYPE);
    entry.insert(KIO::UDSEntry::UDS_DISPLAY_NAME, displayFileName);
    entry.insert(KIO::UDSEntry::UDS_NAME, internalFileName);

    return true;
}

hello::hello( const QByteArray &pool, const QByteArray &app )
: KIO::ForwardingSlaveBase( "hello", pool, app ) {}

#include "hello.moc"
/*    const QString tag("hello-world");
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
    listEntry(tmp);*/
