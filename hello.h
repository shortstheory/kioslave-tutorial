#ifndef HELLO_H
#define HELLO_H

#include <kio/forwardingslavebase.h>

/**
  This class implements a hello-world kioslave
 */
class hello : public KIO::SlaveBase
{
    Q_OBJECT
    public:
        hello( const QByteArray &pool, const QByteArray &app );
        void get( const QUrl &url );
};

#endif
