/***************************************************************************
 *   Copyright (C) 2016 by Arnav Dhamija <arnav.dhamija@gmail.com>         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

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
