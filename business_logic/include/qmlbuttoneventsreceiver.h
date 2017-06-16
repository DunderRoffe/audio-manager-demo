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

#ifndef QMLBUTTONEVENTSRECEIVER_H
#define QMLBUTTONEVENTSRECEIVER_H

#include <QObject>
#include <QQuickView>

#include "business_logic/include/audioManagerInterface.h"
#include "business_logic/include/volumechart.h"

#define BACKGROUND_CHANNEL 1
#define FOREGROUND_CHANNEL 2

class QMLButtonEventsReceiver : public QObject
{
Q_OBJECT

public:
    QMLButtonEventsReceiver(QQuickView *view);

    Q_INVOKABLE QString clicked(QString btnText) const;
    Q_INVOKABLE void slider(QString sliderText, qreal value) const;


public slots:
    void slotRefreshInfo();
    void slotMediaEnd();
    void slotCarEnd();
    void slotNavEnd();
    void slotTTSEnd();
    void slotTelEnd();


private:
    QQuickView       *view;
    audioManagerInterface     *amgr;
    int              channel;

    QString playMusic;
    QString stopMusic;
    QString playCarReverse;
    QString stopCarReverse;
    QString playNav;
    QString stopNav;
    QString playTTS;
    QString stopTTS;
    QString playTel;
    QString stopTel;
    QString getConnections;
    QString getVolumes;
};

#endif // QMLBUTTONEVENTSRECEIVER_H
