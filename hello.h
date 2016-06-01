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
        //KIO::UDSEntry createUDSEntryForTag();
    protected:
        bool rewriteUrl(const QUrl& url, QUrl& newUrl) Q_DECL_OVERRIDE;
};

#endif
