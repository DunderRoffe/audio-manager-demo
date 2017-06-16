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

#include <QDebug>
#include <QProcess>
#include <QApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickItem>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QGraphicsObject>
#include <QFileDialog>
#include <QStringListModel>
#include <QThread>

#include "business_logic/include/qmlbuttoneventsreceiver.h"
#include "business_logic/include/volumechart.h"

/**
 * The value for volume is in percentage and is relative to the PulseAudio
 * volume. Consult PulseAudio documentaion for a description about how
 * volume is measured inside PulseAudio.
 */
static int masterVolumeFG = 100;
static int masterVolumeBG = 100;
static audioManagerInterface *static_amgr;

QMLButtonEventsReceiver::QMLButtonEventsReceiver(QQuickView *view)
{
    playMusic = "/opt/audiomanager-poc/scripts/playmusic.sh";
    stopMusic = "/opt/audiomanager-poc/scripts/stopmusic.sh";
    playCarReverse = "/opt/audiomanager-poc/scripts/playCarReverse.sh";
    stopCarReverse = "/opt/audiomanager-poc/scripts/stopCarReverse.sh";
    playNav = "/opt/audiomanager-poc/scripts/playnav.sh";
    stopNav = "/opt/audiomanager-poc/scripts/stopnav.sh";
    playTTS = "/opt/audiomanager-poc/scripts/playtts.sh";
    stopTTS = "/opt/audiomanager-poc/scripts/stoptts.sh";
    playTel = "/opt/audiomanager-poc/scripts/playtel.sh";
    stopTel = "/opt/audiomanager-poc/scripts/stoptel.sh";
    getConnections = "/opt/audiomanager-poc/scripts/getconnections.sh";
    getVolumes = "/opt/audiomanager-poc/scripts/getvolumes_val.sh";

    this->amgr = new audioManagerInterface(view);
    static_amgr = amgr;
    this->view = view;
    channel = BACKGROUND_CHANNEL;
}

QString QMLButtonEventsReceiver::clicked(QString btnText) const
{
  qDebug() << "Clicked:" << btnText;

  if (btnText == "Play Music") {
    amgr->Connect("MediaPlayer", "AlsaPrimary");
    QProcess *p1 = new QProcess();
    p1->start(playMusic);
    connect(p1, SIGNAL(finished(int)), SLOT(slotMediaEnd()));
    return "Stop Music";
  }

  if (btnText == "Stop Music") {
    amgr->Disconnect("MediaPlayer", "AlsaPrimary");
    QProcess *p1 = new QProcess();
    p1->start(stopMusic);
    return "Play Music";
  }

  if (btnText == "Parking Signal") {
    amgr->Connect("ReverseBeep", "AlsaSecondary");
    QProcess *p1 = new QProcess();
    p1->start(playCarReverse);
    connect(p1, SIGNAL(finished(int)), SLOT(slotCarEnd()));
    return "Stop Parking Signal";
  }

  if (btnText == "Stop Parking Signal") {
    amgr->Disconnect("ReverseBeep", "AlsaSecondary");
    QProcess *p1 = new QProcess();
    p1->start(stopCarReverse);
    return "Parking Signal";
  }

  if (btnText == "Navigation Message") {
    amgr->Connect("NaviPlayer", "AlsaSecondary");
    QProcess *p1 = new QProcess();
    p1->start(playNav);
    connect(p1, SIGNAL(finished(int)), SLOT(slotNavEnd()));
    return "Stop Navigation Message";
  }

  if (btnText == "Stop Navigation Message") {
    amgr->Disconnect("NaviPlayer", "AlsaSecondary");
    QProcess *p1 = new QProcess();
    p1->start(stopNav);
    return "Navigation Message";
  }

  if (btnText == "Text To Speech") {
    amgr->Connect("TTSPlayer", "AlsaSecondary");
    QProcess *p1 = new QProcess();
    p1->start(playTTS);
    connect(p1, SIGNAL(finished(int)), SLOT(slotTTSEnd()));
    return "Stop Text To Speech";
  }

  if (btnText == "Stop Text To Speech") {
    amgr->Disconnect("TTSPlayer", "AlsaSecondary");
    QProcess *p1 = new QProcess();
    p1->start(stopTTS);
    return "Text To Speech";
  }

  if (btnText == "Start Phone Call") {
    amgr->Connect("Skype", "AlsaSecondary");
    QProcess *p1 = new QProcess();
    p1->start(playTel);
    connect(p1, SIGNAL(finished(int)), SLOT(slotTelEnd()));
    return "End Phone Call";
  }

  if (btnText == "End Phone Call") {
    amgr->Disconnect("Skype", "AlsaSecondary");
    QProcess *p1 = new QProcess();
    p1->start(stopTel);
    return "Start Phone Call";
  }

  return btnText;
}


