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

#include <QtDBus>
#include <QDBusVariant>
#include <QVariant>

#include "business_logic/include/audioManagerInterface.h"



audioManagerInterface::audioManagerInterface(QObject *parent) :
    QDBusAbstractInterface(
      QString("org.genivi.audiomanager"),
      QString("/org/genivi/audiomanager/commandinterface"),
      "org.genivi.audiomanager.commandinterface",
      QDBusConnection::sessionBus(),
      parent)
{
    qDBusRegisterMetaType<MainConnection>();
    qDBusRegisterMetaType<Availability>();
    qDBusRegisterMetaType<Sink>();
    qDBusRegisterMetaType<Source>();

    qDBusRegisterMetaType<QList<MainConnection> >();
    qDBusRegisterMetaType<QList<Availability> >();
    qDBusRegisterMetaType<QList<Sink> >();
    qDBusRegisterMetaType<QList<Source> >();

    GetListMainSources();
    GetListMainSinks();
    GetListMainConnections();

}

void audioManagerInterface::Connect(const QString sourceName, const QString sinkName)
{
  qDebug() <<"Connect got called: " << sourceName << " " << sinkName;
  QDBusMessage result = this->call(
        "Connect",
        QVariant::fromValue((ushort) sourceName2SourceID[sourceName]),
        QVariant::fromValue((ushort) sinkName2SinkID[sinkName]));
  QVariant resultCode = result.arguments().at(0);
  QVariant mainConnectionID = result.arguments().at(1);
  qDebug() <<"Connection ID: " << mainConnectionID.toInt();

  if (mainConnectionID.toUInt() != 0) // connection doesn't exist
  {
    mainConnectionID2SourceName[mainConnectionID.toUInt()] = sourceName;
    sourceName2mainConnectionID[sourceName] = mainConnectionID.toUInt();
  }
}

void audioManagerInterface::Disconnect(const QString sourceName, const QString sinkName)
{
  qDebug() <<"Disconnect got called: " << sourceName << " " << sinkName;
  qDebug() <<"Disconnect got called Cond ID: " <<  sourceName2mainConnectionID[sourceName];
  QDBusMessage result = this->call(
        "Disconnect",
        QVariant::fromValue((ushort) sourceName2mainConnectionID[sourceName]));
  QVariant resultCode = result.arguments().at(0);
}

QList<Source> audioManagerInterface::GetListMainSources()
{
  QDBusMessage result = this->call("GetListMainSources");
  if (result.errorMessage() != "")
  {
    return QList<Source>();
  }
  QList<Source> sources = qdbus_cast<QList<Source> >(result.arguments().at(1));
  for (int i = 0; i < sources.size(); i++)
  {

    sourceName2SourceID[sources[i].name] = sources[i].sourceID;
  }
  return sources;
}

QList<Sink> audioManagerInterface::GetListMainSinks()
{
  QDBusMessage result = this->call("GetListMainSinks");
  if (result.errorMessage() != "")
  {
    return QList<Sink>();
  }
  QList<Sink> sinks = qdbus_cast<QList<Sink> >(result.arguments().at(1));
  for (int i = 0; i < sinks.size(); i++)
  {

    sinkName2SinkID[sinks[i].name] = sinks[i].sinkID;
  }
  return sinks;
}

QList<MainConnection> audioManagerInterface::GetListMainConnections()
{
    QDBusMessage result = this->call("GetListMainConnections");

    if (result.errorMessage() != "")
    {
      return QList<MainConnection>();
    }

    QList<MainConnection> connections = qdbus_cast<QList<MainConnection> >(result.arguments().at(1));
    for (int i = 0; i < connections.size(); i++)
    {
      mainConnectionID2SourceName[connections[i].mainConnectionID] = connections[i].mainConnectionID;
    }

    return connections;
}

void audioManagerInterface::SetVolume(const QString sinkName, short volume)
{
  QDBusMessage result = this->call(
        "SetVolume",
        QVariant::fromValue((ushort) sinkName2SinkID[sinkName]),
        QVariant::fromValue(volume));
  QVariant resultCode = result.arguments().at(0);
}

QDBusArgument &operator<<(QDBusArgument &argument, const MainConnection &theStruct)
{
    argument.beginStructure();
    argument << theStruct.mainConnectionID
             << theStruct.sourceID
             << theStruct.sinkID
             << theStruct.delay
             << theStruct.connectionState;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, MainConnection &theStruct)
{
    argument.beginStructure();
    argument >> theStruct.mainConnectionID
             >> theStruct.sourceID
             >> theStruct.sinkID
             >> theStruct.delay
             >> theStruct.connectionState;
    argument.endStructure();
    return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument, const Availability &theStruct)
{
    argument.beginStructure();
    argument << theStruct.available
             << theStruct.reason;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Availability &theStruct)
{
    argument.beginStructure();
    argument >> theStruct.available
             >> theStruct.reason;
    argument.endStructure();
    return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument, const Sink &theStruct)
{
    argument.beginStructure();
    argument << theStruct.sinkID
             << theStruct.name
             << theStruct.availability
             << theStruct.volume
             << theStruct.muteState
             << theStruct.sinkClassID;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Sink &theStruct)
{
    argument.beginStructure();
    argument >> theStruct.sinkID
             >> theStruct.name
             >> theStruct.availability
             >> theStruct.volume
             >> theStruct.muteState
             >> theStruct.sinkClassID;
    argument.endStructure();
    return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument, const Source &theStruct)
{
    argument.beginStructure();
    argument << theStruct.sourceID
             << theStruct.name
             << theStruct.availability
             << theStruct.sourceClassID
             << theStruct.volume;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Source &theStruct)
{
    argument.beginStructure();
    argument >> theStruct.sourceID
             >> theStruct.name
             >> theStruct.availability
             >> theStruct.sourceClassID
             >> theStruct.volume;
    argument.endStructure();
    return argument;
}
