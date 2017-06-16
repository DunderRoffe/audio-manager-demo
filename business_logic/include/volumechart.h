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

#ifndef VOLUMECHART_H
#define VOLUMECHART_H

#include <QQuickImageProvider>
#include <QQuickView>
#include <QPixmap>
#include <QString>
#include <QSize>

class volumechart : public QQuickImageProvider
{
public:
    static QList<QList<int> > volumes;

    volumechart();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
};


#endif // VOLUMECHART_H
