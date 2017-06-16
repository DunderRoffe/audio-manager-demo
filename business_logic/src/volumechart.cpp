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

#include <qqmlextensionplugin.h>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickImageProvider>
#include <QQuickView>
#include <QImage>
#include <QPainter>
#include <QDebug>

#include "business_logic/include/volumechart.h"

QList<QList<int> > volumechart::volumes;


volumechart::volumechart()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
  QList<int> l1;
  volumechart::volumes.push_back(l1);
  QList<int> l2;
  volumechart::volumes.push_back(l2);
  QList<int> l3;
  volumechart::volumes.push_back(l3);
  QList<int> l4;
  volumechart::volumes.push_back(l4);
  QList<int> l5;
  volumechart::volumes.push_back(l5);
}

QPixmap volumechart::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 400;
    int height = 100;

    if (size)
        *size = QSize(width, height);
    QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height);
    pixmap.fill(QColor(0, 0, 0));

    QPainter painter(&pixmap);
    QColor colors[10];
    colors[0] = Qt::red;
    colors[1] = Qt::green;
    colors[2] = Qt::blue;
    colors[3] = Qt::yellow;
    colors[4] = Qt::cyan;
    colors[5] = Qt::magenta;
    colors[6] = Qt::darkCyan;
    painter.setRenderHints(QPainter::Antialiasing);
    for (int src = 0; src < volumes.size(); src++)
    {
      painter.setPen(colors[src]);
      int limitMin = 1;
      if (volumes[src].size() > 40)
      {
        limitMin = volumes[src].size() - 40;
      }
      for (int i = limitMin; i < volumes[src].size(); i++)
      {
        painter.drawLine((i - 1 - (limitMin -1)) * 10, src * 2 + 75 - volumes[src][i - 1] / 2,
                         (i - (limitMin -1)) * 10, src * 2 + 75 - volumes[src][i]/2);
      }
    }
    return pixmap;
}
