#ifndef HELLO_H
#define HELLO_H

#include <kio/forwardingslavebase.h>

/**
  This class implements a hello-world kioslave
 */
class hello : public KIO::ForwardingSlaveBase
{
    Q_OBJECT
    public:
        hello( const QByteArray &pool, const QByteArray &app );
        //void get( const QUrl &url );
        void listDir(const QUrl& url) Q_DECL_OVERRIDE; //for listing
        QStringList serveEntries(const QString &path);
        bool createUDSEntry(const QString &physicalPath, const QString &displayFileName, const QString &internalFileName, KIO::UDSEntry &entry);
        ~hello(){qDebug() << "Quitting slave."}
        //KIO::UDSEntry createUDSEntryForTag();
    protected:
        bool rewriteUrl(const QUrl& url, QUrl& newUrl) Q_DECL_OVERRIDE;
};

#endif
