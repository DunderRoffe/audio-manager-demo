/****************************************************************************
**
** Copyright (C) 2011-2014, Wind River Systems
** Copyright (C) 2014, GENIVI Alliance
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.2

Item {
    id: clock
    width: 180; height: 180

    property int hours
    property int minutes
    property int seconds
    property real shift
    property bool night: false

    function timeChanged() {
        var date = new Date;
        hours = shift ? date.getUTCHours() + Math.floor(clock.shift) : date.getHours()
        night = ( hours < 7 || hours > 19 )
        minutes = shift ? date.getUTCMinutes() + ((clock.shift % 1) * 60) : date.getMinutes()
        seconds = date.getUTCSeconds();
    }

    Timer {
        interval: 1000; running: true; repeat: true;
        onTriggered: clock.timeChanged()
    }

    Image {x: clock.x; y: clock.y; smooth: true;id: background; source: "qrc:/resources/pics/clock.png"; z: clock.z+1; opacity: 0.9;}
    Image {x: clock.x; y: clock.y; smooth: true;id: glass; source: "qrc:/resources/pics/clock_glass.png"; z: clock.z+10}

    Rectangle {
      color: "#888888";
      height: clock.height/2 - 25
      width: 6
      z: clock.z + 2
      x: clock.x + clock.width/2 - 3
      y: clock.y + 35
      smooth: true
      transform: Rotation {
          id: hourRotation
          origin.x: 3; origin.y: clock.height/2 - 35;
          angle: (clock.hours * 30) + (clock.minutes * 0.5)
      }
    }
    Rectangle {
      color: "#333333";
      height: clock.height/2 - 20
      width: 4
      z: clock.z + 3
      x: clock.x + clock.width/2 - 2
      y: clock.y + 30
        smooth: true
        transform: Rotation {
            id: minuteRotation
            origin.x: 2; origin.y: clock.height/2 - 30;
            angle: clock.minutes * 6
        }
    }

    Rectangle {
      height: clock.height/2 - 15
      width: 2
      z: clock.z + 4
      x: clock.x + clock.width/2 - 1
      y: clock.y + 25
      color: "#555555";
        smooth: true
        transform: Rotation {
            id: secondRotation
            origin.x: 1; origin.y: clock.height/2 - 25;
            angle: clock.seconds * 6
        }
    }
    Column {
      x: clock.x - clock.width/2
      y: clock.y + clock.height/2

      Text {
        color: "#FF5555"
        font.pointSize: 12
        font.bold: true
        text: Qt.formatDateTime(new Date(), "ddd,MMM")
      }
      Text {
        color: "#FF3333"
        font.pointSize: 48
        font.bold: true
        text: Qt.formatDateTime(new Date(), "dd")
      }
    }
}
