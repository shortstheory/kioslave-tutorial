# Writing a KIO slave 101

## Project Structure

For the purpose of this tutorial, your project source directory needs to have the following files:

+ kio_hello.h
+ kio_hello.cpp
+ hello.json
+ CMakeLists.txt

### hello.json

The .json file replaces the .protocol files used in KIO slaves pre KF5. The .json file for the KIO slave specifies the properties the KIO slave will have such as the executable path to the KIO slave on installation. The .json file also includes properties of the slave such as being able to read from, write to, delete from, among many others. Fields in this .json file are specified from the KProtocolManager class. For creating a KIO slave capable of showing a directory in a file manager such as Dolphin, the `listing` property must be set to `true`. As an example, the KIO slave used for the Hello KIO slave described in this tutorial looks like this:

```
{
    "KDE-KIO-Protocols" : {
        "hello": {
            "Class": ":local",
            "X-DocPath": "kioslave5/kio_hello.html",
            "exec": "kf5/kio/hello",
            "input": "none",
            "output": "filesystem",
            "protocol": "hello",
            "reading": true
        }
    }
}
```

As for the CMakeLists.txt, you will need to link your KIO slave module with KF5::KIOCore. This can be seen in the project directory.

### kio_hello.h

```
#ifndef HELLO_H
#define HELLO_H

#include <kio/slavebase.h>

/**
  This class implements a Hello World kioslave
 */
class Hello : public QObject, public KIO::SlaveBase
{
    Q_OBJECT
public:
    Hello(const QByteArray &pool, const QByteArray &app);
    void get(const QUrl &url) Q_DECL_OVERRIDE;
};

#endif
```

The Hello KIO slave is derived from KIO::SlaveBase. The SlaveBase class has some basic functions already implemented for the KIO slave. This can be found in the [documentation](https://api.kde.org/frameworks/kio/html/classKIO_1_1SlaveBase.html). However, most of the functions of SlaveBase are virtual functions and have to be re-implemented for the KIO slave. In this case, we are re-implementing the `get` function to print a QString when it is called by `kioclient5`.

In case you don't need special handling of the KIO slave's functions, you can derive your KIO slave class directly from [KIO::ForwardingSlaveBase](http://api.kde.org/frameworks-api/frameworks5-apidocs/frameworks/kio/html/classKIO_1_1ForwardingSlaveBase.html). Here, you would only need to re-implement the `rewriteUrl` function to get your KIO slave working.

### kio_hello.cpp

```
#include "hello.h"
#include <QDebug>

class KIOPluginForMetaData : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.kio.slave.hello" FILE "hello.json")
};

extern "C"
{
    int Q_DECL_EXPORT kdemain(int argc, char **argv)
    {
        qDebug() << "Launching KIO slave.";
        if (argc != 4) {
            fprintf(stderr, "Usage: kio_hello protocol domain-socket1 domain-socket2\n");
            exit(-1);
        }
        Hello slave(argv[2], argv[3]);
        slave.dispatchLoop();
        return 0;
    }
}

void Hello::get(const QUrl &url)
{
    qDebug() << "Entering function.";
    mimeType("text/plain");
    QByteArray str("Hello world!\n");
    data(str);
    finished();
    qDebug() << "Leaving function";
}

Hello::Hello(const QByteArray &pool, const QByteArray &app)
    : SlaveBase("hello", pool, app) {}

#include "hello.moc"
```

The .moc file is, of course, auto-generated at compilation time.

As mentioned earlier, the KIO Slave's .cpp file will also require a new KIOPluginForMetaData class to add the .json file. The following is used for the hello KIO slave and can be used as an example:

```
class KIOPluginForMetaData : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.kio.slave.hello" FILE "hello.json")
};
```

### CMakeLists.txt

```
cmake_minimum_required(VERSION 3.5)
set(QT_MIN_VERSION "5.4.0")
set(KF5_MIN_VERSION "5.16.0")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(
    CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${ECM_MODULE_PATH}
        ${ECM_KDE_MODULE_DIR}
)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)
include(FeatureSummary)
add_library(kio_hello MODULE hello.cpp)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED KIO)
target_link_libraries(kio_hello KF5::KIOCore)
set_target_properties(kio_hello PROPERTIES OUTPUT_NAME "hello")

install(TARGETS kio_hello DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf5/kio )
```

## Installation

After cloning master to your favorite directory, simply run the following commands in the source folder:

```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DKDE_INSTALL_USE_QT_SYS_PATHS=TRUE ..
make
sudo make install
kdeinit5
```

As shown above, we have to run kdeinit5 again so the new KIO slave is discovered by KLauncher and can be loaded when we run a command through an application such as kioclient5.

## Testing

Run:

`kioclient5 'cat' 'hello:/'`

And the output should be:

`Hello_world`
