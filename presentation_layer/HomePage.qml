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

import QtQuick 2.2

Row {
    spacing: 50
    anchors.fill: parent

    Image {
        id: logoGENIVI
        x: 0
        y: 100
        source: "qrc:/resources/pics/genivi_logo.png"
    }

    Column {
        x: 0
        y: 100
        spacing: 80

        Clock {
            id: myClock
            z: 10
            x: 100
            y: 100
        }

        Image {
            id: logoWR
            anchors.horizontalCenter: myClock.horizontalCenter
            anchors.topMargin: myClock.bottom
            source: "qrc:/resources/pics/WindRiver_red_lrg.png"
        }
    }
}
