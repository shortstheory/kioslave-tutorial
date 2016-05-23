#ifndef HELLO_H
#define HELLO_H

#include <kio/slavebase.h>

/**
  This class implements a hello-world kioslave
 */
class hello : public KIO::SlaveBase
{
  public:
    hello( const QByteArray &pool, const QByteArray &app );
    void get( const QUrl &url );
};

#endif
