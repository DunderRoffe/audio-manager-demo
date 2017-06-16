/**
 * SPDX license identifier: MPL-2.0
 *
 * Copyright (C) 2011-2014, Wind River Systems
 * Copyright (C) 2014, GENIVI Alliance
 *
 * This file is part of GENIVI AudioManager PoC.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License (MPL), v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For further information see http://www.genivi.org/.
 *
 * List of changes:
 *
 * 21.09.2014, Adrian Scarlat, First version of the code;
 *                             Added Copyright and License information;
 */

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <stdint.h>

#include <QDBusArgument>
#include <QDBusAbstractInterface>
#include <QDBusVariant>

typedef struct
{
  ushort  mainConnectionID;
  ushort  sourceID;
  ushort  sinkID;
  short   delay;
  short   connectionState;
} MainConnection;


typedef struct
{
  short  available;
  short  reason;
} Availability;


typedef struct
{
  ushort      sinkID;
  QString       name;
  Availability  availability;
  short       volume;
  short       muteState;
  ushort      sinkClassID;
} Sink;


typedef struct
{
  ushort      sourceID;
  QString       name;
  Availability  availability;
  ushort      sourceClassID;
  short       volume;
} Source;


Q_DECLARE_METATYPE(ushort);
Q_DECLARE_METATYPE(MainConnection);
Q_DECLARE_METATYPE(Availability);
Q_DECLARE_METATYPE(Sink);
Q_DECLARE_METATYPE(Source);

Q_DECLARE_METATYPE(QList<MainConnection>);
Q_DECLARE_METATYPE(QList<Availability>);
Q_DECLARE_METATYPE(QList<Sink>);
Q_DECLARE_METATYPE(QList<Source>);

QDBusArgument &operator<<(QDBusArgument &argument, const MainConnection &theStruct);

const QDBusArgument &operator>>(const QDBusArgument &argument, MainConnection &theStruct);

QDBusArgument &operator<<(QDBusArgument &argument, const Availability &theStruct);

const QDBusArgument &operator>>(const QDBusArgument &argument, Availability &theStruct);

QDBusArgument &operator<<(QDBusArgument &argument, const Sink &theStruct);

const QDBusArgument &operator>>(const QDBusArgument &argument, Sink &theStruct);

QDBusArgument &operator<<(QDBusArgument &argument, const Source &theStruct);

const QDBusArgument &operator>>(const QDBusArgument &argument, Source &theStruct);

class Q_DBUS_EXPORT audioManagerInterface : public QDBusAbstractInterface
{
public:
    audioManagerInterface(QObject *parent);
    void Connect(const QString sourceName, const QString sinkName);
    void Disconnect(const QString sourceName, const QString sinkName);
    void SetVolume(const QString sinkName, short volume);

    QList<Source>         GetListMainSources();
    QList<Sink>           GetListMainSinks();
    QList<MainConnection> GetListMainConnections();

private:
    QMap<QString, ushort> sinkName2SinkID;
    QMap<QString, ushort> sourceName2SourceID;
    QMap<uint, QString>   mainConnectionID2SourceName;
    QMap<QString, uint>   sourceName2mainConnectionID;
};

#endif // AUDIOMANAGER_H
