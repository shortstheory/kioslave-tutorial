#Writing a KIO slave 101
##Project Structure
Your source directory needs to have the following files:

+ KIO slave.h
+ KIO slave.cpp
+ KIO slave.json
+ CMakeLists.txt

The .json file replaces the old .protocol files. The .json file for the KIO slave specifies the properties the KIO slave will have such as the executable path to the KIO slave on installation. The .json file also includes properties of the slave such as being able to read from, write to, delete from, among many others. Fields in this .json file are specified from the KProtocolManager class. For creating a KIO slave capable of showing a directory in a file manager such as Dolphin, the `listing` property must be set to `true`. An example of a skeletal .json file used for a KIO slave would look something like this:

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

The KIO Slave's .cpp file will also require a new KIOPluginForMetaData class to add the .json file. The following is used for the hello KIO slave and can be used as an example:

```
class KIOPluginForMetaData : public QObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.kio.slave.hello" FILE "hello.json")
};
```
##Forwarding Slave Base
