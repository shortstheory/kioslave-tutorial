#include "hello.h"
#include <QDebug>
#include <QCoreApplication>
#include <KCmdLineArgs>
#include <KConfigGroup>
#include <KDesktopFile>
#include <KDirNotify>
#include <KGlobalSettings>
#include <KStandardDirs>
#include <KGlobal>
#include <KUrl>

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
    QCoreApplication app(argc, argv);
    //KComponentData("kio_hello", "kdelibs4");
    KLocale::global();
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
