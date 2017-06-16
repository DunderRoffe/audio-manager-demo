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
    id: slider;

    smooth: true;
    // value is read/write.
    property real value
    onValueChanged: { handle.x = 2 + (value - minimum) * slider.xMax / (maximum - minimum); }
    property real maximum: 1
    property real minimum: 1
    property int xMax: slider.width - handle.width - 4

    Rectangle {
      smooth: true;
      anchors.fill: parent
        border.color: "black"; border.width: 0; radius: 16
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#66000000" }
            GradientStop { position: 1.0; color: "#66555555" }
        }
        Text {
          id: channel
          objectName: "channel"
          anchors.verticalCenter: parent.verticalCenter;
          anchors.horizontalCenter: parent.horizontalCenter;
          font.bold: true
          font.pointSize: 16
          color: "#AAAAAA"
          text: "Background Channel"
        }
    }

    Rectangle {
        id: handle; smooth: true
        x: slider.width / 2 - handle.width / 2; y: 2; width: 80; height: slider.height-4;
        radius: 16
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#DDDDDD" }
            GradientStop { position: 0.4; color: "#AAAAAA" }
            GradientStop { position: 1.0; color: "#555555" }
        }

        MouseArea {
            anchors.fill: parent; drag.target: parent
            drag.axis: Drag.XAxis; drag.minimumX: 2; drag.maximumX: slider.xMax+2
            onPositionChanged: {
              value = (maximum - minimum) * (handle.x-2) / slider.xMax + minimum;
              for (var i = 0; i < 5; i++)
              {
                if (value > (i)*20)
                {
                  volumeButton.children[i].color = "#9900AA00";
                  volumeButton.children[i].border.color = "#99005500";
                } else {
                  volumeButton.children[i].color = "#99333333";
                  volumeButton.children[i].border.color = "#99000000";
                }
              }

             QMLButtonEventsReceiver.slider("Volume", value);
            }
        }

        Row {
          id: volumeButton
          spacing: 2
          anchors.verticalCenter:   parent.verticalCenter
          anchors.horizontalCenter: parent.horizontalCenter
          Repeater {
              model: 5
              Rectangle {
                  width: 3;
                  height: 3 * (index + 1)
                  y: (16 - 3 * (index + 1))
                  color: "#9900AA00"
                  border.width: 1
                  border.color: "#99005500"
              }
          }
        }
    }
}
