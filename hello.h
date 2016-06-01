#ifndef HELLO_H
#define HELLO_H

#include <kio/slavebase.h>

/**
  This class implements a Hello World kioslave
 */
class hello : public KIO::SlaveBase
{
    Q_PLUGIN_METADATA(IID "org.kde.kio.slave.hello" FILE "hello.json");
    public:
        hello(const QByteArray &pool, const QByteArray &app);
        void get(const QUrl &url) Q_DECL_OVERRIDE;
};

#endif
