/**
 * SPDX license identifier: MPL-2.0
 *
 * Copyright (C) 2011-2014, Wind River Systems
 * Copyright (C) 2014,2015, GENIVI Alliance
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
 *
 * 28.11.2014, Adrian Scarlat, Added code to allow only one instance of
 *                             AM PoC to run; This was achieved by creating
 *                             a file in /var/run and placing an advisory
 *                             lock on it, using flock(). When another
 *                             instance is created, it can't create the advisory
 *                             lock on the same file since the first instance
 *                             owns it and it will quit with an appropriate
 *                             message.
 * 04.02.2015, Holger Behrens, add support for Wayland ivi-shell
 */

#include <QApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QDebug>
#include <QGraphicsObject>
#include <QTimer>
#include <QQmlEngine>
#include <QQuickItem>

#include <sys/file.h>
#include <errno.h>

#include "business_logic/include/qmlbuttoneventsreceiver.h"
#include "business_logic/include/volumechart.h"
#include "business_logic/include/audioManagerInterface.h"

#define AM_POC_SURFACE_ID 20

int main(int argc, char *argv[])
{
    setenv("QT_QPA_PLATFORM", "wayland", 1); // force to use wayland plugin
    setenv("QT_WAYLAND_DISABLE_WINDOWDECORATION", "1", 1);

    QApplication app(argc, argv);
    int pid_file = open("/var/run/AudioManager_PoC.pid", O_CREAT | O_RDWR, 0666);
    if(pid_file != -1)
    {
        int rc = flock(pid_file, LOCK_EX | LOCK_NB);
        if(rc)
        {
            if(EWOULDBLOCK == errno)
            {
                qDebug() << "Only one instance of AudioManager_PoC is allowed. Quitting!";
                return 0;
            }
        }
        else
        {
            QQuickView view;
            QMLButtonEventsReceiver rec(&view);
            view.setProperty("IVI-Surface-ID", AM_POC_SURFACE_ID);
            view.rootContext()->setContextProperty("QMLButtonEventsReceiver", &rec);
            view.engine()->addImageProvider(QLatin1String("volumes"), new volumechart());
            view.setSource(QUrl("qrc:/presentation_layer/main.qml"));
            view.showMaximized();

            qDebug() << "Show maximized";

            QTimer  *timer = new QTimer(&rec);
            QObject::connect(timer, SIGNAL(timeout()), &rec, SLOT(slotRefreshInfo()));
            timer->start(500);

            QObject *sliderVolume = view.rootObject()->findChild<QObject*>("sliderVolume");
            sliderVolume->setProperty("value", 100.0);

            return app.exec();
        }
    }
    else
    {
        qDebug() << "Couldn't create /var/run/AudioManager_PoC.pid file.";
        return 0;
    }
}