void QMLButtonEventsReceiver::slider(QString sliderText, qreal value) const
{
  if (sliderText == "Volume")
  {
    if (channel == FOREGROUND_CHANNEL)
    {
      masterVolumeFG = (int) value;
      amgr->SetVolume("AlsaSecondary", value);
    }
    else
    {
      masterVolumeBG = (int) value;
      amgr->SetVolume("AlsaPrimary", value);
    }
  }
}

void QMLButtonEventsReceiver::slotRefreshInfo()
{
  QObject *text = view->rootObject()->findChild<QObject*>("textConnections");
  QObject *textSrc = view->rootObject()->findChild<QObject*>("textSources");
  QObject *textVol = view->rootObject()->findChild<QObject*>("textVolumes");

  QProcess *p1 = new QProcess();
  p1->start(getConnections);
  p1->waitForFinished(-1);

  QString p_stdout = p1->readAllStandardOutput();

  text->setProperty("text", QString(p_stdout));
  QStringList linesConnections = QString(p_stdout).split("\n");

  QProcess *p2 = new QProcess();
  p2->start(getVolumes);
  p2->waitForFinished(-1);

  p_stdout = p2->readAllStandardOutput();

  QStringList lines = QString(p_stdout).split("\n");
  QString audiosources = "";
  QString audiovolumes = "";

  int oldChannel = channel;

  channel = BACKGROUND_CHANNEL;
  QObject *channelTXT = view->rootObject()->findChild<QObject*>("channel");

  for (int i = 0; i < lines.size(); i++)
  {
    QStringList x = lines[i].split(",");
    if (x.length() == 2 && x.at(0).length() != 0 && x.at(1).length() != 0 )
    {
      QString src = QString(x.at(0));
      QString vol = "0";
      audiosources += src + "\n";
      int masterVolume = masterVolumeBG;
      for (int j = 0; j < linesConnections.size(); j++)
      {
        if (linesConnections[j].contains(src) && linesConnections[j].contains("Connected"))
        {
          vol = QString(x.at(1));
          if (linesConnections[j].contains("AlsaSecondary"))
          {
            channel = FOREGROUND_CHANNEL;
            masterVolume = masterVolumeFG;
          }
        }
      }
      audiovolumes += vol + "\n";
      volumechart::volumes[i].push_back(masterVolume * vol.toInt() / 100);
    }
  }

  if (oldChannel != channel)
  {
    QObject *sliderVolume = view->rootObject()->findChild<QObject*>("sliderVolume");

    if (channel == BACKGROUND_CHANNEL)
    {
      channelTXT->setProperty("text", "Background Channel");
      sliderVolume->setProperty("value", masterVolumeBG);
    }
    if (channel == FOREGROUND_CHANNEL)
    {
      channelTXT->setProperty("text", "Foreground Channel");
      sliderVolume->setProperty("value", masterVolumeFG);
    }
  }

  textSrc->setProperty("text", audiosources);
  textVol->setProperty("text", audiovolumes);
}

void QMLButtonEventsReceiver::slotMediaEnd()
{
  qDebug() << "slotMediaEnd";
  amgr->Disconnect("MediaPlayer", "AlsaPrimary");
  QProcess *p1 = new QProcess();
  p1->start(stopMusic);

  QObject *connectOptions = view->rootObject()->findChild<QObject*>("music");
  connectOptions->setProperty("text", "Play Music");
}

void QMLButtonEventsReceiver::slotCarEnd()
{
    qDebug() << "slotCarEnd";
    amgr->Disconnect("ReverseBeep", "AlsaSecondary");
    QProcess *p1 = new QProcess();
    p1->start(stopCarReverse);

    QObject *connectOptions = view->rootObject()->findChild<QObject*>("parking");
    connectOptions->setProperty("text", "Parking Signal");
}

void QMLButtonEventsReceiver::slotNavEnd()
{
  qDebug() << "slotNavEnd";
  amgr->Disconnect("NaviPlayer", "AlsaSecondary");
  QProcess *p1 = new QProcess();
  p1->start(stopNav);

  QObject *connectOptions = view->rootObject()->findChild<QObject*>("nav");
  connectOptions->setProperty("text", "Navigation Message");
}


void QMLButtonEventsReceiver::slotTTSEnd()
{
    qDebug() << "slotTTSEnd";
    amgr->Disconnect("TTSPlayer", "AlsaSecondary");
    QProcess *p1 = new QProcess();
    p1->start(stopTTS);

    QObject *connectOptions = view->rootObject()->findChild<QObject*>("tts");
    connectOptions->setProperty("text", "Text To Speech");
}

void QMLButtonEventsReceiver::slotTelEnd()
{
  qDebug() << "slotTelEnd";
  amgr->Disconnect("Skype", "AlsaSecondary");
  QProcess *p1 = new QProcess();
  p1->start(stopTel);

  QObject *connectOptions = view->rootObject()->findChild<QObject*>("phone");
  connectOptions->setProperty("text", "Start Phone Call");
}
